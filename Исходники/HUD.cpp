void CHUD::touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("Multitouch Moved Began");

	for (auto touch : touches)
	{
		if (touch != nullptr)
		{
			auto tap = touch->getLocation();

			//moves the player based on the direction gotten from the movement touchPad
			if (movePad->GetTouch() != nullptr && movePad->GetTouch() == touch)
			{
				Point nextPos = tap;
				movePad->GetSprite()->setPosition(tap);

				float moveDirX = movePad->GetSprite()->getPositionX() - movePad->GetOriginalPos().x;
				float moveDirY = movePad->GetSprite()->getPositionY() - movePad->GetOriginalPos().y;

				Vec2* moveDir = new Vec2(moveDirX, moveDirY);
				moveDir->normalize();
				player->SetVelocity(moveDir->x * player->GetMoveSpeed(), moveDir->y * player->GetMoveSpeed());
			}

			//shoots in the direction provided by the shooting touchPad
			if (shootPad->GetTouch() != nullptr && shootPad->GetTouch() == touch)
			{
				//sets weapon to active
				theWeapon->SetActive(true);

				Point nextPos = tap;
				shootPad->GetSprite()->setPosition(tap);

				float shootDirX = shootPad->GetSprite()->getPositionX() - shootPad->GetOriginalPos().x;
				float shootDirY = shootPad->GetSprite()->getPositionY() - shootPad->GetOriginalPos().y;

				Vec2* shootPos = new Vec2(shootDirX, shootDirY);

				float angleToRot = atan2(shootPos->y, shootPos->x);
				angleToRot = -angleToRot * (180 / 3.14159);

				if (angleToRot < 0)
				{
					angleToRot = 360 - (-angleToRot);
				}

				player->setRotation(angleToRot);
				player->SetShootVec(shootPos);
			}
		}
	}
}