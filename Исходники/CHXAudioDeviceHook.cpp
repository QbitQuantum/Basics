///////////////////////////////////
//
//  IMediaObjectImpl::InternalGetOutputType
//
//  *** Called by GetOutputType, description below ***
//
//  The GetOutputType method retrieves a preferred media type for a specified
//  output stream.
//
//  Parameters
//
//      dwOutputStreamIndex
//          Zero-based index of an output stream on the DMO.
//
//      dwTypeIndex
//          Zero-based index on the set of acceptable media types.
//
//      pmt
//          [out] Pointer to a DMO_MEDIA_TYPE structure allocated by the
//          caller. The method fills the structure with the media type. The
//          format block might be NULL, in which case the format type GUID is GUID_NULL.
//
//  Return Value
//      S_OK Success
//      DMO_E_INVALIDSTREAMINDEX Invalid stream index
//      DMO_E_NO_MORE_ITEMS Type index is out of range
//      E_OUTOFMEMORY Insufficient memory
//      E_POINTER NULL pointer argument
//
//  Call this method to enumerate an output stream's preferred media types. The
//  DMO assigns each media type an index value, in order of preference. The
//  most preferred type has an index of zero. To enumerate all the types, make
//  successive calls while incrementing the type index, until the method returns
//  DMO_E_NO_MORE_ITEMS.
//
//  If the method succeeds, call MoFreeMediaType to free the format block.
//
//  To set the media type, call the SetOutputType method. Setting the media type
//  on one stream can change another stream's preferred types. In fact, a stream
//  might not have a preferred type until the type is set on another stream. For
//  example, a decoder might not have a preferred output type until the input
//  type is set. However, the DMO is not required to update its preferred types
//  dynamically in this fashion. Thus, the types returned by this method are not
//  guaranteed to be valid; they might fail when used in the SetOutputType method.
//  Conversely, the DMO is not guaranteed to enumerate every media type that it
//  supports. To test whether a particular media type is acceptable, call
//  SetOutputType with the DMO_SET_TYPEF_TEST_ONLY flag.
//
//
HRESULT CHXAudioDeviceHookBase::InternalGetOutputType(DWORD dwOutputStreamIndex, DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt)
{
    // This function resembles InternalGetInputType() since the input and output types must
    // be consistent for DirectSound

    HRESULT hr = S_OK;

    if (dwTypeIndex > 0)
    {
        return DMO_E_NO_MORE_ITEMS;
    }

    // If pmt is NULL, and the type index is in range, we return S_OK
    if (pmt == NULL)
    {
        return S_OK;
    }

    // If the input type is set, we prefer to use that one
    if (InputTypeSet(0))
    {
        return MoCopyMediaType(pmt, InputType(0));
    }

    hr = MoInitMediaType(pmt, sizeof(WAVEFORMATEX));

    if (SUCCEEDED(hr))
    {
        pmt->majortype  = MEDIATYPE_Audio;
        pmt->subtype    = MEDIASUBTYPE_PCM;         // We take PCM format!
        pmt->formattype = FORMAT_None;
    }

    return hr;
}