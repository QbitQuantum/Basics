void Image3D::TransformMeshToBinaryImage(Mesh* m, string filename, OrientationType orient, bool sub_segmentation, bool cropUpDown, CVector3* upperSlicePoint, CVector3* upperSliceNormal, CVector3* downSlicePoint, CVector3* downSliceNormal)
{
    //m->subdivision(2);
    MeshTypeB::Pointer mesh;
    MeshFilterType::Pointer meshFilter = MeshFilterType::New();
    if (cropUpDown)
    {
        mesh = MeshTypeB::New();
        vtkSmartPointer<vtkPolyData> polyData;
        try {
            polyData = m->reduceMeshUpAndDown(*upperSlicePoint, *upperSliceNormal, *downSlicePoint, *downSliceNormal);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }

        vtkSmartPointer<vtkFillHolesFilter> fillHolesFilter = vtkSmartPointer<vtkFillHolesFilter>::New();
        fillHolesFilter->SetInputData(polyData);
        fillHolesFilter->SetHoleSize(1000.0);
        fillHolesFilter->Update();

        // Make the triangle windong order consistent
        vtkSmartPointer<vtkPolyDataNormals> normals = vtkSmartPointer<vtkPolyDataNormals>::New();
        normals->SetInputData(fillHolesFilter->GetOutput());
        normals->ConsistencyOn();
        normals->SplittingOff();
        normals->Update();

        // Restore the original normals
        normals->GetOutput()->GetPointData()->SetNormals(polyData->GetPointData()->GetNormals());
        polyData = normals->GetOutput();

        //
        // Transfer the points from the vtkPolyData into the itk::Mesh
        //
        const unsigned int numberOfPoints = polyData->GetNumberOfPoints();
        vtkPoints * vtkpoints = polyData->GetPoints();
        mesh->GetPoints()->Reserve( numberOfPoints );
        for(unsigned int p =0; p < numberOfPoints; p++)
        {
            double * apoint = vtkpoints->GetPoint( p );
            mesh->SetPoint( p, MeshTypeB::PointType( apoint ));
        }

        //
        // Transfer the cells from the vtkPolyData into the itk::Mesh
        //
        vtkCellArray * triangleStrips = polyData->GetStrips();
        vtkIdType  * cellPoints;
        vtkIdType    numberOfCellPoints;

        //
        // First count the total number of triangles from all the triangle strips.
        //
        unsigned int numberOfTriangles = 0;
        triangleStrips->InitTraversal();
        while( triangleStrips->GetNextCell( numberOfCellPoints, cellPoints ) )
        {
            numberOfTriangles += numberOfCellPoints-2;
        }

        vtkCellArray * polygons = polyData->GetPolys();
        polygons->InitTraversal();
        while( polygons->GetNextCell( numberOfCellPoints, cellPoints ) )
        {
            if( numberOfCellPoints == 3 )
            {
                numberOfTriangles ++;
            }
        }

        //
        // Reserve memory in the itk::Mesh for all those triangles
        //
        mesh->GetCells()->Reserve( numberOfTriangles );

        //
        // Copy the triangles from vtkPolyData into the itk::Mesh
        //
        //
        typedef MeshTypeB::CellType   CellType;
        typedef itk::TriangleCell< CellType > TriangleCellType;
        int cellId = 0;

        // first copy the triangle strips
        triangleStrips->InitTraversal();
        while( triangleStrips->GetNextCell( numberOfCellPoints, cellPoints ) )
        {
            unsigned int numberOfTrianglesInStrip = numberOfCellPoints - 2;

            unsigned long pointIds[3];
            pointIds[0] = cellPoints[0];
            pointIds[1] = cellPoints[1];
            pointIds[2] = cellPoints[2];

            for( unsigned int t=0; t < numberOfTrianglesInStrip; t++ )
            {
                MeshTypeB::CellAutoPointer c;
                TriangleCellType * tcell = new TriangleCellType;
                tcell->SetPointIds( pointIds );
                c.TakeOwnership( tcell );
                mesh->SetCell( cellId, c );
                cellId++;
                pointIds[0] = pointIds[1];
                pointIds[1] = pointIds[2];
                pointIds[2] = cellPoints[t+3];
            }
        }

        // then copy the normal triangles
        polygons->InitTraversal();
        while( polygons->GetNextCell( numberOfCellPoints, cellPoints ) )
        {
            if( numberOfCellPoints !=3 ) // skip any non-triangle.
            {
                continue;
            }
            MeshTypeB::CellAutoPointer c;
            TriangleCellType * t = new TriangleCellType;
            t->SetPointIds( (unsigned long*)cellPoints );
            c.TakeOwnership( t );
            mesh->SetCell( cellId, c );
            cellId++;
        }

        meshFilter->SetInput(mesh);
    }
    else
    {
        mesh = MeshTypeB::New();
        vector<Vertex*> points = m->getListPoints();
        PointType pnt;
        CVector3 p, n;
        for (unsigned int i=0; i<points.size(); i++) {
            p = points[i]->getPosition();
            n = points[i]->getNormal();
            pnt[0] = p[0]; pnt[1] = p[1]; pnt[2] = p[2];
            mesh->SetPoint(i,pnt);
        }
        vector<int> triangles = m->getListTriangles();
        for (unsigned int i=0; i<triangles.size(); i+=3)
        {
            CellTypeB::CellAutoPointer triangle;
            triangle.TakeOwnership(new CellTypeB);
            triangle->SetPointId(0,triangles[i]);
            triangle->SetPointId(1,triangles[i+1]);
            triangle->SetPointId(2,triangles[i+2]);
            mesh->SetCell((int)(i+1)/3,triangle);
        }
        meshFilter->SetInput(mesh);
    }

    meshFilter->SetOrigin(imageOriginale_->GetOrigin());
    meshFilter->SetSpacing(imageOriginale_->GetSpacing());
    meshFilter->SetSize(imageOriginale_->GetLargestPossibleRegion().GetSize());
    meshFilter->SetDirection(imageOriginale_->GetDirection());
    meshFilter->SetIndex(imageOriginale_->GetLargestPossibleRegion().GetIndex());
    //meshFilter->SetTolerance(1.0);
    meshFilter->SetInsideValue(1.0);
    meshFilter->SetOutsideValue(0.0);
    try {
        meshFilter->Update();
    }
    catch( itk::ExceptionObject & e )
    {
        cout << "Exception thrown ! " << endl;
        cout << "An error ocurred during creating binary image" << endl;
        cout << "Location    = " << e.GetLocation()    << endl;
        cout << "Description = " << e.GetDescription() << endl;
    }
    
    BinaryImageType::Pointer im = meshFilter->GetOutput();
    
    if (!sub_segmentation)
    {
        imageSegmentation_ = im;
    }
    else
    {
        BinaryImageType::RegionType region = im->GetLargestPossibleRegion();
        itk::ImageRegionConstIterator<BinaryImageType> imageIterator(im,region);
        unsigned char pixel, pixel_seg;
        BinaryIndexType index;
        while(!imageIterator.IsAtEnd())
        {
            index = imageIterator.GetIndex();
            pixel = imageIterator.Get();
            
            pixel_seg = imageSegmentation_->GetPixel(index);
            im->SetPixel(index,pixel && !pixel_seg);
            ++imageIterator;
        }
    }
    
    OrientImage<BinaryImageType> orientationFilter;
    orientationFilter.setInputImage(im);
    orientationFilter.orientation(orient);
    im = orientationFilter.getOutputImage();
    
    // Write the image
    typedef itk::ImageFileWriter< BinaryImageType >     WriterType;
    WriterType::Pointer writer = WriterType::New();
    itk::NiftiImageIO::Pointer io = itk::NiftiImageIO::New();
    writer->SetImageIO(io);
    writer->SetFileName(filename);
    writer->SetInput(im);
    try {
        writer->Update();
    }
    catch( itk::ExceptionObject & e )
    {
        cout << "Exception thrown ! " << endl;
        cout << "An error ocurred during Writing" << endl;
        cout << "Location    = " << e.GetLocation()    << endl;
        cout << "Description = " << e.GetDescription() << endl;
    }
}