Vec2 calculateCosASinAOfVec1ToVec2(const Vec2 &vec1,const Vec2 &vec2)
//return {cos(vec1,vec2),sin(vec1,vec2)}
{
    float cosA= vec1.dot(vec2) / (vec1.getLength() * vec2.getLength());
    float signalOfSinA;
    {
        float _vec1[3]={vec1.x,vec1.y,0};
        float _vec2[3]={vec2.x,vec2.y,0};
        float _rs[3];
        __cross(_vec1, _vec2, _rs);
        if (_rs[2] == 0) {
            signalOfSinA = 0;
        }else if(_rs[2] > 0){
            signalOfSinA = 1;
        }else{
            signalOfSinA = -1;
        }
    }
    float sinA = signalOfSinA*sqrtf(MAX(0,1-cosA*cosA));
    return Vec2(cosA,sinA);
}