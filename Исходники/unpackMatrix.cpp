void unpackMatrixPlusV3(ByteUnpacker &src, u16 *dst, size_t L) {
  // extract key numbers: 
  const vector<size_t> header = src.pop<size_t>(5);   
  const size_t nGood = header[0];
  const size_t nBad = header[1];
  const size_t RANK_GOOD = header[2];
  //const size_t rankBad = header[3];
  const bool uses16Bit = header[4];
  const int N = nGood + nBad; 
  //assert(rankBad == L);
  const fmat basisGood( POP_CONSTRUCTOR(float, L, RANK_GOOD) );
  // extract partion:
  const Col<u8> partion( src.popPtr<u8>(N), N, false, true );
  const uvec goodIdx = find(partion == 0);
  const uvec badIdx = find(partion == 1);
  assert( goodIdx.n_elem == nGood && badIdx.n_elem == nBad);
    
  // make a matrix using the memory pointed to by dst:
  Mat<u16> restored(dst, L, N, false, true);

  //decompress the good traces:
  if ( nGood > 0) {
    if ( uses16Bit ) {
      // extract scores:
      const Mat<i16> scoreGood( POP_CONSTRUCTOR(i16, nGood, RANK_GOOD) );
      //restored.cols(goodIdx) = convToValidU16( basisGood * convToFloat(scoreGood).t() );
      restored.cols(goodIdx) = convToValidU16( basisGood * scoreGood.t() );
    }
    else {
      // extract scores:
      const Mat<i32> scoreGood( POP_CONSTRUCTOR(i32, nGood, RANK_GOOD) );
      // fill this matrix with the matrix multiplications:
      //restored.cols(goodIdx) = convToValidU16( basisGood * conv_to<fmat>::from(scoreGood).t() );
      restored.cols(goodIdx) = convToValidU16( basisGood * scoreGood.t() );
    }
  }
  //Decompress the bad data, output the uncompressed to restored.cols(badIdx);
  if ( nBad > 0)
    {
      vector<size_t> sSize = src.pop<size_t>(1);
      const vector<uint8_t> deltaIn = src.pop<uint8_t>(sSize[0]);
      Decompressor dc;
      size_t nCols;
      size_t nRows;
      size_t oL;
      vector<uint16_t> deltaOut;
      dc.decompress(deltaIn,nRows,nCols, oL, deltaOut);
      Mat<uint16_t> dataBadMat(&deltaOut[0], L, nBad, false, true);
      restored.cols(badIdx) = dataBadMat;
    }
}