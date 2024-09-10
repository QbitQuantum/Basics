EXPORT_C TInt CElementParser::ParseElementsL(const TDesC8& aData)
/** Parses a data buffer into the currently set MSdpElementBuilder interface.

If a whole number of data elements can not be parsed out of aData, the number 
of bytes left unparsed is returned. Those bytes should be prepended to the 
buffer when the function is next called. 

@param aData Buffer to parse
@return Number of bytes not consumed */
	{
	TUint8* ptr = (TUint8*)aData.Ptr();
	const TUint8* ptrE = ptr + aData.Length();

	CloseListsL();
	while ((ptr < ptrE) && (iBuilder != NULL))
		{

		// Remember start of this data element
		TUint8* ptrStart = ptr;

		// We know there's at least one byte already..
		TUint8 type = (TUint8)(*ptr>>KSdpElemHdrTypeShift);
		TUint8 sizedesc  = (TUint8)(*ptr&KSdpElemHdrSizeMask);
		++ptr;

		if ( type >= sizeof(KSdpElementValidSizes) ||
			 !(KSdpElementValidSizes[type]&(1<<sizedesc)) )
			{// Invalid size desc for type.
			LOG2(_L("SDP: Invalid size descriptor %d for type %d!"), sizedesc, type);
			User::Leave(KErrSdpParserInvalidSizeForType);
			}

		TUint elementLen;
		if (type == ETypeNil)
			{// we've already checked that sizedesc == 0
			elementLen = 0;
			}
		else if(sizedesc<=ESizeSixteenBytes)
			{
			elementLen = 1<<sizedesc;
			}
		else
			{
			TUint addSzBytes = 1<<(sizedesc-ESizeOneAdditional);
			if((addSzBytes)>TUint(ptrE-ptr))
				return (ptrE-ptrStart);
			elementLen = SdpUtil::GetUint(TPtrC8(ptr, addSzBytes));
			ptr += addSzBytes;
			}

		if (!iListStack->IsEmpty() && 
			(TInt)((ptr-ptrStart)+elementLen) > iListStack->Head())
			{// Error! This item is longer than the list it is in!!
			User::Leave(KErrSdpParserInvalidSizeForParentList);
			}

		TUint compositeLen = 0;
		if (IsComposite(type))
			{//Composite node. We'll parse down into it.
			compositeLen = elementLen;
			elementLen = 0;		// composites have no element length.
			}

		if((elementLen)>TUint(ptrE-ptr))return (ptrE-ptrStart);

		TPtrC8 data(ptr,elementLen);

		switch (type)
			{
		case ETypeNil:
			iBuilder=iBuilder->BuildNilL();
			break;
		case ETypeUint:
			iBuilder=iBuilder->BuildUintL(data);
			break;
		case ETypeInt:
			iBuilder=iBuilder->BuildIntL(data);
			break;
		case ETypeUUID:
			{
			TUUID uuid;
			uuid.SetL(data);
			iBuilder=iBuilder->BuildUUIDL(uuid);
			}
			break;
		case ETypeString:
			iBuilder=iBuilder->BuildStringL(data);
			break;
		case ETypeBoolean:
			iBuilder=iBuilder->BuildBooleanL(SdpUtil::GetUint(data));
			break;		
		case ETypeURL:
			iBuilder=iBuilder->BuildURLL(data);
			break;
		case ETypeDES:
			iBuilder=iBuilder->BuildDESL();
			break;
		case ETypeDEA:
			iBuilder=iBuilder->BuildDEAL();
			break;
		default:
			iBuilder=iBuilder->BuildUnknownL(type, sizedesc, data);
			break;
			};

		ptr += elementLen;


		if (!iListStack->IsEmpty())
			{// Adjust size of existing head entry so we know when the DES/DEA is finished
			iListStack->Head() -= (ptr-ptrStart)+compositeLen;
			}

		if (IsComposite(type))
			{ // push the length of the DES/DEA on top of the stack and mark the list
			iBuilder=iBuilder->StartListL();
			iListStack->PushL(compositeLen);
			}

		CloseListsL();
		}

	__ASSERT_DEBUG(ptr<=ptrE, ParsePanic(EFrameOverrun));

	return ptrE-ptr;
	}