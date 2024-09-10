INLINE void WriteChar(Int32 const &c) {
#ifdef __linux
    printf("%lc", c);
    fflush(stdout);                     // 令 Linux 终端立即输出　而不是等 \n
#else
	putwchar(c);
#endif
}