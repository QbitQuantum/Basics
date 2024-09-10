void* edge_event(void* args) {
    ImageDB *imgdb = (ImageDB*)args;
    ImageList *current = imgdb->imglists[imgdb->current_id];

#if ShowEdgeResult
    boost::shared_ptr<pcl::visualization::PCLVisualizer> edge_viewer (new pcl::visualization::PCLVisualizer ("EdgeViewer"));
    edge_viewer->setBackgroundColor (0, 0, 0);
    edge_viewer->addPointCloud (current->cloud, "base cloud");
    drawEdge(current->edge, current->cloud, 1, edge_viewer);
    while (!edge_viewer->wasStopped()) {
        edge_viewer->spinOnce(100);
    }
#else
    drawEdge(current->edge, current->cloud, 1);
#endif

    printf("finished egde detect %d\n", current->id);

    if (imgdb->local_viewer) {
        char final_edge_name[20];
        sprintf(final_edge_name, "cloud_%d", current->id);

        imgdb->local_viewer->removeAllShapes();
        imgdb->local_viewer->removeAllPointClouds();
        imgdb->local_viewer->addPointCloud(current->cloud, final_edge_name);
        //imgdb->local_viewer->spinOnce(100);
        
        for (int i = 0; i < current->edge.size(); i++) {
            vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New ();
            vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New ();
            vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New ();
            for (int j = 0; j < current->edge[i].size()-1; j++) {
                points->InsertNextPoint(current->edge[i][j].data);
                points->InsertNextPoint(current->edge[i][j+1].data);
            }
            points->InsertNextPoint(current->edge[i][current->edge[i].size()-1].data);
            points->InsertNextPoint(current->edge[i][0].data);

            vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New ();
            // Add the points to the dataset
            polyData->SetPoints (points);
            polyLine->GetPointIds  ()->SetNumberOfIds(points->GetNumberOfPoints ());
            for(unsigned int j= 0; j < points->GetNumberOfPoints (); j++)
                polyLine->GetPointIds ()->SetId (j,j);
            cells->InsertNextCell (polyLine);
            // Add the lines to the dataset
            polyData->SetLines (cells);
            sprintf(final_edge_name, "final_edge_%d", i);
            imgdb->local_viewer->addModelFromPolyData (polyData, final_edge_name);
        }
        //while (!imgdb->local_viewer->wasStopped()) 
imgdb->local_viewer->spinOnce(100);
        //imgdb->local_viewer->resetStoppedFlag();
        printf("+========  %d ========\n===============\n", current->id);
    }


    imgdb->edge_thread_in_use = false;
    if (!imgdb->qby_thread_in_use) imgdb->edge_thread_item = current;

    return NULL;
}