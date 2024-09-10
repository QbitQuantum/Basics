    void addView()
    {
        // the new View we want to add:
        osgViewer::View* view = new osgViewer::View();

        // a widget to hold our view:
        QWidget* viewWidget = new osgEarth::QtGui::ViewWidget(view);

        // a dialog to hold the view widget:
        QDialog* win = new QDialog(this);
        win->setModal( false );
        win->setLayout( new QHBoxLayout() );
        win->layout()->addWidget( viewWidget );
        int x = osgEarth::Random().next( 1024 );
        int y = osgEarth::Random().next( 768 );
        win->setGeometry( x, y, 640, 480 );
        win->show();

        // set up the view
        view->setCameraManipulator( new osgEarth::Util::EarthManipulator );
        view->setSceneData( _scene.get() );  
        view->getDatabasePager()->setUnrefImageDataAfterApplyPolicy(true,false);

        // add it to the composite viewer.
        _viewer.addView( view );
    }