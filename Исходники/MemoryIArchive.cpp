   /*
   * Receive a block.
   */
   void MemoryIArchive::recv(MPI::Intracomm& comm, int source)
   {
      int  myRank     = comm.Get_rank();
      int  comm_size  = comm.Get_size();

      // Preconditions
      if (source > comm_size - 1 || source < 0) {
         UTIL_THROW("Source rank out of bounds");
      }
      if (source == myRank) {
         UTIL_THROW("Source and desination identical");
      }

      size_t recvCapacity = capacity_ + sizeof(size_t);
      comm.Recv(buffer_, recvCapacity, MPI::UNSIGNED_CHAR, source, 5);

      begin_ = buffer_ + sizeof(size_t);
      cursor_ = begin_;

      size_t* sizePtr = (size_t*) buffer_;
      size_t  size = *sizePtr;
      end_  = buffer_ + size;
   }