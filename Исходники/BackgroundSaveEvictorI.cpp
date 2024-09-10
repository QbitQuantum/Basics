void
Freeze::BackgroundSaveEvictorI::run()
{
    try
    {
        for(;;)
        {
            deque<BackgroundSaveEvictorElementPtr> allObjects;
            deque<BackgroundSaveEvictorElementPtr> deadObjects;

            size_t saveNowThreadsSize = 0;
            
            {
                Lock sync(*this);

                while(!_savingThreadDone &&
                      (_saveNowThreads.size() == 0) &&
                      (_saveSizeTrigger < 0 || static_cast<Int>(_modifiedQueue.size()) < _saveSizeTrigger))
                {
                    if(_savePeriod == IceUtil::Time::milliSeconds(0))
                    {
                        wait();
                    }
                    else if(timedWait(_savePeriod) == false)
                    {
                        //
                        // Timeout, so let's save
                        //
                        break; // while
                    }                           
                }
                
                saveNowThreadsSize = _saveNowThreads.size();
                
                if(_savingThreadDone)
                {
                    assert(_modifiedQueue.size() == 0);
                    assert(saveNowThreadsSize == 0);
                    break; // for(;;)
                }
                
                //
                // Check first if there is something to do!
                //
                if(_modifiedQueue.size() == 0)
                {
                    if(saveNowThreadsSize > 0)
                    {
                        _saveNowThreads.clear();
                        notifyAll();
                    }
                    continue; // for(;;)
                }
                
                _modifiedQueue.swap(allObjects);
            }
            
            const size_t size = allObjects.size();
            
            deque<StreamedObjectPtr> streamedObjectQueue;
            
            Long streamStart = IceUtil::Time::now(IceUtil::Time::Monotonic).toMilliSeconds();
            
            //
            // Stream each element
            //
            for(size_t i = 0; i < size; i++)
            {
                BackgroundSaveEvictorElementPtr& element = allObjects[i];
                
                bool tryAgain;
                do
                {
                    tryAgain = false;
                    ObjectPtr servant = 0;
                    
                    //
                    // These elements can't be stale as only elements with 
                    // usageCount == 0 can become stale, and the modifiedQueue
                    // (us now) owns one count.
                    //

                    IceUtil::Mutex::Lock lockElement(element->mutex);
                    Byte status = element->status;
                    
                    switch(status)
                    {
                        case created:
                        case modified:
                        {
                            servant = element->rec.servant;
                            break;
                        }   
                        case destroyed:
                        {
                            size_t index = streamedObjectQueue.size();
                            streamedObjectQueue.resize(index + 1);
                            streamedObjectQueue[index] = new StreamedObject;
                            stream(element, streamStart, streamedObjectQueue[index]);

                            element->status = dead;
                            deadObjects.push_back(element);

                            break;
                        }   
                        case dead:
                        {
                            deadObjects.push_back(element);
                            break;
                        }
                        default:
                        {
                            //
                            // Nothing to do (could be a duplicate)
                            //
                            break;
                        }
                    }
                    if(servant == 0)
                    {
                        lockElement.release();
                    }
                    else
                    {
                        IceUtil::AbstractMutex* mutex = dynamic_cast<IceUtil::AbstractMutex*>(servant.get());
                        if(mutex != 0)
                        {
                            //
                            // Lock servant and then element so that user can safely lock
                            // servant and call various Evictor operations
                            //
                            
                            IceUtil::AbstractMutex::TryLock lockServant(*mutex);
                            if(!lockServant.acquired())
                            {
                                lockElement.release();

                                IceUtil::TimerTaskPtr watchDogTask;
                                if(_timer)
                                {
                                    watchDogTask = new WatchDogTask(*this);
                                    _timer->schedule(watchDogTask, IceUtil::Time::milliSeconds(_streamTimeout));
                                }
                                lockServant.acquire();
                                if(watchDogTask)
                                {
                                    _timer->cancel(watchDogTask);
                                    watchDogTask = 0;
                                }

                                lockElement.acquire();
                                status = element->status;
                            }
  
                            switch(status)
                            {
                                case created:
                                case modified:
                                {
                                    if(servant == element->rec.servant)
                                    {
                                        size_t index = streamedObjectQueue.size();
                                        streamedObjectQueue.resize(index + 1);
                                        streamedObjectQueue[index] = new StreamedObject;
                                        stream(element, streamStart, streamedObjectQueue[index]);

                                        element->status = clean;
                                    }
                                    else
                                    {
                                        tryAgain = true;
                                    }
                                    break;
                                }
                                case destroyed:
                                {
                                    lockServant.release();
                                    
                                    size_t index = streamedObjectQueue.size();
                                    streamedObjectQueue.resize(index + 1);
                                    streamedObjectQueue[index] = new StreamedObject;
                                    stream(element, streamStart, streamedObjectQueue[index]);

                                    element->status = dead;
                                    deadObjects.push_back(element);
                                    break;
                                }   
                                case dead:
                                {
                                    deadObjects.push_back(element);
                                    break;
                                }
                                default:
                                {
                                    //
                                    // Nothing to do (could be a duplicate)
                                    //
                                    break;
                                }
                            }
                        }
                        else
                        {
                            DatabaseException ex(__FILE__, __LINE__);
			    Ice::Object& servant = *element->rec.servant;
                            ex.message = string(typeid(servant).name()) + " does not implement IceUtil::AbstractMutex";
                            throw ex;
                        }
                    }
                } while(tryAgain);
            }
            
            if(_trace >= 1)
            {
                Long now = IceUtil::Time::now(IceUtil::Time::Monotonic).toMilliSeconds();
                Trace out(_communicator->getLogger(), "Freeze.Evictor");
                out << "streamed " << streamedObjectQueue.size() << " objects in " 
                    << static_cast<Int>(now - streamStart) << " ms";
            }
            
            //
            // Now let's save all these streamed objects to disk using a transaction
            //
            
            //
            // Each time we get a deadlock, we reduce the number of objects to save
            // per transaction
            //
            size_t txSize = streamedObjectQueue.size();
            if(txSize > static_cast<size_t>(_maxTxSize))
            {
                txSize = static_cast<size_t>(_maxTxSize);
            }
            bool tryAgain;
            
            do
            {
                tryAgain = false;
                
                while(streamedObjectQueue.size() > 0)
                {
                    if(txSize > streamedObjectQueue.size())
                    {
                        txSize = streamedObjectQueue.size();
                    }
                    
                    Long saveStart = IceUtil::Time::now(IceUtil::Time::Monotonic).toMilliSeconds();
                   
                    try
                    {
                        DbTxn* tx = 0;
                        _dbEnv->getEnv()->txn_begin(0, &tx, 0);

                        long txnId = 0;
                        if(_txTrace >= 1)
                        {
                            txnId = (tx->id() & 0x7FFFFFFF) + 0x80000000L;
                            Trace out(_communicator->getLogger(), "Freeze.Evictor");
                            out << "started transaction " << hex << txnId << dec << " in saving thread";
                        }

                        try
                        {       
                            for(size_t i = 0; i < txSize; i++)
                            {
                                StreamedObjectPtr obj = streamedObjectQueue[i];
                                Dbt key, value;
                                obj->key->getDbt(key);
                                if(obj->value)
                                {
                                    obj->value->getDbt(value);
                                }
                                obj->store->save(key, value, obj->status, tx);
                            }
                        }
                        catch(...)
                        {
                            tx->abort();
                            if(_txTrace >= 1)
                            {
                                Trace out(_communicator->getLogger(), "Freeze.Evictor");
                                out << "rolled back transaction " << hex << txnId << dec;
                            }
                            throw;
                        }
                        tx->commit(0);

                        if(_txTrace >= 1)
                        {
                            Trace out(_communicator->getLogger(), "Freeze.Evictor");
                            out << "committed transaction " << hex << txnId << dec;
                        }

                        streamedObjectQueue.erase(streamedObjectQueue.begin(), streamedObjectQueue.begin() + txSize);
                        
                        if(_trace >= 1)
                        {
                            Long now = IceUtil::Time::now(IceUtil::Time::Monotonic).toMilliSeconds();
                            Trace out(_communicator->getLogger(), "Freeze.Evictor");
                            out << "saved " << txSize << " objects in " 
                                << static_cast<Int>(now - saveStart) << " ms";
                        }
                    }
                    catch(const DbDeadlockException&)
                    {
                        if(_deadlockWarning)
                        {
                            Warning out(_communicator->getLogger());
                            out << "Deadlock in Freeze::BackgroundSaveEvictorI::run while writing into Db \"" + _filename
                                + "\"; retrying ...";
                        }
                        
                        tryAgain = true;
                        txSize = (txSize + 1)/2;
                    }
                    catch(const DbException& dx)
                    {
                        DatabaseException ex(__FILE__, __LINE__);
                        ex.message = dx.what();
                        throw ex;
                    }
                } 
            }
            while(tryAgain);
            
            {
                Lock sync(*this);
               
                //
                // Release usage count
                //
                for(deque<BackgroundSaveEvictorElementPtr>::iterator p = allObjects.begin();
                    p != allObjects.end(); p++)
                {
                    BackgroundSaveEvictorElementPtr& element = *p;
                    element->usageCount--;
                }
                allObjects.clear();

                for(deque<BackgroundSaveEvictorElementPtr>::iterator q = deadObjects.begin();
                    q != deadObjects.end(); q++)
                {
                    BackgroundSaveEvictorElementPtr& element = *q;
                    if(!element->stale)
                    {
                        //
                        // Can be stale when there are duplicate elements on the
                        // deadObjecst queue
                        //

                        if(!element->stale && element->usageCount == 0 && element->keepCount == 0)
                        {
                            //
                            // Get rid of unused dead elements
                            //
                            IceUtil::Mutex::Lock lockElement(element->mutex);
                            if(element->status == dead)
                            {
                                evict(element);
                            }
                        }
                    }
                }
                deadObjects.clear();
                evict();
                
                if(saveNowThreadsSize > 0)
                {
                    _saveNowThreads.erase(_saveNowThreads.begin(), _saveNowThreads.begin() + saveNowThreadsSize);
                    notifyAll();
                }
            }
        }
    }
    catch(const std::exception& ex)
    {
        Error out(_communicator->getLogger());
        out << "Saving thread killed by exception: " << ex;
        out.flush();
        handleFatalError(this, _communicator);
    }
    catch(...)
    {
        Error out(_communicator->getLogger());
        out << "Saving thread killed by unknown exception";
        out.flush();
        handleFatalError(this, _communicator);
    }
}