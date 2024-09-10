int main(int argc, char** argv)
{
    Stopwatch stopWatch;

    if (argc < 2)
    {
        cerr << "Missing argument: number of items to insert." << endl;
        return 1;
    }

    int const N = atoi(argv[1]);
    size_t* values = new size_t[N];

    srand(123456789);

    for (int i = 0; i < N; ++i)
    {
        values[i] = rand();
    }

    cerr << "Persistent map:" << endl;

    stopWatch.start();

    Map map;

    for (int i = 0; i < N; ++i)
        map = map.insert(values[i], i);

    cerr << "  Time for " << N << " insertions: "
         << stopWatch.format() << endl;

    stopWatch.start();

    double sumA = 0.0;
    for (int i = N / 2; i < N; ++i)
    {
        sumA += map.getVal(values[i], 0);
    }

    cerr << "  Time for " << N/2 << " queries:    "
         << stopWatch.format() << endl;

    stopWatch.start();

    Map copy = map;
    for (int i = 0; i < N; i += 2)
        copy = copy.remove(values[i]);

    cerr << "  Time for " << N/2 << " removals:   "
         << stopWatch.format() << endl;

    cerr << endl;


    cerr << "Boost unordered_map:" << endl;

    stopWatch.start();

    unordered_map<int, int> bmap;

    for (int i = 0; i < N; ++i)
        bmap[values[i]] = i;


    cerr << "  Time for " << N << " insertions: "
         << stopWatch.format() << endl;

    stopWatch.start();

    double sumB = 0.0;
    for (int i = N / 2; i < N; ++i)
    {
        sumB += bmap.at(values[i]);
    }

    cerr << "  Time for " << N/2 << " queries:    "
         << stopWatch.format() << endl;

    stopWatch.start();

    for (int i = 0; i < N; i += 2)
        bmap.erase(values[i]);

    cerr << "  Time for " << N/2 << " removals:   "
         << stopWatch.format() << endl;

    if (sumA != sumB)
        cerr << "Sums don't match!" << endl;

    return 0;
}