void data_recving (MYSQL* conn, char * tablename, int nr_be)
{
	int nr_exited = 0;
	int tag;
	int count = 0;
//	PacketPtr pack;
	int rank, eid, tid, data, finish, nr_record, mpi_rank, type, src_rank, dst_rank, sendsize, sendtype, recvsize, recvtype;
	int mpi_comm, mpi_tag;
	MRN::Network * net = GetNetwork();
	unsigned pid;
	long long unsigned time; 
	unsigned long time_s, time_us;

	char sql[2048];
	char buffer[500];
	char instance[40], metric[40];

	char *ename = NULL;
	char *hostname = NULL;
	char *procdata = NULL;


	Communicator *comm = net->get_BroadcastCommunicator();
	Stream *stream = net->new_Stream( comm, TFILTER_NULL, SFILTER_DONTWAIT );

	stream->send( PROT_DATA, "%d", 0 );

	printf_d("[MRNFE] recieving data...nr_exited is %d nr_be is %d\n",nr_exited,nr_be);

	if (mysql_autocommit (conn, 0) != 0)
		printf_d ("[MRNFE] %s\n", mysql_error(conn));

	while( nr_exited != nr_be )
	{
		PacketPtr pack;
		stream->recv( &tag, pack );
		count ++;
		switch (tag)
		{
			case PROT_DATA:
				pack->unpack("%d %d %d %uld %s %d %s",
						&tid,
						&pid,
						&eid,
						&time, 
						&hostname, 
						&finish,
						&ename);
				
				char *sql_tmp;
				sql_tmp = (char *) calloc (sizeof (char *), 200);
				snprintf_d(sql_tmp, 200, "CALL insertdata ( -1,%d, \"%s\" , %d, \"%s\", 7,\"FFFFFFFF\", '%llu', %d );"
						, pid, hostname, eid, ename, time, finish);
				if (mysql_query (conn, sql_tmp))
					printf_d ("[MRNFE] %s\n", mysql_error(conn));
				free (sql_tmp);
				free (hostname);
				free (ename);
				hostname = NULL;
				ename = NULL;
				
				break;

			case PROT_MPIDATA:											/*MPI wrapper trace 数据*/
				pack->unpack("%d %ud %s %d %s %d %d %d %d %d %d %d %d %d %uld %d",
						&mpi_rank,
						&pid,
						&hostname,
						&eid,
						&ename,
						&type,
						&mpi_comm,
						&mpi_tag,
						&src_rank,
						&dst_rank,
						&sendsize,
						&sendtype,
						&recvsize,
						&recvtype,
						&time,
						&finish);
				
			#ifdef debug
				printf_d ("[DEBUG]:\tRecv_Data: %d %u %s %d %s %d %x %d %d %d %d %d %d %d %llu %d\n", 
						mpi_rank,
						pid,
						hostname,
						eid,
						ename,
						type,
						mpi_comm,
						mpi_tag,
						src_rank,
						dst_rank,
						sendsize,
						sendtype,
						recvsize,
						recvtype,
						time,
						finish);
			#endif
				snprintf_d (sql, 2048,"CALL insertdata (%d, %u, \"%s\", %d, \"%s\", %d, \"%x\", %llu, %d);",
						mpi_rank,
						pid,
						hostname,
						eid,
						ename,
						type,
						mpi_comm,
						time,
						finish);

			#ifdef DEBUG
				printf_d ("[DEBUG]:\t%s\n", sql);
			#endif

				if (mysql_query (conn, sql))
				{
					printf_d ("[MRNFE] %s\n", mysql_error(conn));
				}

				if (type != 0)
				{
					snprintf_d (sql, 2048,"CALL insert_comm_data (%d, %u, \"%s\", %d, \"%s\", %d, %d, %d, %d, %d, %d, %d, %llu, %d);",
						mpi_rank,
						pid,
						hostname,
						eid,
						ename,
						mpi_tag,
						src_rank,
						dst_rank,
						sendsize,
						sendtype,
						recvsize,
						recvtype,
						time,
						finish);
					if (mysql_query (conn, sql))
					{
						printf_d ("[MRNFE] %s\n", mysql_error(conn));
					}

				}
				free (ename);
				free (hostname);
				ename = NULL;
				hostname = NULL;
				break;

			case PROT_PROC:												/*proc数据*/
				if(!use_proc)
				{
					printf_d ("[MRNFE] no proc!!! ignored\n");
					break;
				}
				{
					pack->unpack("%ud %ud %s %d %s %ud",
						&time_s, &time_us, &hostname, &nr_record,
						&procdata, &pid
						);

					//printf_d(" [DEBUG] %ld, %ld, %d %s\n", time_s, time_us, nr_record, procdata );
					char *p = procdata;
					float fdata;
					for( int i = 0; i < nr_record; i++ ){

						sscanf_d( p, "%s", buffer );
						p+=strlen(buffer)+1;
						sscanf_d( buffer, "%[^#]#%[^#]#%f", instance, metric, &fdata );

						snprintf_d(sql, 2048, "CALL insertproc( %ld, %ld, \"%s\", %d, \"%s\", \"%s\", '%f')"
							, time_s, time_us, hostname, pid, metric, instance, fdata);

						if (mysql_query (conn, sql))
                	   			{
			                        	printf_d ("[MRNFE] %s\n", mysql_error(conn));
        	        			}
						//printf_d ("%s\n", sql);
						//mysql_query( conn, sql );
					}

					free(procdata);
					free(hostname);
					procdata = hostname = NULL;
				}
				break;
			case PROT_PAPI:
				if (!use_papi)
				{
					printf_d ("[MRNFE] no papi!!! ignored\n");
					break;
				}
				else
				{
					long long papi_data;
					char *papi_event;
					pack->unpack("%s %ud %d %s %s %ld %uld %d",
							&ename,
							&pid,
							&tid,
							&hostname,
							&papi_event,
							&papi_data,
							&time,
							&finish);

					snprintf_d (sql, 2048, "CALL insert_papi_data(\"%s\", %u, %d, \"%s\", \"%s\", %lld, %llu, %d);", 
							ename,
							pid,
							tid,
							hostname,
							papi_event,
							papi_data,
							time,
							finish);
					if (mysql_query (conn, sql))
							printf_d ("[MRNFE] %s\n", mysql_error(conn));
					free (hostname);
					free (ename);
					free (papi_event);
					hostname = NULL;
					ename = NULL;
					papi_event = NULL;
				}
				break;
			case PROT_IO:
				char *io_data;
				long long unsigned stime, etime;
				pack->unpack ("%s %ud %d %s %s %uld %uld", 
						&ename,
						&pid,
						&tid,
						&hostname,
						&io_data,
						&stime,
						&etime);
				snprintf_d (sql, 2048, "CALL insert_io_data(\"%s\", %u, %d, \"%s\", \"%s\", %llu, %llu);",
						ename,
						pid,
						tid,
						hostname,
						io_data,
						stime,
						etime);	
				if (mysql_query (conn, sql))
						printf_d ("[MRNFE] %s\n", mysql_error(conn));
				free (hostname);
				free (ename);
				free (io_data);
				hostname = NULL;
				ename = NULL;
				io_data = NULL;
				break;
			case PROT_MPIRANK:											/*MPI rank数据*/

				pack->unpack("%d %d", &rank, &data);

				snprintf_d( sql, 2048, "update `%s_nodelist` set mpirank=%d where rank=%d", tablename, data, rank );
				mysql_query( conn, sql );

				break;
			case PROT_NODEDATA:											/*MPI节点数据*/
				pack->unpack ("%ud %d", &pid, &mpi_rank);
				snprintf_d (sql, 2048, "update `%s_nodelist` set mpirank=%d where pid=%u", tablename, mpi_rank, pid);
				mysql_query( conn, sql );
				break;
			case PROT_HALT:												/*发送停止*/
				nr_exited ++ ;
				printf_d( "[DEBUG] %d Back-ends Halted\n", nr_exited );
				break;

			default:
				break;
		}
		if (count % 10000 == 0)
			mysql_commit(conn);
	}

	FE::write_exiting_info();

}