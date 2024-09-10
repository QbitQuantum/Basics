 void onError(const URL& url) {
   ILogger::instance()->logError("Error trying to download image \"%s\"", url.getPath().c_str());
   _mark->onTextureDownloadError();
 }