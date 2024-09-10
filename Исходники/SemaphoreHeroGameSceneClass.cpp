void SemaphoreHeroGameSceneClass::Running(){
	//timer count for display timer
	if(isStart == false){
		isStart = false;
		startTime = GetTickCount();
	}
	endTime = GetTickCount();
	deltaTime = endTime - startTime;
	if(deltaTime>=1000){
		timerNum++;
		timerLabel->displayNum = timerNum;
		startTime = endTime;
		deltaTime = 0;
	}

	//set current signal
	if(questionIndex<SIGNAL_NUM){
		leftFlag->pos3f.x = FlagSignals[questionIndex].lx;
		leftFlag->pos3f.y = FlagSignals[questionIndex].ly;
		rightFlag->pos3f.x = FlagSignals[questionIndex].rx;
		rightFlag->pos3f.y = FlagSignals[questionIndex].ry;
		questionLabel->displayStr = FlagSignals[questionIndex].name;

		//get new signal start time
		newSignalTime = GetTickCount();
	}
	
	/////

	//logic 1,get hand position
	x_left = skeletonPlayer.SkeletonPoints[NUI_SKELETON_POSITION_HAND_LEFT].x * skeletonmanScale;
	y_left = skeletonPlayer.SkeletonPoints[NUI_SKELETON_POSITION_HAND_LEFT].y * skeletonmanScale;

	x_right = skeletonPlayer.SkeletonPoints[NUI_SKELETON_POSITION_HAND_RIGHT].x * skeletonmanScale;
	y_right = skeletonPlayer.SkeletonPoints[NUI_SKELETON_POSITION_HAND_RIGHT].y * skeletonmanScale;

	bool answerL = false;
	bool answerR = false;

	//judge left
	if(leftFlag->CheckInRange2D(x_left,y_left)){
		leftFlag->color3f.z = 1;
		answerL = true;
	}else{
		leftFlag->color3f.z = 0;
		answerL = false;
	}
	//judge right
	if(rightFlag->CheckInRange2D(x_right,y_right)){
		rightFlag->color3f.z = 1;
		answerR = true;
	}else{
		rightFlag->color3f.z = 0;
		answerR = false;
	}

	if(answerL&&answerR){
		//answer right
		answerLabel->letter = "Signal Right";

		finishSignalTime = GetTickCount();
		//calculate score
		scoreTime = finishSignalTime - newSignalTime;
		int k = scoreTime/1000;
		if(k>5){
			itemList[3]->letter = "You are so .... bad";
		}else{
			switch(k){
			case 0:
				scoreLabel->letter = "Right";
				break;
			case 1:
				itemList[3]->letter = "Great";
				//scoreLabel->letter
				break;;
			case 2:
				itemList[3]->letter = "A litter good";
				break;
			case 3:
				itemList[3]->letter = "Common";
				break;
			case 4:
				itemList[3]->letter = "Bad";
				break;
			case 5:
				itemList[3]->letter = "Too Bad";
				break;
			}
		}

		//end

		questionIndex++;
		if(questionIndex >= SIGNAL_NUM){
			//current game end
			allPass = true;
			questionIndex = 0;
		}
	}
	else{
		answerLabel->letter = "Come On...";
	}

	if(allPass){
		End();
	}

}