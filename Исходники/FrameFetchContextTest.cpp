// Tests that when a resource with certificate errors is loaded from the
// memory cache, the embedder is notified.
TEST_F(FrameFetchContextDisplayedCertificateErrorsTest, MemoryCacheCertificateError)
{
    ResourceRequest resourceRequest(url);
    ResourceResponse response;
    response.setURL(url);
    response.setSecurityInfo(securityInfo);
    response.setHasMajorCertificateErrors(true);
    Resource* resource = Resource::create(resourceRequest, Resource::Image);
    resource->setResponse(response);
    fetchContext->dispatchDidLoadResourceFromMemoryCache(createUniqueIdentifier(), resource, WebURLRequest::FrameTypeNone, WebURLRequest::RequestContextImage);
}