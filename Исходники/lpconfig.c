int64_t lp_config_get_int64(const LpConfig *lpconfig,const char *section, const char *key, int64_t default_value){
	const char *str=lp_config_get_string(lpconfig,section,key,NULL);
	if (str!=NULL) {
#ifdef WIN32
		return (int64_t)_atoi64(str);
#else
		return atoll(str);
#endif
	}
	else return default_value;
}