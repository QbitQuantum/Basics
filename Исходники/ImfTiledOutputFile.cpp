void	
TiledOutputFile::writeTiles (int dx1, int dx2, int dy1, int dy2,
                             int lx, int ly)
{
    try
    {
        Lock lock (*_streamData);

        if (_data->slices.size() == 0)
	    throw IEX_NAMESPACE::ArgExc ("No frame buffer specified "
			       "as pixel data source.");

	if (!isValidTile (dx1, dy1, lx, ly) || !isValidTile (dx2, dy2, lx, ly))
	    throw IEX_NAMESPACE::ArgExc ("Tile coordinates are invalid.");

	if (!isValidLevel (lx, ly))
	    THROW (IEX_NAMESPACE::ArgExc,
                   "Level coordinate "
                   "(" << lx << ", " << ly << ") "
                   "is invalid.");
        //
        // Determine the first and last tile coordinates in both dimensions
        // based on the file's lineOrder
        //
                               
        if (dx1 > dx2)
            swap (dx1, dx2);
        
        if (dy1 > dy2)
            swap (dy1, dy2);
        
        int dyStart = dy1;
	int dyStop  = dy2 + 1;
	int dY      = 1;
    
        if (_data->lineOrder == DECREASING_Y)
        {
            dyStart = dy2;
            dyStop  = dy1 - 1;
            dY      = -1;
        }
        
        int numTiles = (dx2 - dx1 + 1) * (dy2 - dy1 + 1);
        int numTasks = min ((int)_data->tileBuffers.size(), numTiles);

        //
        // Create a task group for all tile buffer tasks.  When the
	// task group goes out of scope, the destructor waits until
	// all tasks are complete.
        //

        {
            TaskGroup taskGroup;
    
            //
            // Add in the initial compression tasks to the thread pool
            //
    
            int nextCompBuffer = 0;
	    int dxComp         = dx1;
	    int dyComp         = dyStart;

            while (nextCompBuffer < numTasks)
            {
                ThreadPool::addGlobalTask (new TileBufferTask (&taskGroup,
                                                               _data,
                                                               nextCompBuffer++,
                                                               dxComp, dyComp,
                                                               lx, ly));
                dxComp++;

                if (dxComp > dx2)
                {
                    dxComp = dx1;
                    dyComp += dY;
                }
            }
            
            //
            // Write the compressed buffers and add in more compression
	    // tasks until done
            //
    
            int nextWriteBuffer = 0;
	    int dxWrite         = dx1;
	    int dyWrite         = dyStart;

            while (nextWriteBuffer < numTiles)
            {
		//
                // Wait until the nextWriteBuffer is ready to be written
		//

                TileBuffer* writeBuffer =
                                    _data->getTileBuffer (nextWriteBuffer);

                writeBuffer->wait();
    
		//
                // Write the tilebuffer
		//

                bufferedTileWrite (_streamData, _data, dxWrite, dyWrite, lx, ly,
                                   writeBuffer->dataPtr,
                                   writeBuffer->dataSize);
                
		//
                // Release the lock on nextWriteBuffer
		//

                writeBuffer->post();
                
		//
                // If there are no more tileBuffers to compress, then
		// only continue to write out remaining tileBuffers,
		// otherwise keep adding compression tasks.
		//

                if (nextCompBuffer < numTiles)
                {
		    //
                    // add nextCompBuffer as a compression Task
		    //

                    ThreadPool::addGlobalTask
			(new TileBufferTask (&taskGroup,
					     _data,
					     nextCompBuffer,
                                             dxComp, dyComp,
					     lx, ly));
                }
    
                nextWriteBuffer++;
                dxWrite++;

                if (dxWrite > dx2)
                {
                    dxWrite = dx1;
                    dyWrite += dY;
                }
                    
                nextCompBuffer++;
                dxComp++;

                if (dxComp > dx2)
                {
                    dxComp = dx1;
                    dyComp += dY;
                }
            }

	    //
            // finish all tasks
	    //
        }

	//
	// Exeption handling:
	//
	// TileBufferTask::execute() may have encountered exceptions, but
	// those exceptions occurred in another thread, not in the thread
	// that is executing this call to TiledOutputFile::writeTiles().
	// TileBufferTask::execute() has caught all exceptions and stored
	// the exceptions' what() strings in the tile buffers.
	// Now we check if any tile buffer contains a stored exception; if
	// this is the case then we re-throw the exception in this thread.
	// (It is possible that multiple tile buffers contain stored
	// exceptions.  We re-throw the first exception we find and
	// ignore all others.)
	//

	const string *exception = 0;

        for (size_t i = 0; i < _data->tileBuffers.size(); ++i)
	{
            TileBuffer *tileBuffer = _data->tileBuffers[i];

	    if (tileBuffer->hasException && !exception)
		exception = &tileBuffer->exception;

	    tileBuffer->hasException = false;
	}

	if (exception)
	    throw IEX_NAMESPACE::IoExc (*exception);
    }
    catch (IEX_NAMESPACE::BaseExc &e)
    {
        REPLACE_EXC (e, "Failed to write pixel data to image "
                        "file \"" << fileName() << "\". " << e);
        throw;
    }
}