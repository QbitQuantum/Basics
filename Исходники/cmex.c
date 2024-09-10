/** Get a value (object, clock, or global)
	\verbatim gl('get',name) \endverbatim
 **/
void cmex_get(int nlhs, mxArray *plhs[], /**< {data} */
				int nrhs, const mxArray *prhs[] ) /**< (name) */
{
	if (nrhs>0)
	{
		char name[1024];
		OBJECT *obj=NULL;
		if (!mxIsChar(prhs[0]))
			output_error("entity name (arg 1) is not a string");
		else if (nlhs>1)
			output_error("only one return value is possible");
		else if (mxGetString(prhs[0],name,sizeof(name))!=0)
			output_error("object name too long");
		else if (strcmp(name,"clock")==0)
		{
			char *fnames[] = {"timestamp","timestring","timezone"};
			char buffer[256];
			mxArray *pTimestamp = mxCreateDoubleMatrix(1,1,mxREAL);
			mxArray *pTimestring = mxCreateString(convert_from_timestamp(global_clock,buffer,sizeof(buffer))?buffer:"(error)");
			mxArray *pTimezone = mxCreateString(timestamp_current_timezone());

			*(double*)mxGetPr(pTimestamp) = ((double)global_clock)/TS_SECOND;
			plhs[0] = mxCreateStructMatrix(1,1,sizeof(fnames)/sizeof(fnames[0]),fnames);
			mxSetFieldByNumber(plhs[0],0,0,pTimestamp);
			mxSetFieldByNumber(plhs[0],0,1,pTimestring);
			mxSetFieldByNumber(plhs[0],0,2,pTimezone);
		}
		else if (strcmp(name,"property")==0 && nrhs>1)
		{
			if (mxGetString(prhs[1],name,sizeof(name))!=0)
				output_error("missing property name");
			else
			{
				char classname[256];
				char propname[256];
				if (sscanf(name,"%[^.].%s",classname,propname)==2)
				{
					CLASS *pClass = class_get_class_from_classname(classname);
					if (pClass)
					{
						PROPERTY *pProp = class_find_property(pClass,propname);
						if (pProp)
						{
							char *fields[] = {"class","name","type","size","access","unit","delegation","keywords"};
							int fn = 0;
							mxArray *oclass = mxCreateString(classname);
							mxArray *prop = mxCreateString(pProp->name);
							mxArray *type = mxCreateString(class_get_property_typename(pProp->ptype));
							mxArray *size = mxCreateDoubleMatrix(1,1,mxREAL); 
							mxArray *access = mxCreateString("(na)"); /** @todo implement get_property access info (ticket #187) */
							mxArray *unit = mxCreateString(pProp->unit->name);
							mxArray *delegation = mxCreateString(pProp->delegation?pProp->delegation->oclass->name:"(none)");
							mxArray *keywords = mxCreateString("(na)"); /** @todo implement get_property keywords (ticket #188) */
							*(mxGetPr(size)) = pProp->size==0?1:pProp->size;
							plhs[0] = mxCreateStructMatrix(1,1,sizeof(fields)/sizeof(fields[0]),fields);
							mxSetFieldByNumber(plhs[0],0,fn++,oclass);
							mxSetFieldByNumber(plhs[0],0,fn++,prop);
							mxSetFieldByNumber(plhs[0],0,fn++,type);
							mxSetFieldByNumber(plhs[0],0,fn++,size);
							mxSetFieldByNumber(plhs[0],0,fn++,access);
							mxSetFieldByNumber(plhs[0],0,fn++,unit);
							mxSetFieldByNumber(plhs[0],0,fn++,delegation);
							mxSetFieldByNumber(plhs[0],0,fn++,keywords);
						}
						else
							output_error("property %s is not found in class %s", propname,classname);
					}
					else
						output_error("class %s is not found");
				}
				else
					output_error("property name not in class.name format");
			}
		}
		else if ((convert_to_object(name,&obj,NULL))==0)
		{
			GLOBALVAR *var = global_find(name);
			if (var==NULL)
				output_error("entity '%s' not found", name);
			else if (var->prop->ptype==PT_double)
			{
				size_t size = var->prop->size?var->prop->size:1;
				plhs[0] = mxCreateDoubleMatrix(size,1,mxREAL);
				memcpy(mxGetPr(plhs[0]),(void*)var->prop->addr,sizeof(double)*size);
			}
			else if (var->prop->ptype==PT_int32)
			{
				size_t size = var->prop->size?var->prop->size:1;
				plhs[0] = mxCreateDoubleMatrix(size,1,mxREAL);

				memcpy(mxGetPr(plhs[0]),(void*)var->prop->addr,sizeof(double)*size);
			}
			else if (var->prop->ptype!=PT_double)
				output_error("cannot retrieve globals that are of type %s",class_get_property_typename(var->prop->ptype));
		}
		else if ((plhs[0]=get_object_data(obj))==NULL)
			output_error("unable to extract %s data", name);
	}
	else
		output_error("object not specified");
	return;
}