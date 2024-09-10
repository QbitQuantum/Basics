void GesichtertauschApp::draw() {
    
    glClearColor( 0, 0, 0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    if ( ! mCameraTexture ) {
        return;
    }
        
//    gl::setMatricesWindow( getWindowSize() ),
    gl::setMatricesWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    gl::enableAlphaBlending();
    glScalef(-1.0, 1.0, 1.0);
    glTranslatef(-WINDOW_WIDTH, 0, 0);
    
    /* shader */
    // TODO make this more opt'd
    if (ENABLE_SHADER) {
        mShader.bind();
        const int STEPS = 32;
        float mThresholds[STEPS];// = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
        for (int i=0; i < STEPS; ++i) {
            mThresholds[i] = float(i) / float(STEPS - 1);
        }
        mShader.uniform("thresholds", mThresholds, STEPS);   
        mShader.uniform( "tex0", 0 );
    }

    /* draw the webcam image */
    gl::color( BACKGROUND_IMAGE_COLOR );
    gl::draw( mCameraTexture, Rectf(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) );
    mCameraTexture.disable();
    
    /* normalize texture coordinates */
    Vec2f mNormalizeScale = Vec2f(1.0 / float(WINDOW_WIDTH), 1.0 / float(WINDOW_HEIGHT));
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glScalef(mNormalizeScale.x, mNormalizeScale.y, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    /* draw orgiginal faces */
    if (mEntities.size() < 2) {
        gl::enableAlphaBlending();
        mCameraTexture.enableAndBind();
        for( vector<FaceEntity>::const_iterator mIter = mEntities.begin(); mIter != mEntities.end(); ++mIter ) {
            drawEntity(*mIter, FACE_COLOR_UNO);
        }    
        mCameraTexture.disable();
        gl::disableAlphaBlending();
    }
    
    /* HACK // swap faces */
    mCameraTexture.enableAndBind();
    if (mEntities.size() >= 2) {
        const FaceEntity A = mEntities[0];
        const FaceEntity B = mEntities[1];
        if (A.visible && B.visible) {
            FaceEntity mEntityA = FaceEntity();
            FaceEntity mEntityB = FaceEntity();
            
            mEntityA.border = B.border;
            mEntityB.border = A.border;
            mEntityA.slice = A.slice;
            mEntityB.slice = B.slice;
            mEntityA.visible = A.visible;
            mEntityB.visible = B.visible;
            mEntityA.ID = A.ID;
            mEntityB.ID = B.ID;
            
            drawEntity(mEntityA, FACE_COLOR_DUO);
            drawEntity(mEntityB, FACE_COLOR_DUO);
        }
    }

    /* restore texture coordinates */
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    mCameraTexture.disable();

    /* shader */
    if (ENABLE_SHADER) {
        mShader.unbind();
    }

    /* mask */
    float MASK_LEFT_TOP = 1;
    float MASK_LEFT_BOTTOM = 1;
    float MASK_RIGHT_TOP = 1;
    float MASK_RIGHT_BOTTOM = 1;
    
    gl::color(0, 0, 0, 1);

    Path2d mPathLeft;
    mPathLeft.moveTo(0, 0);
    mPathLeft.lineTo(MASK_LEFT_TOP, 0);
    mPathLeft.lineTo(MASK_LEFT_BOTTOM, WINDOW_HEIGHT);
    mPathLeft.lineTo(0, WINDOW_HEIGHT);
    mPathLeft.close();    
    gl::drawSolid(mPathLeft);
    
    Path2d mPathRight;
    mPathRight.moveTo(WINDOW_WIDTH, 0);
    mPathRight.lineTo(WINDOW_WIDTH-MASK_RIGHT_TOP, 0);
    mPathRight.lineTo(WINDOW_WIDTH-MASK_RIGHT_BOTTOM, WINDOW_HEIGHT);
    mPathRight.lineTo(WINDOW_WIDTH, WINDOW_HEIGHT);
    mPathRight.close();    
    gl::drawSolid(mPathRight);

    /* draw entity IDs */
    const bool DRAW_ENTITY_ID = false;
    if (DRAW_ENTITY_ID) {
        for( vector<FaceEntity>::const_iterator mIter = mEntities.begin(); mIter != mEntities.end(); ++mIter ) {
            const FaceEntity mEntity = *mIter;
            std::stringstream mStr;
            mStr << mEntity.ID;
            gl::drawStringCentered(mStr.str(), mEntity.border.getCenter(), Color(1, 0, 0), mFont);
        }    
    }
        
    /* gooey */
    mGui->draw();
}