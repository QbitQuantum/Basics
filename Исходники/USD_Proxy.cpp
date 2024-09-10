bool
GusdUSD_StageProxy::_Load(ScopedLock& lock,
                          UsdStage::InitialLoadSet loadSet,
                          const UnorderedPathSet* pathsToLoad,
                          GusdUT_ErrorContext* err)
{
    if(!_microNode.requiresUpdate(0)) {
        /* XXX: Errors copied will currently only include errors,
           not warning. This is because TfErrorMark, which is being used to
           capture USD errors, is currently not able to capture warnings.
           
           This means that in the event that the stage is valid, very little
           work will be done. This is expected to change in Tf eventually,
           in which case every stage lookup may involve an excess amount of
           warning copying on every lookup, possibly impacting performance.
           May need to revisit this approach of copying all errors when Tf
           starts allowing warnings to be captured.*/
        if(err)
            _CopyErrors(*err);

        if(pathsToLoad && _primLoader) {
            if(_primLoader->LoadIfNeeded(lock, *pathsToLoad, _stage,
                                         /*have lock*/ false))
                lock.DowngradeToReader();
        }
        return _stage;
    }
    if(lock.UpgradeToWriter() || _microNode.requiresUpdate(0)) {
        /* Mark the proxy clean, so that we don't attempt to load
           again even if loading has failed. To attempt to reload,
           the node should be dirtied with MarkDirty() prior to
           the next load attempt.*/
        _microNode.update(0);

        _errors.clearAndDestroyErrors();

        GusdUT_ErrorManager errMgr(_errors);
        GusdUT_TfErrorScope scope(errMgr);
        
        if(_stage) {
            /* Asking to load when we already have a stage means
               we should reload the stage.*/
            _Reload(_stage);
            
            lock.DowngradeToReader();

            // XXX: Can reloading fail?
            return true;
        }

        if(SdfLayerRefPtr rootLyr =
           SdfLayer::FindOrOpen(_key->path.GetString())) {
            
            // Load the stage from the cache.
            UsdStageCacheContext ctx(_cache.GetCache());
            if(UsdStageRefPtr stage = UsdStage::Open(
                   rootLyr, _key->sessionLyr, _key->resolverCtx, loadSet)) {
                
                _realPath = TfToken(TfRealPath( _key->path));
                struct stat attrib;
                if( stat(_realPath.GetText(), &attrib) == 0 ) {
                    _mtime = attrib.st_mtime;
                }

                UT_ASSERT(_cache.GetCache().Contains(stage));
                _stage = stage;

                _InitLoadSet(loadSet);
                _stageData.Update(stage);

                if(pathsToLoad && _primLoader) {
                    _primLoader->Load(SdfPathSet(pathsToLoad->begin(),
                                                 pathsToLoad->end()), stage);
                }
            }
        } else {
            /* Sdf doesn't throw errors here, so we need
               to report the failure ourselves.*/
            UT_WorkBuffer buf;
            buf.sprintf("Failed to open layer: %s",
                        _key->path.GetString().c_str());
            GusdUT_LogGenericError(_errors, buf.buffer());
        }
    }
    if(err) 
        _CopyErrors(*err);
    lock.DowngradeToReader();
    return _stage;
}