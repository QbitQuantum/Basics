int set_lang(void)
{
	unsigned int lang_usr,lang_sys,id;

	id=GetSystemDefaultLangID();
	lang_sys=PRIMARYLANGID(id);
	id=GetUserDefaultLangID();
	lang_usr=PRIMARYLANGID(id);
	if(lang_usr!=lang_sys) {
		printf("warning: user language differs from system language\r\n\r\n");
		printf("1. system : ");print_lang(lang_sys);
		printf("2. user   : "******"Select(1-2): ");
		id=getch();
	if(id!=49&&id!=50) {
		printf("wrong choice '%c', leaving.\r\n",id);
		exit(0);
		}
	if(id==49) {
		printf("system language\r\n");
		return lang_sys;
		}
	else
		printf("user language\r\n");
	}
	return lang_usr;
}