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
      pulse_starts.push_back(sumCH.SampleToTime(samp));
    }
    else if (in_pulse && sumWF.waveform[samp] < threshold) {
      in_pulse = false;
      pulse_ends.push_back(sumCH.SampleToTime(samp));
    }
    else if (in_pulse && samp == nsamps-1)
      pulse_ends.push_back(sumCH.SampleToTime(samp));
  }

  // check that number of pulse starts and pulse ends are the same
  if (pulse_starts.size() != pulse_ends.size())
    cout <<"ERROR: PulseFinder: something went wrong in discriminator search!"<<endl;

  for (size_t i=0; i<pulse_starts.size(); ++i) {
    arisana::Pulse pulse;
    pulse.pulse_id = i;
    pulse.start_time = pulse_starts[i];
    pulse.end_time = pulse_ends[i];
    pulses.push_back(std::move(pulse));
  }
}






//--------------------------------------------------------------------------
// Evaluate parameters for single Pulse, assuming pulse start and end times
// have been found.
void arisana::PulseFinderHelper::evalParams(vector<arisana::Channel> const& chans,
                                            //vector<arisana::ChannelWF> const& bsWFs,
                                            vector<arisana::ChannelWF> const& integralWFs,
                                            arisana::Pulse & pulse)
{
  const double start_time = pulse.start_time;
  const double end_time = pulse.end_time;
  const int start_samp = chans[0].TimeToSample(start_time);
  const int end_samp = chans[0].TimeToSample(end_time);

  double npe = 0;
  for (size_t ch=0; ch<chans.size(); ++ch) {
    arisana::Channel const& chan  = chans[ch];
    //arisana::ChannelWF const& bsWF = bsWFs[ch];
    arisana::ChannelWF const& intWF = integralWFs[ch];

    const double ch_npe = (intWF.waveform[end_samp] - intWF.waveform[start_samp]) / -chan.pmt.spe_mean;
    pulse.ch_npe.push_back(ch_npe);
    npe += ch_npe;
  }
  pulse.npe = npe;
}
