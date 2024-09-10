    void PretzelColorPicker::setup(){
        
        bDragging = false;
        
        // load images
        mArrowTex = mGlobal->getTextureFromSkin( Rectf(28, 0, 42, 12) );
        mCrosshairTex = mGlobal->getTextureFromSkin( Rectf(44, 0, 52, 8) );
        
        mHueSurf = ci::Surface( loadImage( loadResource(PRETZEL_HSL_BAR) ) );
        mHueStrip = gl::Texture::create( mHueSurf );
        
        mBoxFbo = gl::Fbo::create(256, 256);
        mBoxShader = gl::GlslProg::create( loadAsset("shaders/colorpicker/colorpicker.vert"), loadAsset("shaders/colorpicker/colorpicker.frag") );
        redrawBox();
        
        // set rects
        mCollapsedRect.set(0, 0, mBounds.getWidth(), 23);
        mExpandedRect.set( 0, 0, mBounds.getWidth(), 23+150);
        
        int boxW = 36, boxH = 19;
        mColorPickRect = Rectf( mBounds.x2 - boxW, 0, mBounds.x2, boxH );
        mColorPickRect.offset( vec2(-10, -1) );
        
        int swatchSize = 150;
        mColorSwatchRect = Rectf(mColorPickRect.x2 - swatchSize, mColorPickRect.y2, mColorPickRect.x2, mColorPickRect.y2 + swatchSize);
        mColorSwatchRect.offset( vec2(-1,1) );
        
        Surface checkerSurf( mColorPickRect.getWidth(), mColorPickRect.getHeight(), false);
        ip::fill(&checkerSurf, Color(1,1,1) );
        
        // draw the checkboard pattern
        gl::color(Color::white());
        gl::drawSolidRect(mColorPickRect);
        for( int k=0; k<mColorPickRect.getHeight(); k+=4){
            int i = ((k/4)%2) * 4;
            for( ; i<mColorPickRect.getWidth(); i+=8){
                Rectf tmp(0,0,4,4);
                tmp.offset( vec2(i, k) );
                ip::fill(&checkerSurf, Color::gray(198.0/255.0), Area(tmp));
            }
        }

        mCheckerPat = gl::Texture::create(checkerSurf);
        
        mCrosshairPos = vec2(1,0);
    }