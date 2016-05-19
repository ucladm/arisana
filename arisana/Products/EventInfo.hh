/*

  Definition of the EventInfo class

  AFan 2016-05-19

 */


#ifndef arisana_Products_EventInfo_hh
#define arisana_Products_EventInfo_hh


#include <stdint.h>


namespace arisana
{
  struct EventInfo
  {
    EventInfo():
      run_id(-1),
      subrun_id(-1),
      event_id(-1),
      nchannels(-1)
  {}

  int run_id;
  int subrun_id;
  int event_id;
  int nchannels;

  };

}




#endif
