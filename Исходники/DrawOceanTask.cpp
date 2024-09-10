 DrawOceanTaskResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc, const TiXmlElement *e = NULL) :
     ResourceTemplate<40, DrawOceanTask>(manager, name, desc)
 {
     e = e == NULL ? desc->descriptor : e;
     checkParameters(desc, e, "name,radius,zmin,brdfShader,");
     float radius;
     float zmin;
     ptr<Module> brdfShader;
     if (e->Attribute("brdfShader") != NULL) {
         brdfShader = manager->loadResource(getParameter(desc, e, "brdfShader")).cast<Module>();
     }
     getFloatParameter(desc, e, "radius", &radius);
     getFloatParameter(desc, e, "zmin", &zmin);
     init(radius, zmin, brdfShader);
 }