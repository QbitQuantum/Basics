void CMStuff(char *devID, JNIEnv *env, jobject hashMap, jmethodID methPut)
{
    DEVINST devinst;
    DEVINST devinstparent;
    unsigned long buflen;

	CONFIGRET ret;

    ret = CM_Locate_DevNodeA(&devinst, devID, NULL);
	if (ret != CR_SUCCESS) {
		return;
	}
    ret = CM_Get_Parent(&devinstparent, devinst, NULL);
	if (ret != CR_SUCCESS) {
		return;
	}

	char *has = strstr(devID, "RemovableMedia");
	if (has) {
        CM_Get_Parent(&devinstparent, devinstparent, NULL);
		// if failed, devinstparent should still have previous value (I hope!)
	}

	ret = CM_Get_Device_ID_Size(&buflen, devinst, 0);
	if (ret != CR_SUCCESS) {
		return;
	}

	if (buflen < 2048) {
		buflen++; // add space for null, which CM_Get_Device_ID will add at end
		WCHAR *buffer = new WCHAR[buflen];
		ret = CM_Get_Device_ID(devinst, buffer, buflen, 0);
		if (ret != CR_SUCCESS) {
			delete[] buffer;
			return;
		}

		addToMap(env, hashMap, methPut, "DevInst_DevID", buffer, buflen);
		findVID_PID(buffer, env, hashMap, methPut);
		delete[] buffer;
	}

    ret = CM_Get_Device_ID_Size(&buflen, devinstparent, 0);
	if (ret != CR_SUCCESS) {
		return;
	}
	if (buflen < 2048) {
		buflen++; // add space for null, which CM_Get_Device_ID will add at end
		WCHAR *buffer = new WCHAR[buflen];
		ret = CM_Get_Device_ID(devinstparent, buffer, buflen, 0);
		if (ret != CR_SUCCESS) {
			delete[] buffer;
			return;
		}

		addToMap(env, hashMap, methPut, "DevInstParent_DevID", buffer, buflen);
		findVID_PID(buffer, env, hashMap, methPut);
		delete[] buffer;
	}
}