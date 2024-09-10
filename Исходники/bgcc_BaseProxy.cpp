/*
 * Class:     bgcc_BaseProxy
 * Method:    create
 * Signature: (Lbgcc/ServerInfo;)I
 */
JNIEXPORT jint JNICALL Java_bgcc_BaseProxy_create
  (JNIEnv *env, jobject baseProxy, jobject serverInfo) {
      jclass serverInfoCls = env->GetObjectClass(serverInfo);
      jfieldID serverInfoAddressFid = env->GetFieldID(serverInfoCls, "serverInfoAddress", "J");

      ServerInfo* pServerInfo = (ServerInfo*)env->GetLongField(serverInfo, serverInfoAddressFid);
      if (!pServerInfo) {
          return -1;
      }

      jclass baseProxyCls = env->GetObjectClass(baseProxy);
      jfieldID proxyAddressFid = env->GetFieldID(baseProxyCls, "proxyAddress", "J");

      BaseProxy* pBaseProxy = new(std::nothrow) BaseProxy(*pServerInfo, 3);
	  pBaseProxy->set_errno(BgccSockGetLastError());
      jlong addr = (jlong)pBaseProxy;
      env->SetLongField(baseProxy, proxyAddressFid, addr);
      return 0;
  }