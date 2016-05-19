#ifndef arisana_Products_ChannelWF_hh
#define arisana_Products_ChannelWF_hh

#include <vector>

namespace arisana
{
  struct ChannelWF
  {
    ChannelWF():
      channel_id(-1),
      waveform()
    { }
    
    int channel_id;
    std::vector<double> waveform;
    
  };
}


#endif
