    void flush() {
        if (!_view || !_fd)
            return;

        scoped_lock lk(*_flushMutex);

        int loopCount = 0;
        bool success = false;
        bool timeout = false;
        int dosError = ERROR_SUCCESS;
        const int maximumLoopCount = 1000 * 1000;
        const int maximumTimeInSeconds = 60;
        Timer t;
        while ( !success && !timeout && loopCount < maximumLoopCount ) {
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
                  << " ms" << endl;
        }
        else if ( !success ) {
            log() << "FlushViewOfFile for " << _filename
                  << " failed with error " << dosError
                  << " after " << loopCount
                  << " attempts taking " << t.millis()
                  << " ms" << endl;
        }

        success = FALSE != FlushFileBuffers(_fd);
        if (!success) {
            int err = GetLastError();
            out() << "FlushFileBuffers failed " << err << " file: " << _filename << endl;
        }
    }