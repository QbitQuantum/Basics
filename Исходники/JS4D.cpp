VValueSingle *JS4D::ValueToVValue( ContextRef inContext, ValueRef inValue, ValueRef *outException)
{
	if (inValue == NULL)
		return NULL;
	
	VValueSingle *value;
	JSType type = JSValueGetType( inContext, inValue);
	switch( type)
	{
		case kJSTypeUndefined:
		case kJSTypeNull:
			value = NULL;	//new VEmpty;
			break;
		
		case kJSTypeBoolean:
			value = new VBoolean( JSValueToBoolean( inContext, inValue));
			break;

		case kJSTypeNumber:
			value = new VReal( JSValueToNumber( inContext, inValue, outException));
			break;

		case kJSTypeString:
			{
				JSStringRef jsString = JSValueToStringCopy( inContext, inValue, outException);
				if (jsString != NULL)
				{
					VString *s = new VString;
					size_t length = JSStringGetLength( jsString);
					UniChar *p = (s != NULL) ? s->GetCPointerForWrite( length) : NULL;
					if (p != NULL)
					{
						::memcpy( p, JSStringGetCharactersPtr( jsString), length * sizeof( UniChar));
						s->Validate( length);
						value = s;
					}
					else
					{
						delete s;
						value = NULL;
					}
					JSStringRelease( jsString);
				}
				else
				{
					value = NULL;
				}
				break;
			}
		
		case kJSTypeObject:
			{
				if (ValueIsInstanceOf( inContext, inValue, CVSTR( "Date"), outException))
				{
					VTime *time = new VTime;
					if (time != NULL)
					{
						JSObjectRef dateObject = JSValueToObject( inContext, inValue, outException);
						DateObjectToVTime( inContext, dateObject, *time, outException);
						value = time;
					}
					else
					{
						value = NULL;
					}
				}
				else if (JSValueIsObjectOfClass( inContext, inValue, VJSFolderIterator::Class()))
				{
					value = NULL;
					JS4DFolderIterator* container = static_cast<JS4DFolderIterator*>(JSObjectGetPrivate( JSValueToObject( inContext, inValue, outException) ));
					if (testAssert( container != NULL))
					{
						VFolder* folder = container->GetFolder();
						if (folder != NULL)
						{
							VString *s = new VString;
							if (s != NULL)
								folder->GetPath( *s, FPS_POSIX);
							value = s;
						}
					}
				}
				else if (JSValueIsObjectOfClass( inContext, inValue, VJSFileIterator::Class()))
				{
					value = NULL;
					JS4DFileIterator* container = static_cast<JS4DFileIterator*>(JSObjectGetPrivate( JSValueToObject( inContext, inValue, outException) ));
					if (testAssert( container != NULL))
					{
						VFile* file = container->GetFile();
						if (file != NULL)
						{
							VString *s = new VString;
							if (s != NULL)
								file->GetPath( *s, FPS_POSIX);
							value = s;
						}
					}
				}
				else if (JSValueIsObjectOfClass( inContext, inValue, VJSBlob::Class()))
				{
					// remember File inherits from Blob so one must check File before Blob
					VJSBlob::PrivateDataType* blobValue = static_cast<VJSBlob::PrivateDataType*>(JSObjectGetPrivate( JSValueToObject( inContext, inValue, outException) ));
					if (testAssert( blobValue != NULL))
					{
						VJSDataSlice *slice = blobValue->RetainDataSlice();
						VBlobWithPtr *blob = new VBlobWithPtr;
						if ( (blob != NULL) && (slice != NULL) && (slice->GetDataSize() > 0) )
						{
							if (blob->PutData( slice->GetDataPtr(), slice->GetDataSize()) != VE_OK)
							{
								delete blob;
								blob = NULL;
							}
						}
						value = blob;
						ReleaseRefCountable( &slice);
					}
					else
					{
						value = NULL;
					}
				}
#if !VERSION_LINUX  // Postponed Linux Implementation !
				else if (JSValueIsObjectOfClass( inContext, inValue, VJSImage::Class()))
				{
					VJSImage::PrivateDataType* piccontainer = static_cast<VJSImage::PrivateDataType*>(JSObjectGetPrivate( JSValueToObject( inContext, inValue, outException) ));
					if (testAssert( piccontainer != NULL))
					{
						VPicture *vpic = piccontainer->GetPict();
						value = (vpic != NULL) ? new VPicture(*vpic) : NULL;
					}
					else
					{
						value = NULL;
					}
				}
#endif
				else
				{
					value = NULL;
				}
				break;
			}
		
		default:
			value = NULL;
			break;
	}
	return value;
}