END_TEST


START_TEST ( test_RenderExtension_gradient )
{
    RenderPkgNamespaces renderns;
    LayoutPkgNamespaces layoutns;

    SBMLDocument doc(3,1);

    doc.enablePackage(layoutns.getURI(), "layout", true);
    doc.enablePackage(renderns.getURI(), "render", true);

    Model* model = doc.createModel();

    LayoutModelPlugin *lPlugin = (LayoutModelPlugin*)model->getPlugin("layout");
    fail_unless(lPlugin != NULL);

    Layout* layout = lPlugin->createLayout();
    Dimensions dim(&layoutns, 100,100 );
    layout->setDimensions(&dim);

    GraphicalObject* additional = layout->createAdditionalGraphicalObject();
    additional->setId("go1");
    BoundingBox bb(&layoutns, "bb1", 10, 10, 90, 90);
    additional->setBoundingBox(&bb);
    RenderGraphicalObjectPlugin* goPlugin = (RenderGraphicalObjectPlugin*)additional->getPlugin("render");
    fail_unless(goPlugin != NULL);
    goPlugin->setObjectRole("myRole");


    RenderLayoutPlugin *rPlugin = (RenderLayoutPlugin*)layout->getPlugin("render");
    fail_unless(rPlugin != NULL);

    LocalRenderInformation* local = rPlugin->createLocalRenderInformation();

    ColorDefinition *black = local->createColorDefinition();
    black->setId("black");
    black->setColorValue("#000000");

    ColorDefinition *grey = local->createColorDefinition();
    grey->setId("grey");
    grey->setColorValue("#F0F0F0");

    LinearGradient* gradient = local->createLinearGradientDefinition();
    gradient->setId("test");
    gradient->setPoint1(RelAbsVector(), RelAbsVector());
    gradient->setPoint2(RelAbsVector(0,100), RelAbsVector(0,100));

    GradientStop *stop = gradient->createGradientStop();
    stop->setOffset(RelAbsVector());
    stop->setStopColor("white");

    stop = gradient->createGradientStop();
    stop->setOffset(RelAbsVector(0, 100));
    stop->setStopColor("silver");

    std::string smodel = writeSBMLToStdString(&doc);

    fail_unless( stop->getStopColor() == "silver" );
}