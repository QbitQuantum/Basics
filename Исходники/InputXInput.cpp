//------------------------------------------------
// ctor
//------------------------------------------------
InputXInput::InputXInput( HINSTANCE hInstance )
	: InputDevice( hInstance )
	, padID_( -1 )
	, timeFFB_( 0 )
	, isConnect_( false )
	, isGeneratingFFB_( false )
{

	// XInput有効にする
	XInputEnable( TRUE );

	// PADに管理用IDを振る
	padID_ = InputXInput::padCnt_;

	// パッドの数を更新
	++padCnt_;

	// XInputの能力を取得
	XINPUT_CAPABILITIES capability;
	DWORD result = XInputGetCapabilities( padID_, XINPUT_FLAG_GAMEPAD, &capability );
	
	// 使用の可否を更新
	SetEnable( result == ERROR_SUCCESS );

	// 振動をON
	SetEnableFFB( true );
}