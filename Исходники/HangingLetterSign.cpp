void HangingLetterSign::AnimateWind()
{
	unsigned int time = GetTicks();
	unsigned int elapsed = time - mStartTime;
	IvVector3 pos;
	this->GetLocalPosition(pos);
	float t = elapsed/(float)mWindDuration;
	
	if(t > 1.0f)
	{
			//this->ResetLocalTransform();//Start with identity
			//this->Translate(pos);
			IdleAnimate();
			return;
			/*GameMessage msg;
			msg.mEventName = "FINISHED";
			msg.mSender = mID;
			SendOutMessage(msg);
			return;*/
	}

	float noise = 0.2f* Perlin::Noise(time*0.001f,pos.x*0.01f);
	float hiFreqNoise = Perlin::Noise(time*0.007f,pos.x*0.01f);
	//ramp noise based on proximity to start and end animation
	
	//have to start with 1.0f times noise because that is what was driving the position and motion of the sign before
	//this animation... if you didn't start with the regular noise value then you would get a hitch in position.
	float s = 2.0f;
	if(t <= 0.25f)
		s = LERP(t*4.0f,1.0f,2.0f);
	else if( t >= 0.75f)
		s = LERP((t-0.75f)*4.0f,2.0f,1.0f);

	mLastUpdateTime = time;
	
	this->ResetLocalTransform();//Start with identity
	this->Translate(pos);
	
	float negNoise = -(0.5f*noise + 0.5f);
	this->Rotate(s*noise*0.3,s*hiFreqNoise*0.5f,s*negNoise*0.5);
	
}