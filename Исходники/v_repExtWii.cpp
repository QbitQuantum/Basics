void LUA_START_CALLBACK(SLuaCallBack* p)
{ // the callback function of the new Lua command
	simLockInterface(1);

	int deviceIndex=-1; // error

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have (at least) 1 int as argument
			int effectiveDeviceIndex=-1;
			int desiredIndex=p->inputInt[0];
			if (desiredIndex==-1)
			{ // We want any free device (not yet being used)
				// We search for a free slot:
				for (int i=0;i<4;i++)
				{
					if (_allDevices[i]==NULL)
					{
						desiredIndex=i;
						break;
					}
				}
			}
			if ( (desiredIndex>=0)&&(desiredIndex<4) )
			{
				if (_allDevices[desiredIndex]==NULL)
				{ // We connect to a new device!
					wiimote* it=new wiimote();
					it->ChangedCallback=on_state_change;
					it->CallbackTriggerFlags=(state_change_flags)(CONNECTED|EXTENSION_CHANGED|MOTIONPLUS_CHANGED);
					if (it->Connect(desiredIndex+1))
					{ // Success!
						_allDeviceData[desiredIndex].buttonStates=0;
						_allDeviceData[desiredIndex].batteryState=0;
						_allDeviceData[desiredIndex].accelerationX=0.0f;
						_allDeviceData[desiredIndex].accelerationY=0.0f;
						_allDeviceData[desiredIndex].accelerationZ=0.0f;
						_allDeviceData[desiredIndex].pitch=0.0f;
						_allDeviceData[desiredIndex].roll=0.0f;
						_allDeviceData[desiredIndex].rumble=0;
						_allDeviceData[desiredIndex].leds=0;
						_allDeviceData[desiredIndex].initialized=false;
						_allDevices[desiredIndex]=it;
					}
					else
						desiredIndex=-1; // No more devices available!
				}
			}
			if ( (desiredIndex>=0)&&(desiredIndex<4) )
			{
				if (startCountOverall==0)
				{ // Launch the thread!
					_wiiThreadLaunched=false;
					CreateThread(NULL,0,_wiiThread,NULL,THREAD_PRIORITY_NORMAL,NULL);
					while (!_wiiThreadLaunched)
						Sleep(2);
				}
				startCountOverall++;
				startCountPerDevice[desiredIndex]++;
				deviceIndex=desiredIndex;
			}
			else
				simSetLastError(LUA_START,"Invalid device index, or no available device at given index. Is device connected?"); // output an error
		}
		else
			simSetLastError(LUA_START,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_START,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;	// The return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;				// Not used (table size if the return value was a table)
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(deviceIndex)); // 1 int return value
	p->outputInt[0]=deviceIndex; // This is the int value we want to return

	simLockInterface(0);
}