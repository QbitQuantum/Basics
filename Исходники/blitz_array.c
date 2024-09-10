void bbArraySort( BBArray *arr,int ascending ){
	int n;
	void *p;
	n=arr->scales[0]-1;
	if( n<=0 ) return;
	p=BBARRAYDATA(arr,arr->dims);
	if( ascending ){
		switch( arr->type[0] ){
		case 'b':_qsort_b( (unsigned char*)p,(unsigned char*)p+n );break;
		case 's':qsort_s( (unsigned short*)p,(unsigned short*)p+n );break;
		case 'i':qsort_i( (int*)p,(int*)p+n );break;
		case 'l':qsort_l( (BBInt64*)p,(BBInt64*)p+n );break;
		case 'f':qsort_f( (float*)p,(float*)p+n );break;
		case 'd':qsort_d( (double*)p,(double*)p+n );break;
		case '$':case ':':qsort_obj( (BBObject**)p,(BBObject**)p+n );break;
		}
	}else{
		switch( arr->type[0] ){
		case 'b':qsort_b_d( (unsigned char*)p,(unsigned char*)p+n );break;
		case 's':qsort_s_d( (unsigned short*)p,(unsigned short*)p+n );break;
		case 'i':qsort_i_d( (int*)p,(int*)p+n );break;
		case 'l':qsort_l_d( (BBInt64*)p,(BBInt64*)p+n );break;
		case 'f':qsort_f_d( (float*)p,(float*)p+n );break;
		case 'd':qsort_d_d( (double*)p,(double*)p+n );break;
		case '$':case ':':qsort_obj_d( (BBObject**)p,(BBObject**)p+n );break;
		}
	}
}