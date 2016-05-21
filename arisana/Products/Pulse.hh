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
      start_index(0),
      end_index(0),
      start_time(-999),
      end_time(-999),
      peak_index(0), ch_peak_index(),
      peak_time(-999), ch_peak_time(),
      peak_amplitude(0), ch_peak_amplitude(),
      npe(0), ch_npe()
      //fixed_int1(0), ch_fixed_int1(),
      //fixed_int2(0), ch_fixed_int2(),
      //prompt(0), ch_prompt(),
      //roi()
      // saturated(false), ch_saturated()
    {}

    int pulse_id;
    int start_index;
    int end_index;
    double start_time;
    double end_time;
    double peak_index; std::vector<double> ch_peak_index;
    double peak_time; std::vector<double> ch_peak_time;
    double peak_amplitude; std::vector<double> ch_peak_amplitude;
    double npe; std::vector<double> ch_npe;
    //double fixed1; vector<double> ch_fixed1;
    //double fixed2; vector<double> ch_fixed2;
    //double prompt; vector<double> ch_prompt;
    //vector<arisana::ROI> roi;
    //bool saturated; vector<bool> ch_saturated;
  };
}

#endif
