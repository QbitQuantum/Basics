//-*****************************************************************************
MStatus AbcExportSelected( const Parameters &iConfig )
{
    // Abc::Init();
    
    //-*************************************************************************
    // CREATE SELECTION LIST
    //-*************************************************************************
    MSelectionList slist;
    MGlobal::getActiveSelectionList( slist );
    if ( slist.length() == 0 )
    {
        MGlobal::displayError( "Nothing selected." );
        return MS::kFailure;
    }

    //-*************************************************************************
    // CREATE THE ARCHIVE
    //-*************************************************************************
    if ( iConfig.fileName == "UNSPECIFIED_FILE_NAME.abc" ||
         iConfig.fileName == "" )
    {
        MGlobal::displayError( "No filename specified." );
        return MStatus::kFailure;
    }
        
    // Create the time sampling.
    Abc::TimeSamplingType tSmpType;
    if ( iConfig.endFrame > iConfig.startFrame )
    {
        tSmpType = Abc::TimeSamplingType(
                
            // Increment, in seconds, between samples.
            ( Abc::chrono_t )
            MTime( 1.0, MTime::uiUnit() ).as( MTime::kSeconds ) );
    }

    // Get FPS
    Abc::chrono_t fps =
        MTime( 1.0, MTime::kSeconds ).as( MTime::uiUnit() );
        
    Top top( iConfig.fileName, tSmpType, fps );
        
    std::cout << "AlembicSimpleAbcExport: Opened Alembic Archive: "
              << top.getName()
              << " for writing." << std::endl;
        
    // Build comments
    std::string comments = "AlembicSimpleAbcExport v0.1.1";
    comments += "\n";
    MString exportedFromStr =
        "(Exported from " + MFileIO::currentFile() + ")";
    comments += exportedFromStr.asChar();
    comments += "\n";
    // top.setComments( comments );


    //-*********************************************************************
    // BUILD TREE OF NODE:OBJECT PAIRS TO EXPORT
    //-*********************************************************************
    
    // Create the factory
    Factory factory( iConfig );
    
    for ( MItSelectionList liter( slist ); !liter.isDone(); liter.next() )
    {
        MDagPath dagPath;
        MObject component;
        liter.getDagPath( dagPath, component );
            
        // This will skip nodes we've already visited. HAVE NO
        // FEAR.
        factory.makeTree( top, dagPath, 1000000, tSmpType );
    }
    std::cout << "AlembicSimpleAbcExport: Created DAG Tree to export."
              << std::endl;

    //-*********************************************************************
    // EXPORT SAMPLES PER FRAME
    //-*********************************************************************
    
    // Loop over time
    MComputation computation;
    computation.beginComputation();
    for ( int frame = iConfig.startFrame;
          frame <= iConfig.endFrame; ++frame )
    {   
        // Get a time.
        MTime thisTime( ( double )frame, MTime::uiUnit() );
            
        // Set the time.
        MAnimControl::setCurrentTime( thisTime );
            
        // Get the chrono and the index
        Abc::index_t frameIndex =
            ( Abc::index_t )( frame - iConfig.startFrame );
        Abc::chrono_t frameTime =
            ( Abc::chrono_t )thisTime.as( MTime::kSeconds );
        
        // Is this necessary to force an eval?  Sometimes?
        // MGlobal::viewFrame( t );
        // M3dView currentView = M3dView::active3dView();
        // currentView.refresh( true, true, true );
            
        // Write the frame.
        top.writeSample( Abc::OSampleSelector( frameIndex, frameTime ) );
        std::cout << "AlembicSimpleAbcExport: Wrote frame: "
                  << frame << std::endl;
            
        if ( computation.isInterruptRequested() )
        {
            break;
        }
    }
        
    top.close();
    computation.endComputation();
    // H5close();

    std::cout << "AlembicSimpleAbcExport: Closed Archive." << std::endl;
    return MS::kSuccess;
}