void Agent::orderPathFollow()
{

	if (mPath->GetLength() > 0)
	{
		this->SetMaxSpeed(10);
		//find closest node
		float min = 999999;
		for (int i=0;i<mPath->GetLength();i++)
		{
			Vector3 delta = Position - mPath->GetNode(i).getPos();
			if (delta.length() < min)
			{
				min = delta.length();
				PathPosition = i;
			}
		}

		//go
		this->resetBehavior();
		this->pathOn();

		//avoid obstacles,walls & seperate
		//this->avoid1On();
		//this->avoid2On();
		this->avoid3On();
		//this->seperateOn();
	}
}