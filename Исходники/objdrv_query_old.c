/*** qy_internal_ReadObject - reads an object, with its attributes (blobs
 *** limited to 255 bytes), and stores the data in the object-attr cache,
 *** or looks the object up there if it has already been cached.
 ***/
pQyObjAttr
qy_internal_ReadObject(char* path, pObjSession s)
    {
    pQyObjAttr objattr;
    pObject obj;
    char* attrname;
    int type;
    int ival;
    char* sval;

    	/** Check the cache first. **/
	objattr = (pQyObjAttr)xhLookup(&QY_INF.ObjAttrCache, path);
	if (objattr) 
	    {
	    objattr->CacheTime = time(NULL);
	    objattr->LinkCnt++;
	    return objattr;
	    }

	/** Otherwise, open the object & read its attrs. **/
	obj = objOpen(s, path, O_RDONLY, 0600, "system/file");
	if (!obj) return NULL;

	/** Allocate... **/
	objattr = (pQyObjAttr)nmMalloc(sizeof(QyObjAttr));
	if (!objattr)
	    {
	    objClose(obj);
	    return NULL;
	    }
	memccpy(objattr->ObjPathname,path,0,255);
	objattr->ObjPathname[255]=0;
	xsInit(&objattr->AttrNameBuf);
	xsInit(&objattr->AttrValueBuf);
	xaInit(&objattr->AttrNames,32);
	xaInit(&objattr->AttrValues,32);

	/** Loop through attributes. **/
	for(attrname=objGetFirstAttr(obj);attrname;attrname=objGetNextAttr(obj))
	    {
	    /** Copy attrname to names listing.  Be sure to copy the '\0'. **/
	    xaAddItem(&objattr->AttrNames, xsStringEnd(&objattr->AttrNameBuf));
	    xsConcatenate(&objattr->AttrNameBuf, attrname, strlen(attrname)+1);

	    /** Get type and copy to attrvalues. **/
	    type = objGetAttrType(obj,attrname);
	    switch(type)
	        {
		case DATA_T_INTEGER:
		    if (objGetAttrValue(obj,attrname,&ival) == 0)
		        {
		        xaAddItem(&objattr->AttrValues, xsStringEnd(&objattr->AttrValueBuf));
			xsConcatenate(&objattr->AttrValueBuf, (char*)&ival, 4);
			}
		    else
		        {
		        xaAddItem(&objattr->AttrValues, NULL);
			}
		    break;

		case DATA_T_STRING:
		    if (objGetAttrValue(obj,attrname,&sval) == 0)
		        {
		        xaAddItem(&objattr->AttrValues, xsStringEnd(&objattr->AttrValueBuf));
		        xsConcatenate(&objattr->AttrValueBuf,sval, strlen(sval)+1);
			}
		    else
		        {
		        xaAddItem(&objattr->AttrValues, NULL);
			}
		    break;

		default:
		    break;
		}
	    }

	/** Close up the object **/
	objClose(obj);

	/** Cache the objattr structure **/
	xhAdd(&QY_INF.ObjAttrCache, objattr->ObjPathname, (void*)objattr);
	xaAddItem(&QY_INF.ObjAttrCacheList, (void*)objattr);

    return objattr;
    }