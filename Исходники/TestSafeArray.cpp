void TestSafeArray()
{
	// 创建COM对象实例
	IMarshalSafeArrayPtr comObj(__uuidof(MarshalSafeArrayObj));
	if (comObj)
	{
		// 创建SafeArray
		SAFEARRAY* pIntArray;
		SAFEARRAYBOUND saBnd[1];
		saBnd[0].lLbound = 0;
		saBnd[0].cElements = 5;
		pIntArray = SafeArrayCreate(VT_I4, 1, saBnd);

		// 初始化SafeArray
		int* pArray;
		SafeArrayAccessData(pIntArray, (void HUGEP**)&pArray);
		pArray[0] = 0;
		pArray[1] = 1;
		pArray[2] = 2;
		pArray[3] = 3;
		pArray[4] = 4;
		SafeArrayUnaccessData(pIntArray);

		wprintf(L"(0) 初始化数组\n");
		PrintIntArray(pIntArray);

		int result = 0;
		result = comObj->IntArrayUpdateByVal(pIntArray);
		wprintf(L"元素和：%d\n\n", result);
		wprintf(L"(1) 调用方法 IntArrayUpdateByVal\n");
		PrintIntArray(pIntArray);

		result = comObj->IntArrayUpdateByValInOut(pIntArray);
		wprintf(L"元素和：%d\n\n", result);
		wprintf(L"(2) 调用方法 IntArrayUpdateByValInOut\n");
		PrintIntArray(pIntArray);

		result = comObj->IntArrayUpdateByRef(&pIntArray);
		wprintf(L"元素和：%d\n\n", result);
		wprintf(L"(3) 调用方法 IntArrayUpdateByRef\n");
		PrintIntArray(pIntArray);

		result = comObj->IntArrayUpdateByRefInOnly(&pIntArray);
		wprintf(L"元素和：%d\n\n", result);
		wprintf(L"(4) 调用方法 IntArrayUpdateByRefInOnly\n");
		PrintIntArray(pIntArray);

		// 释放SafeArray
		SafeArrayDestroy(pIntArray);

		SAFEARRAY* pNewArray = comObj->IntArrayReturn(5);
		wprintf(L"\n(5) 调用方法 IntArrayReturn：\n");
		PrintIntArray(pNewArray);

		// 释放SafeArray
		SafeArrayDestroy(pNewArray);

		comObj.Release();
	}
}