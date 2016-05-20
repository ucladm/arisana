#ifndef arisana_Products_BaselineData_hh
#define arisana_Products_BaselineData_hh

namespace arisana
{
  struct BaselineData
  {
    BaselineData():
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
