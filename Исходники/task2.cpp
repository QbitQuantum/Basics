/**
@function toGrayScale
utilizes SSE to realize fast approach to convert RGBA image to grayscale.
It is faster than toGrayScaleSSE, but not so precise
@param [in] in_input is an input image.
@param [out] out_mat is an output image. Each pixel is represented by a single unsigned char value.
*/
void toGrayScaleSSE_16BIT(BMP &in_input, MyMat<uchar> &out_mat)
{
  // pointer to the processed row of the result image
  uchar *row_ptr = out_mat.data;
  // pointer to the processed element of the result image
  uchar *elem_ptr;
  // number of elements to process at a time
  const int block_size = 8;
  // number of elements that will not be processed block-wise
  const int left_cols = out_mat.cols % block_size;
  // number of elements that will be processed block-wise
  const int block_cols = out_mat.cols - left_cols;

  for (size_t row_idx = 0; row_idx  < out_mat.rows; ++row_idx)
  {
    elem_ptr = row_ptr;
    // process block_size elements at a time
    for (int col_idx = 0; col_idx < block_cols; col_idx += block_size)
    {
      // read four pixels
      __m128i BG1;
      __m128i RA1;
      Get4Pixels16Bit(in_input, row_idx, col_idx, &BG1, &RA1);

      // read another four pixels
      __m128i BG2;
      __m128i RA2;
      Get4Pixels16Bit(in_input, row_idx, col_idx + 4, &BG2, &RA2);

      // extract channels
      __m128i blue = _mm_unpacklo_epi64(BG1, BG2);
      __m128i green = _mm_unpackhi_epi64(BG1, BG2);
      __m128i red = _mm_unpacklo_epi64(RA1, RA2);

      // multiply channels by weights
      blue = _mm_mullo_epi16(blue, CONST_BLUE_16_INT);
      green = _mm_mullo_epi16(green, CONST_GREEN_16_INT);
      red = _mm_mullo_epi16(red, CONST_RED_16_INT);

      // sum up channels
      __m128i color = _mm_add_epi16(red, green);
      color = _mm_add_epi16(color, blue);

      // divide by 256
      color = _mm_srli_epi16(color, 8);

      // convert to 8bit
      color = _mm_packus_epi16(color, _mm_setzero_si128());

      // write results to the output image
      _mm_storel_epi64(reinterpret_cast<__m128i*>(elem_ptr), color);
      elem_ptr += block_size;
    }
    // process left elements in the row
    for (size_t col_idx = block_cols; col_idx < out_mat.cols; ++col_idx)
    {
      RGBApixel pixel = in_input.GetPixel(col_idx, row_idx);
      short red = 0.2125f * 256, green =  0.7154f * 256, blue =  0.0721f * 256;
      int carry =(red * pixel.Red + green * pixel.Green + blue * pixel.Blue) / 256;
      *elem_ptr = static_cast<uchar>(carry);
      ++elem_ptr;
    }
    // go to next row
    row_ptr += out_mat.step;
  }

}