#ifndef arisana_Products_Pulse_hh
#define arisana_Products_Pulse_hh

//#include "arisana/Products/ROI.hh"

#include <vector>

//using namespace std;

namespace arisana
{
  struct Pulse
  {
    Pulse():
      pulse_id(-1),
      start_time(-999),
      end_time(-999),
      npe(0), ch_npe()
      //fixed_int1(0), ch_fixed_int1(),
      //fixed_int2(0), ch_fixed_int2(),
      //prompt(0), ch_prompt(),
      //roi()
      // saturated(false), ch_saturated()
    {}

    int pulse_id;
    double start_time;
    double end_time;
    double npe; std::vector<double> ch_npe;
    //double fixed1; vector<double> ch_fixed1;
    //double fixed2; vector<double> ch_fixed2;
    //double prompt; vector<double> ch_prompt;
    //vector<arisana::ROI> roi;
    //bool saturated; vector<bool> ch_saturated;
  };
}

#endif
