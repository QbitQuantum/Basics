//------------------------------------------------------------------------
//
inline void jpeg_encoder_impl::encode_interleaved_impl_(core::jpeg_data_t& ret, core::uint8_sarr arr, int quality)
{
  jpeg_sink.datacount = 0;

  encoder.writeImage(w_, h_, d_, arr.get(), quality);
  
  core::uint8_ptr temp = new all::core::uint8_t[jpeg_sink.datacount];

  memcpy (temp, jpeg_sink.jpeg_arr.get(), jpeg_sink.datacount);

  ret.data.reset(temp);
  ret.size    = jpeg_sink.datacount;
  ret.height  =   h_;
  ret.width   =   w_;
  ret.depth   =   d_;
  //crc
  calc_crc_(ret);
}