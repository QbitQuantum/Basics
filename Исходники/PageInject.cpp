// scan each parm for OBJ_IR (injection request)
// and set it from the hr class then.
// use ptr_string/size_string stuff to point into the hr buf.
// but if we call serialize() then it makes news ones into its own blob.
// so we gotta know our first and last ptr_* pointers for serialize/deseria().
// kinda like how search input works
void setInjectionRequestFromParms ( TcpSocket *sock , 
				    HttpRequest *hr ,
				    CollectionRec *cr ,
				    InjectionRequest *ir ) {

	// just in case set all to zero
	memset ( ir , 0 , sizeof(InjectionRequest ));

	if ( ! cr ) {
		log("inject: no coll rec");
		return;
	}

	// use this, is more reliable, "coll" can disappear from under us
	ir->m_collnum = cr->m_collnum;

	// scan the parms
	for ( int i = 0 ; i < g_parms.m_numParms ; i++ ) {
		Parm *m = &g_parms.m_parms[i];
		if ( m->m_obj != OBJ_IR ) continue;
		// get it
		if ( m->m_type == TYPE_CHARPTR ||
		     m->m_type == TYPE_FILEUPLOADBUTTON ) {
			int32_t stringLen;
			char *str =hr->getString(m->m_cgi,&stringLen,m->m_def);
			// avoid overwriting the "url" parm with the "u" parm
			// since it is just an alias
			if ( ! str ) continue;
			// serialize it as a string
			char *foo = (char *)ir + m->m_off;
			char **ptrPtr = (char **)foo;
			// store the ptr pointing into hr buf for now
			*ptrPtr = str;
			// how many strings are we past ptr_url?
			int32_t count = ptrPtr - &ir->ptr_url;
			// and length. include \0
			int32_t *sizePtr = &ir->size_url + count;
			if ( str ) *sizePtr = stringLen + 1;
			else *sizePtr = 0;
			continue;
		}
		// numbers are easy
		else if ( m->m_type == TYPE_LONG ) {
			int32_t *ii = (int32_t *)((char *)ir + m->m_off);
			int32_t def = atoll(m->m_def);
			*ii = hr->getLong(m->m_cgi,def);
		}
		else if ( m->m_type == TYPE_CHECKBOX || 
			  m->m_type == TYPE_BOOL ) {
			char *ii = (char *)((char *)ir + m->m_off);
			int32_t def = atoll(m->m_def);
			*ii = (char)hr->getLong(m->m_cgi,def);
		}
		else if ( m->m_type == TYPE_IP ) {
			char *ii = (char *)((char *)ir + m->m_off);
			char *is = hr->getString(m->m_cgi,NULL);
			*(int32_t *)ii = 0; // default ip to 0
			// otherwise, set the ip
			if ( is ) *(int32_t *)ii = atoip(is);
		}
		// if unsupported let developer know
		else { char *xx=NULL;*xx=0; }
	}


	// if content is "" make it NULL so XmlDoc will download it
	// if user really wants empty content they can put a space in there
	// TODO: update help then...
	if ( ir->ptr_content && ! ir->ptr_content[0]  )
		ir->ptr_content = NULL;

	if ( ir->ptr_contentFile && ! ir->ptr_contentFile[0]  )
		ir->ptr_contentFile = NULL;

	if ( ir->ptr_contentDelim && ! ir->ptr_contentDelim[0] )
		ir->ptr_contentDelim = NULL;

	if ( ir->ptr_queryToScrape && ! ir->ptr_queryToScrape[0] ) 
		ir->ptr_queryToScrape = NULL;

	if ( ir->ptr_url && ! ir->ptr_url[0] ) 
		ir->ptr_url = NULL;

	// if we had a delimeter but not content, zero it out...
	if ( ! ir->ptr_content && ! ir->ptr_contentFile ) 
		ir->ptr_contentDelim = NULL;
}