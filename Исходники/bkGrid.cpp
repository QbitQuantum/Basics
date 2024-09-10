void cBkGrid::update(sf::Time dt)
{    
    mAccumulator += dt;
    if ( mAccumulator >= mTimer )
    {
        mAccumulator = sf::Time::Zero;
        adjustColor();
    }
    
    // Horizontal lines' velocity
    sf::Vector2f    dVhori { 0.0, mVelocity.y };
    dVhori *= dt.asSeconds();
    for (auto i = 0; i < gGridSize.y * 2; ++i)
    {
        mPoints[i].position += dVhori;
        
        if (mPoints[i].position.y < 0)
        {
            mPoints[i].position.y += mSize;
        }
        if (mPoints[i].position.y > mSize)
        {
            mPoints[i].position.y -= mSize;
        }
    }
    
    // Vertical lines' velocity
    sf::Vector2f    dVvert { mVelocity.x, 0.0 };
    dVvert *= dt.asSeconds();
    for (auto i = mFirstVline; i < gGridPointCount; ++i)
    {
        mPoints[i].position += dVvert;
        
        if (mPoints[i].position.x < 0)
        {
            mPoints[i].position.x += mSize;
        }
        if (mPoints[i].position.x > mSize)
        {
            mPoints[i].position.x -= mSize;
        }
    }
    
    // Now rotate
    mRot += mSpin * dt.asSeconds();
    if ( mRot < -360 ) mRot += 360;
    if ( mRot > 360 ) mRot -= 360;
    setRotation(mRot);
    
    // Adjust position
    setPosition(mHalfSize / 2.0, mHalfSize / 2.0);
}