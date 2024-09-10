Int32 SoftKeyboard::GetKeyYMargin()
{
    AutoPtr<IPinyinEnvironmentHelper> helper;
    CPinyinEnvironmentHelper::AcquireSingleton((IPinyinEnvironmentHelper**)&helper);
    AutoPtr<IPinyinEnvironment> env;
    helper->GetInstance((IPinyinEnvironment**)&env);
    Float factor = 0.f;
    return (Int32) (mKeyYMargin * mSkbCoreHeight * (env->GetKeyYMarginFactor(&factor), factor));
}