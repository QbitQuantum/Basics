// substitute STDampedSpringStep's r with ri (i=imaginary unit),
// you get over-damping equation.
float STOverDampedSpringStep(float value){
    const float r=3.3f; // [???]
    if(value<0.f)value=0.f;
    if(value>1.f)value=1.f;

    float theta=r*value;
    float v=1.f;
    float tt=(value*(value-2.f)+1.f);
    v-=tt*coshf(theta);
    v-=(2.f/r)*(value*(value-2.f)+1.f)*sinhf(theta);
    return v;
}