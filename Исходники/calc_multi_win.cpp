int main(int argc, char **argv)
{
	int i = 0;
	int sum = 0;
	struct data_info d_info;

	DWORD dwThreadArray[THREAD_NUM];
	HANDLE hThreadArray[THREAD_NUM];

	InitializeCriticalSection(&CSLock);
	InitializeConditionVariable(&CalcReady);

	data_array = (int *)malloc(sizeof(int)*ARRAY_SIZE);

	//4개의 쓰래드를 만든다. 
	for (i = 0; i < THREAD_NUM; i++)
	{
		d_info.d_point = data_array;
		d_info.idx = i;
		hThreadArray[i] = CreateThread(NULL, 0, t_func, (void *)&d_info, 0, &dwThreadArray[i]);
		Sleep(10);
	}
	//계산할 100개으 ㅣ데이터르 ㄹ만든다.
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		*data_array = i;
		*data_array++;
	}
	//데이터를 모두 만들었으면 모든 워커 스레드를 깨운다.
	WakeAllConditionVariable(&CalcReady);

	//모든 워커 스레드가 연산을 끝내고 종료하길 기다린다
	WaitForMultipleObjects(THREAD_NUM, hThreadArray, TRUE, INFINITE);

	//워커 스레드들의 연산 결과를 더해서 최종 결과를 출력한다.
	for (i = 0; i < THREAD_NUM; i++)
	{
		CloseHandle(hThreadArray[i]);
		sum += sum_array[i];
	}
	return 0;
}