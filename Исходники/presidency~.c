void presidency_init(t_presidency *x, short initialized)
{
	int i;
	long oldsize,newsize;
	int oldN = x->N;
	int oldN2 = x->N2;
	int oldNw = x->Nw;
	int last_framecount = x->framecount;
	x->lock = 1;
	x->virgin = 1;
	
	if(!power_of_two(x->winfac))
		x->winfac = 1;
	if(!power_of_two(x->overlap))
		x->overlap = 4;
	if(!x->R)
		x->R = 44100;
	if(!x->D){
		x->D = 256;
		x->vector_size = x->D;
	}
	x->N = x->D * x->overlap;
	x->Nw = x->N * x->winfac;
	limit_fftsize(&x->N, &x->Nw, OBJECT_NAME);
	
	x->N2 = (x->N)>>1;
	x->Nw2 = (x->Nw)>>1;
	x->inCount = -(x->Nw);
	x->mult = 1. / (float) x->N;
//	post("mult %f N %d",x->mult,x->N);
	x->current_frame = 0;
	x->fpos = x->last_fpos = 0;
	x->tadv = (float)x->D/(float)x->R;
	x->c_fundamental = (float)x->R/((x->N2)<<1);
	x->c_factor_in = (float) x->R/((float)x->D * TWOPI);
	x->c_factor_out = TWOPI * (float)x->D / (float)x->R;
	x->table_length = 8192;
	x->table_si = (float) x->table_length / (float) x->R;
	x->pitch_increment = 1.0 * x->table_si;
	
	if( x->duration <= 0 ){
		x->duration = 1.0;
	}
	
	x->framecount =  x->duration / x->tadv ;
	x->hopsize = (float)x->N / x->overlap;
	x->read_me = 0;
	
	if(!initialized){
		x->mute = 0;
		x->in2_connected = 0;
		x->in3_connected = 0;
		x->sync = 0;
		x->playthrough = 0;
		x->frame_increment = 1.0;
		x->verbose = 0;
		x->table = (float *) getbytes(x->table_length * sizeof(float));
		x->Wanal = (float *) getbytes(MAX_Nw*sizeof(float));	
		x->Wsyn = (float *) getbytes(MAX_Nw*sizeof(float));	
		x->input = (float *) getbytes(MAX_Nw*sizeof(float));	
		x->Hwin = (float *) getbytes(MAX_Nw*sizeof(float));
		x->bindex = (float *) getbytes( (MAX_N+1) * sizeof(float) );
		x->buffer = (float *) getbytes(MAX_N*sizeof(float));
		x->channel = (float *) getbytes((MAX_N+2)*sizeof(float));
		x->output = (float *) getbytes(MAX_Nw*sizeof(float));
		x->bitshuffle = (int *) getbytes((MAX_N*2)*sizeof(int));
		x->trigland = (float *) getbytes((MAX_N*2)*sizeof(float));
		x->c_lastphase_in = (float *) getbytes((MAX_N2+1)*sizeof(float));
		x->c_lastphase_out = (float *) getbytes((MAX_N2+1)*sizeof(float));
		x->lastamp = (float *) getbytes((MAX_N+1) * sizeof(float));
		x->lastfreq = (float *) getbytes((MAX_N+1) * sizeof(float));
		x->local_frame = (float *) getbytes((MAX_N+2)*sizeof(float));
		x->loveboat = (float **) getbytes(x->framecount*sizeof(float *));
		

		/* here we stay with old reallocation approach and pray */
		for(i=0;i<x->framecount;i++){
			x->loveboat[i] = (float *) getbytes(((x->N)+2)*sizeof(float));
			if(x->loveboat[i] == NULL){
				error("memory error");
				return;
			}
			memset((char *)x->loveboat[i],0,(x->N+2)*sizeof(float));
		}
	} else if(initialized == 1) {
		//free and allocate
		oldsize = (oldN+2)*sizeof(float);
		for(i = 0; i < last_framecount; i++){
			freebytes(x->loveboat[i],oldsize) ;
		}
		oldsize = last_framecount*sizeof(float *);
		freebytes(x->loveboat,oldsize);
		x->loveboat = (float **) getbytes(x->framecount*sizeof(float *));  
		for(i=0;i<x->framecount;i++){
			x->loveboat[i] = (float *) getbytes((x->N+2)*sizeof(float));
			if(x->loveboat[i] == NULL){
				error("memory error");
				return;
			}
			memset((char *)x->loveboat[i],0,(x->N+2)*sizeof(float));
		}
	}  
	memset((char *)x->input,0,x->Nw * sizeof(float));
	memset((char *)x->output,0,x->Nw * sizeof(float));
	memset((char *)x->c_lastphase_in,0,(x->N2+1) * sizeof(float));
	memset((char *)x->lastamp,0,(x->N+1)*sizeof(float));
	memset((char *)x->lastfreq,0,(x->N+1)*sizeof(float));
	memset((char *)x->bindex,0,(x->N+1)*sizeof(float));
	memset((char *)x->buffer,0,x->N * sizeof(float));
	if(!x->vector_size){
		post("zero vector size - something is really screwed up here!");
		return;
	}
	for ( i = 0; i < x->table_length; i++ ) {
		x->table[i] = (float) x->N * cos((float)i * TWOPI / (float)x->table_length);
	}	
	x->c_fundamental =  (float) x->R/(float)x->N ;
	x->c_factor_in =  (float) x->R/((float)x->vector_size * TWOPI);
	
	if( x->hi_freq < x->c_fundamental ) {
		x->hi_freq = x->topfreq ;
	}
	x->hi_bin = 1;  
	x->curfreq = 0;
	while( x->curfreq < x->hi_freq ) {
		++(x->hi_bin);
		x->curfreq += x->c_fundamental ;
	}
	
	x->lo_bin = 0;  
	x->curfreq = 0;
	while( x->curfreq < x->lo_freq ) {
		++(x->lo_bin);
		x->curfreq += x->c_fundamental ;
	}
	
	if( x->hi_bin > x->N2)
		x->hi_bin = x->N2 ;
	if(x->lo_bin > x->hi_bin)
		x->lo_bin = x->hi_bin;
	
	x->i_vector_size = 1.0/x->vector_size;
	x->pitch_increment = x->P*x->table_length/x->R;
	
	makewindows( x->Hwin, x->Wanal, x->Wsyn, x->Nw, x->N, x->D);
	init_rdft( x->N, x->bitshuffle, x->trigland);

		  
	x->lock = 0;
}