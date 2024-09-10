/*@
   MPID_Close_port - Close port

   Input Parameter:
.  port_name - Name of MPI port to close

   Notes:

.N Errors
.N MPI_SUCCESS
.N MPI_ERR_OTHER

@*/
int MPID_Close_port(const char *port_name)
{
    int mpi_errno=MPI_SUCCESS;

    if (portFns.ClosePort) {
	mpi_errno = portFns.ClosePort( port_name );
	if (mpi_errno != MPI_SUCCESS) {
	    TRACE_ERR("ClosePort returned with mpi_errno=%d\n", mpi_errno);
	}
    }

 fn_fail:
    return mpi_errno;
}