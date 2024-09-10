/*
 * Class:     org_jboss_odbc_OdbcClient
 * Method:    disconnect
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_jboss_odbc_OdbcClient_disconnect(JNIEnv *jnienv, jobject obj) {
    int h = getStaticHandle(jnienv, obj);

    SQLDisconnect(dbc[h]);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc[h]);
}