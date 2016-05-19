#ifndef arisana_Products_Channel_hh
#define arisana_Products_Channel_hh

namespace arisana
{
  struct Channel
  {
    Channel():
      board_id(-1),
      board_ch(-1),
      channel_id(-1),
      valid(false),
      sample_rate(-1),
      sample_bits(-1),
      trigger_index(-1),
      nsamps(-1)
    { }

    int board_id;
    int board_ch;
    int channel_id;
    bool valid;
    double sample_rate;
    int sample_bits;
    int trigger_index;
    int nsamps;

    double SampleToTime(int sample) const;
    int    TimeToSample(double time, bool checkrange=false) const;
  };
}

#endif
