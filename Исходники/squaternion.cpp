mat33 getMatrix(vec3 vec, double alpha)
{
    mat33 res;

    mat33 I;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            I(i,j)=(i==j)?1.0:.0;
        }
    }

    vec.normalize();
    mat33 E=crossProductMat(vec);
    //print(E);
    //print(I);
    //std::cout<<vec.transpose()<<"\n";
    res=cos(alpha)*I+(1-cos(alpha))*vec*vec.transpose()-sin(alpha)*E;
    return res;
}