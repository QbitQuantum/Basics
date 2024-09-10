            // We filled the message
            break;
        }
    }

    // Write fileContent end element
    IfFailedExit(WsWriteEndElement(writer, error));

    // Write error element
    IfFailedExit(WsWriteStartElement(writer, NULL, &errorLocalName, &fileChunkNamespace, error));
    const WCHAR* noError = GlobalStrings::noError;
    IfFailedExit(WsWriteType(
        writer,
        WS_ELEMENT_TYPE_MAPPING,
        WS_WSZ_TYPE,
        NULL,
        WS_WRITE_REQUIRED_POINTER,
        &noError,
        sizeof(noError),
        error));

    // Closing elements;
    IfFailedExit(WsWriteEndElement(writer, error));
    IfFailedExit(WsWriteEndElement(writer, error));
    IfFailedExit(WsWriteMessageEnd(channel, replyMessage, NULL, error));

    hr = WsResetMessage(replyMessage, NULL);
    HeapFree(GetProcessHeap(), 0, buf);

    PrintVerbose(L"Leaving CFileRepServer::ReadAndSendChunk");
    return hr;