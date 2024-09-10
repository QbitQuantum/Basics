//计算TI、SI
int tisi(char* ydata,char* prev_ydata,int width,int height,SDLParam sdlparam,float &TI,float &SI)
{
	int nYSize=height*width;
	float nFrameSize = nYSize*1.5;
	int realframe_size=(width-2*PADDING)*(height-2*PADDING);

	unsigned char *pFrame=(unsigned char*)malloc(nYSize);
	unsigned char *pNextFrame=(unsigned char*)malloc(nYSize);
	unsigned char *pFrame_0;
	unsigned char *pFrame_1;
	unsigned char *pFrame_2;
	unsigned char *pNextFrame_0;
	unsigned char *pSobelScreen=(unsigned char*)malloc(realframe_size);
	unsigned char *pDiffScreen=(unsigned char*)malloc(realframe_size);
	memset(pSobelScreen,0,realframe_size);
	memset(pDiffScreen,0,realframe_size);

	float *frame_sobel=(float*)malloc(realframe_size*sizeof(float));
	memset(frame_sobel,0.0f,realframe_size*sizeof(float));
	float avg_frame_sobel=0;
	int index=0;

	float *frame_diff=(float*)malloc(realframe_size*sizeof(float));
	memset(frame_diff,0.0f,realframe_size*sizeof(float));
	float avg_frame_diff=0;

	__m128 sobel_avg_sum=_mm_set1_ps(+0.0f);
	__m128 sobel_square_sum=_mm_set1_ps(+0.0f);
	__m128 diff_avg_sum=_mm_set1_ps(+0.0f);
	__m128 diff_square_sum=_mm_set1_ps(+0.0f);
	__m128 avg_sobel=_mm_set1_ps(+0.0f);
	__m128 avg_diff=_mm_set1_ps(+0.0f);

	int i,j,k;
	int pad_threshold=0;
	
	memcpy(pFrame,prev_ydata,nYSize);
	memcpy(pNextFrame,ydata,nYSize);

	pFrame_0=pFrame+width*(PADDING-1);
	pFrame_1=pFrame+width*PADDING;
	pFrame_2=pFrame+width*(PADDING+1);
	pNextFrame_0=pNextFrame+width*(PADDING-1);

	//Check
	if(mark_exit==1){
		return -1;
	}	

	for(j = PADDING; j < height-PADDING; j++)
	{
		for(i = PADDING; i < width-PADDING; i+=4)
		{
			if(i+4>width-PADDING)
				pad_threshold=1;
			// load 16 components. (0~6 will be used)
			__m128i current_0 = _mm_unpacklo_epi8(_mm_loadu_si128((__m128i*)(pFrame_0+i-1)), _mm_setzero_si128());
			__m128i current_1 = _mm_unpacklo_epi8(_mm_loadu_si128((__m128i*)(pFrame_1+i-1)), _mm_setzero_si128());
			__m128i current_2 = _mm_unpacklo_epi8(_mm_loadu_si128((__m128i*)(pFrame_2+i-1)), _mm_setzero_si128());
			__m128i next_0 = _mm_unpacklo_epi8(_mm_loadu_si128((__m128i*)(pNextFrame_0+i-1)), _mm_setzero_si128());

			// pFrame_00 = { pFrame_0[i-1], pFrame_0[i], pFrame_0[i+1], pFrame_0[i+2] }
			__m128 pFrame_00 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(current_0, _mm_setzero_si128()));
			// pFrame_01 = { pFrame_0[i], pFrame_0[i+1], pFrame_0[i+2], pFrame_0[i+3] }
			__m128 pFrame_01 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(_mm_srli_si128(current_0, 2), _mm_setzero_si128()));
			// pFrame_02 = { pFrame_0[i+1], pFrame_0[i+2], pFrame_0[i+3], pFrame_0[i+4] }
			__m128 pFrame_02 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(_mm_srli_si128(current_0, 4), _mm_setzero_si128()));
			// pFrame_10 = { pFrame_1[i-1], pFrame_1[i], pFrame_1[i+1], pFrame_1[i+2] }
			__m128 pFrame_10 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(current_1, _mm_setzero_si128()));
			// pFrame_12 = { pFrame_1[i+1], pFrame_1[i+2], pFrame_1[i+3], pFrame_1[i+4] }
			__m128 pFrame_12 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(_mm_srli_si128(current_1, 4), _mm_setzero_si128()));
			// pFrame_20 = { pFrame_2[i-1], pFrame_2[i], pFrame_2[i+1], pFrame_2[i+2] }
			__m128 pFrame_20 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(current_2, _mm_setzero_si128()));
			// pFrame_21 = { pFrame_2[i], pFrame_2[i+1], pFrame_2[i+2], pFrame_2[i+3] }
			__m128 pFrame_21 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(_mm_srli_si128(current_2, 2), _mm_setzero_si128()));
			// pFrame_22 = { pFrame_2[i+1], pFrame_2[i+2], pFrame_2[i+3], pFrame_2[i+4] }
			__m128 pFrame_22 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(_mm_srli_si128(current_2, 4), _mm_setzero_si128()));
			
			__m128 pNextFrame_00 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(next_0, _mm_setzero_si128()));
			
			__m128 gx=_mm_add_ps(_mm_sub_ps(_mm_add_ps(_mm_add_ps(_mm_sub_ps(_mm_sub_ps(_mm_sub_ps(pFrame_20,pFrame_22),pFrame_12),pFrame_12),pFrame_10),pFrame_10),pFrame_02),pFrame_00);

			__m128 gy=_mm_sub_ps(_mm_sub_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_sub_ps(pFrame_00,pFrame_20),_mm_sub_ps(pFrame_02,pFrame_22)),pFrame_01),pFrame_01),pFrame_21),pFrame_21);

			__m128 sobel_result = _mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(gx, gx), _mm_mul_ps(gy,gy)));

			__m128 diff_result=_mm_sub_ps(pNextFrame_00,pFrame_00);
			
			if(!pad_threshold)
			{
				frame_sobel[index]=sobel_result.m128_f32[0];
				frame_sobel[index+1]=sobel_result.m128_f32[1];
				frame_sobel[index+2]=sobel_result.m128_f32[2];
				frame_sobel[index+3]=sobel_result.m128_f32[3];
				pSobelScreen[index]=(unsigned char)sobel_result.m128_f32[0];
				pSobelScreen[index+1]=(unsigned char)sobel_result.m128_f32[1];
				pSobelScreen[index+2]=(unsigned char)sobel_result.m128_f32[2];
				pSobelScreen[index+3]=(unsigned char)sobel_result.m128_f32[3];
				
				frame_diff[index]=diff_result.m128_f32[0];
				frame_diff[index+1]=diff_result.m128_f32[1];
				frame_diff[index+2]=diff_result.m128_f32[2];
				frame_diff[index+3]=diff_result.m128_f32[3];
				pDiffScreen[index]=(unsigned char)abs(diff_result.m128_f32[0]);
				pDiffScreen[index+1]=(unsigned char)abs(diff_result.m128_f32[1]);
				pDiffScreen[index+2]=(unsigned char)abs(diff_result.m128_f32[2]);
				pDiffScreen[index+3]=(unsigned char)abs(diff_result.m128_f32[3]);
				index+=4;
			}
			else
			{
				for(k=0;k<width-PADDING-i;k++)
				{
					frame_sobel[index+k]=sobel_result.m128_f32[k];
					pSobelScreen[index+k]=(unsigned char)sobel_result.m128_f32[k];
					frame_diff[index+k]=diff_result.m128_f32[k];
					pDiffScreen[index+k]=(unsigned char)abs(diff_result.m128_f32[k]);
				}
				index+=width-PADDING-i;
			}		
		}
		pFrame_0 += width;
		pFrame_1 += width;
		pFrame_2 += width;
		pNextFrame_0 += width;
		pad_threshold=0;
	}

	//画图
	if(sdlparam.graphically_si==true&&sdlparam.isinterval==false){
		memcpy(sdlparam.show_YBuffer,pSobelScreen,realframe_size);
		SDL_Event event;
		event.type = REFRESH_EVENT;
		SDL_PushEvent(&event);
	}

	//画图
	if(sdlparam.graphically_ti==true&&sdlparam.isinterval==false){
		memcpy(sdlparam.show_YBuffer,pDiffScreen,realframe_size);
		SDL_Event event;
		event.type = REFRESH_EVENT;
		SDL_PushEvent(&event);
	}

	for(i=0;i<index;i+=4)
	{
		__m128 sobel_result_0 = _mm_set_ps (frame_sobel[i],frame_sobel[i+1], frame_sobel[i+2], frame_sobel[i+3]);
		sobel_avg_sum = _mm_add_ps(sobel_avg_sum,sobel_result_0);

		__m128 diff_result_0 = _mm_set_ps (frame_diff[i],frame_diff[i+1], frame_diff[i+2], frame_diff[i+3]);
		diff_avg_sum = _mm_add_ps(diff_avg_sum,diff_result_0);
	}		
	avg_frame_sobel=(sobel_avg_sum.m128_f32[0]+
		sobel_avg_sum.m128_f32[1]+
		sobel_avg_sum.m128_f32[2]+
		sobel_avg_sum.m128_f32[3])/index;
	avg_sobel = _mm_set_ps (avg_frame_sobel,avg_frame_sobel, avg_frame_sobel, avg_frame_sobel);

	avg_frame_diff=(diff_avg_sum.m128_f32[0]+
		diff_avg_sum.m128_f32[1]+
		diff_avg_sum.m128_f32[2]+
		diff_avg_sum.m128_f32[3])/index;
	avg_diff = _mm_set_ps (avg_frame_diff,avg_frame_diff, avg_frame_diff, avg_frame_diff);

	for(i=0;i<index;i+=4)
	{
		__m128 sobel_result_1 = _mm_set_ps (frame_sobel[i],frame_sobel[i+1], frame_sobel[i+2], frame_sobel[i+3]);
		__m128 sobel_square=_mm_mul_ps(_mm_sub_ps(sobel_result_1,avg_sobel),_mm_sub_ps(sobel_result_1,avg_sobel));
		sobel_square_sum = _mm_add_ps(sobel_square_sum,sobel_square);

		__m128 diff_result_1 = _mm_set_ps (frame_diff[i],frame_diff[i+1], frame_diff[i+2], frame_diff[i+3]);
		__m128 diff_square=_mm_mul_ps(_mm_sub_ps(diff_result_1,avg_diff),_mm_sub_ps(diff_result_1,avg_diff));
		diff_square_sum = _mm_add_ps(diff_square_sum,diff_square);
	}
	
	SI=sqrt((sobel_square_sum.m128_f32[0]+sobel_square_sum.m128_f32[1]+sobel_square_sum.m128_f32[2]+sobel_square_sum.m128_f32[3])/index);
	avg_frame_sobel=0;
	sobel_avg_sum=_mm_set1_ps(+0.0f);
	sobel_square_sum=_mm_set1_ps(+0.0f);
	
	TI=sqrt((diff_square_sum.m128_f32[0]+diff_square_sum.m128_f32[1]+diff_square_sum.m128_f32[2]+diff_square_sum.m128_f32[3])/index);
	avg_frame_diff=0;
	diff_avg_sum=_mm_set1_ps(+0.0f);
	diff_square_sum=_mm_set1_ps(+0.0f);

	index=0;

	//--------
	delete pFrame;
	delete pNextFrame;
	delete pSobelScreen;
	delete pDiffScreen;
	delete frame_diff;
	delete frame_sobel;

	return 0;
}