#include "arisana/Products/Channel.hh"
#include "art/Utilities/Exception.h"
#include <limits>


double arisana::Channel::SampleToTime(int sample) const
{
  if (trigger_index < 0 || sample_rate < 0)
    return std::numeric_limits<double>::quiet_NaN();

  return ((double)(sample - trigger_index)) / sample_rate;
}

int arisana::Channel::TimeToSample(double time, bool checkrange) const
{
  if (trigger_index < 0 || sample_rate < 0)
    return -1;

  int samp = (int)(time*sample_rate + trigger_index+0.001); //add 0.001 to avoid rounding errors
  if (checkrange) {
    if (samp < 0) samp = 0;
    if (samp > nsamps -1) samp = nsamps - 1;
  }
  return samp;
  
}
