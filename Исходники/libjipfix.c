 jobject buildDataRecord(ipfix_datarecord_t *d, ipfixt_node_t *t) {
     jclass cObject = (*senv)->FindClass(senv, "java/lang/Object");
     int nfields = t->ipfixt->nfields;
     jobjectArray addrs = (*senv)->NewObjectArray(senv, nfields, cObject, NULL);
     int i;
     for (i=0; i<nfields; i++) {
         int len = d->lens[i];
         int coding = t->ipfixt->fields[i].elem->ft->coding;
         jobject record;
         jbyteArray value = (*senv)->NewByteArray(senv, len);
         (*senv)->SetByteArrayRegion(senv, value, 0, len, d->addrs[i]);

         switch (coding) {
         case IPFIX_CODING_INT:
         case IPFIX_CODING_NTP:    //todo: convert into java/util/Timestamp
         case IPFIX_CODING_UINT: { //todo: make unsigned (increase [B len by 1?)
             jclass cBigInteger = (*senv)->FindClass(senv, "java/math/BigInteger");
             jmethodID mCon = (*senv)->GetMethodID(senv, cBigInteger, "<init>", "([B)V");
             record = (*senv)->NewObject(senv, cBigInteger, mCon, value);
             break;
         }
         case IPFIX_CODING_IPADDR: {
             jclass cInetAddress = (*senv)->FindClass(senv, "java/net/InetAddress");
             jmethodID mCon = (*senv)->GetStaticMethodID(senv, cInetAddress, "getByAddress", "([B)Ljava/net/InetAddress;");
             record = (*senv)->CallStaticObjectMethod(senv, cInetAddress, mCon, value);
             break;
         }
         case IPFIX_CODING_STRING: {
             jclass cString = (*senv)->FindClass(senv, "java/lang/String");
             jmethodID mCon = (*senv)->GetMethodID(senv, cString, "<init>", "([B)V");
             record = (*senv)->NewObject(senv, cString, mCon, value);
             break;
         }
         case IPFIX_CODING_FLOAT: {
             uint32_t tmp32;
             uint64_t tmp64;
             float tmpfloat;
             double tmpdouble;
             switch ( len ) {
               case 4:
                   memcpy( &tmp32, d->addrs[i], 8);
                   tmp32 = htonl( tmp32);
                   memcpy( &tmpfloat, &tmp32, 8);
                   jclass cFloat = (*senv)->FindClass(senv, "java/lang/Float");
                   jmethodID mCon = (*senv)->GetMethodID(senv, cFloat, "<init>", "(F)V");
                   record = (*senv)->NewObject(senv, cFloat, mCon, tmpfloat);
               case 8: {
                   memcpy( &tmp64, d->addrs[i], 8);
                   tmp64 = HTONLL( tmp64);
                   memcpy( &tmpdouble, &tmp64, 8);
                   jclass cDouble = (*senv)->FindClass(senv, "java/lang/Double");
                   jmethodID mCon = (*senv)->GetMethodID(senv, cDouble, "<init>", "(D)V");
                   record = (*senv)->NewObject(senv, cDouble, mCon, tmpdouble);
               }
             }
//             jclass cBigDecimal = (*senv)->FindClass(senv, "java/math/BigDecimal");
//             jmethodID mCon = (*senv)->GetMethodID(senv, cBigDecimal, "<init>", "([B)V");
//             record = (*senv)->NewObject(senv, cBigDecimal, mCon, value);
             break;
         }
         case IPFIX_CODING_BYTES:
         default: {
             record = value;
             break;
         }
         }

         (*senv)->SetObjectArrayElement(senv, addrs, i, record);
     }
     jint maxfields = d->maxfields;

     jclass cDR = (*senv)->FindClass(senv, "de/fraunhofer/fokus/ants/jipfix/data/IPFIXDataRecord");
     jmethodID mCon = (*senv)->GetMethodID(senv, cDR, "<init>", "([Ljava/lang/Object;I)V");
     jobject oDR = (*senv)->NewObject(senv, cDR, mCon, addrs, maxfields);
     return oDR;
 }