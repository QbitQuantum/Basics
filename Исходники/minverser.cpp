int main(int argc, char **argv)
{
    print_version(argv[0]);

    if(argc==1)
    {
        cerr << "Not enough arguments \nPlease try \"" << argv[0] << " -h\" or \"" << argv[0] << " --help \" \n" << endl;
        return 0;
    }

    if ((!strcmp(argv[1],"-h")) | (!strcmp(argv[1],"--help"))) getHelp(argv);

    disp_argv(argc,argv);

    // Start Chrono
    auto start_time = std::chrono::system_clock::now();

    SymMatrix HeadMat;

    HeadMat.load(argv[1]);
    HeadMat.invert(); // invert inplace
    HeadMat.save(argv[2]);

    // Stop Chrono
    auto end_time = std::chrono::system_clock::now();
    dispEllapsed(end_time-start_time);

    return 0;
}