    MatcherAccessor(JNIEnv* env, jint addr, jstring javaInput, bool reset) {
        init(env, addr);

        mJavaInput = javaInput;
        mChars = env->GetStringChars(mJavaInput, NULL);
        if (mChars == NULL) {
            return;
        }

        mUText = utext_openUChars(NULL, mChars, env->GetStringLength(mJavaInput), &mStatus);
        if (mUText == NULL) {
            return;
        }

        if (reset) {
            mMatcher->reset(mUText);
        } else {
            mMatcher->refreshInputText(mUText, mStatus);
        }
    }