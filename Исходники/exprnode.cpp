int FloatConstNode::intValue(){
	float flt=value;
	int temp;
	_control87( _RC_NEAR|_PC_24|_EM_INVALID|_EM_ZERODIVIDE|_EM_OVERFLOW|_EM_UNDERFLOW|_EM_INEXACT|_EM_DENORMAL,0xfffff );
	_asm{
		fld [flt];
		fistp [temp];
	}
	_control87( _CW_DEFAULT,0xfffff );
	return temp;
}