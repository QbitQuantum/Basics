void dynamicdsp_threadprocess(t_dynamicdsp *x, void **sig_outs, void *temp_mem_ptr, t_ptr_uint temp_mem_size, long vec_size, long thread_num, long num_active_threads)
{
    long num_sig_outs = x->num_sig_outs;
    
    // Turn off denormals
    
#if defined( __i386__ ) || defined( __x86_64__ )
    int oldMXCSR = _mm_getcsr();						// read the old MXCSR setting
    _mm_setcsr(oldMXCSR | 0x8040);						// write the new MXCSR setting setting DAZ and FZ bits
#endif
    
    // Zero outputs
    
    for (long i = 0; i < num_sig_outs; i++)
        memset(sig_outs[i], 0, sig_size * vec_size);
    
    if (x->manual_threading)
    {
        for (long i = 0; i < x->slots->size(); i++)
            x->slots->processIfThreadMatches(i, temp_mem_ptr, sig_outs, temp_mem_size, thread_num, num_active_threads);
    }
    else
    {
        long size = x->slots->size();
        long index = (thread_num * (size / num_active_threads)) - 1;
        for (long i = 0; i < size; i++)
        {
            if (++index >= size)
                index -= size;
            
            x->slots->processIfUnprocessed(i, temp_mem_ptr, sig_outs, temp_mem_size);
        }
    }
    
    // return denormals to previous state 
    
#if defined( __i386__ ) || defined( __x86_64__ )	
    _mm_setcsr(oldMXCSR);	
#endif
}