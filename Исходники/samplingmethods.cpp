// analytical marginal inverse CDF for inverse squared sampling points vrl, phi is angle between camera vector and vrl vector
float invSqrCDF(float r,float phi,float h, float v0, float v1){
    return h*sinhf(Lerp(r,A(v0, phi, h), A(v1,phi,h)))/sinf(phi);
}