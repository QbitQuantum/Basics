//------------------------------------------------------------------------------
//
// Opens up a gnuplot session, ready to receive commands
//
void Gnuplot::init()
{
    // char * getenv ( const char * name );  get value of environment variable
    // Retrieves a C string containing the value of the environment variable
    // whose name is specified as argument.  If the requested variable is not
    // part of the environment list, the function returns a NULL pointer.
#if ( defined(unix) || defined(__unix) || defined(__unix__) ) && !defined(__APPLE__)
    if (getenv("DISPLAY") == NULL)
    {
        valid = false;
        throw GnuplotException("Can't find DISPLAY variable");
    }
#endif


    // if gnuplot not available
    if (!Gnuplot::get_program_path())
    {
        valid = false;
        throw GnuplotException("Can't find gnuplot");
    }


    //
    // open pipe
    //
    std::string tmp = Gnuplot::m_sGNUPlotPath + "/" +
        Gnuplot::m_sGNUPlotFileName;

    // FILE *popen(const char *command, const char *mode);
    // The popen() function shall execute the command specified by the string
    // command, create a pipe between the calling program and the executed
    // command, and return a pointer to a stream that can be used to either read
    // from or write to the pipe.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
    gnucmd = _popen(tmp.c_str(),"w");
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    gnucmd = popen(tmp.c_str(),"w");
#endif

    // popen() shall return a pointer to an open stream that can be used to read
    // or write to the pipe.  Otherwise, it shall return a null pointer and may
    // set errno to indicate the error.
    if (!gnucmd)
    {
        valid = false;
        throw GnuplotException("Couldn't open connection to gnuplot");
    }

    nplots = 0;
    valid = true;
    smooth = "";

    //set terminal type
    showonscreen();

    return;
}