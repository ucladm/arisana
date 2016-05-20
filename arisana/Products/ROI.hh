#ifndef arisana_Products_ROI_hh
#define arisana_Products_ROI_hh

#include <vector>

namespace arisana
{
  struct ROI
  {
    ROI():
      start_time(-1),
      end_time(-1),
      roi(-1),
      ch_roi()
    {}

    double start_time;
    double end_time;
    double roi;
    std::vector<double> ch_roi;
    
  };
}

#endif
