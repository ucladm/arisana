#include "arisana/Modules/BaselineHelper.hh"

#include <iostream>
#include <cmath>
#include <vector>

arisana::BaselineHelper::BaselineHelper()
{ }

arisana::BaselineHelper::BaselineHelper(fhicl::ParameterSet const& p)
  : mode(p.get<std::string>("mode"))
  , fixed_params(p.get<fhicl::ParameterSet>("fixedBaselineParams"))
{ }

void arisana::BaselineHelper::evalBaselineSubtractedWF(arisana::Channel const& ch,
                                                       arisana::ChannelWF const& rawWF,
                                                       arisana::ChannelWF & bsWF,
                                                       arisana::BaselineData & baselineData)
{
  if      (mode == "FIXED") { fixedBaseline(ch, rawWF, bsWF, baselineData); }
  else if (mode == "ZERO")  { zeroBaseline(ch, rawWF, bsWF, baselineData);  }
  else                      { invalidBaseline(ch, bsWF, baselineData);      }
}

///////////////////////////////////////////////////////////////////////////////////
////////////////////      DRIFTING BASELINE ALGORITHM       ///////////////////////
///////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////
//////////////////////      FIXED BASELINE ALGORITHM       ////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
void arisana::BaselineHelper::fixedBaseline(arisana::Channel const& ch,
                                            arisana::ChannelWF const& rawWF,
                                            arisana::ChannelWF & bsWF,
                                            arisana::BaselineData & baselineData)
{
  // Evaluate average of baseline region
  const int start_samp = ch.TimeToSample(fixed_params.start_time, true);
  const int end_samp = ch.TimeToSample(fixed_params.end_time, true);
  const int n_baseline_samps = end_samp-start_samp;
  double baseline_mean = 0;
  double baseline_var = 0;
  for (int i=start_samp; i<end_samp; ++i) {
    baseline_mean += rawWF.waveform[i];
    baseline_var += rawWF.waveform[i]*rawWF.waveform[i];
  }
  baseline_mean = baseline_mean/n_baseline_samps;
  baseline_var = baseline_var/n_baseline_samps - baseline_mean*baseline_mean;

  bool baseline_valid = false;
  if (baseline_var < fixed_params.max_sigma*fixed_params.max_sigma) baseline_valid = true;


  // set arisana::Baseline object
  baselineData.mean = baseline_mean;
  baselineData.variance = baseline_var;
  baselineData.valid = baseline_valid;


  // build baseline-subtracted waveform
  bsWF.channel_id = ch.channel_id;
  bsWF.waveform.resize(ch.nsamps);
  if (baseline_valid) {
    for (int i=0; i<ch.nsamps; ++i)
      bsWF.waveform[i] = rawWF.waveform[i] - baseline_mean;
  }
  else {
    for (int i=0; i<ch.nsamps; ++i)
      bsWF.waveform[i] = 0;
  } 
  
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////      ZERO BASELINE ALGORITHM       ////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void arisana::BaselineHelper::zeroBaseline(arisana::Channel const& ch,
                                           arisana::ChannelWF const& rawWF,
                                           arisana::ChannelWF & bsWF,
                                           arisana::BaselineData & baselineData)
{
  bsWF.channel_id = ch.channel_id;
  bsWF.waveform.resize(ch.nsamps);
  for (int i=0; i<ch.nsamps; ++i) bsWF.waveform[i] = rawWF.waveform[i];

  baselineData.mean = 0;
  baselineData.variance = 0;
  baselineData.valid = true;
}


////////////////////////////////////////////////////////////////////////////////
///////////////////////      INVALID BASELINE       ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void arisana::BaselineHelper::invalidBaseline(arisana::Channel const& ch,
                                              arisana::ChannelWF & bsWF,
                                              arisana::BaselineData & baselineData)
{
  bsWF.channel_id = ch.channel_id;
  bsWF.waveform.resize(ch.nsamps);
  for (int i=0; i<ch.nsamps; ++i) bsWF.waveform[i] = 0;

  baselineData.mean = -1;
  baselineData.variance = -1;
  baselineData.valid = true;
}
