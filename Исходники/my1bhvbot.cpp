//------------------------------------------------------------------------------
void my1BhvScout::Evaluate(void)
{
	mActive = true;
	if(mInput->info.bview)
	{
		mDrive.drive = MOVE_F;
		mDrive.turn = mInput->info.bside;
		mActive = false; // can be override
	}
	else
	{
		// basically turn away fom obstacle
		if(!mSense->r_safe&&mSense->l_safe)
			mDrive.turn = TURN_L;
		else if(mSense->r_safe&&!mSense->l_safe)
			mDrive.turn = TURN_R;
		else
		{
			// 1/8 chance turning
			mDrive.turn = rand()%2? TURN_R : TURN_L;
			mDrive.turn = rand()%4==0? mDrive.turn : TURN_0;
		}
		mDrive.drive = mDrive.turn? MOVE_0 : MOVE_F; // don't move if turning
	}
	// assign drive parameters
	mDrive.dist = mDrive.drive*1.0;
	mDrive.angle = mDrive.turn*0.5; // only turn half as much
}