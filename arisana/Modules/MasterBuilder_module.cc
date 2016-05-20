////////////////////////////////////////////////////////////////////////
// Class:       MasterBuilder
// Module Type: producer
// File:        MasterBuilder_module.cc
//
// Generated at Fri May 20 14:10:42 2016 by Alden Fan using artmod
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

#include "arisana/Products/EventInfo.hh"
#include "arisana/Products/Channel.hh"
//#include "arisana/Products/ChannelWF.hh"
#include "arisana/Products/BaselineData.hh"
#include "arisana/Products/ROI.hh"
//#include "arisana/Products/Pulse.hh"
#include "arisana/Products/EventData.hh"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace arisana {
  class MasterBuilder;
}

class arisana::MasterBuilder : public art::EDProducer {
public:
  explicit MasterBuilder(fhicl::ParameterSet const & p);
  // The destructor generated by the compiler is fine for classes
  // without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  MasterBuilder(MasterBuilder const &) = delete;
  MasterBuilder(MasterBuilder &&) = delete;
  MasterBuilder & operator = (MasterBuilder const &) = delete;
  MasterBuilder & operator = (MasterBuilder &&) = delete;

  // Required functions.
  void produce(art::Event & e) override;


private:

  art::InputTag _eventInfo_tag;
  art::InputTag _chan_tag;
  art::InputTag _baseline_tag;
  art::InputTag _roi_tag;
  
  int _counter;
};


arisana::MasterBuilder::MasterBuilder(fhicl::ParameterSet const & p)
  : _eventInfo_tag(p.get<std::string>("eventInfo_tag"))
  , _chan_tag(p.get<std::string>("chan_tag"))
  , _baseline_tag(p.get<std::string>("baseline_tag"))
  , _roi_tag(p.get<std::string>("roi_tag"))
  , _counter(-1)
{
  produces<arisana::EventData>();
}

void arisana::MasterBuilder::produce(art::Event & e)
{
  _counter += 1;

  // make the data product, which begins empty
  std::unique_ptr<arisana::EventData> eventData(new arisana::EventData);

  // get the code version
  if (const char* version = std::getenv("CETPKG_VERSION")) eventData->arisana_version = version;
  else eventData->arisana_version = std::getenv("DARKART_VERSION");

  // Get the EventInfo
  art::Handle<arisana::EventInfo> eventInfoHandle;
  e.getByLabel(_eventInfo_tag, eventInfoHandle);
  arisana::EventInfo const& eventInfo(*eventInfoHandle);

  // Get the vector<Channel>
  art::Handle<vector<arisana::Channel> > chansHandle;
  e.getByLabel(_chan_tag, chansHandle);
  vector<arisana::Channel> const& channels(*chansHandle);

  // Get the vector<BaselineData>
  art::Handle<vector<arisana::BaselineData> > baselinesHandle;
  e.getByLabel(_baseline_tag, baselinesHandle);
  vector<arisana::BaselineData> const& baselines(*baselinesHandle);

  // Get the vector<ROI>
  art::Handle<vector<arisana::ROI> > roisHandle;
  e.getByLabel(_roi_tag, roisHandle);
  vector<arisana::ROI> const& rois(*roisHandle);


  eventData->info = std::move(eventInfo);
  eventData->nchannels = channels.size();
  eventData->channels = std::move(channels);
  eventData->baselines = std::move(baselines);
  eventData->rois = std::move(rois);
  
  
  // put the completed data product in the art::Event
  e.put(std::move(eventData));

}

DEFINE_ART_MODULE(arisana::MasterBuilder)