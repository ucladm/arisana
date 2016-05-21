#include "arisana/Modules/PulseFinderHelper.hh"

#include <iostream>

using namespace std;


//--------------------------------------------------------------------------
arisana::PulseFinderHelper::PulseFinderHelper(fhicl::ParameterSet const& p)
  : mode(p.get<std::string>("mode"))
  , discParams(p.get<fhicl::ParameterSet>("discriminatorParams"))
{}


//--------------------------------------------------------------------------
void arisana::PulseFinderHelper::findPulses(arisana::Channel const& sumCH,
                                            arisana::ChannelWF const& sumWF,
                                            vector<arisana::Pulse> & pulses)
{
  if (mode=="DISCRIMINATOR") { DiscriminatorPulseFinder(sumCH, sumWF, pulses); }
  else { return; } 
}

//--------------------------------------------------------------------------
// Simple threshold search
void arisana::PulseFinderHelper::DiscriminatorPulseFinder(arisana::Channel const& sumCH,
                                                          arisana::ChannelWF const& sumWF,
                                                          vector<arisana::Pulse> & pulses)
{
  
  const double threshold = discParams.threshold;

  const int nsamps = sumCH.nsamps;

  vector<double> pulse_starts;
  vector<double> pulse_ends;
  bool in_pulse = false;
  for (int samp = 0; samp<nsamps; ++samp) {
    if (!in_pulse && sumWF.waveform[samp] > threshold) {
      in_pulse = true;
      pulse_starts.push_back(samp);
    }
    else if (in_pulse && sumWF.waveform[samp] < threshold) {
      in_pulse = false;
      pulse_ends.push_back(samp);
    }
    else if (in_pulse && samp == nsamps-1)
      pulse_ends.push_back(samp);
  }

  // check that number of pulse starts and pulse ends are the same
  if (pulse_starts.size() != pulse_ends.size())
    cout <<"ERROR: PulseFinder: something went wrong in discriminator search!"<<endl;

  for (size_t i=0; i<pulse_starts.size(); ++i) {
    arisana::Pulse pulse;
    pulse.pulse_id = i;
    pulse.start_index = pulse_starts[i];
    pulse.end_index = pulse_ends[i];
    pulse.start_time = sumCH.SampleToTime(pulse.start_index);
    pulse.end_time = sumCH.SampleToTime(pulse.end_index);
    pulses.push_back(std::move(pulse));
  }
}






//--------------------------------------------------------------------------
// Evaluate parameters for single Pulse, assuming pulse start and end times
// have been found.
void arisana::PulseFinderHelper::evalParams(vector<arisana::Channel> const& chans,
                                            vector<arisana::ChannelWF> const& bsWFs,
                                            vector<arisana::ChannelWF> const& integralWFs,
                                            arisana::Channel const& sumCH,
                                            arisana::ChannelWF const& sumWF,
                                            arisana::Pulse & pulse)
{
  const double start_time = pulse.start_time;
  const double end_time = pulse.end_time;
  const int start_samp = sumCH.TimeToSample(start_time);
  const int end_samp = sumCH.TimeToSample(end_time);

  
  double peak_samp = start_samp;
  double peak_amp = sumWF.waveform[start_samp];
  for (int samp = start_samp+1; samp<end_samp; ++samp) {
    if (sumWF.waveform[samp] > peak_amp) {
      peak_samp = samp;
      peak_amp = sumWF.waveform[samp];
    }
  }
  pulse.peak_index = peak_samp;
  pulse.peak_time = sumCH.SampleToTime(peak_samp);
  pulse.peak_amplitude = peak_amp;


  double npe = 0;
  for (size_t ch=0; ch<chans.size(); ++ch) {
    arisana::Channel const& chan  = chans[ch];
    arisana::ChannelWF const& bsWF = bsWFs[ch];
    arisana::ChannelWF const& intWF = integralWFs[ch];


    // Find peak time and amplitude
    double ch_peak_samp = start_samp;
    double ch_peak_amp = bsWF.waveform[start_samp];
    for (int samp = start_samp+1; samp<end_samp; ++samp) {
      if (bsWF.waveform[samp] < ch_peak_amp) {
        ch_peak_samp = samp;
        ch_peak_amp = bsWF.waveform[samp];
      }
    }
    pulse.ch_peak_index.push_back(ch_peak_samp);
    pulse.ch_peak_time.push_back(sumCH.SampleToTime(ch_peak_samp));
    pulse.ch_peak_amplitude.push_back(ch_peak_amp);

    
    // Evaluate integrals
    const double ch_npe = (intWF.waveform[end_samp] - intWF.waveform[start_samp]) / -chan.pmt.spe_mean;
    pulse.ch_npe.push_back(ch_npe);
    npe += ch_npe;
  }
  pulse.npe = npe;
}
