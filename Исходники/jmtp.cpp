//nog werk nodig! met de union!!
PROPVARIANT ConvertJavaToPropVariant(JNIEnv* env, jobject jobjPropVariant)
{
	//variabelen
	jclass cls;
	jmethodID mid;
	PROPVARIANT pv;
	jstring jsValue;
	LPWSTR wszBuffer;
	LPWSTR wszValue;
	jobject jobjObjectValue;


	//methode implementatie
	PropVariantInit(&pv);
	cls = env->FindClass("jmtp/PropVariant");
	//printf("convert 1\n");
	mid = env->GetMethodID(cls, "getVt", "()I");
	pv.vt = static_cast<VARTYPE>(env->CallIntMethod(jobjPropVariant, mid));
	//printf("convert 2\n");
	int strLength;
	switch(pv.vt)
	{
		case VT_LPWSTR:
			//printf("convert 3\n");
			mid = env->GetMethodID(cls, "getValue", "()Ljava/lang/Object;");
			jsValue = (jstring)env->CallObjectMethod(jobjPropVariant, mid);
			strLength = env->GetStringLength(jsValue);
			//printf("convert3.4:%d\n", strLength);
			wszBuffer = ConvertJavaStringToWCHAR(env, jsValue); //(WCHAR*)env->GetStringChars(jsValue, NULL);
			wszValue = new WCHAR[strLength+1];
			if (wszValue == NULL) {
				//printf("conver tproblem null\n");
			}
			for (int i = 0; i < strLength; i++) {
				wszValue[i] = wszBuffer[i];
			}
			wszValue[strLength] = 0;
			//wcscpy_s(wszValue, strLength, wszBuffer);
			//wprintf(L"convert3.5:%s\n", wszBuffer);
			//wprintf(L"convert3.6:%s\n", wszValue);
			delete wszBuffer;
			pv.pwszVal = wszValue;
			//wprintf(L"convert4:%s\n", pv.pwszVal);
			break;
		case VT_BOOL:
			mid = env->GetMethodID(cls, "getValue", "()Ljava/lang/Object;");
			jobjObjectValue = env->CallObjectMethod(jobjPropVariant, mid);
			mid = env->GetMethodID(env->FindClass("java/lang/Boolean"), "booleanValue", "()Z");
			pv.boolVal = env->CallBooleanMethod(jobjObjectValue, mid);
			break;
	}
	//andere types worden momenteel niet ondersteunt
	
	return pv;
}