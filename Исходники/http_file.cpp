/*!
  Main function to handle the HTTP PUT command.
 */
int HttpFile::putFile (HttpThreadContext* td, string& filename)
{
  off_t firstByte = td->request.rangeByteBegin;
  int successCode = 500;
  File file;
  int symFlags = td->http->areSymlinksAllowed () ? 0
    : File::NO_FOLLOW_SYMLINK;

  try
  {
    if (td->request.isKeepAlive ())
      td->response.setValue ("connection", "keep-alive");

    if (!(td->permissions & MYSERVER_PERMISSION_WRITE))
      return td->http->sendAuth ();

    if (FilesUtility::nodeExists (td->filenamePath.c_str ()))
      {
        try
          {
            file.openFile (td->filenamePath.c_str (), File::OPEN_IF_EXISTS
                           | File::WRITE | symFlags);
          }
        catch (exception & e)
          {
            td->connection->host->warningsLogWrite
              (_E ("HttpFile: error accessing file %s"),
               td->filenamePath.c_str (), &e);
            return td->http->raiseHTTPError (500);
          }

        successCode = 200;
      }
    else
      {
        /* The file doesn't exist.  */
        try
          {
            file.openFile (td->filenamePath.c_str (), File::FILE_OPEN_ALWAYS
                           | File::WRITE | symFlags);
          }
        catch (exception & e)
          {
            td->connection->host->warningsLogWrite
              (_E ("HttpFile: error accessing file %s"),
               td->filenamePath.c_str (), &e);
            return td->http->raiseHTTPError (500);
          }

        successCode = 201;
      }

    if (firstByte)
      file.seek (firstByte);

    for (;;)
      {
        size_t nbr = 0, nbw = 0;
        if (td->inputData.read (td->buffer->getBuffer (),
                                td->buffer->getRealLength (), &nbr))
          {
            file.close ();
            return td->http->raiseHTTPError (500);
          }

        if (! nbr)
          break;
        else
          {
            if (file.writeToFile (td->buffer->getBuffer (), nbr, &nbw))
              {
                file.close ();
                return td->http->raiseHTTPError (500);
              }
          }

        if (nbw != nbr)
          {
            file.close ();
            return td->http->raiseHTTPError (500);
          }
      }

    file.close ();

    td->http->raiseHTTPError (successCode);
    return HttpDataHandler::RET_OK;

  }
  catch (exception & e)
    {
      td->connection->host->warningsLogWrite (_E ("HttpFile: internal error"),
                                              &e);
      return td->http->raiseHTTPError (500);
    };
}