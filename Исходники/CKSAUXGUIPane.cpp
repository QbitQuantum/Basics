void CKSAUXGUIPane::Init()
{
	mpPane = ge::IPane::Create();
	//mpPane->SetBackgroundColour(ge::SRGB(0, 0, 0));
	mpPane->SetSize(gAUX);
	
	//-------------------------------
	// Backdrop for AUX
	CreateBitmap(ge::IControl::giNoID, IDB_Back_AUX, ge::SPos(0, 0));
	//-------------------------------
	
	//--------------------------------
	// ECHO
	//--------------------------------
	
	Create2StateButton(giCtrl_Delay_Power, IDB_Button_Power, ge::SPos(25, 36), true);
	
	tint32 iX		=	154+126;
	tint32 iY		=	75;
	
	// Delay time 
	CreateKnob(giCtrl_Delay_Time, IDB_Dial_Medium, ge::SPos(iX, iY), 65);		iX += 64;
	CreateDisplay( giCtrl_Delay_Time_Display, ge::SPos(184, 65),  ge::SSize(56, 12), CreateFont(Generic128, IDB_Font_Axel_Tight, ge::SRGB(0, 180, 0)));
	
	// Predlay
	CreateKnob(giCtrl_Delay_Feedback, IDB_Dial_Medium, ge::SPos(iX, iY), 65);	iX += 64;
	CreateDisplay( giCtrl_Delay_Feedback_Display, ge::SPos(184, 77),  ge::SSize(56, 12), CreateFont(Generic128, IDB_Font_Axel_Tight, ge::SRGB(0, 180, 0)));
	
	// Lo Filt
	CreateKnob(giCtrl_Delay_LP_Dampning, IDB_Dial_Medium, ge::SPos(iX, iY), 65);	iX += 64;
	CreateDisplay( giCtrl_Delay_LP_Dampning_Display, ge::SPos(184, 89),  ge::SSize(56, 12), CreateFont(Generic128, IDB_Font_Axel_Tight, ge::SRGB(0, 180, 0)));
	
	// High Filt
	CreateKnob(giCtrl_Delay_HP_Dampning, IDB_Dial_Medium, ge::SPos(iX, iY), 65);	iX += 64;
	CreateDisplay( giCtrl_Delay_HP_Dampning_Display, ge::SPos(184, 101),  ge::SSize(56, 12), CreateFont(Generic128, IDB_Font_Axel_Tight, ge::SRGB(0, 180, 0)));
	
	
	// Output meter, Left
	mpEcho_MeterOutL = CreatePeakMeter(ge::IControl::giNoID, ge::SPos(534, 151-88), 47, ge::IPeakMeter::Up);
	FindPane(mpEcho_MeterOutL)->CreateBitmap(ge::IControl::giNoID, IDB_Meter_Off_Left_AUX, ge::SPos(0, 0));
	// Output meter, Right
	mpEcho_MeterOutR = CreatePeakMeter(ge::IControl::giNoID, ge::SPos(541, 151-88), 47, ge::IPeakMeter::Up);
	FindPane(mpEcho_MeterOutR)->CreateBitmap(ge::IControl::giNoID, IDB_Meter_Off_Right_AUX, ge::SPos(0, 0));
	//--------------------------------
	// REVERB
	//--------------------------------
	Create2StateButton(giCtrl_Reverb_Power, IDB_Button_Power, ge::SPos(25, 124), true);
	iX		=	152;
	iY		=	165;
	// Reverb Size
	CreateKnob(giCtrl_Reverb_Size, IDB_Dial_Medium, ge::SPos(iX, iY), 65);		iX += 64;
	// Predlay
	CreateKnob(giCtrl_Reverb_PDelay, IDB_Dial_Medium, ge::SPos(iX, iY), 65);		iX += 64;
	// Damping
	CreateKnob(giCtrl_Reverb_Damp, IDB_Dial_Medium, ge::SPos(iX, iY), 65);		iX += 64;
	// Reverb
	CreateKnob(giCtrl_Reverb_Panorama, IDB_Dial_Medium, ge::SPos(iX, iY), 65);	iX += 64;
	// Reverb
	CreateKnob(giCtrl_Reverb_Color1, IDB_Dial_Medium, ge::SPos(iX, iY), 65);		iX += 64;
	// Reverb
	CreateKnob(giCtrl_Reverb_Color2, IDB_Dial_Medium, ge::SPos(iX, iY), 65);		iX += 64;
	
	// Output meter, Left
	mpReverb_MeterOutL = CreatePeakMeter(ge::IControl::giNoID, ge::SPos(534, 153), 47, ge::IPeakMeter::Up);
	FindPane(mpReverb_MeterOutL)->CreateBitmap(ge::IControl::giNoID, IDB_Meter_Off_Left_AUX, ge::SPos(0, 0));
	// Output meter, Right
	mpReverb_MeterOutR = CreatePeakMeter(ge::IControl::giNoID, ge::SPos(541, 153), 47, ge::IPeakMeter::Up);
	FindPane(mpReverb_MeterOutR)->CreateBitmap(ge::IControl::giNoID, IDB_Meter_Off_Right_AUX, ge::SPos(0, 0));
}