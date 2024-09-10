pixel_t min_layer_mode_fun::operator()( const pixel_t& back, const pixel_t& front) const
{
    __m128 b = _mm_load_ps( reinterpret_cast<const float*>( &back));
    __m128 f = _mm_load_ps( reinterpret_cast<const float*>( &front));

    f = lerp( _mm_min_ps( f, b), b);
    float *p = reinterpret_cast<float*>( &f);
    return pixel_t( p[0], p[1], p[2], p[3]);
}