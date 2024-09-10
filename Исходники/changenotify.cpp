/*************************************************************************
 * NTSHChangeNotifyDeregister            [SHELL32.641]
 */
EXTERN_C DWORD WINAPI NTSHChangeNotifyDeregister(ULONG x1)
{
    FIXME("(0x%08x):semi stub.\n",x1);

    return SHChangeNotifyDeregister( x1 );
}