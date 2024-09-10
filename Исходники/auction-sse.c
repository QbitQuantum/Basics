void dist_price_sse(float *dist, float *prices, float *dist_price) {
    __m128 asse, bsse, csse;
    int i;

    for (i = 0; i < GRAPHSIZE; i += SSE_FOUR) {
        asse = _mm_load_ps(&dist[i]);
        bsse = _mm_load_ps(&prices[i]);
        csse = _mm_add_ps (asse, bsse);
        _mm_store_ps(&dist_price[i], csse);
    }
}