///checks if the Parse service is active for use
bool platform_isParseActive()
{
    return gIsActive.getEnv()->CallStaticBooleanMethod(gIsActive.classID, gIsActive.methodID);
}