 CPUElevationProducerResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc, const TiXmlElement *e = NULL) :
     ResourceTemplate<3, CPUElevationProducer>(manager, name, desc)
 {
     e = e == NULL ? desc->descriptor : e;
     ptr<TileCache> cache;
     ptr<TileProducer> residuals;
     checkParameters(desc, e, "name,cache,residuals,");
     cache = manager->loadResource(getParameter(desc, e, "cache")).cast<TileCache>();
     residuals = manager->loadResource(getParameter(desc, e, "residuals")).cast<TileProducer>();
     init(cache, residuals);
 }