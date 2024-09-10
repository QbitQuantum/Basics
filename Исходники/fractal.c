fractal_context *
make_fractalc (const int formula, float wi, float he)
{
    fractal_context *new_ctxt;

#ifdef __GNUC__
#ifdef __i386__
#ifndef NOASSEMBLY
    _control87 (PC_64 | MCW_EM | MCW_RC, MCW_PC | MCW_EM | MCW_RC);
#endif
#endif
#endif
    new_ctxt = (fractal_context *) calloc (1, sizeof (fractal_context));
    if (new_ctxt == NULL)
        return 0;
    new_ctxt->windowwidth = wi;
    new_ctxt->periodicity = 1;
    new_ctxt->windowheight = he;
    new_ctxt->maxiter = DEFAULT_MAX_ITER;
    new_ctxt->bailout = DEFAULT_BAILOUT;
    new_ctxt->coloringmode = 0;
    new_ctxt->intcolor = 0;
    new_ctxt->outtcolor = 0;
    new_ctxt->slowmode = 0;
    new_ctxt->range = 3;
    new_ctxt->angle = 0;
    set_formula (new_ctxt, formula);
    return (new_ctxt);
}