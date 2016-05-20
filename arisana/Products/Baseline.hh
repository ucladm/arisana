#ifndef arisana_Products_Baseline_hh
#define arisana_Products_Baseline_hh

namespace arisana
{
  struct Baseline
  {
    Baseline():
      mean(-1),
      variance(-1),
      valid(0)
    {}

    double mean;
    double variance;
    bool valid;
    
  };
}

#endif
