static BOOL script_initCodeFromUri(struct Shader_Script* me, const char* uri)
{
 size_t i;
 int rv;
 resource_item_t *res;
	ppCScripts p = (ppCScripts)gglobal()->CScripts.prv;

  rv = FALSE; /* initialize it */

 /* strip off whitespace at the beginning JAS */
 while ((*uri<= ' ') && (*uri>0)) uri++;

 /* Try javascript protocol */
 for(i=0; i!=ARR_SIZE(JS_PROTOCOLS); ++i)
 {
  const char* u=uri;
  const char* v=JS_PROTOCOLS[i];

  while(*u && *v && *u==*v)
  {
   ++u;
   ++v;
  }

  /* Is this a "data:text/plain," uri? JAS*/
  if((!*v && *u==',') || (!*v && *u==':')) {
   	if (me != NULL) {
		return script_initCode(me, u+1); /* a script */
	} else {
		p->buffer = STRDUP(u+1);
		return TRUE; /* a shader, program text will be in the "buffer" */
	}
   }
 }

 /* Not a valid script in this SFString. Lets see if this
    is this a possible file that we have to get? */

 DEBUG_CPARSER("script_initCodeFromUri, uri is %s\n", uri); 
 printf ("script_initCodeFromUri, uri is %s\n", uri); 

 res = resource_create_single(uri);
 resource_identify(gglobal()->resources.root_res, res);
 if (res->type != rest_invalid) {
	 if (resource_fetch(res)) {
		 if (resource_load(res)) {
			 s_list_t *l;
			 openned_file_t *of;

			 l = res->openned_files;
			 of = ml_elem(l);

			/* ok - Scripts get initialized; shaders get the buffer returned */
			if (me==NULL) { /* a Shader */
			 	p->buffer = STRDUP(of->fileData);
			 	/* JAS printf("**** Shader:\n%s\n", buffer); 
				printf ("*** Shader: doing the quick return here\n"); */
				return TRUE;
			} else {
				/* a Script */
			 	/* printf("**** Script:\n%s\n", buffer); */
			 	rv = script_initCode(me, of->fileData);
			}
		 }
	 }
 }
 
 
 if (res->status == ress_loaded && rv) {
	 /* ok - we are replacing EXTERNPROTO with PROTO */
	 res->status = ress_parsed;
	 res->complete = TRUE;
	 return TRUE;
 } else {
	 /* failure, FIXME: remove res from root_res... */
/* 		resource_destroy(res); */
 }

 return FALSE;
}