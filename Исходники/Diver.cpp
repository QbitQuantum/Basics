void Diver::debugDrawIndices(const CameraOrtho &camera){
    static const float fontScale = 0.005f;
    
    Vec3f v;
    Vec3f w;
    Vec3f u;
    
    camera.getBillboardVectors(&w, &u);
    v = w.cross(u);
    
    const static Vec2f zero;
    const gl::TextureFontRef& sharedTextureFont = SharedTextureFont::Get();
    float fontDescent = sharedTextureFont->getDescent();
    
    Matrix44f mat;
    Matrix44f rot = Matrix44f::createRotationOnb(u,w,v);
    rot*= Matrix44f::createRotation(Vec3f::zAxis(), M_PI_2);
    rot*= Matrix44f::createScale(Vec3f(fontScale,fontScale,fontScale));
    
    gl::enableAlphaTest();
    gl::enableAlphaBlending();

    glColor3f(1,1,1);
    int i = -1;
    while(++i < mPoints.size()){
        mat.setToIdentity();
        mat *= Matrix44f::createTranslation(mPoints[i]);
        mat *= rot;
        
        string stringTexCoord = toString(mTexcoords[i]);
        Vec2f  stringSize = sharedTextureFont->measureString(stringTexCoord);
        
        glPushMatrix();
        glMultMatrixf(&mat[0]);
        glColor4f(0,0,0,0.75f);
        gl::drawSolidRect(Rectf(0,fontDescent,stringSize.x, stringSize.y * -1+fontDescent));
        glColor3f(1,1,1);
        sharedTextureFont->drawString(stringTexCoord, zero);
        glPopMatrix();
    }
    
    gl::disableAlphaBlending();
    gl::disableAlphaTest();
}