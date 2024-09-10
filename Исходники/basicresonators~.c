//#define MAXMAXVECTOR 4096
// double precision interpolating (smooth) with input
void diresonators_perform64(t_resonators *x, 
			  t_object *dsp64, 
			  double **ins, 
			  long numins, 
			  double **outs, 
			  long numouts, 
			  long sampleframes, 
			  long flags, 
			  void *userparam)
{
	const double *in = *ins;
	t_resonators *op = x;
	double *out = *outs;
	long n = sampleframes;
	int nfilters = op->nres;
	register	double yn,yo;
	int i, j;
	double rate = 1.0/n;
	
	if(op->b_obj.z_disabled){
		return;
	}
    
#ifdef SQUASH_DENORMALS
	static int sq;
	if(!sq){
		printf("squashing denormals\n");
		sq++;
	}
#if defined( __i386__ ) || defined( __x86_64__ )
	int oldMXCSR = _mm_getcsr(); // read the old MXCSR setting
	int newMXCSR = oldMXCSR | 0x8040; // set DAZ and FZ bits
	_mm_setcsr( newMXCSR );	 // write the new MXCSR setting to the MXCSR
#endif
#endif
	{
		dresdesc *f = op->dbase;
		for(j=0;j<n;++j)
			out[j] = 0.0;
	
		for(i=0;i< nfilters ;++i)
			{
				register double b1=f[i].o_b1, b2=f[i].o_b2, a1=f[i].o_a1;
				double a1inc = (f[i].a1-f[i].o_a1) *  rate;
				double b1inc = (f[i].b1-f[i].o_b1) *  rate;
				double b2inc = (f[i].b2-f[i].o_b2) *  rate;

	
				yo= f[i].out1;
				yn =f[i].out2;
				for(j=0;j<n;++j)
					{
						double x = yo;
						yo = b1*yo + b2*yn + a1*in[j];	

						out[j] += yo;

						yn = x;
						a1 += a1inc;
						b1 += b1inc;
						b2 += b2inc;
					}

				f[i].o_a1 = f[i].a1;
				f[i].o_b1 = f[i].b1;
				f[i].o_b2 = f[i].b2;
				f[i].out1= yo;
				f[i].out2 = yn;	
			}
	}
#ifdef SQUASH_DENORMALS
#if defined( __i386__ ) || defined( __x86_64__ )
	_mm_setcsr(oldMXCSR);
#endif
#endif
}