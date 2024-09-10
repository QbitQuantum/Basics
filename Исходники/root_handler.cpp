void RootHandler::service( HttpRequest & request, HttpResponse & response )
{
    QString path = request.getPath();
    if ( pd->camHandler->service( request, response ) )
        return;
    if ( pd->chHandler->service( request, response ) )
        return;
    if ( pd->resHandler->service( request, response ) )
        return;
    if ( path == "/" )
    {
        bool res = pd->resHandler->service( request, response, "index.html" );
        return;
    }
}