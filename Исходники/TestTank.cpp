void TestTank::Render()
{


	//Call parent render.
	BaseTank::Render();

	//Draw the left cannon.

	if (mDrawTarget)
		mTargetSprite->Render(Vector2D(mTargetPos.x + mTargetSprite->GetWidth() / 2, mTargetPos.y + mTargetSprite->GetHeight() / 2)); //+ 16


																																	  //DrawDebugCircle(Vector2D(GetCentrePosition().x - mHeading.x * 20, GetCentrePosition().y - mHeading.y* 20), 10);

	Vector2D normVel = Vec2DNormalize(mVelocity);

	DrawDebugCircle(Vector2D(GetCentrePosition().x + normVel.x * 20, GetCentrePosition().y + normVel.y * 20), 10);
	if (mShowingDebug)
	{

		for (int i = 50; i > 44; i--)
		{
			DrawDebugCircle(Vector2D(mMouseX, mMouseY), i);
		}
		// drawing the heading vector line
		//Start position will be the front of the tank
		//the End position will be the tanks heading vector 
		SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
		//heading end = centreposition - mHeading * by some length
		SDL_RenderDrawLine(mRenderer, GetCentrePosition().x, GetCentrePosition().y, GetCentrePosition().x - mHeading.x * 50, GetCentrePosition().y - mHeading.y * 50);

		//Render the Steering Force
		SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(mRenderer, GetCentrePosition().x, GetCentrePosition().y, GetCentrePosition().x + mSteeringForce.x * 5, GetCentrePosition().y + mSteeringForce.y * 5);
	}

	Vector2D ahead = Vec2DNormalize(mVelocity);
	if (ahead.Length() == 0)
		ahead = mHeading;

	Vector2D cenPos = GetCentralPosition();
	Vector2D aheadDistance = cenPos + ahead * 30;
	DrawDebugCircle(Vector2D(aheadDistance.x, aheadDistance.y), 5);


}