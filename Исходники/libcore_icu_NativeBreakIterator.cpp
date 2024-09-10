  BreakIteratorAccessor(JNIEnv* env, jlong address, jstring javaInput, bool reset) {
    init(env, address);
    mJavaInput = javaInput;

    if (mJavaInput == NULL) {
      return;
    }

    mChars = env->GetStringChars(mJavaInput, NULL);
    if (mChars == NULL) {
      return;
    }

    mUText = utext_openUChars(NULL, mChars, env->GetStringLength(mJavaInput), &mStatus);
    if (mUText == NULL) {
      return;
    }

    if (reset) {
      mBreakIterator->setText(mUText, mStatus);
    } else {
      mBreakIterator->refreshInputText(mUText, mStatus);
    }
  }