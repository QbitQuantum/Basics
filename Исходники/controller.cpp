//-----------------------------------------------------------------------------
//!	振動開始
//!	@param [in] L_vib	左振動値(0.0f ~ 1.0f)
//!	@param [in] R_vib	右振動値(0.0f ~ 1.0f)
//-----------------------------------------------------------------------------
void Controller::EnableVibration( f32 L_vib, f32 R_vib )
{
	//	振動値を0.0~1.0fから 0 ~ 65535に変換
	L_vib = 65535 * L_vib;
	R_vib = 65535 * R_vib;
	//	振動用の構造体
	XINPUT_VIBRATION	vibration;
	//	初期化
	ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
	//	振動値代入
	vibration.wLeftMotorSpeed  = L_vib;
	vibration.wRightMotorSpeed = R_vib;
	//	結果転送
	XInputSetState( _controllerNum, &vibration);
}