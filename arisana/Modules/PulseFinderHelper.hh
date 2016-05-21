#ifndef arisana_Modules_PulseFinderHelper_hh
#define arisana_Modules_PulseFinderHelper_hh

#include "fhiclcpp/ParameterSet.h"

#include "arisana/Products/ChannelWF.hh"
#include "arisana/Products/Channel.hh"
#include "arisana/Products/Pulse.hh"

#include <vector>

namespace arisana
{
  class PulseFinderHelper
  {
  public:
    PulseFinderHelper(){}
    PulseFinderHelper(fhicl::ParameterSet const& p);

    void findPulses(arisana::Channel const& sumCH,
                    arisana::ChannelWF const& sumWF,
                    std::vector<arisana::Pulse> & pulses);

    void evalParams(std::vector<arisana::Channel> const& chans,
                    //std::vector<arisana::ChannelWF> const& bsWFs,
                    std::vector<arisana::ChannelWF> const& integralWFs,
                    arisana::Pulse & pulse);

  private:

    std::string mode;

    
    struct DiscriminatorParams
    {
      DiscriminatorParams(){}
      DiscriminatorParams(fhicl::ParameterSet const& p)
        : threshold(p.get<double>("threshold"))
      {}
      
      double threshold;
    } discParams;
    void DiscriminatorPulseFinder(arisana::Channel const& sumCH,
                                  arisana::ChannelWF const& sumWF,
                                  std::vector<arisana::Pulse> & pulses);

    
  };
}

#endif
