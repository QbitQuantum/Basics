// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_METADATA* metadata = NULL;
    WS_CHANNEL* channel = NULL;
    WS_XML_READER* reader = NULL;
    WS_HEAP* heap = NULL;
    
    // Declare constraints on what policy is acceptable
    
    // Require HTTP
    WS_CHANNEL_BINDING channelBinding = WS_HTTP_CHANNEL_BINDING;
    
    // Set up channel property contraints that override the default constraints
    WS_CHANNEL_PROPERTY_CONSTRAINT channelPropertyConstraints[3];
    
    // Allow text encodings
    WS_ENCODING allowedEncodings[] =
    {
        WS_ENCODING_XML_UTF8,
        WS_ENCODING_XML_UTF16LE,
        WS_ENCODING_XML_UTF16BE
    };
    channelPropertyConstraints[0].id = WS_CHANNEL_PROPERTY_ENCODING;
    channelPropertyConstraints[0].allowedValues = allowedEncodings;
    channelPropertyConstraints[0].allowedValuesSize = sizeof(allowedEncodings);
    
    // Allow addressing 1.0
    WS_ADDRESSING_VERSION allowedAddressingVersions[] =
    {
        WS_ADDRESSING_VERSION_1_0,
    };
    channelPropertyConstraints[1].id = WS_CHANNEL_PROPERTY_ADDRESSING_VERSION;
    channelPropertyConstraints[1].allowedValues = allowedAddressingVersions;
    channelPropertyConstraints[1].allowedValuesSize = sizeof(allowedAddressingVersions);
    
    // Allow SOAP 1.1 or SOAP 1.2
    WS_ENVELOPE_VERSION allowedEnvelopeVersions[] =
    {
        WS_ENVELOPE_VERSION_SOAP_1_1,
        WS_ENVELOPE_VERSION_SOAP_1_2,
    };
    channelPropertyConstraints[2].id = WS_CHANNEL_PROPERTY_ENVELOPE_VERSION;
    channelPropertyConstraints[2].allowedValues = allowedEnvelopeVersions;
    channelPropertyConstraints[2].allowedValuesSize = sizeof(allowedEnvelopeVersions);
    
    // Set up security property contraints that override the default constraints
    WS_SECURITY_PROPERTY_CONSTRAINT securityPropertyConstraints[1];
    
    // Allow with/without a timestamp
    WS_SECURITY_TIMESTAMP_USAGE allowedTimestampValues[] =
    {
        WS_SECURITY_TIMESTAMP_USAGE_NEVER,
        WS_SECURITY_TIMESTAMP_USAGE_ALWAYS,
    };
    securityPropertyConstraints[0].id = WS_SECURITY_PROPERTY_TIMESTAMP_USAGE;
    securityPropertyConstraints[0].allowedValues = allowedTimestampValues;
    securityPropertyConstraints[0].allowedValuesSize = sizeof(allowedTimestampValues);
    
    // Set up the ssl security binding constraint structure
    WS_SSL_TRANSPORT_SECURITY_BINDING_CONSTRAINT sslSecurityBindingConstraint = { };
    sslSecurityBindingConstraint.bindingConstraint.type = WS_SSL_TRANSPORT_SECURITY_BINDING_CONSTRAINT_TYPE;
    
    // Set up the X.509 security binding constraint structure
    WS_CERT_MESSAGE_SECURITY_BINDING_CONSTRAINT certSecurityBindingConstraint = { };
    certSecurityBindingConstraint.bindingConstraint.type = WS_CERT_MESSAGE_SECURITY_BINDING_CONSTRAINT_TYPE;
    certSecurityBindingConstraint.bindingUsage = WS_SUPPORTING_MESSAGE_SECURITY_USAGE;
    
    // Set up the set of security binding constraints
    WS_SECURITY_BINDING_CONSTRAINT* securityBindingConstraints[] =
    {
        &sslSecurityBindingConstraint.bindingConstraint,
        &certSecurityBindingConstraint.bindingConstraint
    };
    
    // Set up the security constraint structure
    WS_SECURITY_CONSTRAINTS securityConstraints = { };
    securityConstraints.securityPropertyConstraints = securityPropertyConstraints;
    securityConstraints.securityPropertyConstraintCount = WsCountOf(securityPropertyConstraints);
    securityConstraints.securityBindingConstraints = securityBindingConstraints;
    securityConstraints.securityBindingConstraintCount = WsCountOf(securityBindingConstraints);
    
    // Set up the policy constraint structure
    WS_POLICY_CONSTRAINTS policyConstraints = { };
    policyConstraints.channelBinding = channelBinding;
    policyConstraints.channelPropertyConstraints = channelPropertyConstraints;
    policyConstraints.channelPropertyConstraintCount = WsCountOf(channelPropertyConstraints);
    policyConstraints.securityConstraints = &securityConstraints;
    
    // Set up port type to match
    static const WS_XML_STRING desiredPortTypeName = WS_XML_STRING_VALUE("IPingService");
    static const WS_XML_STRING desiredPortTypeNs = WS_XML_STRING_VALUE("http://example.com");
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create object that will hold metadata documents
    hr = WsCreateMetadata(NULL, 0, &metadata, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create an XML reader
    hr = WsCreateReader(
        NULL,
        0, 
        &reader, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Set the input of the reader to the policy text
    WS_XML_READER_BUFFER_INPUT bufferInput;
    ZeroMemory(&bufferInput, sizeof(bufferInput));
    bufferInput.input.inputType = WS_XML_READER_INPUT_TYPE_BUFFER;
    bufferInput.encodedData = wsdlXml.bytes;
    bufferInput.encodedDataSize = wsdlXml.length;
    WS_XML_READER_TEXT_ENCODING textEncoding;
    ZeroMemory(&textEncoding, sizeof(textEncoding));
    textEncoding.encoding.encodingType = WS_XML_READER_ENCODING_TYPE_TEXT;
    textEncoding.charSet = WS_CHARSET_AUTO;
    hr = WsSetInput(reader, &textEncoding.encoding, &bufferInput.input, NULL, 0, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Read the metadata into the metadata object.
    hr = WsReadMetadata(metadata, reader, &wsdlUrl, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // After adding a document to the metadata object, it can be queried
    // to determine the address of any documents which have been referenced
    // but have not yet been added.
    WS_ENDPOINT_ADDRESS* missingAddress;
    hr = WsGetMissingMetadataDocumentAddress(metadata, &missingAddress, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    if (missingAddress != NULL)
    {
        // We only support one document in this example
        hr = E_FAIL;
        goto Exit;
    }
    
    // Get the endpoints from the metadata object
    WS_METADATA_ENDPOINTS endpoints;
    hr = WsGetMetadataEndpoints(metadata, &endpoints, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    BOOL foundEndpoint = FALSE;
    WS_METADATA_ENDPOINT* endpoint = NULL;
    
    // Search for port types
    for (ULONG i = 0; i < endpoints.endpointCount; i++)
    {
        // Get the endpoint from the array of endpoints
        endpoint = &endpoints.endpoints[i];
        
        // See if the port type name matches
        hr = WsXmlStringEquals(endpoint->portTypeName, &desiredPortTypeName, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        if (hr == S_FALSE)
        {
            continue;
        }
        
        // See if the port type namespace matches
        hr = WsXmlStringEquals(endpoint->portTypeNs, &desiredPortTypeNs, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        if (hr == S_FALSE)
        {
            continue;
        }
        
        foundEndpoint = TRUE;
        break;
    }
    
    if (!foundEndpoint)
    {
        // No matching port types
        hr = E_FAIL;
        goto Exit;
    }
    
    // Get the policy for the endpoint
    WS_POLICY* policy;
    policy = endpoint->endpointPolicy;
    
    // Get the number of policy alternatives available in the policy object
    ULONG alternativeCount;
    hr = WsGetPolicyAlternativeCount(
        policy,
        &alternativeCount,
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create a heap used to allocate fields of initialized values
    hr = WsCreateHeap(/* maxSize */ 16*1024, /* trimSize */ 2*1024, NULL, 0, &heap, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    BOOL matchFound = FALSE;
    
    // For each alternative in the policy object
    for (ULONG alternativeIndex = 0; alternativeIndex < alternativeCount; alternativeIndex++)
    {
        // This example uses FALSE for the matchRequired parameter to WsMatchPolicyAlternative
        // which means that the function will return S_FALSE if there is not a match.
        // If diagnosing why a policy can not be matched, it may be useful to instead set
        // matchRequired to TRUE meaning an error will be returned (and the error object
        // will contain information about why the policy did not match).
        BOOL matchRequired = FALSE;
        
        // Try to match policy given the constraints
        hr = WsMatchPolicyAlternative(
            policy,
            alternativeIndex,
            &policyConstraints,
            matchRequired,
            heap,
            error);
        
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        if (hr == S_OK)
        {
            // The policy met the constraints
            matchFound = TRUE;
            break;
        }
    }
    
    if (!matchFound)
    {
        // None of the policy alternatives matched
        hr = E_FAIL;
        goto Exit;
    }
    
    // Initialize channel properties based on the values found in the policy
    WS_CHANNEL_PROPERTY channelProperties[4];
    channelProperties[0] = channelPropertyConstraints[0].out.channelProperty;
    channelProperties[1] = channelPropertyConstraints[1].out.channelProperty;
    channelProperties[2] = channelPropertyConstraints[2].out.channelProperty;
    
    // Initialize additional channel properties that specify local behavior
    // that is not part of policy.
    WS_TRANSFER_MODE transferMode = WS_BUFFERED_TRANSFER_MODE;
    channelProperties[3].id = WS_CHANNEL_PROPERTY_TRANSFER_MODE;
    channelProperties[3].value = &transferMode;
    channelProperties[3].valueSize = sizeof(transferMode);
    
    // Initialize security properties based on values extracted from policy
    WS_SECURITY_PROPERTY securityProperties[1];
    securityProperties[0] = securityPropertyConstraints[0].out.securityProperty;
    
    // Set up SSL security binding
    WS_SSL_TRANSPORT_SECURITY_BINDING sslSecurityBinding;
    ZeroMemory(&sslSecurityBinding, sizeof(sslSecurityBinding));
    sslSecurityBinding.binding.bindingType = WS_SSL_TRANSPORT_SECURITY_BINDING_TYPE;
    if (sslSecurityBindingConstraint.out.clientCertCredentialRequired)
    {
        // Server wants a client cert, but this example does not have one
        hr = E_FAIL;
        goto Exit;
    }
    else
    {
        sslSecurityBinding.localCertCredential = NULL;
    }
    
    // The runtime does not support X.509 binding hence use a WS_XML_TOKEN_MESSAGE_SECURITY_BINDING to create a channel
    WS_XML_TOKEN_MESSAGE_SECURITY_BINDING xmlTokenSecurityBinding;
    ZeroMemory(&xmlTokenSecurityBinding, sizeof(xmlTokenSecurityBinding));
    xmlTokenSecurityBinding.binding.bindingType = WS_XML_TOKEN_MESSAGE_SECURITY_BINDING_TYPE;
    xmlTokenSecurityBinding.bindingUsage = certSecurityBindingConstraint.bindingUsage;
    
    // To obtain a security token to specify for the xmlToken field, use the following steps:
    // - Find the appropriate certificate and create a X.509 token
    // - Use WsCreateXmlSecurityToken and to create a security token with the keys from the above X.509 token
    xmlTokenSecurityBinding.xmlToken = NULL;
    
    // Set up security bindings
    WS_SECURITY_BINDING* securityBindings[2];
    securityBindings[0] = &sslSecurityBinding.binding;
    securityBindings[1] = &xmlTokenSecurityBinding.binding;
    
    // Set up security description
    WS_SECURITY_DESCRIPTION securityDescription;
    securityDescription.securityBindings = securityBindings;
    securityDescription.securityBindingCount = WsCountOf(securityBindings);
    securityDescription.properties = securityProperties;
    securityDescription.propertyCount = WsCountOf(securityProperties);
    
    // Create a channel or proxy to the service using the accumulated binding information:
    // - channelBinding
    // - channelProperties
    // - securityDecription
    
Exit:
    if (FAILED(hr))
    {
        // Print out the error
        PrintError(hr, error);
    }
    
    if (metadata != NULL)
    {
        WsFreeMetadata(metadata);
    }
    if (channel != NULL)
    {
        WsFreeChannel(channel);
    }
    if (reader != NULL)
    {
        WsFreeReader(reader);
    }
    if (heap != NULL)
    {
        WsFreeHeap(heap);
    }
    if (error != NULL)
    {
        WsFreeError(error);
    }
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}