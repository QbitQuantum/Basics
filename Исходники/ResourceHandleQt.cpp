void WebCoreSynchronousLoader::didFinishLoading(ResourceHandle*)
{
    m_eventLoop.exit();
}