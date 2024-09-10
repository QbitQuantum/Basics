void mpi_send_workaround(int dest, int tag, const T& value,
                         boost::mpi::communicator & comm)
{
    // serialize T into a string
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << value;
    // send the string
    comm.send(dest, tag, oss.str());
}