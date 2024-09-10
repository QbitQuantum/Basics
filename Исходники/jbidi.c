JNIEXPORT void JNICALL Java_java_text_Bidi_nativeBidiChars
  (JNIEnv *env, jclass cls, jobject jbidi, jcharArray text, jint tStart, jbyteArray embs, jint eStart, jint length, jint dir)
{
    UErrorCode err = U_ZERO_ERROR;
    UBiDi* bidi = ubidi_openSized(length, length, &err);
    if (!U_FAILURE(err)) {
        jchar *cText = (jchar*)(*env)->GetPrimitiveArrayCritical(env, text, NULL);
        if (cText) {
            UBiDiLevel baseLevel = (UBiDiLevel)dir;
            jbyte *cEmbs = 0;
	    uint8_t *cEmbsAdj = 0;
            if (embs != NULL) {
                cEmbs = (jbyte*)(*env)->GetPrimitiveArrayCritical(env, embs, NULL);
		if (cEmbs) {
		    cEmbsAdj = (uint8_t*)(cEmbs + eStart);
		}
            }
            ubidi_setPara(bidi, cText + tStart, length, baseLevel, cEmbsAdj, &err);
	    if (cEmbs) {
		(*env)->ReleasePrimitiveArrayCritical(env, embs, cEmbs, JNI_ABORT);
	    }

            (*env)->ReleasePrimitiveArrayCritical(env, text, cText, JNI_ABORT);

            if (!U_FAILURE(err)) {
                jint resDir = (jint)ubidi_getDirection(bidi);
                jint resLevel = (jint)ubidi_getParaLevel(bidi);
                jint resRunCount = 0;
                jintArray resRuns = 0;
                jintArray resCWS = 0;
                if (resDir == UBIDI_MIXED) {
                    resRunCount = (jint)ubidi_countRuns(bidi, &err);
                    if (!U_FAILURE(err)) {
                        if (resRunCount) {
                            jint* cResRuns = (jint*)calloc(resRunCount * 2, sizeof(jint));
                                  if (cResRuns) {
                                    UTextOffset limit = 0;
                                    UBiDiLevel level;
                                    jint *p = cResRuns;
                                    while (limit < length) {
                                        ubidi_getLogicalRun(bidi, limit, &limit, &level);
                                        *p++ = (jint)limit;
                                        *p++ = (jint)level;
                                    }

                                    {
                                        const DirProp *dp = bidi->dirProps;
                                        jint ccws = 0;
                                        jint n = 0;
                                        p = cResRuns;
                                        do {
                                            if ((*(p+1) ^ resLevel) & 0x1) {
                                                while (n < *p) {
                                                    if (dp[n++] == WS) {
                                                        ++ccws;
                                                    }
                                                }
                                            } else {
                                                n = *p;
                                            }
                                            p += 2;
                                        } while (n < length);

                                        resCWS = (*env)->NewIntArray(env, ccws);
                                        if (resCWS) {
                                            jint* cResCWS = (jint*)(*env)->GetPrimitiveArrayCritical(env, resCWS, NULL);
                                            if (cResCWS) {
                                                jint ccws = 0;
                                                jint n = 0;
                                                p = cResRuns;
                                                do {
                                                    if ((*(p+1) ^ resLevel) & 0x1) {
                                                        while (n < *p) {
                                                            if (dp[n] == WS) {
                                                                cResCWS[ccws++] = n;
                                                            }
                                                            ++n;
                                                        }
                                                    } else {
                                                        n = *p;
                                                    }
                                                    p += 2;
                                                } while (n < length);
                                                (*env)->ReleasePrimitiveArrayCritical(env, resCWS, cResCWS, 0);
                                            }
                                        }
                                    }

                                    resRuns = (*env)->NewIntArray(env, resRunCount * 2);
				    if (resRuns) {
					(*env)->SetIntArrayRegion(env, resRuns, 0, resRunCount * 2, cResRuns);
				    }
                                    free(cResRuns);
                                }
                            }
                        }
                    }

                resetBidi(env, cls, jbidi, resDir, resLevel, length, resRuns, resCWS);
            }
        }
        ubidi_close(bidi);
    }
}