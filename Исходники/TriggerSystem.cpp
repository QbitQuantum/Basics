void TriggerSystem::Update(double pDeltaTime)
{
	if (mCreateNextLevel)
	{
		mCurrentLevel++;
		//if we have enough maps
		if (mMapNames.size() - 1 >= mCurrentLevel)
		{
			LevelManager::GetInstance()->GenerateWorld(mMapNames[mCurrentLevel]);
		}
		mCreateNextLevel = false;
	}



	EntityManager* tEntMan = tEntMan->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();

	int tMaxEnt = tEntMan->GetLastEntity();

	mNumOfBallsActive = 0;
	mNumOfGoalBlocksActive = 0;

	//check how many balls we have active and goals cause why not
	for (int i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, LabelType))
		{
			Label tLabel = GetComponent<LabelComponent>(i)->mLabel;

			if (tLabel == Label::Ball)
			{
				mNumOfBallsActive++;
			}
			else if (tLabel == Label::GoalBlock)
			{
				mNumOfGoalBlocksActive++;
			}
		}
	}

	//if no goal blocks, we go to next map, even if we can do this by event, we might explode or something that doesn't trigger, not sure how we want it
	if (mNumOfGoalBlocksActive == 0 && mNumOfBallsActive != 0)
	{
		//DEBUG
#ifdef _DEBUG
		cout << "WARNING - MAP HAS NO GOAL LEFT, EITHER WRONG IN MAP OR SOME REALLY WIERD BUG" << endl;
#endif
		//END DEBUG
	}

	


}