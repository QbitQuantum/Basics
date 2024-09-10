static void *sinh_new(t_floatarg f)
{
    t_sinh *x = (t_sinh *)pd_new(sinh_class);
    /* CHECKME large values */
    x->x_value = sinhf(f);
    outlet_new((t_object *)x, &s_float);
    return (x);
}