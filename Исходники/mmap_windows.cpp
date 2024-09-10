        void flush() {
            if (!_view || !_fd)
                return;

            {
                LockMongoFilesShared mmfilesLock;

                std::set<MongoFile*> mmfs = MongoFile::getAllFiles();
                std::set<MongoFile*>::const_iterator it = mmfs.find(_theFile);
                if ( it == mmfs.end() || (*it)->getUniqueId() != _id ) {
                    // this was deleted while we were unlocked
                    return;
                }

                // Hold the flush mutex to ensure the file is not closed during flush
                _flushMutex.lock();
            }

            stdx::lock_guard<stdx::mutex> lk(_flushMutex, stdx::adopt_lock);

            int loopCount = 0;
            bool success = false;
            bool timeout = false;
            int dosError = ERROR_SUCCESS;
            const int maximumTimeInSeconds = 60 * 15;
            Timer t;
            while ( !success && !timeout ) {
                ++loopCount;
                success = FALSE != FlushViewOfFile( _view, 0 );
                if ( !success ) {
                    dosError = GetLastError();
                    if ( dosError != ERROR_LOCK_VIOLATION ) {
                        break;
                    }
                    timeout = t.seconds() > maximumTimeInSeconds;
                }
            }
            if ( success && loopCount > 1 ) {
                log() << "FlushViewOfFile for " << _filename
                        << " succeeded after " << loopCount
                        << " attempts taking " << t.millis()
                        << "ms" << endl;
            }
            else if ( !success ) {
                log() << "FlushViewOfFile for " << _filename
                        << " failed with error " << dosError
                        << " after " << loopCount
                        << " attempts taking " << t.millis()
                        << "ms" << endl;
                // Abort here to avoid data corruption
                fassert(16387, false);
            }

            success = FALSE != FlushFileBuffers(_fd);
            if (!success) {
                int err = GetLastError();
                log() << "FlushFileBuffers failed: " << errnoWithDescription( err )
                      << " file: " << _filename << endl;
                dataSyncFailedHandler();
            }
        }