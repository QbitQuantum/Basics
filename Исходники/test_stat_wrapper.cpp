int
main( int argc, const char *argv[] )
{
	int				 fd;
	const char		*path;
	StatWrapper		*wrapper = NULL;
	const char	*usage =
		"test [-h|--help] <file> [operations]";

	if ( argc < 2 ) {
		fprintf( stderr, "no file specified\n" );
		fprintf( stderr, "%s\n", usage );
		exit( 1 );
	}
	path = argv[1];
	if ( *path == '-' ) {
		fprintf( stderr, "no file specified\n" );
		fprintf( stderr, "%s\n", usage );
		Help( argv[0] );
		exit( 1 );
	}
	fd = safe_open_wrapper_follow( path, O_RDONLY );
	printf( "path set to '%s', fd to %d\n", path, fd );

	int		argno;
	int		skip = 0;
	for( argno = 2; argno < argc;  argno++ ) {
		if ( skip ) {
			skip--;
			continue;
		}
		const char	*arg = argv[argno];
		const char	*arg1 = NULL;
		const char	*arg2 = NULL;
		const char	*arg3 = NULL;
		if ( arg  && (argc > (argno+1)) && (*argv[argno+1] != '-')  ) {
			arg1 = argv[argno+1];
		}
		if ( arg1 && (argc > (argno+2)) && (*argv[argno+2] != '-')  ) {
			arg2 = argv[argno+2];
		}
		if ( arg2 && (argc > (argno+3)) && (*argv[argno+3] != '-')  ) {
			arg3 = argv[argno+3];
		}

		if ( (!strcmp( arg, "--help" )) || (!strcmp( arg, "-h")) ) {
			Help( argv[0] );
			exit( 0 );
		}

		else if ( (!strcmp( arg, "--path" )) || (!strcmp( arg, "-p")) ) {
			if ( !arg1 ) {
				fprintf( stderr, "--path usage: --path <path>\n" );
				exit( 1 );
			}
			path = arg1;
			fd = safe_open_wrapper_follow( path, O_RDONLY );
			skip = 1;
			printf( "path set to '%s', fd to %d\n", path, fd );
		}

		else if ( (!strcmp( arg, "--create" )) || (!strcmp( arg, "-c")) ) {

			if ( !arg1 || !arg2 ) {
				fprintf( stderr, "--create usage: --create <op> <which>\n" );
				exit( 1 );
			}

			skip = 2;
			const StatOp *op    = get_op( arg1 );
			const StatOp *which = get_op( arg1 );
			const char *n = "";
			bool auto_stat = false;

			// Create the object
			switch ( op->type ) {
			case StatWrapper::STATOP_STAT:
			case StatWrapper::STATOP_LSTAT:
			case StatWrapper::STATOP_BOTH:
				n = "StatWrapper(path,which)";
				auto_stat = ( (which->type==StatWrapper::STATOP_STAT)  ||
							  (which->type==StatWrapper::STATOP_LSTAT) ||
							  (which->type==StatWrapper::STATOP_BOTH)  ||
							  (which->type==StatWrapper::STATOP_ALL)   );
				wrapper = new StatWrapper( path, which->type );
				break;
			case StatWrapper::STATOP_FSTAT:
				n = "StatWrapper(fd,which)";
				wrapper = new StatWrapper( fd, which->type );
				auto_stat = ( (which->type==StatWrapper::STATOP_FSTAT) ||
							  (which->type==StatWrapper::STATOP_ALL)   );
				break;
			case StatWrapper::STATOP_NONE:
				n = "StatWrapper(void)";
				wrapper = new StatWrapper;
				break;
			case StatWrapper::STATOP_ALL:
			case StatWrapper::STATOP_LAST:
			default:
				fprintf( stderr, "%s (%d) doesn't make sense for create\n",
						 op->str, op->type );
				exit( 1 );
				break;
			}
			if ( !wrapper ) {
				fprintf( stderr,
						 "Failed to create StatWrapper (%s) object!\n", n );
				exit( 1 );
			}
			printf( "Created StatWrapper object via %s\n", n );

			printf( "Stat Functions:\n" );
			int		opint;
			for( opint = (int)StatWrapper::STATOP_MIN;
				 opint <= (int)StatWrapper::STATOP_MAX;
				 opint++ ) {
				StatWrapper::StatOpType	opno = (StatWrapper::StatOpType) opint;
				const char	*fn = wrapper->GetStatFn( opno );
				if ( NULL == fn ) {
					fn = "<NULL>";
				}
				const char	*name = get_op_name( opno );
				printf( "  %s = %s\n", name, fn );
			}

			if ( auto_stat ) {
				dump_status( *wrapper, "Stat results" );
			}
		}

		else if ( !strcmp( arg, "--set" ) ) {
			skip = 1;

			if ( !arg1 ) {
				fprintf( stderr, "--set usage: --set <op>\n" );
				exit( 1 );
			}
			const StatOp *op = get_op( arg1 );

			if ( !wrapper ) {
				fprintf( stderr, "--set: no wrapper object!\n" );
				exit( 1 );
			}

			// Set operations
			bool rc1 = false, rc2 = false;
			const char *n1 = "", *n2 = "";
			switch ( op->type ) {
			case StatWrapper::STATOP_STAT:
			case StatWrapper::STATOP_LSTAT:
			case StatWrapper::STATOP_BOTH:
				n1 = "SetPath";
				rc1 = wrapper->SetPath( path );
				break;
			case StatWrapper::STATOP_FSTAT:
				n1 = "SetFd";
				rc1 = wrapper->SetFD( fd );
				break;
			case StatWrapper::STATOP_NONE:
				break;
			case StatWrapper::STATOP_ALL:
				n1 = "SetPath";
				rc1 = wrapper->SetPath( path );
				n2 = "SetFD";
				rc2 = wrapper->SetFD( fd );
				break;
			case StatWrapper::STATOP_LAST:
			default:
				fprintf( stderr, "%s (%d) doesn't make sense for set\n",
						 op->str, op->type );
				exit( 1 );
				break;
			}
			if ( rc1 || rc2 ) {
				printf( "set via %s [%s/%s] OK\n",
						op->str, n1, n2 );
			} else {
				fprintf( stderr, "set via %s [%s/%s] FAILED\n",
						 op->str, n1, n2 );
				exit( 1 );
			}
		}

		else if ( (!strcmp( arg, "--stat" )) || (!strcmp( arg, "-s")) ) {
			if ( !arg2 ) {
				fprintf( stderr,
						 "--stat usage: --stat <op> <which> [f[orce]|[no]]\n");
				exit( 1 );
			}
			const StatOp *op    = get_op( arg1 );
			const StatOp *which = get_op( arg2 );
			bool force = true;
			bool force_set;

			if ( arg3 ) {
				skip = 3;
				force = (  (!strcasecmp(arg3,"f"))  ||
						   (!strcasecmp(arg3,"force")) );
			}
			else {
				skip = 2;
				force_set = false;
			}

			if ( !wrapper ) {
				fprintf( stderr, "--stat: no wrapper object!\n" );
				exit( 1 );
			}

			// Stat operations
			int		rc1 = 0, rc2 = 0;
			bool	op2 = false;
			char	*n1 = "", *n2 = "";
			switch ( op->type ) {
			case StatWrapper::STATOP_NONE:
			case StatWrapper::STATOP_LAST:
				if ( force_set ) {
					n1 = "Stat(which,force)";
					rc1 = wrapper->Stat( which->type, force );
				} else {
					n1 = "Stat(which)";
					rc1 = wrapper->Stat( which->type );
				}
				break;
			case StatWrapper::STATOP_STAT:
			case StatWrapper::STATOP_LSTAT:
			case StatWrapper::STATOP_BOTH:
				if ( force_set ) {
					n1 = "Stat(path,which,force)";
					rc1 = wrapper->Stat( path, which->type, force );
				} else {
					n1 = "Stat(path,which)";
					rc1 = wrapper->Stat( path, which->type );
				}
				break;
			case StatWrapper::STATOP_FSTAT:
				if ( force_set ) {
					n1 = "Stat(fd,force)";
					rc1 = wrapper->Stat( fd, which->type, force );
				} else {
					n1 = "Stat(fd)";
					rc1 = wrapper->Stat( fd );
				}
				break;
			case StatWrapper::STATOP_ALL:
				if ( force_set ) {
					n1 = "Stat(path,which,force)";
					rc1  = wrapper->Stat( path, which->type, force );
					n2 = "Stat(fd,force)";
					rc2 = wrapper->Stat( fd, force );
				} else {
					n1 = "Stat(path,which)";
					rc1  = wrapper->Stat( path, which->type );
					n2 = "Stat(fd)";
					rc2 = wrapper->Stat( fd );
				}
				op2 = true;
				break;
			default:
				fprintf( stderr, "%s (%d) doesn't make sense for create\n",
						 op->str, op->type );
			}
			printf( "%s %s (%d)\n", n1, rc1 ? "Failed":"OK", rc1 );
			if ( op2 ) {
				printf( "%s %s (%d)\n", n2, rc2 ? "Failed":"OK", rc2 );
			}	

			dump_status( *wrapper, "Stat results" );
		}

		else if ( (!strcmp( arg, "--retry" )) || (!strcmp( arg, "-r")) ) {
			if ( !wrapper ) {
				fprintf( stderr, "--retry: no wrapper object!\n" );
				exit( 1 );
			}

			int		rc = wrapper->Retry( );
			printf( "Retry %s: %d\n", rc ? "Failed":"OK", rc );

			dump_status( *wrapper, "Retry results" );
		}

		else if ( (!strcmp( arg, "--query" )) || (!strcmp( arg, "-q")) ) {
			if ( !wrapper ) {
				fprintf( stderr, "--query: no wrapper object!\n" );
				exit( 1 );
			}

			dump_status( *wrapper, "Query results" );
		}

		else {
			fprintf( stderr, "Unknown command %s\n", arg );
		}
	}

	return 0;
}