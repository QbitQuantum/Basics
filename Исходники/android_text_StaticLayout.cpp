        ScopedBreakIterator(JNIEnv* env, BreakIterator* breakIterator, jcharArray inputText,
                            jint length) : mBreakIterator(breakIterator), mChars(env, inputText) {
            UErrorCode status = U_ZERO_ERROR;
            mUText = utext_openUChars(NULL, mChars.get(), length, &status);
            if (mUText == NULL) {
                return;
            }

            mBreakIterator->setText(mUText, status);
        }