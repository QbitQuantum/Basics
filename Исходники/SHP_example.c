void updata_temperature(void){
/******get cpu performance*******begin***/{
	BOOL res ;
 
	static FILETIME preidleTime;
	static FILETIME prekernelTime;
	static FILETIME preuserTime;

	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;


	res = GetSystemTimes( &idleTime, &kernelTime, &userTime );
	{
	__int64 idle = CompareFileTimeXXX(preidleTime,idleTime);
	__int64 kernel = CompareFileTimeXXX( prekernelTime, kernelTime);
	__int64 user = CompareFileTimeXXX(preuserTime, userTime);

	if((kernel+user)>0){
		__int64 cpu = (kernel +user - idle) *100/(kernel+user);
		temperature = cpu;
		disp_temperature(temperature);
	}
	}
/******get cpu performance*******end*****/}
}