static HRESULT WINAPI mxwriter_saxcontent_startDocument(ISAXContentHandler *iface)
{
    mxwriter *This = impl_from_ISAXContentHandler( iface );

    TRACE("(%p)\n", This);

    /* If properties have been changed since the last "endDocument" call
     * we need to reset the output buffer. If we don't the output buffer
     * could end up with multiple XML documents in it, plus this seems to
     * be how Windows works.
     */
    if (This->prop_changed) {
        reset_output_buffer(This);
        This->prop_changed = FALSE;
    }

    if (This->props[MXWriter_OmitXmlDecl] == VARIANT_TRUE) return S_OK;

    write_prolog_buffer(This);

    if (This->dest && This->xml_enc == XmlEncoding_UTF16) {
        static const char utf16BOM[] = {0xff,0xfe};

        if (This->props[MXWriter_BOM] == VARIANT_TRUE)
            /* Windows passes a NULL pointer as the pcbWritten parameter and
             * ignores any error codes returned from this Write call.
             */
            IStream_Write(This->dest, utf16BOM, sizeof(utf16BOM), NULL);
    }

    return S_OK;
}