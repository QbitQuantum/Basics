static void tanh_float(t_tanh *x, t_float f)
{
    /* CHECKME large values */
    outlet_float(((t_object *)x)->ob_outlet, x->x_value = tanhf(f));
}