/**************************************************************************
 *          WsWriteBody		[webservices.@]
 */
HRESULT WINAPI WsWriteBody( WS_MESSAGE *handle, const WS_ELEMENT_DESCRIPTION *desc, WS_WRITE_OPTION option,
                            const void *value, ULONG size, WS_ERROR *error )
{
    struct msg *msg = (struct msg *)handle;
    HRESULT hr;

    TRACE( "%p %p %08x %p %u %p\n", handle, desc, option, value, size, error );
    if (error) FIXME( "ignoring error parameter\n" );

    if (!handle || !desc) return E_INVALIDARG;
    if (msg->state != WS_MESSAGE_STATE_WRITING) return WS_E_INVALID_OPERATION;

    if (desc->elementLocalName &&
        (hr = WsWriteStartElement( msg->writer_body, NULL, desc->elementLocalName, desc->elementNs,
                                   NULL )) != S_OK) return hr;

    if ((hr = WsWriteType( msg->writer_body, WS_ANY_ELEMENT_TYPE_MAPPING, desc->type, desc->typeDescription,
                           option, value, size, NULL )) != S_OK) return hr;

    if (desc->elementLocalName) hr = WsWriteEndElement( msg->writer_body, NULL );
    return hr;
}