    bool CheckAccessControlHeaders(const char* headerName, bool exposed)
    {
        std::string id("http://www.other.com/CheckAccessControlExposeHeaders_");
        id.append(headerName);
        if (exposed)
            id.append("-Exposed");
        id.append(".html");

        KURL url = toKURL(id);
        WebURLRequest request;
        request.initialize();
        request.setURL(url);

        WebString headerNameString(WebString::fromUTF8(headerName));
        m_expectedResponse = WebURLResponse();
        m_expectedResponse.initialize();
        m_expectedResponse.setMIMEType("text/html");
        m_expectedResponse.setHTTPStatusCode(200);
        m_expectedResponse.addHTTPHeaderField("Access-Control-Allow-Origin", "*");
        if (exposed)
            m_expectedResponse.addHTTPHeaderField("access-control-expose-headers", headerNameString);
        m_expectedResponse.addHTTPHeaderField(headerNameString, "foo");
        Platform::current()->unitTestSupport()->registerMockedURL(url, m_expectedResponse, m_frameFilePath);

        WebURLLoaderOptions options;
        options.crossOriginRequestPolicy = WebURLLoaderOptions::CrossOriginRequestPolicyUseAccessControl;
        m_expectedLoader = createAssociatedURLLoader(options);
        EXPECT_TRUE(m_expectedLoader);
        m_expectedLoader->loadAsynchronously(request, this);
        serveRequests();
        EXPECT_TRUE(m_didReceiveResponse);
        EXPECT_TRUE(m_didReceiveData);
        EXPECT_TRUE(m_didFinishLoading);

        return !m_actualResponse.httpHeaderField(headerNameString).isEmpty();
    }