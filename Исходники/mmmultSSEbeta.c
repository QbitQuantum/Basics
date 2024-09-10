int main(int argc, char  **argv)
{

  struct timespec  t1, t2; 
  int c, d, k, sum = 0;
  int size, opt, i;
  char *fname; 
  
  while((opt = getopt(argc, argv, "f:s:"))!= -1) {
    switch (opt){
    case 's':
      size = atoi(optarg);
      break;
    case 'f':
      fname = optarg;
      break;
    default:
      size = MEDIUM; 
      break; 
    }
  }
 
  FILE *fp;
  fp = fopen(fname,"a");
  
  int edge;
  int *first; 
  posix_memalign((void**)&first,16,sizeof(int)*size*size);  //use posix_memalign to get 16byte alignment 
  int *multiply; 
  posix_memalign((void**)&multiply,16,sizeof(int)*size*size);  
  __m128i m1, m2,m3; 
 
  for (  c = 0 ; c < size ; c++ )
  	for ( d = 0 ; d < size ; d++ )    	
      first[c*size+d] = ((c+d) % 2) - 1;
  multiply[c*size+d] = 0;
      
	
  printf("multiplying the %d-size matrices\n  You should try to time this part.\n",size);
	
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);

	for ( c = 0 ; c < size ; c++ )
	{
		for ( k = 0 ; k < size ; k++ )
	    {
	    	m2 = _mm_set1_epi32(first[c*size+k]); //first[c][k]
			for (d = 0 ; d < size ; d+=4) 
			{
				edge = size - d; 
				if (edge < 4){	//account for non-div by 4 matrices
					for (i = d; i < size; i++)
						multiply[c*size+i] += first[c*size+k]*first[k*size+i];
				}
				else{ 
				  m1 = _mm_loadu_si128(&first[k*size+d]);  //first[k][d]
				  m1 = _mm_mullo_epi32(m1,m2); // first[k][d] * first[c][k]
				  m3 = _mm_loadu_si128(&multiply[c*size+d]);//load up old values of multiply[c][d] 
				  
				  m1 = _mm_add_epi32(m3,m1);  //[+= to mult]
			
				  _mm_storeu_si128(&multiply[c*size+d],m1);
			  	}
			  	
	      		} 
	    	}
		}
	
		
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);

  double nanos = (diff(t1,t2).tv_nsec) * pow(10,-9);
  double secs = (diff(t1,t2).tv_sec);
  double dif = secs + nanos;
  
  fprintf(fp,"%.10f\n", dif); 
  
  fclose(fp);

  printf("test first %d\n",first[size]);
  printf("test mult %d\n",multiply[size]);
  

  free(first);   //free SSE aligned array with _aligned_free
  free(multiply);
  return 0;
}