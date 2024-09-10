void AssetUpload::start() {
    if (QThread::currentThread() != thread()) {
        QMetaObject::invokeMethod(this, "start");
        return;
    }
    
    if (_data.isEmpty() && !_filename.isEmpty()) {
        // try to open the file at the given filename
        QFile file { _filename };
        
        if (file.open(QIODevice::ReadOnly)) {            
            _data = file.readAll();
        } else {
            // we couldn't open the file - set the error result
            _error = FileOpenError;
            
            // emit that we are done
            emit finished(this, QString());

            return;
        }
    }
    
    // ask the AssetClient to upload the asset and emit the proper signals from the passed callback
    auto assetClient = DependencyManager::get<AssetClient>();
   
    if (!_filename.isEmpty()) {
        qCDebug(asset_client) << "Attempting to upload" << _filename << "to asset-server.";
    }
    
    assetClient->uploadAsset(_data, [this](bool responseReceived, AssetServerError error, const QString& hash){
        if (!responseReceived) {
            _error = NetworkError;
        } else {
            switch (error) {
                case AssetServerError::NoError:
                    _error = NoError;
                    break;
                case AssetServerError::AssetTooLarge:
                    _error = TooLarge;
                    break;
                case AssetServerError::PermissionDenied:
                    _error = PermissionDenied;
                    break;
                case AssetServerError::FileOperationFailed:
                    _error = ServerFileError;
                    break;
                default:
                    _error = FileOpenError;
                    break;
            }
        }
        
        if (_error == NoError && hash == hashData(_data).toHex()) {
            saveToCache(getATPUrl(hash), _data);
        }
        
        emit finished(this, hash);
    });
}