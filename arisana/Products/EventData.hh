/*

  Defines the EventData data product. Will be a 'super-product'
  which contains all the information from other products. This
  product will be written to a separate output ROOT TTree in a
  separate output file. 

  AFan 2016-05-20

 */


#ifndef arisana_Products_EventData_hh
#define arisana_Products_EventData_hh

#include "EventInfo.hh"
#include "Channel.hh"
#include "BaselineData.hh"
#include "ROI.hh"
//#include "Pulse.hh"

#include <string>
#include <vector>

namespace arisana
{
  struct EventData
  {
    EventData():
      arisana_version(""),
      info(),
      nchannels(0),
      channels(),
      baselines(),
      rois(),
      sumch()
      //pulses()
    {}

    std::string arisana_version;
    arisana::EventInfo info;
    int nchannels;
    std::vector<arisana::Channel> channels;
    std::vector<arisana::BaselineData> baselines;
    std::vector<arisana::ROI> rois;
    std::vector<arisana::Channel> sumch;
    //std::vector<arisana::Pulse> pulses;

    void clear();
  };
}


inline void arisana::EventData::clear()
{
  arisana_version = "";
  info = EventInfo();
  nchannels = 0;
  channels.clear();
  baselines.clear();
  rois.clear();
  sumch.clear();
}




#endif
