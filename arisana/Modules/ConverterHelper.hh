#ifndef arisana_Modules_ConverterHelper_hh
#define arisana_Modules_ConverterHelper_hh

#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "artdaq-core/Data/Fragment.hh"
#include "artdaq-core/Data/Fragments.hh"

#include "darksidecore/Data/V172xFragment.hh"
#include "darksidecore/Data/V1495Fragment.hh"

#include "arisana/Products/EventInfo.hh"
#include "arisana/Products/Channel.hh"
#include "arisana/Products/ChannelWF.hh"

namespace arisana
{
  // Need to keep track of trigger timing from event to event, so put these
  // these functions in a class and keep one instance of the class in the
  // Converter producer module.
  
  class ConverterHelper {
  public:
    ConverterHelper() { }

    // Convert the data for one channel held in a Fragment (as integral
    // raw ADC counts) to the values stored as floating-point
    // numbers. 
    std::vector<double>
    convertWaveform(ds50::V172xFragment::adc_type const * begin,
                    ds50::V172xFragment::adc_type const * end);

    
    // Loop over all one artdaq::Fragments. Translate each artdaq::Fragment
    // into a series of arisana::ChannelWF and arisana::Channel objects.
    void
    convertFragments(artdaq::Fragments const& frags,
                     //darkart::WaveformVec& wfmVec,
                     //darkart::WaveformInfoVec& wfmInfoVec,
                     //darkart::ChannelVec& chVec,
                     //std::vector<int> skip_ch);
                     std::vector<arisana::Channel> & channels,
                     std::vector<arisana::ChannelWF> & raw_wfs);

  };
}



#endif
