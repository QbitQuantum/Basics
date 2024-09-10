IC BOOL OrientToNorm(Fvector& local_norm, Fmatrix33& form, Fvector& hs)
{
    Fvector * ax_pointer= (Fvector*)&form;
    int 	max_proj=0,min_size=0;
    for (u32 k=1; k<3; k++){
    	if (_abs(local_norm[k])>_abs(local_norm[max_proj]))
        	max_proj=k;
        if (hs[k]<hs[min_size])
        	min_size=k; 
    }
    if (min_size!=max_proj) return FALSE;
    if (local_norm[max_proj]<0.f){
    	local_norm.invert();
        ax_pointer[max_proj].invert();
        ax_pointer[(max_proj+1)%3].invert();
    }
    return TRUE;
}