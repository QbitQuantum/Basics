/**
 *  Function for creating and holding of shared context.
 *  Generation and uploading of new textures over some period with sleep time.
 */
void GPUAsyncLoader::runLocal()
{
    LBASSERT( !_storageTexture3D );
    EQ_GL_CALL( glGenTextures( 1, &_storageTexture3D ));

    // confirm successfull loading
    _loadResponds.push( GPULoadRespond( GPULoadRequest(), GPULoadStatus::INITIALIZED ));

    // start fresh in paused state
    postCommand( GPUCommand::PAUSE );

    std::string name = std::string( "GPU_Loader " ).append( strUtil::toString<>(this) );
    util::EventLogger* events = util::StatLogger::instance().createLogger( name );
    LBASSERT( events );
    uint64_t blocksLoaded = 0;

    LBINFO << "async GPU fetcher initialized: " << getWindow() << std::endl;
    LBINFO << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << std::endl;


    lunchbox::Clock clock;
    while( true )
    {
        // try to read new loading request
        bool sleepWait = true;

        GPULoadRequest loadRequestTmp;

        if( _loadRequests.getFront( loadRequestTmp ))
        {
//            LBWARN << "GPUAsyncLoader: trying to load request" << std::endl;
            sleepWait = false;
            _loadResponds.push( GPULoadRespond( loadRequestTmp, GPULoadStatus::STARTED ));

            GPULoadRequest loadRequest;

            bool loadingFailed = true;
            if( _decompressor && _ramPool &&
                _loadRequests.tryPop( loadRequest ) &&
                loadRequest == loadRequestTmp )
            {
                // load / request new texture
                const RAMDataElement* dataEl = _ramPool->getData( loadRequest.nodeId, _dataVersion, loadRequest.reload );

                bool sizePassed = true;
                if( dataEl && dataEl->size() < _compressedBS )
                {
                    LBERROR << "size of the data returned by RAM Pool is smaller than required by GPU" << std::endl;
                    sizePassed = false;
                }

                if( dataEl && sizePassed )
                {
                    clock.reset();

                    // LBWARN << "GPUAsyncLoader: got positive feedback from RAM Pool" << std::endl;
                    const Box_i32 coords = _cacheIndex->getBlockCoordinates( loadRequest.posOnGPU );

                    if( coords != Box_i32( ))
                    {
                        if( blocksLoaded == 0 )
                            LBWARN << "Loaded blocks to GPU: " << blocksLoaded << std::endl;

//                        LBWARN << loadRequest << std::endl;
                        _decompressor->load( dataEl, loadRequest );

                        const uint32_t blockDim = _cacheIndex->getBlockDim();
                        _pbo->bind();
                        EQ_GL_CALL( glBindTexture( GL_TEXTURE_3D, _storageTexture3D ));
                        EQ_GL_CALL( glTexSubImage3D( GL_TEXTURE_3D, 0,
                                            coords.s.x, coords.s.y, coords.s.z,
                                            blockDim, blockDim, blockDim,
                                            GL_ALPHA, _byteFormat3D, NULL ));
                        _pbo->unbind();

                        EQ_GL_CALL( glFinish( ));

                        _loadResponds.push( GPULoadRespond( loadRequest, GPULoadStatus::FINISHED ));
                        loadingFailed = false;

                        const uint32_t compressedSize = _ramPool->getDataHDDIO()->getBlockSize_( loadRequest.treePos );

                        double timeD = clock.getTimed();
                        double speedC = (compressedSize                             / (1024.f * 1024.f)) / timeD;
                        double speedD = ((blockDim*blockDim*blockDim*sizeof(float)) / (1024.f * 1024.f)) / timeD;

                        *events << "GBL (GPU_Block_Loaded) " << (++blocksLoaded) << " in " << timeD << " ms, at " 
                                << speedC << " MB/s (" << speedD << " MB/s)" <<std::endl;

                        if( blocksLoaded % 100 == 0 )
                            LBWARN << "Loaded blocks to GPU: " << blocksLoaded << std::endl;
                    }
                }
            }
            if( loadingFailed )
                _loadResponds.push( GPULoadRespond( loadRequestTmp, GPULoadStatus::FAILED ));
        }


        // check for commands
        if( _processCommands( sleepWait )) return;

        // in case there were no commands it will sleep a bit till the next check
        if( sleepWait )
        {
            lunchbox::sleep( 20 ); // time in ms
            if( _processCommands( sleepWait )) return; // check again for new commands
        }
    }
}