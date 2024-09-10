bool setVolume(DWORD volume) {
	HMIXER mixer;
	int mixerNum ;//总的混音器数量
	bool is_find_mic;

	//获取当前系统总的混音器数量
	mixerNum= mixerGetNumDevs(); 	
	is_find_mic = false;
	for(int i=0;i<mixerNum;i++)
	{

		if (mixerOpen(&mixer, i, 0, 0, 0) != MMSYSERR_NOERROR) {   //这里修改麦克风音量是没有问题的，第一个你要找出那个混音器是麦克风啊
			printf("mixer open failed ...\n");
			MessageBoxW(NULL, L"Error: mixerOpen()", NULL, MB_ICONHAND);
			return false;
		}

		// Get the line info
		MIXERCAPS mixcaps;
		MIXERLINE mixerLine;
		mixerGetDevCaps(i, &mixcaps, sizeof(MIXERCAPS));
		mixerLine.cbStruct = sizeof(MIXERLINE);
		mixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;  //用MIXERLINE_COMPONENTTYPE_DST_WAVEIN 作参数可得到所有录音的Connection
		mixerLine.dwSource = 0;
		mixerLine.dwDestination = 0;

		if (mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(mixer), &mixerLine, MIXER_GETLINEINFOF_SOURCE)
			!= MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Error: mixerGetLineInfo()", NULL, MB_ICONHAND);
				return false;
		}

		if(mixerLine.dwComponentType !=MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE ){
			printf("i = %d ,this device is not microphone \n" ,i);
			mixerClose(mixer);
			continue;
		}

		is_find_mic = true;
		printf("mixerLine.dwComponentType = %xH ,MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE = %xH \n" ,mixerLine.dwComponentType ,MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE);

		//下面的代码只有是耳麦的时候才去执行
		// Get control for mixerline
		MIXERCONTROL mixerCtrl;
		MIXERLINECONTROLS mixerLineCtrl;

		mixerLineCtrl.cbStruct = sizeof(MIXERLINECONTROLS);
		mixerLineCtrl.dwLineID = mixerLine.dwLineID;
		mixerLineCtrl.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
		mixerLineCtrl.cControls = 1;
		mixerLineCtrl.pamxctrl = &mixerCtrl;
		mixerLineCtrl.cbmxctrl = sizeof(MIXERCONTROL);
		mixerLineCtrl.cControls = 5;

		if (mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(mixer), &mixerLineCtrl, MIXER_GETLINECONTROLSF_ONEBYTYPE)
			!= MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Error: mixerGetLineControls()", NULL, MB_ICONHAND);
				return false;
		}

		// Volume..
		MIXERCONTROLDETAILS mixerCtrlDetails;
		MIXERCONTROLDETAILS_UNSIGNED mixerCtrlDetailsUnsigned;

		mixerCtrlDetailsUnsigned.dwValue = volume;		//volume size 
		mixerCtrlDetails.dwControlID = mixerCtrl.dwControlID;
		mixerCtrlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
		mixerCtrlDetails.cMultipleItems = 0;
		mixerCtrlDetails.paDetails = &mixerCtrlDetailsUnsigned;
		mixerCtrlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
		mixerCtrlDetails.cChannels = 1;

		if (mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(mixer), &mixerCtrlDetails, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE)
			!= MMSYSERR_NOERROR) {
				MessageBoxW(NULL, L"Error: mixerSetControlDetails()", NULL, MB_ICONHAND);
				return false;
		}

		mixerClose(mixer);
	}//for loop

	return is_find_mic;
}