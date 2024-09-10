/**
 * @brief PathDelegator::service -- Delegate the request to the service designed to handle that request
 * @param request
 * @param response
 */
void PathDelegator::service(HttpRequest &request, HttpResponse &response) {
    QByteArray path = removeExtension(request.getPath());
    if (paths.contains(path)) {
        paths[path]->service(request, response);
    }
    else {
        response.setStatus(HttpHeaders::STATUS_NOT_FOUND, QByteArray("Cannot find ") + path);
    }
    WebLogger::log(QtWarningMsg, QByteArray::number(response.getStatus()) + ": " + response.getStatusText(), "pathdelegator", "service");
}