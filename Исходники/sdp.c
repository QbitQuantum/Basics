NTSTATUS
CreateSdpRecord(
    _In_ PBTHDDI_SDP_NODE_INTERFACE SdpNodeInterface,
    _In_ PBTHDDI_SDP_PARSE_INTERFACE SdpParseInterface,
    _In_ const GUID * ClassId,
    _In_ LPWSTR Name,
    _In_ USHORT Psm,
    _Out_ PUCHAR * Stream,
    _Out_ ULONG * Size
    )
/*++

Description:

    Create server SDP record

Arguments:

    SdpNodeInterface - Node interface that we obtained from bth stack
    SdpParseInterface - Parse interface that we obtained from bth stack
    ClassId - Service Class ID to publish
    Name - Service name to publish
    Psm - Server PSM
    Stream - receives the sdp record stream
    Size - receives size of sdp record stream

Return Value:

    NTSTATUS Status code.

--*/
{
    NTSTATUS status;
    PSDP_TREE_ROOT_NODE tree = NULL;
    PSDP_NODE seqClsIdList, seqProto, seqLang; 
    PSDP_NODE nodeName = NULL, nodeDesc = NULL, nodeProto; 
    UNICODE_STRING unicodeStrName;
    ANSI_STRING ansiStrName;
    PUCHAR stream = NULL;
    ULONG size;
    ULONG_PTR errorByte = 0;

    RtlInitUnicodeString(&unicodeStrName, Name);
    RtlInitAnsiString(&ansiStrName, NULL);

    status = RtlUnicodeStringToAnsiString(&ansiStrName, &unicodeStrName, TRUE);
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_SDP, 
            "Creating ANSI string for service name failed, Status code %!STATUS!\n", status);

        ansiStrName.Length = 0;
        goto exit;
    }
        
    tree = SdpNodeInterface->SdpCreateNodeTree(
        POOLTAG_BTHECHOSAMPLE
        );

    if (NULL == tree)
    {
        status = STATUS_INSUFFICIENT_RESOURCES;

        TraceEvents(TRACE_LEVEL_ERROR, DBG_SDP, 
            "SdpCreateNodeTree failed, returning Status code %!STATUS!\n", status);
        
        goto exit;
    }

    //
    // Add ClassIdList attribute
    //

    status = AddSeqAttribute(SdpNodeInterface, tree, SDP_ATTRIB_CLASS_ID_LIST, &seqClsIdList);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    status = AppendNodeUuid128(SdpNodeInterface, seqClsIdList, ClassId);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    //
    // Add protocols
    //

    //
    // L2CAP
    //
    status = AddSeqAttribute(SdpNodeInterface, tree, SDP_ATTRIB_PROTOCOL_DESCRIPTOR_LIST, &seqProto);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    status = AppendSeqNode(SdpNodeInterface, seqProto, &nodeProto);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }
    
    status = AppendNodeUuid16(SdpNodeInterface, nodeProto, L2CAP_PROTOCOL_UUID16);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    status = AppendNodeUint16(SdpNodeInterface, nodeProto, Psm);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    //
    // SDP
    //

    status = AppendSeqNode(SdpNodeInterface, seqProto, &nodeProto);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    status = AppendNodeUuid16(SdpNodeInterface, nodeProto, SDP_PROTOCOL_UUID16);            
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    //
    // Add lang attributes
    //
    status = AddSeqAttribute(SdpNodeInterface, tree, SDP_ATTRIB_LANG_BASE_ATTRIB_ID_LIST, &seqLang);
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    status = AppendNodeUint16(SdpNodeInterface, seqLang, 0x656e); //TODO: find constants for these           
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }

    status = AppendNodeUint16(SdpNodeInterface, seqLang, 0x006A);            
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }
    
    status = AppendNodeUint16(SdpNodeInterface, seqLang, 0x0100);            
    if (!NT_SUCCESS(status))
    {
        goto exit;
    }
    
    //
    // Add service name
    //

    nodeName = SdpNodeInterface->SdpCreateNodeString(
        ansiStrName.Buffer, 
        ansiStrName.Length, 
        POOLTAG_BTHECHOSAMPLE
        );
    if(NULL == nodeName)
    {
        status = STATUS_INSUFFICIENT_RESOURCES;

        TraceEvents(TRACE_LEVEL_ERROR, DBG_SDP, 
            "Creating node for service name failed, Status code %!STATUS!\n", status);

        goto exit;
    }
    
    status = SdpNodeInterface->SdpAddAttributeToTree(
        tree, 
        LANG_DEFAULT_ID+STRING_NAME_OFFSET, 
        nodeName, 
        POOLTAG_BTHECHOSAMPLE
        );
    if(!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_SDP, 
            "SdpAddAttributeToTree for service name failed, Status code %!STATUS!\n", status);

        goto exit;
    }

    nodeName = NULL; //transferred owenership to tree
    
    nodeDesc = SdpNodeInterface->SdpCreateNodeString(
        ansiStrName.Buffer, 
        ansiStrName.Length, 
        POOLTAG_BTHECHOSAMPLE
        );
    if(NULL == nodeDesc)
    {
        status = STATUS_INSUFFICIENT_RESOURCES;

        TraceEvents(TRACE_LEVEL_ERROR, DBG_SDP, 
            "Creating node for service desc failed, Status code %!STATUS!\n", status);

        goto exit;
    }
    
    status = SdpNodeInterface->SdpAddAttributeToTree(
        tree, 
        LANG_DEFAULT_ID+STRING_DESCRIPTION_OFFSET, 
        nodeDesc, 
        POOLTAG_BTHECHOSAMPLE
        );
    if(!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_SDP, 
            "SdpAddAttributeToTree for service desc failed, Status code %!STATUS!\n", status);
        
        goto exit;
    }

    nodeDesc = NULL;

    //
    // Create stream from tree
    //

    status = SdpParseInterface->SdpConvertTreeToStream(tree, &stream, &size, POOLTAG_BTHECHOSAMPLE);
    if(!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_SDP, 
            "Failed to get stream from tree for SDP record, Status code %!STATUS!\n", status);
        
        goto exit;
    }

    status = SdpParseInterface->SdpValidateStream(
        stream,
        size,
        &errorByte
        );

    if(!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_ERROR, DBG_SDP, 
            "Validate stream failed for SDP record, first failure at address %p\n", (PVOID)errorByte);
        
        goto exit;
    }

    *Stream = stream;
    *Size = size;
    
exit:
    if (NULL != tree)
    {
        SdpNodeInterface->SdpFreeTree(tree);
    }

    if (NULL != nodeName)
    {
        //
        // If we failed to add attribute to tree use ExFreePool to free it
        //
        ExFreePool(nodeName);
    }
    
    if (NULL != nodeDesc)
    {
        //
        // If we failed to add attribute to tree use ExFreePool to free it
        //
        ExFreePool(nodeDesc);
    }
    
    RtlFreeAnsiString(&ansiStrName);

    if (!NT_SUCCESS(status))
    {
        if (stream != NULL)
        {
            ExFreePoolWithTag(stream, POOLTAG_BTHECHOSAMPLE);
        }
    }
    
    return status;
}