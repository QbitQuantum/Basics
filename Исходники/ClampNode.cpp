void ClampNode::createGeode(void) {
    // Remove children
    removeChildren(0, getNumChildren());
    
    // Create geode
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    addChild(geode);
    geode->addDrawable(createBrick());

    // Distance between two plot center
    double distPlot = Lego::length_unit;

    // Get the brick
    Clamp* clamp = static_cast<Clamp*>(_lego);

    // Get clamp bounding box
    clamp->calculateBoundingBox();
    BoundingBox bb = clamp->getBoundingBox();
    // Get integer sizes
    int width = bb.getWidth();
    int length = bb.getLength();
    int height = bb.getHeight();

    // Calculate x max and y max for plots
    double xminb = -(length-2)*Lego::length_unit/2;
    double yminb = -(width-1)*Lego::length_unit/2;

    double w = (-width)*Lego::length_unit/2+Lego::height_unit/2;
    double h = (height)*Lego::height_unit/2-Lego::height_unit/2;

    // Add cylinder parts

    // Create geode
    osg::ref_ptr<osg::Geode> cylinderGeode = new osg::Geode;

    // Create drawable cylinder
    osg::Drawable* cylinderPart = makeCylinder(0, w, h, length*Lego::length_unit, Lego::height_unit/2);
    // Add drawable to geode
    cylinderGeode->addDrawable(cylinderPart);

    // Create top and bottom cylinder
    osg::Drawable* topPart = makeDisk(0, w, h, Lego::height_unit/2, length*Lego::length_unit, true);
    osg::Drawable* bottomPart = makeDisk(0, w, h, Lego::height_unit/2, length*Lego::length_unit, false);
    // Add drawables to geode
    cylinderGeode->addDrawable(topPart);
    cylinderGeode->addDrawable(bottomPart);

    // Create matrix transform to rotate cylinder
    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
    // Create matrix to handle rotation
    osg::Matrix matRot, matTrans;
    // Make PI/2 rotation according to y axis
    matRot.makeRotate(M_PI_2, osg::Vec3(0.f, 1.f, 0.f));
    // Translate
    matTrans.makeTranslate(-length*Lego::length_unit/4-Lego::height_unit/4, 0, 3*height*Lego::height_unit/8);
    // Set matrix transform matrix
    mt->setMatrix(matRot*matTrans);
    // Add geode to matrix transform
    mt->addChild(cylinderGeode.get());
    // Add matrix transform
    addChild(mt);

    // Add bottom cylinders iteratively
    for (int i = 0; i < length-1; i++) {
        for (int j = 0; j < width; j++) {
            double radiusX = xminb + i*distPlot;
            double radiusY = yminb + j*distPlot;

            addChild(createBottomCylinder(radiusX, radiusY, 0.5, true, (-height+0.5)*Lego::height_unit/2));
        }
    }
}