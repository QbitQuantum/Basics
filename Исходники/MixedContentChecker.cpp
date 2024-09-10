void MixedContentChecker::handleCertificateError(LocalFrame* frame, const ResourceResponse& response, WebURLRequest::FrameType frameType, WebURLRequest::RequestContext requestContext)
{
    Frame* effectiveFrame = effectiveFrameForFrameType(frame, frameType);
    if (frameType == WebURLRequest::FrameTypeTopLevel || !effectiveFrame)
        return;

    // Use the current local frame's client; the embedder doesn't
    // distinguish mixed content signals from different frames on the
    // same page.
    FrameLoaderClient* client = frame->loader().client();
    bool strictMixedContentCheckingForPlugin = effectiveFrame->settings() && effectiveFrame->settings()->strictMixedContentCheckingForPlugin();
    WebMixedContent::ContextType contextType = WebMixedContent::contextTypeFromRequestContext(requestContext, strictMixedContentCheckingForPlugin);
    if (contextType == WebMixedContent::ContextType::Blockable) {
        client->didRunContentWithCertificateErrors(response.url(), response.getSecurityInfo());
    } else {
        // contextTypeFromRequestContext() never returns NotMixedContent (it
        // computes the type of mixed content, given that the content is
        // mixed).
        DCHECK(contextType != WebMixedContent::ContextType::NotMixedContent);
        client->didDisplayContentWithCertificateErrors(response.url(), response.getSecurityInfo());
    }
}