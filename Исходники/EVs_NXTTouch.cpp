bool EVs_NXTTouch::isPressed()
{
  int a;
	a = readRaw();

	if ( a < 300 ) return true;
	else return false;
}