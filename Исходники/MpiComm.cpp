bool MpiComm::connect(ConstString port) {

    char* port_name = new char[port.length()+1];
    memcpy(port_name, port.c_str(), port.length());
    port_name[port.length()] = '\0';

    #ifdef MPI_DEBUG
    printf("[MpiComm @ %s] Waiting for accept\n", name.c_str());
    #endif

    MPI_Comm intercomm;
    MPI_Comm_set_errhandler(comm, MPI_ERRORS_RETURN);
    int err = MPI_Comm_connect( port_name, MPI_INFO_NULL, 0, comm,  &intercomm );
    MPI_Comm_set_errhandler(comm, MPI_ERRORS_ARE_FATAL);

    if (err != MPI_SUCCESS ) {
        yError("MpiCarrier: Couldn't create connection\n");
        return false;
    }


    #ifdef MPI_DEBUG
    printf("[MpiComm @ %s] Connection established\n", name.c_str());
    #endif

    bool high = true;
    MPI_Intercomm_merge(intercomm, high, &comm);
    MPI_Comm_disconnect(&intercomm);

    #ifdef MPI_DEBUG
    printf("[MpiComm @ %s] Comms merged \n", name.c_str());
    #endif

    delete[] port_name;

    return true;
}