FILE *fmemopen (void *buf, size_t size, const char *opentype)
{
FILE *f;
assert(strcmp(opentype, "r") == 0);
/* f = tmpfile(); 
errno_t err; */
tmpfile_s(&f);
fwrite(buf, 1, size, f);
rewind(f);
return f;
}