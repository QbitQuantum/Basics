__m128 _mm_parteentera_ps(__m128 a){//calcula parte  para evtar problemas en la implementacion de la funcion _mm_pow_ps
    float f[4] __attribute__((aligned(16)));
    _mm_store_ps(f,a);
    
    f[0]=(int) f[0];
    f[1]=(int) f[1];
    f[2]=(int) f[2];
    f[3]=(int) f[3];

    return _mm_load_ps(&f[0]);
}