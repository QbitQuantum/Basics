int main(int argc, char **argv){
    #ifdef HAS_PARMETIS
    int size, rank, rc;
    char lfname[100];
    char efname[100];
    testcount = 0;
    rc = MPI_Init(&argc, &argv);
    if(rc != MPI_SUCCESS){
        FERROR("MPI Initialization error\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
    rank = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    sprintf(lfname, "parmetislog.%04d", rank);
    //0: debug, 5: critical
    LOG_INIT(lfname, NULL, 0);

    parmetis_with_amd();
    parmetis_only();
    parmetis_with_metmmd();

    MPI_Finalize();
    LOG_CLOSE();
    #else // ifdef HAS_PARMETIS
    cout << "Enable HAS_PARMETIS flag and recompile to test parmetis functions" << endl;
    #endif // HAS_PARMETIS
    return 0;
} // main