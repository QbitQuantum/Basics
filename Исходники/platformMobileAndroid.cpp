///returns if the application was launched via a Custom URL Scheme
bool platform_wasOpenedViaCustomURL()
{
    jboolean result = gDidCustomURLOpen.getEnv()->CallStaticBooleanMethod(gDidCustomURLOpen.classID, gDidCustomURLOpen.methodID);    
    return (bool)result;
}