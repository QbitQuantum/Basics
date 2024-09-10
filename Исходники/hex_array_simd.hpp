inline __m256i avx2_uv_to_hexid_ccw(const __m256i u, const __m256i v)
{
  // if(u==0 and v==0)return 0;
  // int ringid = uv_to_ringid(u,v);
  // unsigned segid;
  // int runid;
  // int upv = u+v;
  // if(upv==ringid and v!=ringid)         { segid=0; runid=v; }
  // else if(v==ringid and u!=-ringid)     { segid=1; runid=-u; }
  // else if(u==-ringid and upv!=-ringid)  { segid=2; runid=ringid-v; }
  // else if(u+v==-ringid and v!=-ringid)  { segid=3; runid=-v; }
  // else if(v==-ringid and u!=ringid)     { segid=4; runid=u; }
  // else /*if(u==ringid and upv!=ringid)*/{ segid=5; runid=ringid+v; }
  // return positive_ringid_segid_runid_to_hexid(ringid, segid, runid);
  const __m256i one = _mm256_set1_epi32(1);
  const __m256i minus_one = _mm256_set1_epi32(-1);
  const __m256i ringid = avx2_uv_to_ringid(u,v);
  const __m256i minus_ringid = _mm256_sign_epi32(ringid, minus_one);
  const __m256i upv = _mm256_add_epi32(u, v);
  __m256i not_found_mask = minus_one;
  __m256i hexid = avx2_ringid_to_nsites_contained(_mm256_sub_epi32(ringid, one));

  // Seg ID = 0
  // if(upv==ringid and v!=ringid)         { segid=0; runid=v; }
  __m256i here_mask = _mm256_cmpeq_epi32(upv, ringid);
  hexid = _mm256_add_epi32(hexid, _mm256_and_si256(not_found_mask,
    _mm256_blendv_epi8(ringid, v, here_mask)));
  not_found_mask = _mm256_andnot_si256(here_mask, not_found_mask);
  // hexid = _mm256_add_epi32(hexid, _mm256_or_si256(
  //   _mm256_and_si256(here_mask, v),
  //   _mm256_and_si256(not_found_mask, ringid)));

  // Seg ID = 1
  // else if(v==ringid and u!=-ringid)     { segid=1; runid=-u; }
  here_mask = _mm256_cmpeq_epi32(v, ringid);
  hexid = _mm256_sub_epi32(hexid, _mm256_and_si256(not_found_mask,
    _mm256_blendv_epi8(minus_ringid, u, here_mask)));
  not_found_mask = _mm256_andnot_si256(here_mask, not_found_mask);
  // hexid = _mm256_sub_epi32(hexid, _mm256_or_si256(
  //   _mm256_and_si256(here_mask, u),
  //   _mm256_and_si256(not_found_mask, minus_ringid)));

  // Seg ID = 2
  // else if(u==-ringid and upv!=-ringid)  { segid=2; runid=ringid-v; }
  here_mask = _mm256_cmpeq_epi32(u, minus_ringid);
  hexid = _mm256_sub_epi32(hexid, _mm256_and_si256(not_found_mask,
    _mm256_blendv_epi8(minus_ringid, upv, here_mask)));
  not_found_mask = _mm256_andnot_si256(here_mask, not_found_mask);
  // hexid = _mm256_sub_epi32(hexid, _mm256_or_si256(
  //   _mm256_and_si256(here_mask, upv),
  //   _mm256_and_si256(not_found_mask, minus_ringid)));

  // Seg ID = 3
  // else if(u+v==-ringid and v!=-ringid)  { segid=3; runid=-v; }
  here_mask = _mm256_cmpeq_epi32(upv, minus_ringid);
  hexid = _mm256_sub_epi32(hexid, _mm256_and_si256(not_found_mask,
    _mm256_blendv_epi8(minus_ringid, v, here_mask)));
  not_found_mask = _mm256_andnot_si256(here_mask, not_found_mask);
  // hexid = _mm256_sub_epi32(hexid, _mm256_or_si256(
  //   _mm256_and_si256(here_mask, v),
  //   _mm256_and_si256(not_found_mask, minus_ringid)));

  // Seg ID = 4
  // else if(v==-ringid and u!=ringid)     { segid=4; runid=u; }
  here_mask = _mm256_cmpeq_epi32(v, minus_ringid);
  hexid = _mm256_add_epi32(hexid, _mm256_and_si256(not_found_mask,
    _mm256_blendv_epi8(ringid, u, here_mask)));
  not_found_mask = _mm256_andnot_si256(here_mask, not_found_mask);
  // hexid = _mm256_add_epi32(hexid, _mm256_or_si256(
  //   _mm256_and_si256(here_mask, u),
  //   _mm256_and_si256(not_found_mask, ringid)));

  // Seg ID = 5
  // else /*if(u==ringid and upv!=ringid)*/{ segid=5; runid=ringid+v; }
  hexid = _mm256_add_epi32(hexid, _mm256_and_si256(not_found_mask, upv));

  const __m256i mask = _mm256_cmpeq_epi32(ringid, _mm256_setzero_si256());
  hexid = _mm256_andnot_si256(mask, hexid);
  return hexid;
}