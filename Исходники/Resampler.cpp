int main(int argc, char **argv){
  
  _mm_setcsr(_mm_getcsr() | 0x8040);

  int num_frames = atoi(argv[1]); // If we hardcode the value, the compiler is likely to optimize things which it wouldn't have done normally
  //fprintf(stderr, "num_frames: %d\n",num_frames);
  
  float *data = (float*)malloc(sizeof(float)*num_frames);
 
  for(int i=0;i<num_frames;i++){
    data[i] = (float)i / (float)num_frames; // Insert some some legal values.
  }

  void *resampler = RESAMPLER_create(src_callback, 1, NULL, RESAMPLER_CUBIC);

  int top = 1024*1024*8 * 64 / num_frames;
  
  for(int i=0 ; i < top ; i ++)
    RESAMPLER_read(resampler, scale(i,0,top,0.1,8.0), num_frames, data);
  
  //printf("hello\n");
  return 0;
}