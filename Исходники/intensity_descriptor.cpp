void
IntensityDescriptorExtractor::normalizeDescriptor(uint8_t* desc) const
{
  assert(FOVIS_IS_ALIGNED16(_descriptor_brightness_offset));

  // get mean of patch
  uint32_t desc_mean = std::accumulate(desc, desc + _descriptor_len, 0)/_descriptor_len;
  // subtract mean, adding offset so 0 -> 128
  if(desc_mean < 128) {
    std::fill(_descriptor_brightness_offset, _descriptor_brightness_offset+16, 128-desc_mean);
    for(int op=0; op<_brightess_offset_num_sse_ops; op++) {
      ((__m128i*)desc)[op] = _mm_adds_epu8(((__m128i*)desc)[op],
        *(__m128i*)_descriptor_brightness_offset);
    }
  } else if (desc_mean > 128){
    std::fill(_descriptor_brightness_offset, _descriptor_brightness_offset+16, desc_mean-128);
    for(int op=0; op<_brightess_offset_num_sse_ops; op++) {
      ((__m128i*)desc)[op] = _mm_subs_epu8(((__m128i*)desc)[op],
        *(__m128i*)_descriptor_brightness_offset);
    }
  }
}