void MProject::expand( ContFile& pmak, const MCommand& cmd, const char* head )
{
    if( cmd.size() > 0 ) {
        pmak.printf( "%s\n", head );
        MCommand c;
        cmd.expand( c, &_filename, _config->nilTool(), "*", NULL, 0 );
        insertBlanks( c );
        pmak.puts( c );
        pmak.puts( "\n" );
    }
}