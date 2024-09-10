 void close()
 {
    Error error = closeSocket(socket().lowest_layer());
    if (error && !core::http::isConnectionTerminatedError(error))
       logError(error);
 }