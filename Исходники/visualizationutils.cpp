    // visualizzazione doppia
   void VisualizationUtils::vis_doppia( string name1, string name2) {

        std::stringstream firstCloud;
        firstCloud<<"./../registrazione/cloud"<<name1<<".ply";
        std::stringstream secondCloud;
        secondCloud<<"./../registrazione/cloud"<<name2<<".ply";
        cout<<firstCloud.str()<<endl;
        cout<<secondCloud.str()<<endl;

        pcl::PointCloud<POINT_TYPE>::Ptr cloud1 (new pcl::PointCloud<POINT_TYPE>);
        pcl::PointCloud<POINT_TYPE>::Ptr cloud2 (new pcl::PointCloud<POINT_TYPE>);
        pcl::io::loadPLYFile(firstCloud.str().c_str(),*cloud1);
        pcl::io::loadPLYFile(secondCloud.str().c_str(),*cloud2);

        pcl::PointCloud<POINT_TYPE>::Ptr clicked_points_app(new pcl::PointCloud<POINT_TYPE>);
        pcl::PointCloud<POINT_TYPE>::Ptr clicked_points2_app(new pcl::PointCloud<POINT_TYPE>);
        // resetto le variabili globali
        clicked_points_app->clear();
        clicked_points2_app->clear();

        points_left.clear_stack();
        points_right.clear_stack();

        color_left.restart();
        color_right.restart();

        clicked_points = clicked_points2_app;
        clicked_points2 = clicked_points2_app;

        // creo la finestra
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
        global_viewer = viewer;
//        viewer->initCameraParameters();
//        viewer->setSize(1200, 650);


        // assegno la prima cloud
        viewer->createViewPort(0.0, 0.0, 0.5, 1.0, v1);
        viewer->setCameraPosition(0.0, 0.0, 0.0, 0.0, 0.0, 0.15, 0.0, 1.0, 0.0, v1);
        viewer->setBackgroundColor(0.2, 0.2, 0.2, v1); // background grigio
        viewer->addText("Prossimo colore: " + color_left.getColorName(), 10, 10, "v1_text", v1);
        pcl::visualization::PointCloudColorHandlerRGBField<POINT_TYPE> rgb(cloud1);
        viewer->addPointCloud<POINT_TYPE>(cloud1, rgb, name1, v1);
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, name1);

        // assegno la seconda cloud
        viewer->createViewPort(0.5, 0.0, 1.0, 1.0, v2);
        viewer->setBackgroundColor(0.3, 0.3, 0.3, v2);
        viewer->addText("Prossimo colore: " + color_right.getColorName(), 10, 10, "v2_text", v2);
        pcl::visualization::PointCloudColorHandlerRGBField<POINT_TYPE> rgb2(cloud2);
        // la traslo per poter identificare i suoi punti
        Eigen::Affine3f transform = Eigen::Affine3f::Identity();
        transform.translation() << 0.0, 0.0, TRANLSATION_Z_SECOND_CLOUD;
        //cout << "matrice applicata alla seconda cloud" << endl << transform.matrix() << endl;
        pcl::PointCloud<POINT_TYPE>::Ptr transformed_cloud2(new pcl::PointCloud<POINT_TYPE>);
        pcl::transformPointCloud(*cloud2, *transformed_cloud2, transform);
        viewer->addPointCloud<POINT_TYPE>(transformed_cloud2, rgb2, name2, v2);
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, name2);

        // gestione separata della telecamera
        viewer->createViewPortCamera(v2);
        viewer->setCameraPosition(0.0, 0.0, TRANLSATION_Z_SECOND_CLOUD, 0.0, 0.0, TRANLSATION_Z_SECOND_CLOUD + 0.15, 0.0, 1.0, 0.0, v2);

//        viewer->registerKeyboardCallback(keyboardEventOccurred, (void*)&viewer);
//        viewer->registerPointPickingCallback(pointPickDoubleViewEvent, (void*)&viewer);

        loop_view(viewer);

        // chiusa la view, stampo i punti catturati
        cout << "Punti selezionati:" << endl << " -> cloud sinistra:" << endl;
        //cout << endl << points_left.makeMatrix() << endl;
        points_left.print_all();
        cout << " -> cloud destra:" << endl;
        //cout << endl << points_right.makeMatrix() << endl;
        points_right.print_all();

        Eigen::MatrixXf Mx = points_left.makeMatrix();
        Eigen::MatrixXf My = points_right.makeMatrix();

        if (Mx.cols() != My.cols()) {
            cout << "Errore... Hai preso un numero diverso di punti tra destra e sinistra?" << endl;
            return ;
        }

        /*if (Mx.cols() < 3) {
            cout << "Dai, sforzati di prendere almeno 3 punti..." << endl;
            return;
        }*/

        Eigen::Matrix4f T = TransformationUtils::trovaT(Mx, My);
        ofstream outFile("/home/miky/Scrivania/trasformazione.txt");
        outFile << T;
        cout << " -> matrice di trasformazione salvata nel file trasformazione.txt" << endl;

        pcl::PointCloud<POINT_TYPE>::Ptr result(new pcl::PointCloud<POINT_TYPE>);
        pcl::transformPointCloud(*cloud1, *result, T);
        pcl::io::savePLYFileBinary("/home/miky/Scrivania/Cloud12.ply", *result);
        cout << " -> salvata la cloud traslata con nome Cloud12.ply" << endl;

        return ;
    }