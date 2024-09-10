HRESULT CreateSourceNode(
    IMFMediaSource *pSource,          // Media source.
    IMFPresentationDescriptor *pPD,   // Presentation descriptor.
    IMFStreamDescriptor *pSD,         // Stream descriptor.
    IMFTopologyNode **ppNode          // Receives the node pointer.
    )
{
    CComPtr<IMFTopologyNode> pNode;
    HRESULT hr = S_OK;

    // Create the node.
    hr = MFCreateTopologyNode(
        MF_TOPOLOGY_SOURCESTREAM_NODE,
        &pNode);

    // Set the attributes.
    if (SUCCEEDED(hr))
    {
        hr = pNode->SetUnknown(MF_TOPONODE_SOURCE, pSource);
    }

    if (SUCCEEDED(hr))
    {
        hr = pNode->SetUnknown(
            MF_TOPONODE_PRESENTATION_DESCRIPTOR,
            pPD);
    }

    if (SUCCEEDED(hr))
    {
        hr = pNode->SetUnknown(
            MF_TOPONODE_STREAM_DESCRIPTOR,
            pSD);
    }

    // Return the pointer to the caller.
    if (SUCCEEDED(hr))
    {
        *ppNode = pNode;
        (*ppNode)->AddRef();
    }
    return hr;
}