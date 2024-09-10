    void PoissonReconstruction::PoissonRecon(int argc , char* argv[], const MagicDGP::Point3DSet* pPC, std::vector< PlyValueVertex< float > >& vertices, std::vector< std::vector< int > >& polygons)
    {
        cmdLineString
            In( "in" ) ,
            Out( "out" ) ,
            VoxelGrid( "voxel" ) ,
            XForm( "xForm" );

        cmdLineReadable
            Performance( "performance" ) ,
            ShowResidual( "showResidual" ) ,
            NoComments( "noComments" ) ,
            PolygonMesh( "polygonMesh" ) ,
            Confidence( "confidence" ) ,
            NonManifold( "nonManifold" ) ,
            ASCII( "ascii" ) ,
            Density( "density" ) ,
            Verbose( "verbose" );

        cmdLineInt
            Depth( "depth" , 8 ) ,
            SolverDivide( "solverDivide" , 8 ) ,
            IsoDivide( "isoDivide" , 8 ) ,
            KernelDepth( "kernelDepth" ) ,
            AdaptiveExponent( "adaptiveExp" , 1 ) ,
            MinIters( "minIters" , 24 ) ,
            FixedIters( "iters" , -1 ) ,
            VoxelDepth( "voxelDepth" , -1 ) ,
            MinDepth( "minDepth" , 5 ) ,
            MaxSolveDepth( "maxSolveDepth" ) ,
            BoundaryType( "boundary" , 1 ) ,
            Threads( "threads" , omp_get_num_procs() );

        cmdLineFloat
            SamplesPerNode( "samplesPerNode" , 1.f ) ,
            Scale( "scale" , 1.1f ) ,
            SolverAccuracy( "accuracy" , float(1e-3) ) ,
            PointWeight( "pointWeight" , 4.f );

        cmdLineReadable* params[] =
        {
            &In , &Depth , &Out , &XForm ,
            &SolverDivide , &IsoDivide , &Scale , &Verbose , &SolverAccuracy , &NoComments ,
            &KernelDepth , &SamplesPerNode , &Confidence , &NonManifold , &PolygonMesh , &ASCII , &ShowResidual , &MinIters , &FixedIters , &VoxelDepth ,
            &PointWeight , &VoxelGrid , &Threads , &MinDepth , &MaxSolveDepth ,
            &AdaptiveExponent , &BoundaryType ,
            &Density
        };

        cmdLineParse( argc , argv , sizeof(params)/sizeof(cmdLineReadable*) , params , 1 );
        /*if( Density.set ) 
            return Execute< 2 , PlyValueVertex< Real > , true  >(argc , argv, pPC);
        else       
            return Execute< 2 ,      PlyVertex< Real > , false >(argc , argv, pPC);*/
        //Execute
        int i;
        int paramNum = sizeof(params)/sizeof(cmdLineReadable*);
        int commentNum=0;
        char **comments;

        comments = new char*[paramNum + 7];
        for( i=0 ; i<paramNum+7 ; i++ ) comments[i] = new char[1024];

        //if( Verbose.set ) echoStdout=1;

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
                for( int i=0 ; i<4 ; i++ ) for( int j=0 ; j<4 ; j++ ) fscanf( fp , " %f " , &xForm( i , j ) );
                fclose( fp );
            }
        }
        else xForm = XForm4x4< Real >::Identity();
        iXForm = xForm.inverse();

        //DumpOutput2( comments[commentNum++] , "Running Screened Poisson Reconstruction (Version 5.0)\n" , Degree );
        //char str[1024];
        //for( int i=0 ; i<paramNum ; i++ )
        //    if( params[i]->set )
        //    {
        //        params[i]->writeValue( str );
        //        if( strlen( str ) ) DumpOutput2( comments[commentNum++] , "\t--%s %s\n" , params[i]->name , str );
        //        else                DumpOutput2( comments[commentNum++] , "\t--%s\n" , params[i]->name );
        //    }

        double t;
        double tt=Time();
        Real isoValue = 0;

        //Octree< Degree , OutputDensity > tree;
        Octree< 2 , true > tree;
        tree.threads = Threads.value;
        //if( !In.set )
        //{
        //    ShowUsage(argv[0]);
        //    return 0;
        //}
        if( !MaxSolveDepth.set ) MaxSolveDepth.value = Depth.value;
        if( SolverDivide.value<MinDepth.value )
        {
            fprintf( stderr , "[WARNING] %s must be at least as large as %s: %d>=%d\n" , SolverDivide.name , MinDepth.name , SolverDivide.value , MinDepth.value );
            SolverDivide.value = MinDepth.value;
        }
        if( IsoDivide.value<MinDepth.value )
        {
	        fprintf( stderr , "[WARNING] %s must be at least as large as %s: %d>=%d\n" , IsoDivide.name , MinDepth.name , IsoDivide.value , IsoDivide.value );
	        IsoDivide.value = MinDepth.value;
        }
	
        OctNode< TreeNodeData< true > , Real >::SetAllocator( MEMORY_ALLOCATOR_BLOCK_SIZE );

        t=Time();
        int kernelDepth = KernelDepth.set ?  KernelDepth.value : Depth.value-2;

        tree.setBSplineData( Depth.value , BoundaryType.value );
        //if( kernelDepth>Depth.value )
        //{
        //    fprintf( stderr,"[ERROR] %s can't be greater than %s: %d <= %d\n" , KernelDepth.name , Depth.name , KernelDepth.value , Depth.value );
        //    return EXIT_FAILURE;
        //}
        //
        int pointNumber = pPC->GetPointNumber();
        std::vector<float> posList(pointNumber * 3);
        std::vector<float> norList(pointNumber * 3);
        for (int pIndex = 0; pIndex < pointNumber; pIndex++)
        {
            posList.at(3 * pIndex + 0) = pPC->GetPoint(pIndex)->GetPosition()[0];
            posList.at(3 * pIndex + 1) = pPC->GetPoint(pIndex)->GetPosition()[1];
            posList.at(3 * pIndex + 2) = pPC->GetPoint(pIndex)->GetPosition()[2];
            norList.at(3 * pIndex + 0) = pPC->GetPoint(pIndex)->GetNormal()[0];
            norList.at(3 * pIndex + 1) = pPC->GetPoint(pIndex)->GetNormal()[1];
            norList.at(3 * pIndex + 2) = pPC->GetPoint(pIndex)->GetNormal()[2];
        }
        //
        double maxMemoryUsage;
        t=Time() , tree.maxMemoryUsage=0;
        //int pointCount = tree.setTree( In.value , Depth.value , MinDepth.value , kernelDepth , Real(SamplesPerNode.value) , Scale.value , Confidence.set , PointWeight.value , AdaptiveExponent.value , xForm );
        int pointCount = tree.setTree( posList, norList, Depth.value , MinDepth.value , kernelDepth , Real(SamplesPerNode.value) , Scale.value , Confidence.set , PointWeight.value , AdaptiveExponent.value , xForm );
        tree.ClipTree();
        tree.finalize( IsoDivide.value );

        /*DumpOutput2( comments[commentNum++] , "#             Tree set in: %9.1f (s), %9.1f (MB)\n" , Time()-t , tree.maxMemoryUsage );
        DumpOutput( "Input Points: %d\n" , pointCount );
        DumpOutput( "Leaves/Nodes: %d/%d\n" , tree.tree.leaves() , tree.tree.nodes() );
        DumpOutput( "Memory Usage: %.3f MB\n" , float( MemoryInfo::Usage() )/(1<<20) );*/

        maxMemoryUsage = tree.maxMemoryUsage;
        t=Time() , tree.maxMemoryUsage=0;
        tree.SetLaplacianConstraints();
        /*DumpOutput2( comments[commentNum++] , "#      Constraints set in: %9.1f (s), %9.1f (MB)\n" , Time()-t , tree.maxMemoryUsage );
        DumpOutput( "Memory Usage: %.3f MB\n" , float( MemoryInfo::Usage())/(1<<20) );*/
        maxMemoryUsage = std::max< double >( maxMemoryUsage , tree.maxMemoryUsage );

        t=Time() , tree.maxMemoryUsage=0;
        tree.LaplacianMatrixIteration( SolverDivide.value, ShowResidual.set , MinIters.value , SolverAccuracy.value , MaxSolveDepth.value , FixedIters.value );
        /*DumpOutput2( comments[commentNum++] , "# Linear system solved in: %9.1f (s), %9.1f (MB)\n" , Time()-t , tree.maxMemoryUsage );
        DumpOutput( "Memory Usage: %.3f MB\n" , float( MemoryInfo::Usage() )/(1<<20) );*/
        maxMemoryUsage = std::max< double >( maxMemoryUsage , tree.maxMemoryUsage );

        CoredFileMeshData< PlyValueVertex< Real > > mesh;

        if( Verbose.set ) tree.maxMemoryUsage=0;
        t=Time();
        isoValue = tree.GetIsoValue();
        //DumpOutput( "Got average in: %f\n" , Time()-t );
        //DumpOutput( "Iso-Value: %e\n" , isoValue );

        if( VoxelGrid.set )
        {
            double t = Time();
            FILE* fp = fopen( VoxelGrid.value , "wb" );
            if( !fp ) fprintf( stderr , "Failed to open voxel file for writing: %s\n" , VoxelGrid.value );
            else
            {
                int res;
                Pointer( Real ) values = tree.GetSolutionGrid( res , isoValue , VoxelDepth.value );
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
            //DumpOutput( "Got voxel grid in: %f\n" , Time()-t );
        }

        if( Out.set )
        {
            t = Time() , tree.maxMemoryUsage = 0;
            tree.GetMCIsoTriangles( isoValue , IsoDivide.value , &mesh , 0 , 1 , !NonManifold.set , PolygonMesh.set );
            //if( PolygonMesh.set ) DumpOutput2( comments[commentNum++] , "#         Got polygons in: %9.1f (s), %9.1f (MB)\n" , Time()-t , tree.maxMemoryUsage );
            //else                  DumpOutput2( comments[commentNum++] , "#        Got triangles in: %9.1f (s), %9.1f (MB)\n" , Time()-t , tree.maxMemoryUsage );
            maxMemoryUsage = std::max< double >( maxMemoryUsage , tree.maxMemoryUsage );
            //DumpOutput2( comments[commentNum++],"#             Total Solve: %9.1f (s), %9.1f (MB)\n" , Time()-tt , maxMemoryUsage );

            //if( NoComments.set )
            //{
            //    if( ASCII.set ) PlyWritePolygons( Out.value , &mesh , PLY_ASCII         , NULL , 0 , iXForm );
            //    else            PlyWritePolygons( Out.value , &mesh , PLY_BINARY_NATIVE , NULL , 0 , iXForm );
            //}
            //else
            //{
            //    if( ASCII.set ) PlyWritePolygons( Out.value , &mesh , PLY_ASCII         , comments , commentNum , iXForm );
            //    else            PlyWritePolygons( Out.value , &mesh , PLY_BINARY_NATIVE , comments , commentNum , iXForm );
            //}
            vertices.clear();
            polygons.clear();
            int incorePointNum = int( mesh.inCorePoints.size() );
            int outofcorePointNum = mesh.outOfCorePointCount();
            DebugLog << "incorePointNum: " << incorePointNum << std::endl;
            DebugLog << "outofcorePointNum: " << outofcorePointNum << std::endl;
            mesh.resetIterator();
            for(int pIndex = 0 ; pIndex < incorePointNum ; pIndex++ )
            {
                PlyValueVertex< Real > vertex = iXForm * mesh.inCorePoints[pIndex];
                vertices.push_back(vertex);
                //ply_put_element(ply, (void *) &vertex);
            }
            for(int pIndex = 0; pIndex < outofcorePointNum; pIndex++ )
            {
                PlyValueVertex< Real > vertex;
                mesh.nextOutOfCorePoint( vertex );
                vertex = iXForm * ( vertex );
                vertices.push_back(vertex);
                //ply_put_element(ply, (void *) &vertex);
            }
            int polyNum = mesh.polygonCount();
            DebugLog << "polyNum: " << polyNum << std::endl;
            for (int pIndex = 0; pIndex < polyNum; pIndex++)
            {
                std::vector< CoredVertexIndex > coreIndex;
                mesh.nextPolygon(coreIndex);
                std::vector< int > pureIndex;
                for (int ii = 0; ii < coreIndex.size(); ii++)
                {
                    if (coreIndex.at(ii).inCore)
                    {
                        pureIndex.push_back(coreIndex.at(ii).idx);
                    }
                    else
                    {
                        pureIndex.push_back(coreIndex.at(ii).idx + incorePointNum);
                    }
                }
                if (coreIndex.size() != 3)
                {
                    DebugLog << "Error: coreIndex.size: " << coreIndex.size() << std::endl;
                }
                polygons.push_back(pureIndex);
            }
            //just for test
            /*DebugLog << "Export inter object" << std::endl;
            std::ofstream fout("pc_inter.obj");
            for (int pIndex = 0; pIndex < vertices.size(); pIndex++)
            {
                PlyValueVertex< float > vert = vertices.at(pIndex);
                fout << "v " << vert.point[0] << " " << vert.point[1] << " " << vert.point[2] << std::endl;
            }
            for (int pIndex = 0; pIndex < polygons.size(); pIndex++)
            {
                fout << "f " << polygons.at(pIndex).at(0) + 1 << " " << polygons.at(pIndex).at(1) + 1 << " " << polygons.at(pIndex).at(2) + 1 << std::endl;
            }
            fout.close();*/
        }
    }