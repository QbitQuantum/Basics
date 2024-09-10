stream* GetStream(anynode *AnyNode, const tchar_t* URL, int Flags)
{
	tchar_t Protocol[MAXPROTOCOL];
	stream* Stream = NULL;
    fourcc_t FourCC;

    GetProtocol(URL,Protocol,TSIZEOF(Protocol),NULL);

    FourCC = NodeEnumClassStr(AnyNode,NULL,STREAM_CLASS,NODE_PROTOCOL,Protocol);

#if defined(CONFIG_STREAM_CACHE)
    if ((Flags & (SFLAG_NO_CACHING|SFLAG_WRONLY|SFLAG_CREATE))==0)
        Stream = (stream*)NodeCreate(AnyNode,NodeClass_Meta(NodeContext_FindClass(AnyNode,FourCC),STREAM_CACHE_CLASS,META_PARAM_CUSTOM));
#endif

    if (!Stream)
        Stream = (stream*)NodeCreate(AnyNode,FourCC);

    if (Stream && (Flags & SFLAG_NON_BLOCKING))
        Stream_Blocking(Stream,0);

    if (!Stream && !(Flags & SFLAG_SILENT))
    {
	    tcsupr(Protocol);
	    NodeReportError(AnyNode,NULL,ERR_ID,ERR_PROTO_NOT_FOUND,Protocol);
    }
#if defined(CONFIG_DEBUGCHECKS)
    if (Stream)
        tcscpy_s(Stream->URL,TSIZEOF(Stream->URL),URL);
#endif
	return Stream;
}