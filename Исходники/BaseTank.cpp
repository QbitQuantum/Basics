void BaseTank::Rebound(Vector2D position)
{
	//DEBUG: Alert on colliding.
	//cout << "Collision" << endl;

	//We need to rebound, but which direction?
	Vector2D newHeading = GetCentralPosition()-position;
	newHeading.Normalize();

	//Flip the y coordinate because of the 0,0 position of SDL.
	newHeading.y *= -1.0f;

	//Set new velocity.
	mVelocity = newHeading*-kReboundSpeed;

	//Cut the speed.
	mCurrentSpeed = 0.0f;
}