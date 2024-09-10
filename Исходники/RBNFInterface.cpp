static jobject parseRBNFImpl(JNIEnv *env, jclass clazz, jint addr, jstring text, 
        jobject position, jboolean lenient) {

    // LOGI("ENTER parseRBNFImpl");

    const char * parsePositionClassName = "java/text/ParsePosition";
    const char * longClassName = "java/lang/Long";
    const char * doubleClassName = "java/lang/Double";


    UErrorCode status = U_ZERO_ERROR;

    UNumberFormat *fmt = (UNumberFormat *)(int)addr;

    jchar *str = (UChar *)env->GetStringChars(text, NULL);
    int strlength = env->GetStringLength(text);

    jclass parsePositionClass = env->FindClass(parsePositionClassName);
    jclass longClass =  env->FindClass(longClassName);
    jclass doubleClass =  env->FindClass(doubleClassName);

    jmethodID getIndexMethodID = env->GetMethodID(parsePositionClass, 
            "getIndex", "()I");
    jmethodID setIndexMethodID = env->GetMethodID(parsePositionClass, 
            "setIndex", "(I)V");
    jmethodID setErrorIndexMethodID = env->GetMethodID(parsePositionClass, 
            "setErrorIndex", "(I)V");

    jmethodID longInitMethodID = env->GetMethodID(longClass, "<init>", "(J)V");
    jmethodID dblInitMethodID = env->GetMethodID(doubleClass, "<init>", "(D)V");

    int parsePos = env->CallIntMethod(position, getIndexMethodID, NULL);

    // make sure the ParsePosition is valid. Actually icu4c would parse a number 
    // correctly even if the parsePosition is set to -1, but since the RI fails 
    // for that case we have to fail too
    if(parsePos < 0 || parsePos > strlength) {
        return NULL;
    }

    Formattable res;

    const UnicodeString src((UChar*)str, strlength, strlength);
    ParsePosition pp;
    
    pp.setIndex(parsePos);
    
    if(lenient) {
        unum_setAttribute(fmt, UNUM_LENIENT_PARSE, JNI_TRUE);
    }
    
    ((const NumberFormat*)fmt)->parse(src, res, pp);

    if(lenient) {
        unum_setAttribute(fmt, UNUM_LENIENT_PARSE, JNI_FALSE);
    }
    
    env->ReleaseStringChars(text, str);

    if(pp.getErrorIndex() == -1) {
        parsePos = pp.getIndex();
    } else {
        env->CallVoidMethod(position, setErrorIndexMethodID, 
                (jint) pp.getErrorIndex());        
        return NULL;
    }

    Formattable::Type numType;
    numType = res.getType();
    UErrorCode fmtStatus;

    double resultDouble;
    long resultLong;
    int64_t resultInt64;

    switch(numType) {
        case Formattable::kDouble:
            resultDouble = res.getDouble();
            env->CallVoidMethod(position, setIndexMethodID, (jint) parsePos);
            return env->NewObject(doubleClass, dblInitMethodID, 
                    (jdouble) resultDouble);
        case Formattable::kLong:
            resultLong = res.getLong();
            env->CallVoidMethod(position, setIndexMethodID, (jint) parsePos);
            return env->NewObject(longClass, longInitMethodID, 
                    (jlong) resultLong);
        case Formattable::kInt64:
            resultInt64 = res.getInt64();
            env->CallVoidMethod(position, setIndexMethodID, (jint) parsePos);
            return env->NewObject(longClass, longInitMethodID, 
                    (jlong) resultInt64);
        default:
            break;
    }

    return NULL;
}