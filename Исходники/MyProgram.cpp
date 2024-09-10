void MyProgram::timeBoard(const float timeDelta)
{
	/*m_RunTimerF = (float)this->m_timer.getMilliseconds()/1000;

	int decimal, sign;
    char *buffer;
    buffer =   _fcvt(m_RunTimerF,7,&decimal,&sign);
    String temp(buffer);
	String subtemp =   temp.substr(decimal,3);
	int t =   atoi(subtemp.c_str());
    int secondNum;
    secondNum = 30 - m_RunTimerF - 2;*/
	int decimal, sign;

	time = time-timeDelta;
	//time = time -(float)this->m_timer.getMilliseconds()/1000;
	
	char *buffer;
	buffer =  _fcvt(time,7,&decimal,&sign);
	String temp(buffer);
	String uptemp;
	String subtemp;
	if(time>=10)
	{
		uptemp = temp.substr(0,2);
		subtemp = temp.substr(decimal,2);
	}
	else if(time<10 && time>=1)
	{
		uptemp = temp.substr(0,1);
		subtemp = temp.substr(decimal,2);
	}
	else 
	{
		uptemp = '0';
		subtemp = temp.substr(0,2);
	}

	if(time<0.01) 
	{
			gameOver = true;
			win = false;
			EleTime->setCaption("TimeLeft: 0:00\n Life:  " + Ogre::StringConverter::toString(myPlayer->myHP));
	}
	else
		EleTime->setCaption("TimeLeft: " + uptemp +":"+ subtemp +"\n Life:  " + Ogre::StringConverter::toString(myPlayer->myHP));
	

	//EleTime->setCaption("TimeLeft: " + Ogre::StringConverter::toString(secondNum) +":"+ Ogre::StringConverter::toString(t) +"\n Life:  " + Ogre::StringConverter::toString(myPlayer->myHP));

}