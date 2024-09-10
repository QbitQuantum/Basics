void lzham_debug_break(void)
{
#if LZHAM_USE_WIN32_API
   DebugBreak();
#endif   
}