void CraytDlg::OnBnClickedTestSse2()
{
	vec3 A = vec3(1,1,1);
	vec3 B = vec3(2,-1,-2);

	__m128 C = _mm_setr_ps(1,1,1,0);
	__m128 D = _mm_setr_ps(2,-1,-2,0);
	

	LARGE_INTEGER F,T0,T1;   // address of current frequency
	QueryPerformanceFrequency(&F);
	QueryPerformanceCounter(&T0);

	for(int j=0;j<100;++j)
	for(int i=0;i<1000000;++i)
		_mm_dp_ps(C,D,0x7F);

	QueryPerformanceCounter(&T1);
	float elapsed_timeA = (float)(T1.QuadPart - T0.QuadPart) / (float)F.QuadPart;
	T0 = T1;

	for(int j=0;j<100;++j)
	for(int i=0;i<1000000;++i)
		dot(A,B);

	QueryPerformanceCounter(&T1);
	float elapsed_timeB = (float)(T1.QuadPart - T0.QuadPart) / (float)F.QuadPart;


	char buffer[255];
	sprintf(buffer,"Fast= %.2f s       Normal=%.2f s" , elapsed_timeA,elapsed_timeB);
	AfxMessageBox(buffer);
}