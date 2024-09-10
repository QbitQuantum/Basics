int runLocallyFallback( char const * reason, void * vpCompilerExe )
{
    char const * compilerExecutable = static_cast<char const *>( vpCompilerExe );
    std::cerr
        << "ERROR: " << reason << "\nRunning command locally...\n";
    return createProcess( compilerExecutable, GetCommandLineA() );
}