/*
Description:

    This is used whenever there is a media type change on an output pin and the 
    Output queue is being reconfigured.
    The possible return values for the function are as follows
    
    DeviceMftTransformXVPIllegal        -> If either of the mediatypes or both are NULL
    DeviceMftTransformXVPDisruptiveIn   -> If the mediatype  at the output pin is greater than the input pin. This will result in change of the media type on the input
    DeviceMftTransformXVPDisruptiveOut  -> This is a reconfiguration or addition of the XVP in the Output pin queue
    DeviceMftTransformXVPCurrent        -> No XVP needed at all
    Note: This iteration doesn't support decoder. The next one will and this function will accordingly change
*/
STDMETHODIMP CompareMediaTypesForXVP(
    _In_opt_ IMFMediaType *inMediaType,
    _In_    IMFMediaType                *newMediaType,
    _Inout_ MF_TRANSFORM_XVP_OPERATION  *operation 
    )
{
    UINT32  unWidthin, unHeightin, unWidthNew, unHeightNew = 0;
    HRESULT hr          = S_OK;
    GUID    guidTypeA   = GUID_NULL;
    GUID    guidTypeB   = GUID_NULL;
    
    *operation = DeviceMftTransformXVPIllegal;
    if ((!inMediaType) || (!newMediaType))
    {
       goto done;
    }

    DMFTCHECKHR_GOTO( MFGetAttributeSize( inMediaType, MF_MT_FRAME_SIZE, &unWidthin, &unHeightin ), done );
    DMFTCHECKHR_GOTO( MFGetAttributeSize( newMediaType, MF_MT_FRAME_SIZE, &unWidthNew, &unHeightNew ), done );


    if ( SUCCEEDED( inMediaType->GetGUID(  MF_MT_MAJOR_TYPE, &guidTypeA ) ) &&
         SUCCEEDED( newMediaType->GetGUID( MF_MT_MAJOR_TYPE, &guidTypeB ) ) &&
        IsEqualGUID( guidTypeA, guidTypeB ) )
    {
        if ( SUCCEEDED( inMediaType->GetGUID ( MF_MT_SUBTYPE, &guidTypeA ) ) &&
             SUCCEEDED( newMediaType->GetGUID( MF_MT_SUBTYPE, &guidTypeB ) ) &&
            IsEqualGUID( guidTypeA, guidTypeB ) )
        {
            //Comparing the MF_MT_AM_FORMAT_TYPE for the directshow format guid
#if 0
            if (SUCCEEDED(inMediaType->GetGUID(MF_MT_AM_FORMAT_TYPE, &guidTypeA)) &&
                SUCCEEDED(newMediaType->GetGUID(MF_MT_AM_FORMAT_TYPE, &guidTypeB)) &&
                IsEqualGUID(guidTypeA, guidTypeB))
#endif
            {

                if (!(( unWidthin == unWidthNew ) &&
                    ( unHeightin == unHeightNew ) ) )
                {
                    if ( ( unWidthNew > unWidthin ) || ( unHeightNew > unHeightin ) )
                    {
                      *operation = DeviceMftTransformXVPDisruptiveIn; //Media type needs to change at input
                    }
                    else
                    {
                        *operation = DeviceMftTransformXVPDisruptiveOut; //Media type needs to change at output
                    }
                    goto done;
                }

                if ( MFGetAttributeUINT32( inMediaType,  MF_MT_SAMPLE_SIZE, 0 ) !=
                     MFGetAttributeUINT32( newMediaType, MF_MT_SAMPLE_SIZE, 0 ) )
                {
                    hr = S_FALSE; //Sample sizes differ. 
                    goto done;
                }
                else
                {
                    //Same media type.. No XVP needed or the current XVP is fine!
                    *operation = DeviceMftTransformXVPCurrent;
                }
            }
        }
        else
        {
            //This is a disruptive operation. Actually a decoder operation!
            *operation = DeviceMftTransformXVPDisruptiveIn;
        }
    }
 done:
    return hr;
}