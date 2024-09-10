int main(int argc, char **argv)
{
    progname = argv[0];
    if (argc < 5)
    {
        usage();
    }

    clock_t start = clock();
    WholeGenomeAlignment wga(argv[2], GetAlignmentBlockStorage(argv[4]));

    {
        set<string> filter;
        filter.insert(argv[2]);
        for (int i = 5; i < argc; ++i)
        {
            filter.insert(argv[i]);
        }

        BitSequenceFactory * factory = GetSequenceFactory(argv[3]);

        if (filter.size() > 1)
        {
            ReadMafFile(argv[1], wga, *factory, &filter);
        }
        else
        {
            ReadMafFile(argv[1], wga, *factory);
        }

        delete factory;
    }
    clock_t end = clock();
    cerr.precision(10);
    cerr << "Parsed MAF in " << clock_to_sec(end - start) <<
            " seconds." << endl;

    size_t reference_size = wga.getReferenceSize();

    while (1)
    {
        size_t position = rand() % reference_size;
        try
        {
            WholeGenomeAlignment::PositionMapping *mapping;
            mapping = wga.mapPositionToAll(position);
            if (mapping->begin() == mapping->end())
            {
                delete mapping;
                throw OutOfSequence();
            }
            cout << mapping->begin()->first << "\t" << position << endl;
            delete mapping;
        }
        catch (OutOfSequence &e)
        { }
    }
}