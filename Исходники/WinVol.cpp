//设置音量值
bool WINAPI SetVolume(LONG vol)
{
	bool Result=false;   //用于判断函数是否执行成功
	MIXERCONTROL volCtrl;
	HMIXER hmixer;
	if(mixerOpen(&hmixer, 0, 0, 0, 0)) return 0;
	if(GetVolumeControl(hmixer,MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,MIXERCONTROL_CONTROLTYPE_VOLUME,&volCtrl))
	{ 
		int ChangeValue=volCtrl.Bounds.lMaximum/INTERVAL;
		int TotalValue=ChangeValue*vol;
		if(SetVolumeValue(hmixer,&volCtrl,TotalValue))
			Result=true;
	}   
	mixerClose(hmixer);
	return Result;
}