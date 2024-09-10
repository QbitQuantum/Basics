//------------------------------------------------------------------------------
LoadConfiguration::LoadConfiguration(const Setting &parameters):
    InitialConfiguration(parameters)
{
    string pathConfigFile = getSetting(parameters, {"initialConfiguration",
                                                    "pathConfigFile"});

    // Reading configuration file
    Config cfg;
    try
    {
        cfg.readFile( pathConfigFile.c_str() );
    }
    catch (const FileIOException &fioex)
    {
        std::cerr << "I/O error while reading the configuration file:" << std::endl;
        std::cerr << pathConfigFile << std::endl;
        exit(EXIT_FAILURE);
    }
    catch (const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        exit(EXIT_FAILURE);
    }

    const Setting & metaConfig = cfg.getRoot();

    // Reading in path to config at t=0
    string pathFile = getSetting(metaConfig, {"particleDataPathT0"});
    this->pathFile = pathFile;
    if(!metaConfig.lookupValue("pathOfHoles", pathOfHoles))
        pathOfHoles = "";

    const Setting & latticePoints = getSetting( metaConfig, {"latticePoints"} );
    const Setting & boundaries = getSetting( metaConfig, {"boundaries"} );
    spacing = getSetting( metaConfig, {"spacing"} );
    nParticles = getSetting( metaConfig, {"nParticles"} );
    delta = getSetting( metaConfig, {"delta"} );
    dim = latticePoints.getLength();
    nXYZ.zeros();

    for(int d=0; d<dim; d++)
    {
        nXYZ[d] = latticePoints[d];
    }

    // Resetting the volume and horizon after reloading the spacing
    volumeCorreactionRadius = 0.5*spacing;

    // TODO: The height should be in the material properties, not in the force
    if(localDim == 3)
        volume = spacing*spacing*spacing;
    else if(localDim == 2)
    {
        double h = getSetting( parameters, {"peridynamicForce", "h"} );
        volume = spacing*spacing*h;
    }
    else
    {
        double h = getSetting( parameters, {"peridynamicForce", "h"} );
        volume = spacing*h*h;
    }
    // Setting the domain
    dom.empty();
    dom.push_back( VEC2(boundaries[0], boundaries[1]) );
    dom.push_back( VEC2(boundaries[2], boundaries[3]) );
    dom.push_back( VEC2(boundaries[4], boundaries[5]) );


    // Setting the default load parameters
    loadParameters["id"] = -1;
    loadParameters["x"]  = -1;
    loadParameters["y"]  = -1;
    loadParameters["z"]  = -1;
    loadParameters["x0"] = -1;
    loadParameters["y0"] = -1;
    loadParameters["z0"] = -1;
    loadParameters["vx"] = -1;
    loadParameters["vy"] = -1;
    loadParameters["vz"] = -1;
    loadParameters["micromodulus"] = -1;
    loadParameters["fractureStrength"] = -1;
    loadParameters["volume"]   = -1;
}