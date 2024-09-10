// Check if a point is within the ball at the end of the chain
// If so, set dragged = true;
void Chain::contains( Vec2f pos )
{
//    float d = dist(x,y,tail.x,tail.y);
	float d = pos.distance( mTail->getPosition() );
    if( d < mRadius ) {
		mOffset.x = mTail->getPosition().x - pos.x;
		mOffset.y = mTail->getPosition().y - pos.y;
		mTail->makeFixed();
		mDragged = true;
    }
}