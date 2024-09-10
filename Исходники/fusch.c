void* seam_progress(void *arg) {
	const int n = labs(*(int*)arg);
	const float fn = n;
#ifdef ANDROID_BUILD
	char progBuf[500];
	JNIEnv *env;
	jmethodID updateProgMID;
	(*cachedJvm)->AttachCurrentThread(cachedJvm, &env, NULL);
	jstring progStr;
	jclass mainActivityClass = (*env)->GetObjectClass(env, cachedMainActObj);
	updateProgMID = (*env)->GetMethodID(env, mainActivityClass, "updateProgress", "(Ljava/lang/String;I)V");
	if (NULL == updateProgMID) {
		LOGE(1, "error finding method updateProgress at seam_progress");
		(*cachedJvm)->DetachCurrentThread(cachedJvm);
		pthread_exit((void*)NULL);
	}
#endif
	
//	printf("Fugensuche: ges. erm.   %% Fu/s    Dauer  verstr.   verbl.\n            %4d ", n);
#ifdef ANDROID_BUILD
	sprintf(progBuf, "%s\n", MSG[I_COMPUTING_TABLE]);
	progStr = (*env)->NewStringUTF(env, progBuf);
	(*env)->CallVoidMethod(env, cachedMainActObj, updateProgMID, progStr, 0);
#else
	puts(MSG[I_COMPUTING_TABLE]);
	printf("            %4d ", n);
#endif
	int i = 0,
		s = 0;
	bool goon = true;
	do {
		sleep_sync(500);
		s = sc_seam_progress();
		goon = (s < n);

		const int ela = i >> 1;
		const float rate = ela? (float)(s) / (float)(ela): 1;
		const int lrate = lrintf(rate),
					 pc = (float)(s * 100) / fn;

		if ((i++ & 1) && goon) {
			printf("%4d %3d %4d\b\b\b\b\b\b\b\b\b\b\b\b\b\b ", s, pc, lrate);
		} else {
			const int ttl = lrintf(n / rate);
			struct hms_s tela, trem, tttl;
			ftime(ela, &tela);
			ftime(ttl - ela, &trem);
			ftime(ttl, &tttl);
#ifdef ANDROID_BUILD
			sprintf(progBuf, "%4d %4d %3d %4d "
				"%02d:%02d:%02d %02d:%02d:%02d %02d:%02d:%02d",
				n, s, pc, lrate,
				tttl.h, tttl.m, tttl.s, tela.h, tela.m, tela.s, trem.h, trem.m, trem.s
			);
			progStr = (*env)->NewStringUTF(env, progBuf);
			(*env)->CallVoidMethod(env, cachedMainActObj, updateProgMID, progStr, 1);
#else
			printf(
				"%4d %3d %4d "
				"%02d:%02d:%02d %02d:%02d:%02d %02d:%02d:%02d"
				"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
				s, pc, lrate,
				tttl.h, tttl.m, tttl.s, tela.h, tela.m, tela.s, trem.h, trem.m, trem.s
			);
#endif
		}
	} while (goon);
#ifdef ANDROID_BUILD
	(*cachedJvm)->DetachCurrentThread(cachedJvm);
#endif
	pthread_exit((void*)NULL);
}