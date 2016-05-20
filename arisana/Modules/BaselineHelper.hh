#ifndef arisana_Modules_BaselineHelper_hh
#define arisana_Modules_BaselineHelper_hh

#include "fhiclcpp/ParameterSet.h"

#include "arisana/Products/ChannelWF.hh"
#include "arisana/Products/Channel.hh"
#include "arisana/Products/BaselineData.hh"

#include <vector>

namespace arisana
{

  class BaselineHelper
  {
  public:
    BaselineHelper();
    BaselineHelper(fhicl::ParameterSet const& p);

    void evalBaselineSubtractedWF(arisana::Channel const& ch,
                                  arisana::ChannelWF const& rawWF,
                                  arisana::ChannelWF & bsWF,
                                  arisana::BaselineData & baselineData);
    
  private:

    std::string mode;

    ////////////////////////////////////////////////////////////////////////////////
    /////////////////      DRIFTING BASELINE ALGORITHM       ///////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    /* to be filled */


    ////////////////////////////////////////////////////////////////////////////////
    ///////////////////      FIXED BASELINE ALGORITHM       ////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    struct FixedBaselineParams
    {
      FixedBaselineParams() {}
      FixedBaselineParams(fhicl::ParameterSet const& p)
        : start_time(p.get<double>("start_time"))
        , end_time(p.get<double>("end_time"))
        , max_sigma(p.get<double>("max_sigma"))
      {}

      double start_time;
      double end_time;
      double max_sigma;
    } fixed_params;

    void fixedBaseline(arisana::Channel const& ch,
                       arisana::ChannelWF const& rawWF,
                       arisana::ChannelWF & bsWF,
                       arisana::BaselineData & baselineData);



    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////      ZERO BASELINE ALGORITHM       ////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    void zeroBaseline(arisana::Channel const& ch,
                      arisana::ChannelWF const& rawWF,
                      arisana::ChannelWF & bsWF,
                      arisana::BaselineData & baselineData);

    ////////////////////////////////////////////////////////////////////////////////
    ///////////////////////      INVALID BASELINE       ////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    void invalidBaseline(arisana::Channel const& ch,
                         arisana::ChannelWF & bsWF,
                         arisana::BaselineData & baselineData);
  };
}

#endif
