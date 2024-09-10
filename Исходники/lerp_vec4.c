t_vec4		lerp_vec4_1(t_vec4 a, t_vec4 b, t_float x, t_float max)
{
    a.x = LERP(a.x, b.x, x, max);
    a.y = LERP(a.y, b.y, x, max);
    a.z = LERP(a.z, b.z, x, max);
    a.w = LERP(a.w, b.w, x, max);
    return (a);
}