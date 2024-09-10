void MpiP2PStream::write(const Bytes& b) {
    int size = b.length();
    //MPI_Bcast(&size, 1, MPI_INT, MPI_ROOT, intercomm );
    MPI_Request request;
    MPI_Status status;
    int flag = 0;
    int rank = comm->rank();
    //MPI_Send(b.get(), size, MPI_BYTE, 0, 0, intercomm);

    MPI_Isend(b.get(), size, MPI_BYTE, !rank , 0, comm->comm, &request );
    while(true) {
        /*
        // TODO: Need to implement a mechanism for breaking!!
        if (terminate)
            break;
        */
        // Check if message has been received
        MPI_Test(&request, &flag, &status);
        if (flag)
            break;
        // Prevent the busy polling which hurts
        // performance in the oversubscription scenario
        Time::yield();
    }
}