/*
    JSCFRelease
*/
void JSCFRelease(CFAllocatorRef allocator, const void *value)
{
    JSRelease((JSTypeRef)value);
}