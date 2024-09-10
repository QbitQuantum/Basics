  /** Method to write out the old objects that have been
   * stored in the "toWrite" buffer.
   */
  void DiskBuffer::writeOldObjects()
  {
    if (m_writeBufferUsed > DISK_BUFFER_SIZE_TO_REPORT_WRITE)
      std::cout << "DiskBuffer:: Writing out " << m_writeBufferUsed << " events in " << m_writeBuffer.size() << " blocks." << std::endl;
//    std::cout << getMemoryStr() << std::endl;
//    std::cout << getFreeSpaceMap().size() << " entries in the free size map." << std::endl;
//    for (freeSpace_t::iterator it = m_free.begin(); it != m_free.end(); it++)
//      std::cout << " Free : " << it->getFilePosition() << " size " << it->getSize() << std::endl;
//    std::cout << m_fileLength << " length of file" << std::endl;

    // Holder for any objects that you were NOT able to write.
    writeBuffer_t couldNotWrite;
    size_t memoryNotWritten = 0;

    // Prevent simultaneous file access (e.g. write while loading)
    m_fileMutex.lock();

    // Iterate through the map
    writeBuffer_t::iterator it = m_writeBuffer.begin();
    writeBuffer_t::iterator it_end = m_writeBuffer.end();

    ISaveable * obj = NULL;
    for (; it != it_end; ++it)
    {
      // the object will be changed so no other way to go! TODO: Rethink the desighn
      obj = const_cast<ISaveable *>(*it);
      if (!obj->isBusy())
      {
        uint64_t NumAllEvents = obj->getTotalDataSize();
        uint64_t fileIndexStart;
        if (!obj->wasSaved())
        {
            fileIndexStart=this->allocate(NumAllEvents);
           // Write to the disk; this will call the object specific save function;
            obj->saveAt(fileIndexStart,NumAllEvents);
        }
        else
        {
          uint64_t NumFileEvents= obj->getFileSize();
          if (NumAllEvents != NumFileEvents)
          {
          // Event list changed size. The MRU can tell us where it best fits now.
            fileIndexStart= this->relocate(obj->getFilePosition(), NumFileEvents, NumAllEvents);
           // Write to the disk; this will call the object specific save function;
            obj->saveAt(fileIndexStart,NumAllEvents);
          }       
          else // despite object size have not been changed, it can be modified other way. In this case, the method which changed the data should set dataChanged ID
          {
            if(obj->isDataChanged())
            {
              fileIndexStart = obj->getFilePosition();
              obj->saveAt(fileIndexStart,NumAllEvents);
            }
            else // just clean the object up -- it just occupies memory
              obj->clearDataFromMemory();
          }
        }
      } 
      else // object busy
      {
        // The object is busy, can't write. Save it for later
        //couldNotWrite.insert( pairObj_t(obj->getFilePosition(), obj) );
        couldNotWrite.insert( obj );
        memoryNotWritten += obj->getDataMemorySize();
      }
    }

    // use last object to clear NeXus buffer and actually write data to HDD
    if (obj)
    {
      // NXS needs to flush the writes to file by closing and re-opening the data block.
      // For speed, it is best to do this only once per write dump, using last object saved
      obj->flushData();
    }

    // Exchange with the new map you built out of the not-written blocks.
    m_writeBuffer.swap(couldNotWrite);
    m_writeBufferUsed = memoryNotWritten;

    m_fileMutex.unlock();
  }