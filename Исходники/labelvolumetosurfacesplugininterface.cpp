void LabelVolumeToSurfacesPluginInterface::Run()
{
    IbisAPI *ibisAPI = GetIbisAPI();
    Q_ASSERT(ibisAPI);
    ImageObject * image = ImageObject::SafeDownCast( ibisAPI->GetCurrentObject() );
    if( image && image->IsLabelImage() )
    {  
        // Get the range of labels
        double imageRange[2];
        image->GetImageScalarRange( imageRange );
        int minLabel = (int)floor( imageRange[ 0 ] );
        if( minLabel == 0 )
            minLabel = 1;  // Usually, label 0 is a mask in minc files
        int maxLabel = (int)floor( imageRange[ 1 ] );
        int numberOfLabels = maxLabel - minLabel + 1;

        // Compute the histogram to find out which labels really exist in the volume
        vtkImageAccumulate * histogram = vtkImageAccumulate::New();
        histogram->SetInputData( image->GetImage() );
        histogram->SetComponentExtent( 0, maxLabel, 0, 0, 0, 0 );
        histogram->SetComponentOrigin( 0, 0, 0 );
        histogram->SetComponentSpacing( 1, 1, 1 );
        histogram->Update();

        // Setup filters
        vtkDiscreteMarchingCubes * contourExtractor = vtkDiscreteMarchingCubes::New();
        contourExtractor->SetInputData( image->GetImage() );
        vtkTriangleFilter * triangleFilter = vtkTriangleFilter::New();
        triangleFilter->SetInputConnection( contourExtractor->GetOutputPort() );
        vtkStripper * stripper = vtkStripper::New();
        stripper->SetInputConnection( triangleFilter->GetOutputPort() );

        unsigned int smoothingIterations = 15;
        double passBand = 0.001;
        double featureAngle = 120.0;
        vtkWindowedSincPolyDataFilter * smoother = vtkWindowedSincPolyDataFilter::New();
        smoother->SetInputConnection( stripper->GetOutputPort() );
        smoother->SetNumberOfIterations(smoothingIterations);
        smoother->BoundarySmoothingOff();
        smoother->FeatureEdgeSmoothingOff();
        smoother->SetFeatureAngle(featureAngle);
        smoother->SetPassBand(passBand);
        smoother->NonManifoldSmoothingOn();
        smoother->NormalizeCoordinatesOn();

        IbisAPI *ibisAPI = GetIbisAPI();
        Q_ASSERT(ibisAPI);
        QProgressDialog * pd = ibisAPI->StartProgress( 100, "Extracting surfaces..." );
        QApplication::processEvents();

        for( int i = minLabel; i <= maxLabel; ++i )
        {
            // skip label if there is no voxel from this label
            double frequency = histogram->GetOutput()->GetPointData()->GetScalars()->GetTuple1(i);
            if( frequency == 0.0 )
                continue;

            contourExtractor->SetValue( 0, i );

            // Do the processing
            smoother->Update();

            // Setup a PolyDataObject with output and add it to the scene
            vtkPolyData * outCopy = vtkPolyData::New();
            outCopy->DeepCopy( smoother->GetOutput() );
            PolyDataObject * polyDataObj = PolyDataObject::New();
            QString objName = QString("Label %1").arg( i );
            polyDataObj->SetName( objName );
            polyDataObj->SetPolyData( outCopy );
            if( i < 256 )
                polyDataObj->SetColor( labelColors[i] );
            ibisAPI->AddObject( polyDataObj, image );

            // cleanup
            outCopy->Delete();
            polyDataObj->Delete();

            int progress = (int)( 100 * i / (double) numberOfLabels );
            ibisAPI->UpdateProgress( pd, progress );
            QApplication::processEvents();
        }

        ibisAPI->StopProgress( pd );

        // Cleanup
        contourExtractor->Delete();
        triangleFilter->Delete();
        stripper->Delete();
        smoother->Delete();
        histogram->Delete();
    }
    else
        QMessageBox::warning( 0, "Error!", "Current object should be a label volume" );
}