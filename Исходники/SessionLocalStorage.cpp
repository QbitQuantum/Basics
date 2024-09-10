        Nd4jLong nd4j::graph::SessionLocalStorage::startSession() {
            auto tid = getThreadId();

            nd4j_debug("Adding ThreadId: %i;\n", (int) tid);
            Nd4jLong ntid = _sessionCounter++;
            _mutex.lock();

            _threadSession[tid] = ntid;
            _threadVariableSpace[ntid] = _variableSpace->clone();

            _mutex.unlock();

            return ntid;
        }