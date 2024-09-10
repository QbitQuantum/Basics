void P_2_1_3_01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    
    gl::color(0, 0, 0, 0.5f);
    
    mRand.seed(mRandomSeed);
    
    gl::pushMatrices();
    gl::translate(mTileWidth / 2.0f, mTileHeight / 2.0f);
    
    mCircleCount = mMousePos.x / 30.0f + 1.0f;
    
    mEndSize = lmap(float(mMousePos.x), 0.0f, float(getWindowWidth()), mTileWidth / 2.0f, 0.0f);
    mEndOffset = lmap(float(mMousePos.y), 0.0f, float(getWindowHeight()), 0.0f, (mTileWidth - mEndSize)/2.0f);
    
    for (int gridY = 0; gridY <= mTileCountY; gridY++) {
        for (int gridX = 0; gridX <= mTileCountX; gridX++) {
            gl::pushMatrices();
            gl::translate(mTileWidth * gridX, mTileHeight * gridY);
            gl::scale(Vec2f(1.0f, mTileHeight / mTileWidth));
            
            int toggle = mRand.nextInt(4);
            if (toggle == 0) gl::rotate(-90.0f);
            if (toggle == 1) gl::rotate(0.0f);
            if (toggle == 2) gl::rotate(90.0f);
            if (toggle == 3) gl::rotate(180.0f);
            
            for (int i = 0; i < mCircleCount; i++) {
                float diameter = lmap(float(i), 0.0f, mCircleCount - 1.0f, mTileWidth, mEndSize);
                float offset = lmap(float(i), 0.0f, mCircleCount - 1.0f, 0.0f, mEndOffset);
                gl::drawStrokedCircle(Vec2f(offset, 0.0f), diameter / 2.0f);
            }
            
            gl::popMatrices();
        }
    }
    
    gl::popMatrices();
}