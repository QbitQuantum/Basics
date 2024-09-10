void AssetRequest::start() {
    if (QThread::currentThread() != thread()) {
        QMetaObject::invokeMethod(this, "start", Qt::AutoConnection);
        return;
    }

    if (_state != NotStarted) {
        qCWarning(asset_client) << "AssetRequest already started.";
        return;
    }

    // in case we haven't parsed a valid hash, return an error now
    if (!isValidHash(_hash)) {
        _error = InvalidHash;
        _state = Finished;

        emit finished(this);
        return;
    }
    
    // Try to load from cache
    _data = loadFromCache(getUrl());
    if (!_data.isNull()) {
        _error = NoError;

        _loadedFromCache = true;

        _state = Finished;
        emit finished(this);

        return;
    }

    _state = WaitingForData;

    auto assetClient = DependencyManager::get<AssetClient>();
    auto that = QPointer<AssetRequest>(this); // Used to track the request's lifetime
    auto hash = _hash;

    _assetRequestID = assetClient->getAsset(_hash, _byteRange.fromInclusive, _byteRange.toExclusive,
        [this, that, hash](bool responseReceived, AssetServerError serverError, const QByteArray& data) {

        if (!that) {
            qCWarning(asset_client) << "Got reply for dead asset request " << hash << "- error code" << _error;
            // If the request is dead, return
            return;
        }
        _assetRequestID = INVALID_MESSAGE_ID;

        if (!responseReceived) {
            _error = NetworkError;
        } else if (serverError != AssetServerError::NoError) {
            switch (serverError) {
                case AssetServerError::AssetNotFound:
                    _error = NotFound;
                    break;
                case AssetServerError::InvalidByteRange:
                    _error = InvalidByteRange;
                    break;
                default:
                    _error = UnknownError;
                    break;
            }
        } else {
            if (!_byteRange.isSet() && hashData(data).toHex() != _hash) {
                // the hash of the received data does not match what we expect, so we return an error
                _error = HashVerificationFailed;
            }

            if (_error == NoError) {
                _data = data;
                _totalReceived += data.size();
                emit progress(_totalReceived, data.size());

                if (!_byteRange.isSet()) {
                    saveToCache(getUrl(), data);
                }
            }
        }
        
        if (_error != NoError) {
            qCWarning(asset_client) << "Got error retrieving asset" << _hash << "- error code" << _error;
        }
        
        _state = Finished;
        emit finished(this);
    }, [this, that](qint64 totalReceived, qint64 total) {
        if (!that) {
            // If the request is dead, return
            return;
        }
        emit progress(totalReceived, total);
    });
}