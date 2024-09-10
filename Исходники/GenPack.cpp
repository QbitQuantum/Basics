int main(int argc, char** argv) {
    using namespace Sirikata;

    InitOptions();
    Trace::Trace::InitOptions();
    OHTrace::InitOptions();
    InitSimOHOptions();
    ParseOptions(argc, argv);

    PluginManager plugins;
    plugins.loadList( GetOptionValue<String>(OPT_PLUGINS) );
    plugins.loadList( GetOptionValue<String>(OPT_OH_PLUGINS) );

    String trace_file = GetPerServerFile(STATS_OH_TRACE_FILE, 1);
    Trace::Trace* gTrace = new Trace::Trace(trace_file);

    BoundingBox3f region = GetOptionValue<BoundingBox3f>("region");
    Duration duration = GetOptionValue<Duration>("duration");

    // Get the starting time
    Time start_time = Timer::now();

    srand( GetOptionValue<uint32>("rand-seed") );

    Network::IOService* ios = Network::IOServiceFactory::makeIOService();
    Network::IOStrand* mainStrand = ios->createStrand();

    ObjectHostContext* ctx = new ObjectHostContext(ObjectHostID(1), ios, mainStrand, gTrace, start_time, duration);
    ObjectFactory* obj_factory = new ObjectFactory(ctx, region, duration);

    // Nothing actually runs here -- we only cared about getting the
    // object factory setup so it could dump the object pack data.

    gTrace->prepareShutdown();

    delete obj_factory;
    delete ctx;

    gTrace->shutdown();
    delete gTrace;
    gTrace = NULL;

    delete mainStrand;
    Network::IOServiceFactory::destroyIOService(ios);

    return 0;
}