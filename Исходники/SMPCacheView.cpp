void setInt(CStatic &control, int &i)
{
	char cadena[20];
	_itoa_s(i,cadena,10);
	control.SetWindowTextW((CString)cadena);
}