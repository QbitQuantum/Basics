/* Vector dot product  w/ SSE */
float vec_dotProd_sse(data_t* pArray1,       // [in] 1st source array
                data_t* pArray2,       // [in] 2nd source array
                long int nSize)            // [in] size of all arrays
{
  int  i, nLoop = nSize/4;
  float dotProductResult = 0.0f; 
  __m128 m1;  
  __m128*  pSrc1 = (__m128*) pArray1;
  __m128*  pSrc2 = (__m128*) pArray2;

  for (i = 0; i < nLoop; i++) {
    m1 = _mm_dp_ps(*pSrc1, *pSrc2, 0xFF);
    dotProductResult += m1[0]; 

    pSrc1++;
    pSrc2++;
  }
}