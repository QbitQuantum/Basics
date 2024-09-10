char *_GIO_decomposeURL(const unichar_t *url,char **host, int *port, char **username,
	char **password) {
    unichar_t *pt, *pt2, *upt, *ppt;
    char *path;
    char proto[40];
    /* ftp://[user[:password]@]ftpserver[:port]/url-path */

    *username = NULL; *password = NULL; *port = -1;
    pt = uc_strstr(url,"://");
    if ( pt==NULL ) {
	*host = NULL;
return( cu_copy(url));
    }
    cu_strncpy(proto,url,(size_t)(pt-url)<sizeof(proto)?(size_t)(pt-url):sizeof(proto));
    pt += 3;

    pt2 = u_strchr(pt,'/');
    if ( pt2==NULL ) {
	pt2 = pt+u_strlen(pt);
	path = copy("/");
    } else {
	path = cu_copy(pt2);
    }

    upt = u_strchr(pt,'@');
    if ( upt!=NULL && upt<pt2 ) {
	ppt = u_strchr(pt,':');
	if ( ppt==NULL )
	    *username = cu_copyn(pt,upt-pt);
	else {
	    *username = cu_copyn(pt,ppt-pt);
	    *password = cu_copyn(ppt+1,upt-ppt-1);
	}
	pt = upt+1;
    }

    ppt = u_strchr(pt,':');
    if ( ppt!=NULL && ppt<pt2 ) {
	char *temp = cu_copyn(ppt+1,pt2-ppt-1), *end;
	*port = strtol(temp,&end,10);
	if ( *end!='\0' )
	    *port = -2;
	free(temp);
	pt2 = ppt;
    }
    *host = cu_copyn(pt,pt2-pt);
    if ( *username )
	*password = GIO_PasswordCache(proto,*host,*username,*password);
return( path );
}