// Shading
Vector4f diffuseTerm(Vector4f kd, Vector4f intens, Vector4f normal, Vector4f light){
    float dotProduct = light.adjoint()*normal;
    dotProduct = max(dotProduct,(float)0);
    if (dotProduct == (float)0) {
        return Vector4f(0,0,0,0);
    } 
    else{
        return times(kd,intens).adjoint()*dotProduct;
    }
};