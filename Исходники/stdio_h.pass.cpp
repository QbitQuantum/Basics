int main()
{
    FILE* fp = 0;
    fpos_t fpos = {0};
    size_t s = 0;
    char* cp = 0;
    va_list va;
    static_assert((std::is_same<decltype(remove("")), int>::value), "");
    static_assert((std::is_same<decltype(rename("","")), int>::value), "");
    static_assert((std::is_same<decltype(tmpfile()), FILE*>::value), "");
    static_assert((std::is_same<decltype(tmpnam(cp)), char*>::value), "");
    static_assert((std::is_same<decltype(fclose(fp)), int>::value), "");
    static_assert((std::is_same<decltype(fflush(fp)), int>::value), "");
    static_assert((std::is_same<decltype(fopen("", "")), FILE*>::value), "");
    static_assert((std::is_same<decltype(freopen("", "", fp)), FILE*>::value), "");
    static_assert((std::is_same<decltype(setbuf(fp,cp)), void>::value), "");
    static_assert((std::is_same<decltype(vfprintf(fp,"",va)), int>::value), "");
    static_assert((std::is_same<decltype(fprintf(fp," ")), int>::value), "");
    static_assert((std::is_same<decltype(fscanf(fp,"")), int>::value), "");
    static_assert((std::is_same<decltype(printf("\n")), int>::value), "");
    static_assert((std::is_same<decltype(scanf("\n")), int>::value), "");
    static_assert((std::is_same<decltype(snprintf(cp,0,"p")), int>::value), "");
    static_assert((std::is_same<decltype(sprintf(cp," ")), int>::value), "");
    static_assert((std::is_same<decltype(sscanf("","")), int>::value), "");
    static_assert((std::is_same<decltype(vfprintf(fp,"",va)), int>::value), "");
    static_assert((std::is_same<decltype(vfscanf(fp,"",va)), int>::value), "");
    static_assert((std::is_same<decltype(vprintf(" ",va)), int>::value), "");
    static_assert((std::is_same<decltype(vscanf("",va)), int>::value), "");
    static_assert((std::is_same<decltype(vsnprintf(cp,0," ",va)), int>::value), "");
    static_assert((std::is_same<decltype(vsprintf(cp," ",va)), int>::value), "");
    static_assert((std::is_same<decltype(vsscanf("","",va)), int>::value), "");
    static_assert((std::is_same<decltype(fgetc(fp)), int>::value), "");
    static_assert((std::is_same<decltype(fgets(cp,0,fp)), char*>::value), "");
    static_assert((std::is_same<decltype(fputc(0,fp)), int>::value), "");
    static_assert((std::is_same<decltype(fputs("",fp)), int>::value), "");
    static_assert((std::is_same<decltype(getc(fp)), int>::value), "");
    static_assert((std::is_same<decltype(getchar()), int>::value), "");
    static_assert((std::is_same<decltype(gets(cp)), char*>::value), "");
    static_assert((std::is_same<decltype(putc(0,fp)), int>::value), "");
    static_assert((std::is_same<decltype(putchar(0)), int>::value), "");
    static_assert((std::is_same<decltype(puts("")), int>::value), "");
    static_assert((std::is_same<decltype(ungetc(0,fp)), int>::value), "");
    static_assert((std::is_same<decltype(fread((void*)0,0,0,fp)), size_t>::value), "");
    static_assert((std::is_same<decltype(fwrite((const void*)0,0,0,fp)), size_t>::value), "");
    static_assert((std::is_same<decltype(fgetpos(fp, &fpos)), int>::value), "");
    static_assert((std::is_same<decltype(fseek(fp, 0,0)), int>::value), "");
    static_assert((std::is_same<decltype(fsetpos(fp, &fpos)), int>::value), "");
    static_assert((std::is_same<decltype(ftell(fp)), long>::value), "");
    static_assert((std::is_same<decltype(rewind(fp)), void>::value), "");
    static_assert((std::is_same<decltype(clearerr(fp)), void>::value), "");
#if !defined(feof)
    //check return type of feof only if it's not an macro which may be a compound expression
    static_assert((std::is_same<decltype(feof(fp)), int>::value), "");
#endif
#if !defined(ferror)
    //check return type of ferror only if it's not an macro which may be a compound expression
    static_assert((std::is_same<decltype(ferror(fp)), int>::value), "");
#endif
    static_assert((std::is_same<decltype(perror("")), void>::value), "");
}