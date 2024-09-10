int Execute( int argc , char* argv[] )
{
    Reset< Real >();
    int i;
    int paramNum = sizeof(params)/sizeof(cmdLineReadable*);
    int commentNum=0;
    char **comments;

    comments = new char*[paramNum+7];
    for( i=0 ; i<paramNum+7 ; i++ ) comments[i] = new char[1024];

    if( Verbose.set ) echoStdout=1;

    XForm4x4< Real > xForm , iXForm;
    if( XForm.set )
    {
        FILE* fp = fopen( XForm.value , "r" );
        if( !fp )
        {
            fprintf( stderr , "[WARNING] Could not read x-form from: %s\n" , XForm.value );
            xForm = XForm4x4< Real >::Identity();
        }
        else
        {
            for( int i=0 ; i<4 ; i++ ) for( int j=0 ; j<4 ; j++ )
            {
                float f;
                fscanf( fp , " %f " , &f );
                xForm(i,j) = (Real)f;
            }
            fclose( fp );
        }
    }
    else xForm = XForm4x4< Real >::Identity();
    iXForm = xForm.inverse();

    DumpOutput2( comments[commentNum++] , "Running Screened Poisson Reconstruction (Version 6.13)\n" );
    char str[1024];
    for( int i=0 ; i<paramNum ; i++ )
        if( params[i]->set )
        {
            params[i]->writeValue( str );
            if( strlen( str ) ) DumpOutput2( comments[commentNum++] , "\t--%s %s\n" , params[i]->name , str );
            else                DumpOutput2( comments[commentNum++] , "\t--%s\n" , params[i]->name );
        }

    double t;
    double tt=PTime();
    Real isoValue = 0;

    Octree< Real > tree;
    tree.threads = Threads.value;
    if( !In.set )
    {
        ShowUsage(argv[0]);
        return 0;
    }
    if( !MaxSolveDepth.set ) MaxSolveDepth.value = Depth.value;

    OctNode< TreeNodeData >::SetAllocator( MEMORY_ALLOCATOR_BLOCK_SIZE );

    t=PTime();
    int kernelDepth = KernelDepth.set ?  KernelDepth.value : Depth.value-2;
    if( kernelDepth>Depth.value )
    {
        fprintf( stderr,"[ERROR] %s can't be greater than %s: %d <= %d\n" , KernelDepth.name , Depth.name , KernelDepth.value , Depth.value );
        return EXIT_FAILURE;
    }

    double maxMemoryUsage;
    t=PTime() , tree.maxMemoryUsage=0;
    typename Octree< Real >::PointInfo* pointInfo = new typename Octree< Real >::PointInfo();
    typename Octree< Real >::NormalInfo* normalInfo = new typename Octree< Real >::NormalInfo();
    std::vector< Real >* kernelDensityWeights = new std::vector< Real >();
    std::vector< Real >* centerWeights = new std::vector< Real >();
    PointStream< float >* pointStream;
    char* ext = GetFileExtension( In.value );
    if     ( !strcasecmp( ext , "bnpts" ) ) pointStream = new BinaryPointStream< float >( In.value );
    else if( !strcasecmp( ext , "ply"   ) ) pointStream = new    PLYPointStream< float >( In.value );
    else                                    pointStream = new  ASCIIPointStream< float >( In.value );
    delete[] ext;
    int pointCount = tree.template SetTree< float >( pointStream , MinDepth.value , Depth.value , FullDepth.value , kernelDepth , Real(SamplesPerNode.value) , Scale.value , Confidence.set , NormalWeights.set , PointWeight.value , AdaptiveExponent.value , *pointInfo , *normalInfo , *kernelDensityWeights , *centerWeights , BoundaryType.value , xForm , Complete.set );
    if( !Density.set ) delete kernelDensityWeights , kernelDensityWeights = NULL;

    DumpOutput2( comments[commentNum++] , "#             Tree set in: %9.1f (s), %9.1f (MB)\n" , PTime()-t , tree.maxMemoryUsage );
    DumpOutput( "Input Points: %d\n" , pointCount );
    DumpOutput( "Leaves/Nodes: %d/%d\n" , tree.tree.leaves() , tree.tree.nodes() );
    DumpOutput( "Memory Usage: %.3f MB\n" , float( MemoryInfo::Usage() )/(1<<20) );

    maxMemoryUsage = tree.maxMemoryUsage;
    t=PTime() , tree.maxMemoryUsage=0;
    Pointer( Real ) constraints = tree.SetLaplacianConstraints( *normalInfo );
    delete normalInfo;
    DumpOutput2( comments[commentNum++] , "#      Constraints set in: %9.1f (s), %9.1f (MB)\n" , PTime()-t , tree.maxMemoryUsage );
    DumpOutput( "Memory Usage: %.3f MB\n" , float( MemoryInfo::Usage())/(1<<20) );
    maxMemoryUsage = std::max< double >( maxMemoryUsage , tree.maxMemoryUsage );

    t=PTime() , tree.maxMemoryUsage=0;
    Pointer( Real ) solution = tree.SolveSystem( *pointInfo , constraints , ShowResidual.set , Iters.value , MaxSolveDepth.value , CGDepth.value , CSSolverAccuracy.value );
    delete pointInfo;
    FreePointer( constraints );
    DumpOutput2( comments[commentNum++] , "# Linear system solved in: %9.1f (s), %9.1f (MB)\n" , PTime()-t , tree.maxMemoryUsage );
    DumpOutput( "Memory Usage: %.3f MB\n" , float( MemoryInfo::Usage() )/(1<<20) );
    maxMemoryUsage = std::max< double >( maxMemoryUsage , tree.maxMemoryUsage );

    CoredFileMeshData< Vertex > mesh;

    if( Verbose.set ) tree.maxMemoryUsage=0;
    t=PTime();
    isoValue = tree.GetIsoValue( solution , *centerWeights );
    delete centerWeights;
    DumpOutput( "Got average in: %f\n" , PTime()-t );
    DumpOutput( "Iso-Value: %e\n" , isoValue );

    if( VoxelGrid.set )
    {
        double t = PTime();
        FILE* fp = fopen( VoxelGrid.value , "wb" );
        if( !fp ) fprintf( stderr , "Failed to open voxel file for writing: %s\n" , VoxelGrid.value );
        else
        {
            int res;
            Pointer( Real ) values = tree.Evaluate( solution , res , isoValue , VoxelDepth.value );
            fwrite( &res , sizeof(int) , 1 , fp );
            if( sizeof(Real)==sizeof(float) ) fwrite( values , sizeof(float) , res*res*res , fp );
            else
            {
                float *fValues = new float[res*res*res];
                for( int i=0 ; i<res*res*res ; i++ ) fValues[i] = float( values[i] );
                fwrite( fValues , sizeof(float) , res*res*res , fp );
                delete[] fValues;
            }
            fclose( fp );
            DeletePointer( values );
        }
        DumpOutput( "Got voxel grid in: %f\n" , PTime()-t );
    }

    if( Out.set )
    {
        t = PTime() , tree.maxMemoryUsage = 0;
        tree.GetMCIsoSurface( kernelDensityWeights ? GetPointer( *kernelDensityWeights ) : NullPointer< Real >() , solution , isoValue , mesh , true , !NonManifold.set , PolygonMesh.set );
        if( PolygonMesh.set ) DumpOutput2( comments[commentNum++] , "#         Got polygons in: %9.1f (s), %9.1f (MB)\n" , PTime()-t , tree.maxMemoryUsage );
        else                  DumpOutput2( comments[commentNum++] , "#        Got triangles in: %9.1f (s), %9.1f (MB)\n" , PTime()-t , tree.maxMemoryUsage );
        maxMemoryUsage = std::max< double >( maxMemoryUsage , tree.maxMemoryUsage );
        DumpOutput2( comments[commentNum++],"#             Total Solve: %9.1f (s), %9.1f (MB)\n" , PTime()-tt , maxMemoryUsage );

        if( NoComments.set )
        {
            if( ASCII.set ) PlyWritePolygons( Out.value , &mesh , PLY_ASCII         , NULL , 0 , iXForm );
            else            PlyWritePolygons( Out.value , &mesh , PLY_BINARY_NATIVE , NULL , 0 , iXForm );
        }
        else
        {
            if( ASCII.set ) PlyWritePolygons( Out.value , &mesh , PLY_ASCII         , comments , commentNum , iXForm );
            else            PlyWritePolygons( Out.value , &mesh , PLY_BINARY_NATIVE , comments , commentNum , iXForm );
        }
        DumpOutput( "Vertices / Polygons: %d / %d\n" , mesh.outOfCorePointCount()+mesh.inCorePoints.size() , mesh.polygonCount() );
    }
    FreePointer( solution );
    return 1;
}