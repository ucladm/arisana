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
#include "arisana/Products/Channel.hh"
#include "arisana/Products/ChannelWF.hh"

#include "arisana/Modules/converter_helper.hh"

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

  int _max_nchannels;

  ConverterHelper _helper;
};


arisana::Converter::Converter(fhicl::ParameterSet const & p)
  : _v1720_tag(p.get<std::string>("v1720_tag"))
  , _v1495_tag(p.get<std::string>("v1495_tag"))
  , _max_nchannels(p.get<int>("max_nchannels"))
{
  produces<arisana::EventInfo>();
  produces<std::vector<arisana::Channel> >();
  produces<std::vector<arisana::ChannelWF> >();
}

void arisana::Converter::produce(art::Event & e)
{
  // Get handle to the V1720 block
  auto v1720 = e.getValidHandle<artdaq::Fragments>(_v1720_tag);
  auto v1495 = e.getValidHandle<artdaq::Fragments>(_v1495_tag);

  // Make our products, which begin empty.
  std::unique_ptr<arisana::EventInfo> eventInfo(new arisana::EventInfo);
  std::unique_ptr<std::vector<arisana::Channel> > channels(new std::vector<arisana::Channel>);
  std::unique_ptr<std::vector<arisana::ChannelWF> > rawWFs(new std::vector<arisana::ChannelWF>);

  // Resize Channel and ChannelWF vectors to guarantee to hold all channels
  channels->resize(_max_nchannels);
  rawWFs->resize(_max_nchannels);
  
  // Extract info and raw waveforms for each channel
  // The channel_id (defined as board_id * board_size + ch # on board) is
  // the index of the object within the vector.
  _helper.convertFragments( *v1720, *channels, *rawWFs );
  
  // Fill EventInfo
  artdaq::Fragment const& frag = v1495->front();
  ds50::V1495Fragment overlay(frag);
  eventInfo->run_id    = e.run();
  eventInfo->subrun_id = e.subRun();
  eventInfo->event_id  = e.event();
  eventInfo->nchannels = channels->size();

  // Put our complete products into the art::Event
  e.put(std::move(eventInfo));
  e.put(std::move(channels));
  e.put(std::move(rawWFs));
}

//void arisana::Converter::beginRun(art::Run & r)
//{
//  // Implementation of optional member function here.
//}


DEFINE_ART_MODULE(arisana::Converter)