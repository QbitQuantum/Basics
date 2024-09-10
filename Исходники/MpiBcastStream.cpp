ssize_t MpiBcastStream::read(const Bytes& b) {
    if (terminate) {
      return -1;
    }
    if (readAvail == 0) {
        // get new data
        reset();
        int size;
        #ifdef MPI_DEBUG
        printf("[MpiBcastStream @ %s] Trying to read\n", name.c_str());
        #endif

        MPI_Bcast(&size, 1, MPI_INT, 0,comm->comm);
        #ifdef MPI_DEBUG
        printf("[MpiBcastStream @ %s] got size %d\n", name.c_str(), size);
        #endif
        if (size < 0) {
            execCmd(size);
            return 0;
        }
        if ((size_t)size == b.length()) {
            // size of received data matches expected data
            // do not use buffer, but write directly
            MPI_Bcast(b.get(), size, MPI_BYTE, 0, comm->comm);
            return size;
        }
        else {
            // allocate new buffer
            readBuffer = new char[size];
            MPI_Bcast(readBuffer, size, MPI_BYTE, 0, comm->comm);
            //printf("got new msg of size %d\n", size);
            readAvail = size;
            readAt = 0;
        }
    }
    if (readAvail>0) {
        // copy data from buffer to destination object
        int take = readAvail;
        if (take>(int)b.length()) {
            take = b.length();
        }
        memcpy(b.get(),readBuffer+readAt,take);
        //printf("read %d of %d \n", take, readAvail);
        readAt += take;
        readAvail -= take;
        return take;
    }
    return 0;
}