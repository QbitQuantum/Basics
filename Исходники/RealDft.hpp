void opendsp::RealDft<Sample_T>::invert(opendsp::Signal<opendsp::Complex<Sample_T>>& in, opendsp::Signal<Sample_T>& out)
{
    OPEN_DSP_COND_WARNING(calcOutputLength(out.getLength()) != in.getLength(), "invalid lengths");
    double factor = 2 * M_PIl / out.getLength();
    for (uint k=0 ; k<out.getLength(); k++)
    {
        Complex<Sample_T> result(0,0);
        Complex<Sample_T> mul;
        for (uint n=0 ; n<out.getLength() ; ++n)
        {
            Complex<Sample_T> root(cos(n * k * factor), sin(n * k * factor) );
            if(n < in.getLength())
            {
                mul = in[n];
            }
            else
            {
                mul = in[out.getLength() - n];
                mul.conjugate();
            }
            root *= mul;
            result += root;
        }
        out[k] = result.real / out.getLength();
    }
}