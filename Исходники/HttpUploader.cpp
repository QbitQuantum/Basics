void HttpUploader::setRequestHeaders(const StringBuffer& luid, HttpConnection& httpConnection, InputStream& inputStream) {
    
    StringBuffer dataSize;
    int totalSize = inputStream.getTotalSize();
    LOG.debug("[%s]: input stream size is %i", __FUNCTION__, totalSize);
    LOG.debug("[%s]: totalDataToUpload size is %i", __FUNCTION__, totalDataToUpload);
    if (totalDataToUpload > 0) {
        totalSize = totalDataToUpload;
    } 
    dataSize.sprintf("%d", totalSize);
    

    httpConnection.setRequestHeader(HTTP_HEADER_ACCEPT,         "*/*");
    httpConnection.setRequestHeader(HTTP_HEADER_CONTENT_TYPE,   "application/octet-stream");

    // set transfer enconding to chunked
    //httpConnection.setRequestHeader(HTTP_HEADER_TRANSFER_ENCODING, "chunked");

    // set Funambol mandatory custom headers
    httpConnection.setRequestHeader(HTTP_HEADER_X_FUNAMBOL_FILE_SIZE, dataSize);
    httpConnection.setRequestHeader(HTTP_HEADER_X_FUNAMBOL_DEVICE_ID, deviceID);
    httpConnection.setRequestHeader(HTTP_HEADER_X_FUNAMBOL_LUID, luid);
    
    if (partialUploadedData > 0) {
        StringBuffer s;
        s.sprintf("bytes %d-%d/%d", partialUploadedData, totalSize-1, totalSize);
        
        httpConnection.setRequestHeader(HTTP_HEADER_CONTENT_RANGE, s.c_str());
    }
}