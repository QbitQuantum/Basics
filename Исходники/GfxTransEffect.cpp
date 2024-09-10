EXPORT_C void GfxTransEffect::Abort(const CCoeControl * aKey)
{
    __ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicAbortArgument));
#ifndef TRANSITIONS_DISABLED
    CGfxTransEffect *singleton = CGfxTransEffect::StaticNoCreate(aKey);
    if(singleton)
        singleton->Abort(aKey);
#endif
}