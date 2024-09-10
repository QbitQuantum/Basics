// ----------------- Main program -----------------
int
main(int argc, char** argv)
try
{
    using namespace Opm;
    if (argc <= 1) {
        usage();
        exit(1);
    } 
    const char* eclipseFilename = argv[1];
    EclipseStateConstPtr eclState; 
    ParserPtr parser(new Opm::Parser);
    Opm::ParseContext parseContext({{ ParseContext::PARSE_RANDOM_SLASH , InputError::IGNORE }, 
                              { ParseContext::PARSE_UNKNOWN_KEYWORD, InputError::IGNORE},
                              { ParseContext::PARSE_RANDOM_TEXT, InputError::IGNORE},
                              { ParseContext::UNSUPPORTED_SCHEDULE_GEO_MODIFIER, InputError::IGNORE},
                              { ParseContext::UNSUPPORTED_COMPORD_TYPE, InputError::IGNORE},
                              { ParseContext::UNSUPPORTED_INITIAL_THPRES, InputError::IGNORE},
                              { ParseContext::INTERNAL_ERROR_UNINITIALIZED_THPRES, InputError::IGNORE}
                             });
    Opm::DeckConstPtr deck(parser->parseFile(eclipseFilename, parseContext));
    eclState.reset(new EclipseState(deck, parseContext));

    GridManager gm(deck);
    const UnstructuredGrid& grid = *gm.c_grid();
    using boost::filesystem::path; 
    path fpath(eclipseFilename);
    std::string baseName;
    if (boost::to_upper_copy(path(fpath.extension()).string())== ".DATA") {
        baseName = path(fpath.stem()).string();
    } else {
        baseName = path(fpath.filename()).string();
    }

    std::string logFile = baseName + ".SATFUNCLOG";
    Opm::time::StopWatch timer;
    timer.start();
    RelpermDiagnostics diagnostic(logFile);
    diagnostic.diagnosis(eclState, deck, grid);
    timer.stop();
    double tt = timer.secsSinceStart();
    std::cout << "relperm diagnostics: " << tt << " seconds." << std::endl;
}
catch (const std::exception &e) {
    std::cerr << "Program threw an exception: " << e.what() << "\n";
    throw;
}