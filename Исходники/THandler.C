void THandler::verifyInterpolantWithExternalTool( vector< Enode * > & expl
                                                , Enode * interp_list )
{
  uint64_t mask = 0xFFFFFFFFFFFFFFFEULL;
  for ( unsigned in = 1 ; in < core_solver.getNofPartitions( ) ; in ++ )
  {
    Enode * args = interp_list;
    // Advance in the interpolants list
    for ( unsigned i = 0 ; i < in - 1 ; i ++ )
      args = args->getCdr( );
    Enode * interp = args->getCar( );
    mask &= ~SETBIT( in );
    // Check A -> I, i.e., A & !I
    // First stage: print declarations
    const char * name = "/tmp/verifyinterp.smt2";
    std::ofstream dump_out( name );
    core_solver.dumpHeaderToFile( dump_out );
    // Print only A atoms
    dump_out << "(assert " << endl;
    dump_out << "(and" << endl;
    for ( size_t j = 0 ; j < expl.size( ) ; j ++ )
    {
      Enode * e = expl[ j ];
      assert( e->isTAtom( ) );
      assert( e->getPolarity( ) != l_Undef );
      assert( (core_solver.getIPartitions( e ) &  mask) != 0
           || (core_solver.getIPartitions( e ) & ~mask) != 0 );
      if ( (core_solver.getIPartitions( e ) & ~mask) != 0 )
      {
        bool negated = e->getPolarity( ) == l_False;
        if ( negated )
          dump_out << "(not ";
        e->print( dump_out );
        if ( negated )
          dump_out << ")";
        dump_out << endl;
      }
    }

    dump_out << "(not " << interp << ")" << endl;
    dump_out << "))" << endl;
    dump_out << "(check-sat)" << endl;
    dump_out << "(exit)" << endl;
    dump_out.close( );
    // Check !
    bool tool_res;
    if ( int pid = fork() )
    {
      int status;
      waitpid(pid, &status, 0);
      switch ( WEXITSTATUS( status ) )
      {
        case 0:
          tool_res = false;
          break;
        case 1:
          tool_res = true;
          break;
        default:
          perror( "Tool" );
          exit( EXIT_FAILURE );
      }
    }
    else
    {
      execlp( "tool_wrapper.sh", "tool_wrapper.sh", name, 0 );
      perror( "Tool" );
      exit( 1 );
    }

    if ( tool_res == true )
      opensmt_error2( config.certifying_solver, " says A -> I does not hold" );
    // Now check B & I
    dump_out.open( name );
    core_solver.dumpHeaderToFile( dump_out );
    // Print only B atoms
    dump_out << "(assert " << endl;
    dump_out << "(and" << endl;
    for ( size_t j = 0 ; j < expl.size( ) ; j ++ )
    {
      Enode * e = expl[ j ];
      assert( e->isTAtom( ) );
      assert( e->getPolarity( ) != l_Undef );
      assert( (core_solver.getIPartitions( e ) &  mask) != 0
           || (core_solver.getIPartitions( e ) & ~mask) != 0 );
      if ( (core_solver.getIPartitions( e ) & mask) != 0 )
      {
        bool negated = e->getPolarity( ) == l_False;
        if ( negated )
          dump_out << "(not ";
        e->print( dump_out );
        if ( negated )
          dump_out << ")";
        dump_out << endl;
      }
    }
    dump_out << interp << endl;
    dump_out << "))" << endl;
    dump_out << "(check-sat)" << endl;
    dump_out << "(exit)" << endl;
    dump_out.close( );
    // Check !
    tool_res;
    if ( int pid = fork() )
    {
      int status;
      waitpid(pid, &status, 0);
      switch ( WEXITSTATUS( status ) )
      {
        case 0:
          tool_res = false;
          break;
        case 1:
          tool_res = true;
          break;
        default:
          perror( "Tool" );
          exit( EXIT_FAILURE );
      }
    }
    else
    {
      execlp( "tool_wrapper.sh", "tool_wrapper.sh", name, 0 );
      perror( "Tool" );
      exit( 1 );
    }
    if ( tool_res == true )
      opensmt_error2( config.certifying_solver, " says B & I does not hold" );
  }
}