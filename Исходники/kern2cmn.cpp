void checkOptions(Options& opts, int argc, char* argv[]) {
    opts.define("debug=b",           "trace input parsing");
    opts.define("author=b",          "author of the program");
    opts.define("version=b",         "compilation information");
    opts.define("example=b",         "example usage");
    opts.define("h|help=b",          "short description");
    opts.process(argc, argv);

    // handle basic options:
    if (opts.getBoolean("author")) {
        cout << "Written by Craig Stuart Sapp, "
             << "[email protected], April 2001" << endl;
        exit(0);
    } else if (opts.getBoolean("version")) {
        cout << argv[0] << ", version: 28 April 2001" << endl;
        cout << "compiled: " << __DATE__ << endl;
        cout << MUSEINFO_VERSION << endl;
        exit(0);
    } else if (opts.getBoolean("help")) {
        usage(opts.getCommand());
        exit(0);
    } else if (opts.getBoolean("example")) {
        example();
        exit(0);
    }
}