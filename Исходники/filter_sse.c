void
png_read_filter_row_paeth3_sse(png_row_infop row_info, png_bytep row,
   png_const_bytep prev_row)
{
   png_size_t i;
   png_bytep rp = row;
   png_const_bytep prp = prev_row;
   __m128i npix = _mm_cvtsi32_si128(*(uint32_t*)rp);
   __m128i ppix = _mm_setzero_si128();           // Same as 'a' in C version.
   __m128i prppix = _mm_setzero_si128();         // Same as 'c' in C version.
   const __m128i zero = _mm_setzero_si128();

   for (i = 0; i < row_info->rowbytes; i += 3, rp += 3, prp += 3)
   {
      __m128i prpix = _mm_cvtsi32_si128(*(uint32_t*)prp);  // Same as 'b' in C ver.
      __m128i pix, pa, pb, pc, temp;

      prpix = _mm_unpacklo_epi8(prpix, zero);
      temp = _mm_sub_epi16(prpix, prppix);  // p = b - c
      pc = _mm_sub_epi16(ppix, prppix);     // pc = a - c

#ifndef __SSSE3__
      pa = _mm_max_epi16(temp, _mm_sub_epi16(prppix, prpix));
      pb = _mm_max_epi16(pc, _mm_sub_epi16(prppix, ppix));
      temp = _mm_add_epi16(temp, pc);
      pc = _mm_max_epi16(temp, _mm_sub_epi16(zero, temp));
#else
      pa = _mm_abs_epi16(temp);             // pa = abs(p)
      pb = _mm_abs_epi16(pc);               // pb = abs(pc)
      temp = _mm_add_epi16(temp, pc);
      pc = _mm_abs_epi16(temp);             // pc = abs(p + pc)
#endif

      temp = _mm_cmplt_epi16(pb, pa);       // if (pb < pa) pa = pb, a = b
      pa = _mm_andnot_si128(temp, pa);
      pa = _mm_or_si128(pa, _mm_and_si128(temp, pb));
      ppix = _mm_andnot_si128(temp, ppix);
      ppix = _mm_or_si128(ppix, _mm_and_si128(temp, prpix));

      pix = npix;
      npix = _mm_cvtsi32_si128(*(uint32_t*)(rp + 3));
      temp = _mm_cmplt_epi16(pc, pa);       // if (pc < pa) a = c
      ppix = _mm_andnot_si128(temp, ppix);
      ppix = _mm_or_si128(ppix, _mm_and_si128(temp, prppix));

      pix = _mm_unpacklo_epi8(pix, zero);
      prppix = prpix;
      ppix = _mm_add_epi16(ppix, pix);

      ppix = _mm_slli_epi16(ppix, 8);
      ppix = _mm_srli_epi16(ppix, 8);
      pix = _mm_packus_epi16(ppix, zero);
      *(uint32_t*)rp = _mm_cvtsi128_si32(pix);
   }
}