/*===================================================================
函数名称 :  sendkeyString
功能描述 :  模拟键盘发送字符串

返回值: 返回值:BOOL类型
_TRUE表示成功,_FALSE表示失败

参数:
名称        类型             描述
-----------------------------------------------
list       MyDataList *   传进来键盘按下的字符串
ret        _variant_t *      接收返回值传出去

修改历史 :
修改者   日期           描述
邓媛元   2010-07-18      
邓媛元   2010-07-20     检测 
====================================================================*/
bool  MyKeyboardNamespace::sendkeyString(wchar_t *strs,DWORD delays)
{
	int length = wcslen(strs);
	for (int i = 0; i < length; ++i)
	{
		INPUT   keyin;
		keyin.type=INPUT_KEYBOARD;
		keyin.ki.wVk=0;
		keyin.ki.wScan=strs[i];
		keyin.ki.time=100;
		keyin.ki.dwFlags=KEYEVENTF_UNICODE;
		keyin.ki.dwExtraInfo=GetMessageExtraInfo();
		::SendInput(1,  &keyin, sizeof(INPUT));
		Sleep(delays);
	}
	return true;
}