void BlacknWhiteLayer::calReflectedRay_Black(){
    Vec2 vec1 = paddleNode->convertToWorldSpace( Vec2(paddle2->getBoundingBox().getMaxX(),paddle2->getBoundingBox().getMaxY()) );
    Vec2 vec2 = paddleNode->convertToWorldSpace( Vec2(paddle2->getBoundingBox().getMinX(),paddle2->getBoundingBox().getMaxY()) );
    
    vec1.subtract(vec2);
    Vec2 normalVec = vec1;
    normalVec.normalize();
    
    
    float x_1 = m_x_Black + 357 * normalVec.x;
    float y_1 = m_y_Black + 357 * normalVec.y;
    float x_2 = m_x_Black;
    float y_2 = m_y_Black;
    float x_0 = monster->getPosition().x;
    float y_0 = monster->getPosition().y;
    
    
    float A_ = y_2 - y_1;
    float B_ = x_1 - x_2;
    float C_ = x_2 * y_1 - x_1 * y_2;
    float k_ = -2 * (A_ * x_0 + B_ * y_0 + C_) / (A_ * A_ + B_ * B_);
    
    if (x_2 - x_1 != 0 && y_2 - y_1 != 0) {
        mReflectX_Black = x_0 + k_ * A_;
        mReflectY_Black = y_0 + k_ * B_;
    }
}