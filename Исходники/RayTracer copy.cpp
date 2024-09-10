// Shading
Color diffuseTerm(Color kd, Color intens, Vector4f normal, Vector4f light){
    float dotProduct = light.adjoint()*normal;
    dotProduct = max(dotProduct,(float)0);
    if (dotProduct == (float)0) {
        return Color(0.0f, 0.0f, 0.0f);
    } 
    else{
        return (kd*intens)*dotProduct;
    }
};