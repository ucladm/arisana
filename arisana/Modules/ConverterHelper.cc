#include "arisana/Modules/ConverterHelper.hh"
#include "darksidecore/Data/Config.hh"
#include "art/Utilities/Exception.h"
#include "artdaq-core/Data/Fragment.hh"

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>


//----------------------------------------------------------------------------
std::vector<double>
arisana::ConverterHelper::convertWaveform(ds50::V172xFragment::adc_type const * begin,
                                          ds50::V172xFragment::adc_type const * end)
{
  std::vector<double> wave;
  wave.reserve(end-begin);
  for ( ; begin != end; ++begin)
    wave.push_back(*begin);
  return wave;
}


//----------------------------------------------------------------------------
void
arisana::ConverterHelper::convertFragments(artdaq::Fragments const& frags,
                                           //darkart::WaveformVec& wfmVec,
                                           //darkart::WaveformInfoVec& wfmInfoVec,
                                           //darkart::ChannelVec& chVec,
                                           //std::vector<int> skip_ch);
                                           std::vector<arisana::Channel> & channels,
                                           std::vector<arisana::ChannelWF> & raw_wfs)
{
  for (auto const& frag : frags) {

    // Use the overlay to allow us to read channels
    ds50::V172xFragment overlay(frag);

    // Loop over all channels in the fragment 
    for (size_t ch_num=0; ch_num<overlay.enabled_channels(); ++ch_num) {
      
      // Some of the info is in V172xFragment metadata
      ds50::V172xFragment::metadata const md = *(frag.metadata<ds50::V172xFragment::metadata>());
        
      // Define channel_id
      int board_size = overlay.enabled_channels();
      int board_id = overlay.board_id();
      int board_ch = ch_num;
      int channel_id = board_size*board_id + board_ch;

      // Set raw wf data
      arisana::ChannelWF raw_wf;
      raw_wf.channel_id = channel_id;
      raw_wf.waveform = std::move(convertWaveform(overlay.chDataBegin(ch_num), overlay.chDataEnd(ch_num)));
      //raw_wf.waveform = convertWaveform(overlay.chDataBegin(ch_num), overlay.chDataEnd(ch_num));
      if (channel_id>=0) raw_wfs.at(channel_id) = std::move(raw_wf);
      //if (channel_id>=0) raw_wfs.at(channel_id) = raw_wf;

      // Set Channel data
      arisana::Channel ch;
      ch.board_id = board_id;
      ch.board_ch = board_ch;
      ch.channel_id = channel_id;
      ch.sample_rate = md.sample_rate_MHz;
      ch.sample_bits = md.sample_bits;
      ch.trigger_index = (int)(md.record_length - md.record_length*md.post_trigger/100.);
      ch.nsamps = raw_wfs[channel_id].waveform.size();
      ch.valid = true;
      if (channel_id>=0) channels.at(channel_id) = std::move(ch);
      
    }// end loop over channels
  }// end loop over Fragment objects

}
