static void ONI_CALLBACK_TYPE deviceDisconnectedCallback(const OniDeviceInfo* pInfo, void*)
{
	JNIEnvSupplier suplier;
	JNIEnv *env = suplier.GetEnv();
	jclass videoStreamCls = env->FindClass("org/openni/OpenNI");
	jmethodID methodID = env->GetStaticMethodID(videoStreamCls, "deviceDisconnected", "(Lorg/openni/DeviceInfo;)V");
	jobject nameObj = env->NewStringUTF(pInfo->name);
	jobject uriObj = env->NewStringUTF(pInfo->uri);
	jobject vendorObj = env->NewStringUTF(pInfo->vendor);
	jclass deviceInfoCls = env->FindClass("org/openni/DeviceInfo");
	jobject deviceObj = (*env).NewObject(deviceInfoCls, (*env).GetMethodID(deviceInfoCls, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;II)V"),
		uriObj, vendorObj, nameObj, pInfo->usbVendorId, pInfo->usbProductId);
	env->CallStaticVoidMethod(videoStreamCls, methodID, deviceObj);
}