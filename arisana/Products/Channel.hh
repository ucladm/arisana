#ifndef arisana_Products_Channel_hh
#define arisana_Products_Channel_hh

namespace arisana
{
  struct Channel
  {
    Channel():
      pmt(),
      board_id(-1),
      board_ch(-1),
      channel_id(-1),
      valid(false),
      sample_rate(-1),
      sample_bits(-1),
      trigger_index(-1),
      nsamps(-1)
    { }

    struct PMT
    {
      PMT():
        spe_mean(1),
        spe_sigma(0),
        xpos(0),
        ypos(0),
        zpos(0)
      {}

      double spe_mean;
      double spe_sigma;
      double xpos;
      double ypos;
      double zpos;
    } pmt;
      
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

    static const int SUMCH_ID = -2;

  };
}

#endif
