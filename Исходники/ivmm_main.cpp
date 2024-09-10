int main(int argc, char *argv[]) { string configFile;
    fs::path outputDirs;
    po::options_description desc("ivmm main");
    desc.add_options()
        ("config,c", po::value<string>(&configFile)->default_value(string("default.ini")), "load ivmm config file")
        ("output,o", po::value(&outputDirs), "output dir")
        ("help,h", "show help");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if ( vm.find("help") != vm.end()){
        cout << desc << endl;
        return 0;
    }

    if ( vm.count("output") == 0)
    {
        cerr << "need output dir " << endl;
        cerr << desc << endl;
        return 1;
    }


    pt::ptree ptree;
    if (fs::exists(configFile) ){
        try{
            fs::ifstream ins(configFile);
            pt::read_ini(ins, ptree);
        }catch ( pt::ini_parser_error const& err){
            fmt::print(cerr, "while read config {}", err.what());
            return 1;
        }
    }else{
        try{
            generator_default_ini(configFile.c_str());
            fmt::print("{} not exists generator a default one\n", configFile);
        }catch ( pt::ini_parser_error const& err){
            fmt::print(cerr, "while generator a default config {} \n", err.what());
            return 1;
        }
        return 0;
    }

    string road = ptree.get<string>("Network.road", "road");
    Network network;

    boost::timer timer;
    if ( not network.load(road) ){
        fmt::print("load network from {} fail!\n", road);
        return 1;
    }

    fmt::print("load network within {}s.\n", timer.elapsed());

    if (not fs::exists(outputDirs) ){
        boost::system::error_code err;
        fs::create_directories(outputDirs, err);
        if ( err){
            fmt::print("can not create {}\n {}\n", outputDirs, err.message());
            return 1;
        }
    }
    IVMMParamEX param = load_ivmm_param_ex(ptree);
    IVMM ivmm(&network);

    string line;
    list<string> inputLines;
    while( getline(cin, line))
        inputLines.push_back(std::move(line));

    size_t allLines = inputLines.size();
    while( not inputLines.empty() ){
        line = std::move( inputLines.front() );
        inputLines.pop_front();
        fs::path path(line);
        if (not fs::exists(path) ){
            continue;
        }
        fmt::print("input:{},", path);
        vector<GpsPoint> gps = loadGps( path );
        if ( gps.size() < 10)
        {
            cout << "too few records" <<endl;
            continue;
        }

        fmt::print(" with {} records ", gps.size());
        cout .flush();
        boost::timer timer;
        CandidateGraph g;
        Path matched_path = ivmm.ivmm_ex(gps, param);
        //Path matched_path = ivmm.ivmm(gps,  param);
        if ( matched_path.empty() or matched_path.infinity() )
        {
            fmt::print(" ignored path is :{} ", matched_path.empty()?"empty":"infinity");
        } else
        {
            string filename = path.filename().stem().string();
            string id = boost::copy_range<string>(boost::find_if<boost::return_begin_found>(filename, boost::is_any_of("-")));
            fs::path dir = outputDirs/id;
            if ( not fs::exists(dir))
            {
                try
                {
                    fs::create_directories(dir);
                }catch(fs::filesystem_error const& e)
                {
                    cerr << e.what() << endl;
                    continue;
                }
            }
            //cdbid, rdbid, timestamp, x,y, where, dist of path
            string crossDBID;
            long timestamp;
            char timeStr[20];
            //savePath(matched_path,(outputDirs/id/filename).c_str());
            //savePoints(matched_path, (outputDirs/id/(filename+"-points")).c_str());
            matched_path.estimate_time_at_cross();
            //saveEndpoint(network, matched_path, (outputDirs/id/(filename+"-endpoints")).c_str());
            fs::ofstream os(dir/path.filename());
            for (PathEndpointWalker<Path const> walker(matched_path);not walker.isEnd(); ++walker)
            {
                int cid;
                if ( walker.isFirst())
                {
                    if (walker.second->cid == -1) continue;
                    cid = walker.second->cid;
                    timestamp = walker.second->timestamp;
                } else if ( walker.isLast() )
                {
                    if ( walker.first->cid == -1) continue;
                    cid = walker.first->cid;
                    timestamp = walker.first->timestamp;
                }else
                {
                    cid = walker.first->cid;
                    assert(cid == walker.second->cid);
                    timestamp = walker.first->timestamp;
                    assert(timestamp == walker.second->timestamp);
                }
                crossDBID = network.cross(cid).dbId;
                tm t = *localtime(&timestamp);
                strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &t);
                os << crossDBID << ","<<timeStr<<","<<timestamp<<"\n";
            }
            /*
            for ( PathPoint const& p : matched_path.points){
                crossDBID = p.cid == -1 ? "           ":network.cross(p.cid).dbId;
                }
                x = p.x;
                y = p.y;
                paramOfRoad = p.where;
                distOfPath = p.dist_of_path;
                fmt::print( os, "{},{},{},{},{:.6f},{:.6f},{:.4f},{:.3f}\n",crossDBID, roadDBID, timestamp,timeStr, x, y, paramOfRoad, distOfPath);
            }*/
        }
        fmt::print(" cost {}s {:.2f}%\n", timer.elapsed(), (double(allLines - inputLines.size()) / allLines )*100);

    }
    return 0;
}