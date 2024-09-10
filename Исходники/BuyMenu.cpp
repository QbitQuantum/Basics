//------------------------------------------------------------------------------------------------
void BuyMenu::Update(float dt)
{
	int team = mPlayer->mTeam;
	if (mEngine->GetButtonClick(PSP_CTRL_CIRCLE)) {
		Disable();
		//mIsActive = false;
		return;
	}
	if (mEngine->GetButtonClick(PSP_CTRL_TRIANGLE) && mCategoryIndex != MAIN) {
		mCategoryIndex = MAIN;
	}

	if (mEngine->GetButtonClick(PSP_CTRL_CROSS)) {
		if (mSelectedIndex != -1) {
			if (mCategoryIndex == MAIN) {
				mCategoryIndex = mCategories[team][mCategoryIndex].buttons[mSelectedIndex].id;
				if (mIsOldStyle) {
					mSelectedIndex = 0;
				}
			}
			else {	
				mChoice = mCategories[team][mCategoryIndex].buttons[mSelectedIndex].id;
				mIsSelected = true;
				Disable();
			}
		}
		else {
			if (mCategoryIndex == MAIN) {
				mChoice = -1;
				mIsSelected = true;
				Disable();
			}
		}
	}

	if (!mIsOldStyle) {
		float aX = mEngine->GetAnalogX()-127.5f;
		float aY = mEngine->GetAnalogY()-127.5f;
		
		int size = mCategories[team][mCategoryIndex].buttons.size();
		if (aX >= 20 || aX <= -20 || aY >= 20 || aY <= -20) {
			angle = atan2f(aX,aY) + M_PI;
			mSelectedIndex = (int)(size*angle/(2*M_PI)+0.5f);
			if (mSelectedIndex == size) {
				mSelectedIndex = 0;
			}
		}
		else {
			mSelectedIndex = -1;
		}
	}
	else {
		int size = mCategories[team][mCategoryIndex].buttons.size();
		if (mEngine->GetButtonClick(PSP_CTRL_UP)) {
			mSelectedIndex--;
			if (mCategoryIndex == MAIN) {
				if (mSelectedIndex < -1) mSelectedIndex = size-1;
			}
			else {
				if (mSelectedIndex < 0) mSelectedIndex = size-1;
			}
		}
		else if (mEngine->GetButtonClick(PSP_CTRL_DOWN)) {
			mSelectedIndex++;
			if (mCategoryIndex == MAIN) {
				if (mSelectedIndex >= size) mSelectedIndex = -1;
			}
			else {
				if (mSelectedIndex >= size) mSelectedIndex = 0;
			}
		}
	}
}