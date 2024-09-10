void FdoXslTransformerXalan::Transform()
{
    // Reading from a stream at EOF is a common client error.
    // Therefore trap this particular problem.
    FdoIoStreamP stream = FdoXmlReaderP(GetInDoc())->GetStream();

    FdoInt64 streamLen = stream->GetLength();

    if ( (streamLen >= 0) && (stream->GetIndex() >= streamLen) ) 
        throw FdoXmlException::Create(
            FdoException::NLSGetMessage(
                FDO_NLSID(FDO_55_XSLINPUTEOF)
            )
        );

    stream = FdoXmlReaderP(GetStylesheet())->GetStream();

    streamLen = stream->GetLength();

    if ( (streamLen >= 0) && (stream->GetIndex() >= streamLen) ) 
        throw FdoXmlException::Create(
            FdoException::NLSGetMessage(
                FDO_NLSID(FDO_56_XSLSTYLESHEETEOF)
            )
        );

    // Create the Xalan transformer
    XALAN_CPP_NAMESPACE::XalanTransformer transformer;
    // Attach the in document to it
	FdoXmlReaderP readerP = GetInDoc();
    InputSource inSource( readerP );
    // Attach the stylesheet to it.
	readerP = GetStylesheet();
	InputSource sheetSource( readerP );
    sheetSource.setSystemId((const XMLCh*) L"sheet");

    try {
        FdoDictionaryP params = GetParameters();
        FdoInt32 i;

        // Give Xalan all the parameters
        for ( i = 0; i < params->GetCount(); i++ ) {
            FdoDictionaryElementP param = params->GetItem(i);

            if ( param->GetValue() )
                transformer.setStylesheetParam( 
                    XALAN_CPP_NAMESPACE::XalanDOMString( (const char*) FdoStringP(param->GetName()) ), 
                    XALAN_CPP_NAMESPACE::XalanDOMString( (const char*) FdoStringP(param->GetValue()) )
                );
        }

        // Listen to messages, warnings, and errors:
        transformer.setProblemListener(this);

        // Do the transformation.
        if ( transformer.transform( inSource, sheetSource, (void*) this, (XalanOutputHandlerType) outputHandler, (XalanFlushHandlerType) flushHandler ) ) {
			const char* lastError = transformer.getLastError();
			size_t i = strlen ( lastError ) + 1;
			wchar_t* wstrLastError = (wchar_t*)alloca (i * sizeof (wchar_t));

//#ifdef _WIN32
//			i = MultiByteToWideChar ( CP_THREAD_ACP, 0,lastError,(int)i, wstrLastError,(int)i);
			
//#else
			i = mbstowcs (wstrLastError, lastError, i);
//#endif
			if( i == 0 )
				wstrLastError[0] = 0;
			throw FdoXmlException::Create(
                FdoException::NLSGetMessage(
                    FDO_NLSID(FDO_42_GENERICCHAR),
                    wstrLastError
                )
            );

        }
    }
    catch ( const XALAN_CPP_NAMESPACE::XSLException& ex ) {
        throw FdoXmlException::Create(
            FdoException::NLSGetMessage(
                FDO_NLSID(FDO_43_XSLERROR),
                ex.getLineNumber(),
                ex.getColumnNumber(),
                (FdoString*)XalanDomStringToUnicode(ex.getMessage())
            )
        );
    }
}