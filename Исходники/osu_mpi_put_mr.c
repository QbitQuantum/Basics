double message_rate (long * buffer, int size, int iterations, int me, int pairs, int nxtpe, MPI_Win win)
{
	int64_t begin, end; 
	int i, offset;

	/*
	 * Touch memory
	 */
	memset(buffer, size, MAX_MSG_SZ * ITERS_LARGE * sizeof(long));

	MPI_Barrier(MPI_COMM_WORLD);
	
	if (me < pairs) {
		begin = TIME();

		for (i = 0, offset = 0; i < iterations; i++, offset++) {
			MPI_Put ((buffer + offset*size), size, MPI_LONG, nxtpe, offset*size, size, MPI_LONG, win);
			//MPI_Win_flush_local (nxtpe, win);
		}
		//MPI_Win_flush_all(win);
		MPI_Win_flush(nxtpe, win);
		end = TIME();

		return ((double)iterations * 1e6) / ((double)end - (double)begin);
	}
	return 0;
}