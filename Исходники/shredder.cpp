float AltGammaLogPdf::f(float mean, float shape, float x)
{
    float scale =  mean / shape;
    float part = (shape - 1.0) * fastlog(x) - x / scale;
    return -(lgammaf(shape) + shape * fastlog(scale)) + part;
}