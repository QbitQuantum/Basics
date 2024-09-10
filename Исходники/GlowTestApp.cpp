void GlowTestApp::draw()
{
    // clear out the window with black

    gl::clear( Color( 0, 0, 0 ) );


    // 일단 Fbo 를 하나 만들어서 그린다. 드로잉 컨텍스트가 완전 새로운게 되는듯? Fbo 에 대해 더 공부해볼 필요가 있당...
    // 뭔가 카메라 설정도 마구마구 해서

    mNormalFbo.bindFramebuffer();
    gl::clear( ColorA(0, 0, 0, 0 ) );
    gl::color(1.0, 1.0, 1.0);
    gl::drawSphere(Vec3f(200,100, 0), 50.0);
    gl::drawSphere(Vec3f(500,100, 0), 50.0);
    mNormalFbo.unbindFramebuffer();






    // 블러 때리는용 Fbo 를 만들어서 또 그린다. (지금은 그냥 오리지널만 써도 될듯.)

    mGlowFbo.bindFramebuffer();
    gl::setMatricesWindowPersp(getWindowSize());
    gl::clear( ColorA(0, 0, 0, 0 ) );
    gl::color(0.4, 0.2, 0.5);
    gl::drawSphere(Vec3f(200,100, 0), 50.0);


    mGlowFbo.unbindFramebuffer();


    // 텍스쳐 블러시킬 Fbo 를 만든다. 텍스쳐가 정면에 나와야 되니까 카메라 세팅을 신더 기본으로 해준다.
    // 블러 때리는용 Fbo 를 텍스쳐화 시켜 그린다.
    mBlurFbo.bindFramebuffer();
    gl::clear( ColorA(0, 0, 0, 0 ) );

    gl::setMatricesWindowPersp(getWindowSize());

    mGlowFbo.getTexture().bind(1);  // 얘를 바인딩 해야한다. 그래서 sampler 로 전달하구, 텍스쳐로 그려내야돼.
    mBlurShader.bind();
    mBlurShader.uniform("GlowFboTex", 1);   // glowfbo 를 전사한 텍스쳐를 sampler1d 로 보낸다.
    mBlurShader.uniform("sampleOffset", Vec2f(0.7, 0.3) * ( 3.0f / getWindowWidth() ) );

    gl::drawSolidRect( Rectf(0.0, 0.0, getWindowWidth(), getWindowHeight() ) );
    mBlurShader.unbind();
    mGlowFbo.getTexture().unbind();
    mBlurFbo.unbindFramebuffer();

    //  섞어보자.


    mMultiplyFbo.bindFramebuffer();
    gl::clear( ColorA(0, 0, 0, 0 ) );
    gl::setMatricesWindowPersp(getWindowSize());

    // 두가지 합칠 소스 가져오기
    mNormalFbo.getTexture().bind(1);
    mBlurFbo.getTexture().bind(2);


    mMultiShader.bind();
    mMultiShader.uniform("Tex1", 1);
    mMultiShader.uniform("Tex2", 2);
    gl::drawSolidRect( Rectf(0.0, 0.0, getWindowWidth(), getWindowHeight() ) );
    mMultiShader.unbind();
    mMultiplyFbo.unbindFramebuffer();

    // 최종적으로 블러된 Fbo 를 전사한다.


    //gl::draw(mMultiplyFbo.getTexture());


    // 뒤집힘 해결 테스트

    gl::drawSphere(Vec3f(200,100, 0), 50.0);
    gl::drawSphere(Vec3f(500,100, 0), 50.0);

    gl::draw(mNormalFbo.getTexture());


}