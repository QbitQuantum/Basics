/* parse the segment number.
 * The extra %c picks up characters that might be after the number,
 * so that page5_hash doesn't match for page5.
 */
int64_t	af_segname_page_number(const char *name)
{
#ifdef KERNEL_LIBRARY
#define PAGE_NAME "page"
	if(_strnicmp(name,PAGE_NAME,strlen(PAGE_NAME))==0)
	{
		int64_t pagenum;
		for (int i=strlen(PAGE_NAME);i<strlen(name);i++)
			if (!isdigit(name[i])) return -1;

		pagenum = _atoi64(name+strlen(PAGE_NAME));
		return pagenum;
	}
#define SEG_NAME "seg"
	if(_strnicmp(name,SEG_NAME,strlen(SEG_NAME))==0)
	{
		int64_t pagenum;
		for (int i=strlen(SEG_NAME);i<strlen(name);i++)
			if (!isdigit(name[i])) return -1;

		pagenum = _atoi64(name+strlen(SEG_NAME));
		return pagenum;
	}
	return -1;
#else
    int64_t pagenum;
    char  ch;
    if(sscanf(name,AF_PAGE"%c",&pagenum,&ch)==1){
	return pagenum;			// new-style page number
    }
    if(sscanf(name,AF_SEG_D"%c",&pagenum,&ch)==1){
	return pagenum;			// old-style page number
    }
    return -1;
#endif
}