void TS::init( const string& modulename )
{
    data_search_subdir.push_back(modulename);
#ifndef WINRT
    char* datapath_dir = getenv("OPENCV_TEST_DATA_PATH");
#else
    char* datapath_dir = OPENCV_TEST_DATA_PATH;
#endif

    if( datapath_dir )
    {
        data_path = path_join(path_join(datapath_dir, modulename), "");
    }

    cv::redirectError((cv::ErrorCallback)tsErrorCallback, this);

    if( ::testing::GTEST_FLAG(catch_exceptions) )
    {
#if defined _WIN32
#ifdef _MSC_VER
        _set_se_translator( SEHTranslator );
#endif
#else
        for( int i = 0; tsSigId[i] >= 0; i++ )
            signal( tsSigId[i], signalHandler );
#endif
    }
    else
    {
#if defined _WIN32
#ifdef _MSC_VER
        _set_se_translator( 0 );
#endif
#else
        for( int i = 0; tsSigId[i] >= 0; i++ )
            signal( tsSigId[i], SIG_DFL );
#endif
    }

    if( params.use_optimized == 0 )
        cv::setUseOptimized(false);

    rng = RNG(params.rng_seed);
}