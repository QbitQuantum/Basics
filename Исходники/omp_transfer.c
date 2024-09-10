inline void transfer_omp_loop_nontemp(uintptr_t rbuf, uintptr_t sbuf, size_t size, HMPI_Request recv_req, HMPI_Request send_req){
    int N_DOUBLES_PER_BLOCK = (64/sizeof(char)) ;
    size_t total = size / 64 ;
    int i = 0;
//#pragma vector nontemporal
#pragma omp parallel for
    for (i = 0; i < total; i++) {
        __m512d v_b = _mm512_load_pd(sbuf+ N_DOUBLES_PER_BLOCK*i);
        _mm512_storenrngo_pd(rbuf+ N_DOUBLES_PER_BLOCK*i, v_b);
    }

}