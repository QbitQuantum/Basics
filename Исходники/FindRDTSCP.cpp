int main ()
{
#ifdef _MSC_VER
        unsigned aux = 0x00;
        __rdtscp(&aux);
#else // _MSC_VER
        unsigned eax = 0x00;
        unsigned edx = 0x00;
        unsigned ecx = 0x00;
        __asm__ volatile
            (
             "rdtscp\\n"
             : "=a" (eax), "=d" (edx), "=c" (ecx)
            );
#endif // _MSC_VER

    return 0;
}