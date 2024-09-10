double _getLocalTZA()
{
	if(!FSDK_IsSandBoxPolicyEnabled(FPDF_POLICY_MACHINETIME_ACCESS))
		return 0;
	time_t t = 0;
	time(&t);
	localtime(&t);
#if _MSC_VER >= 1900
  // In gcc and in Visual Studio prior to VS 2015 'timezone' is a global
  // variable declared in time.h. That variable was deprecated and in VS 2015
  // is removed, with _get_timezone replacing it.
  long timezone = 0;
  _get_timezone(&timezone);
#endif
	return (double)(-(timezone * 1000));
}