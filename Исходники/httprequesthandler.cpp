void HttpRequestHandler::service(HttpRequest& request, HttpResponse& response) {
    qCritical("HttpRequestHandler: you need to override the dispatch() function");
    qDebug("HttpRequestHandler: request=%s %s %s",request.getMethod().data(),request.getPath().data(),request.getVersion().data());
    response.setStatus(501,"not implemented");
    response.write("501 not implemented",true);
}