//-------------------------------------------------------------------------------------
void EntitySimple::addTime(Real deltaTime)
{
	if(blocktime_ <= 0.f)
	{
		Ogre::Vector3 currpos = getLastPosition();
		if(kbe_playerID() != mID)
		{
			Ogre::Vector3 movement = destPos_ - currpos;
			float speed = mMoveSpeed * deltaTime;

			movement.y = 0.f;

			Real mlen = movement.length();

			if(mlen < speed || (mLastAnimName != "Run" && mlen <= 1.0f))
			{
				if (mLastAnimName == "Run")
				{
					float y = currpos.y;
					currpos = destPos_;
					currpos.y = y;

					playAnimation("Idle");
				}
			}
			else
			{
				movement.normalise();

				// ÒÆ¶¯Î»ÖÃ
				movement *= speed;
				currpos += movement;
				
				playAnimation("Run");
			}
		}

		blocktime_ = 0.f;
	
		setPosition(currpos.x, currpos.y, currpos.z);
		KBEntity::addTime(deltaTime);
	}
	else
	{
		blocktime_ -= deltaTime;
		playAnimation("Block");
	}

	if(mLastAnims)
		mLastAnims->addTime(deltaTime);
}