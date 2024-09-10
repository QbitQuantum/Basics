/*
 * getPacket
 *     description: retrieve data from the provides (input) port
 *
 *  timeout: the amount of time to wait for data before a NULL is returned.
 *           Use 0.0 for non-blocking and -1 for blocking.
 */
BULKIO_dataFloat_In_i::dataTransfer *BULKIO_dataFloat_In_i::getPacket(float timeout, std::string streamID )
{
    if (breakBlock) {
        return NULL;
    }
    //if (workQueue.size() == 0) {
    if ( (workQueue.size() == 0 ) or (( workQueue.size() != 0 ) and ( workQueue.size() == lastQueueSize )) ){
        if (timeout == 0.0) {
            lastQueueSize = workQueue.size();
            return NULL;
        } else if (timeout > 0){
             uint64_t secs = (unsigned long)(trunc(timeout));
            uint64_t msecs = (unsigned long)((timeout - secs) * 1e6);
            boost::system_time to_time  = boost::get_system_time() + boost::posix_time::seconds(secs) + boost::posix_time::microseconds(msecs);
            boost::unique_lock< boost::mutex > lock(dataAvailableMutex);
            if ( dataAvailable.timed_wait( lock, to_time) == false ) {
                return NULL;
            }

            if (breakBlock) {
                return NULL;
            }
        } else {
            boost::unique_lock< boost::mutex > lock(dataAvailableMutex);
            dataAvailable.wait(lock);
            if (breakBlock) {
                return NULL;
            }
        }       
        
    }
    boost::mutex::scoped_lock lock1(dataBufferLock);
    BULKIO_dataFloat_In_i::dataTransfer *tmp = NULL;
    if ( streamID == "" ){
        tmp = workQueue.front();
        workQueue.pop_front();
    } else {
        std::deque< dataTransfer * >::iterator p = workQueue.begin();
        while ( p != workQueue.end() ) {
            if ( (*p)->streamID == streamID ) {
                tmp = *p;
                workQueue.erase(p);
                break;
            }
            p++;
       }
    
    }
    
    if ( tmp == NULL ) {
        lastQueueSize = workQueue.size();
        return NULL;
    }
    
    boost::mutex::scoped_lock lock2(sriUpdateLock);
    if (tmp->EOS) {
	    RH_SRIMap::iterator target = currentHs.find(std::string(tmp->streamID));
        if (target != currentHs.end()) {
            if (target->second.first.blocking) {
                RH_SRIMap::iterator currH;
                bool keepBlocking = false;
                for (currH = currentHs.begin(); currH != currentHs.end(); currH++) {
                    if (currH->second.first.blocking) {
                        keepBlocking = true;
                        break;
                    }
                }

                if (!keepBlocking) {
                    queueSem->setCurrValue(0);
                    blocking = false;
                }
            }
            currentHs.erase(target);
        }
    }

    if (blocking) {
        queueSem->decr();
    }
    
    lastQueueSize=0;
    return tmp;
}