////////////////////////////////////////////////////////////////////////
// Class:       Converter
// Module Type: producer
// File:        Converter_module.cc
//
// Generated at Thu May 19 16:38:07 2016 by Alden Fan using artmod
// from cetpkgsupport v1_08_06.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "artdaq-core/Data/Fragment.hh"
#include "artdaq-core/Data/Fragments.hh"
#include "artdaq-core/Data/detail/RawFragmentHeader.hh"


// TO BE CHANGED WITH NEW DAQ
#include "darksidecore/Data/V172xFragment.hh"
#include "darksidecore/Data/V1495Fragment.hh"
#include "darksidecore/Data/Config.hh"
#include "darksidecore/ArtServices/DBInterface.hh"


#include "arisana/Products/EventInfo.hh"

#include <memory>
#include <vector>
#include <iostream>

namespace arisana {
  class Converter;
}

class arisana::Converter : public art::EDProducer {
public:
  explicit Converter(fhicl::ParameterSet const & p);
  // The destructor generated by the compiler is fine for classes
  // without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  Converter(Converter const &) = delete;
  Converter(Converter &&) = delete;
  Converter & operator = (Converter const &) = delete;
  Converter & operator = (Converter &&) = delete;

  // Required functions.
  void produce(art::Event & e) override;

  // Selected optional functions.
  //void beginRun(art::Run & r) override;

private:

  art::InputTag _v1720_tag;
  art::InputTag _v1495_tag;

};


arisana::Converter::Converter(fhicl::ParameterSet const & p)
  : _v1720_tag(p.get<std::string>("v1720_tag"))
  , _v1495_tag(p.get<std::string>("v1495_tag"))
{
  produces<arisana::EventInfo>();
}

void arisana::Converter::produce(art::Event & e)
{
  // Get handle to the V1720 block
  //auto v1720 = e.getValidHandle<artdaq::Fragments>(_v1720_tag);
  auto v1495 = e.getValidHandle<artdaq::Fragments>(_v1495_tag);

  // Make our products, which begin empty.
  std::unique_ptr<arisana::EventInfo> eventInfo(new arisana::EventInfo);



  // Fill EventInfo
  artdaq::Fragment const& frag = v1495->front();
  ds50::V1495Fragment overlay(frag);
  eventInfo->run_id    = e.run();
  eventInfo->subrun_id = e.subRun();
  eventInfo->event_id  = e.event();

  if (overlay.run_number() != eventInfo->run_id) {
    std::cout << "ERROR! RUN ID MISMATCH!"<<std::endl;
  }
  
  // Put our complete products into the art::Event
  e.put(std::move(eventInfo));
}

//void arisana::Converter::beginRun(art::Run & r)
//{
//  // Implementation of optional member function here.
//}


DEFINE_ART_MODULE(arisana::Converter)
