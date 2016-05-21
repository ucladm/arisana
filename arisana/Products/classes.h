/*

  This file is necessary to create the dictionary used to build
  the ROOT tree. This is necessary for every class that is an
  instantiation of a class template (e.g., std::vector<Channel>
  is an instantiation of the class template std::vector). Note
  this is necessary for the art::Wrapper instantiation for each
  top-level data product.

 */



#include "arisana/Products/EventInfo.hh"
#include "arisana/Products/Channel.hh"
#include "arisana/Products/ChannelWF.hh"
#include "arisana/Products/BaselineData.hh"
#include "arisana/Products/ROI.hh"
#include "arisana/Products/Pulse.hh"
#include "arisana/Products/EventData.hh"

#include <vector>
#include <utility>

// art stuff
#include "art/Persistency/Common/Wrapper.h"

template class art::Wrapper<int>;
template class art::Wrapper<float>;
template class art::Wrapper<double>;
template class art::Wrapper<bool>;

template class std::vector<std::vector<double> >;
template class art::Wrapper<std::vector<std::vector<double> > >;

template class art::Wrapper<arisana::EventInfo>;

template class art::Wrapper<arisana::Channel>;
template class std::vector<arisana::Channel>;
template class art::Wrapper<std::vector<arisana::Channel> >;

template class art::Wrapper<arisana::Channel::PMT>;
template class std::vector<arisana::Channel::PMT>;
template class art::Wrapper<std::vector<arisana::Channel::PMT> >;


template class art::Wrapper<arisana::ChannelWF>;
template class std::vector<arisana::ChannelWF>;
template class art::Wrapper<std::vector<arisana::ChannelWF> >;

template class art::Wrapper<arisana::BaselineData>;
template class std::vector<arisana::BaselineData>;
template class art::Wrapper<std::vector<arisana::BaselineData> >;


template class art::Wrapper<arisana::ROI>;
template class std::vector<arisana::ROI>;
template class art::Wrapper<std::vector<arisana::ROI> >;

template class art::Wrapper<arisana::Pulse>;
template class std::vector<arisana::Pulse>;
template class art::Wrapper<std::vector<arisana::Pulse> >;

template class art::Wrapper<arisana::EventData>;
