bool
Interpreter::SignalType::Get( CommandInterpreter& inInterpreter )
{
    Lock lock( inInterpreter.StateMachine() );
    const GenericSignal& signal = inInterpreter.StateMachine().ControlSignal();
    string name = inInterpreter.GetToken();
    if( !::stricmp( name.c_str(), "Channels" ) )
    {
        inInterpreter.Out() << signal.Channels();
    }
    else if( !::stricmp( name.c_str(), "Elements" ) )
    {
        inInterpreter.Out() << signal.Elements();
    }
    else
    {
        CommandInterpreter::ArgumentList args;
        inInterpreter.ParseArguments( name, args );
        if( ::stricmp( name.c_str(), "Signal" ) )
            throw bciexception( "Use 'Signal' to address the signal" );
        if( args.size() != 1 || args[0].size() != 2 )
            throw bciexception( "Expected two signal indices" );
        int idx1 = ::atoi( args[0][0].c_str() ) - 1,
            idx2 = ::atoi( args[0][1].c_str() ) - 1;
        if( idx1 < 0 || idx2 < 0 || idx1 >= signal.Channels() || idx2 >= signal.Elements() )
            throw bciexception( "Signal index out of range" );
        inInterpreter.Out() << signal( idx1, idx2 );
    }
    return true;
}