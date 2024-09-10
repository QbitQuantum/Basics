void DeferredRenderingApp::drawDepthParticles() const
{
    gl::enableAdditiveBlending();
    
    //this where typically a particle engine would go. For now lets just draw some "earths"
    glColor4ub(255, 255, 255, 160);
    mEarthTex.bind();
    gl::drawCube(Vec3f(3.0f, 2.0f, 8.0f), Vec3f(3.0f, 3.0f, 3.0f));
    gl::drawCube(Vec3f(1.0f, 5.0f, -3.0f), Vec3f(3.0f, 3.0f, 3.0f));
    gl::drawCube(Vec3f(-3.0f, 3.0f, 4.0f), Vec3f(3.0f, 3.0f, 3.0f));
    gl::drawCube(Vec3f(-2.0f, 4.0f, 7.0f), Vec3f(3.0f, 3.0f, 3.0f));
    mEarthTex.unbind();
    glColor4ub(255, 255, 255, 255);
}