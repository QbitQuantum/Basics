void elasticitySolver::readInputFile(const std::string &fn)
{
  FILE *f = Fopen(fn.c_str(), "r");
  if(!f) {
    Msg::Error("Could not open file '%s'", fn.c_str());
    return;
  }
  char what[256];
  while(!feof(f)) {
    if(fscanf(f, "%s", what) != 1) {
      fclose(f);
      return;
    }
    if(what[0] == '#') {
      char buffer[1024];
      if(fgets(buffer, sizeof(buffer), f) == NULL)
        Msg::Error("Cannot read line.");
    }
    else if(!strcmp(what, "ElasticDomain")) {
      elasticField field;
      int physical;
      if(fscanf(f, "%d %lf %lf", &physical, &field._e, &field._nu) != 3) {
        fclose(f);
        return;
      }
      field._tag = _tag;
      field.g = new groupOfElements(_dim, physical);
      elasticFields.push_back(field);
    }
    else if(!strcmp(what, "LagrangeMultipliers")) {
      LagrangeMultiplierField field;
      int physical;
      double d1, d2, d3, val;
      if(fscanf(f, "%d %lf %lf %lf %lf %lf %d", &physical, &field._tau, &d1,
                &d2, &d3, &val, &field._tag) != 7) {
        fclose(f);
        return;
      }
      SVector3 sv(d1, d2, d3);
      field._d = sv.unit();
      field._f = new simpleFunction<double>(val);
      field.g = new groupOfElements(_dim - 1, physical);
      LagrangeMultiplierFields.push_back(field);
      LagrangeMultiplierSpaces.push_back(
        new ScalarLagrangeFunctionSpaceOfElement(field._tag));
    }
    else if(!strcmp(what, "Void")) {
      elasticField field;
      int physical;
      if(fscanf(f, "%d", &physical) != 1) {
        fclose(f);
        return;
      }
      field._e = field._nu = 0;
      field.g = new groupOfElements(_dim, physical);
      field._tag = 0;
      elasticFields.push_back(field);
    }
    else if(!strcmp(what, "NodeDisplacement")) {
      double val;
      int node, comp;
      if(fscanf(f, "%d %d %lf", &node, &comp, &val) != 3) {
        fclose(f);
        return;
      }
      dirichletBC diri;
      diri.g = new groupOfElements(0, node);
      diri._f = new simpleFunction<double>(val);
      diri._comp = comp;
      diri._tag = node;
      diri.onWhat = BoundaryCondition::ON_VERTEX;
      allDirichlet.push_back(diri);
    }
    else if(!strcmp(what, "EdgeDisplacement")) {
      double val;
      int edge, comp;
      if(fscanf(f, "%d %d %lf", &edge, &comp, &val) != 3) {
        fclose(f);
        return;
      }
      dirichletBC diri;
      diri.g = new groupOfElements(1, edge);
      diri._f = new simpleFunction<double>(val);
      diri._comp = comp;
      diri._tag = edge;
      diri.onWhat = BoundaryCondition::ON_EDGE;
      allDirichlet.push_back(diri);
    }
    else if(!strcmp(what, "FaceDisplacement")) {
      double val;
      int face, comp;
      if(fscanf(f, "%d %d %lf", &face, &comp, &val) != 3) {
        fclose(f);
        return;
      }
      dirichletBC diri;
      diri.g = new groupOfElements(2, face);
      diri._f = new simpleFunction<double>(val);
      diri._comp = comp;
      diri._tag = face;
      diri.onWhat = BoundaryCondition::ON_FACE;
      allDirichlet.push_back(diri);
    }
    else if(!strcmp(what, "NodeForce")) {
      double val1, val2, val3;
      int node;
      if(fscanf(f, "%d %lf %lf %lf", &node, &val1, &val2, &val3) != 4) {
        fclose(f);
        return;
      }
      neumannBC neu;
      neu.g = new groupOfElements(0, node);
      neu._f = new simpleFunction<SVector3>(SVector3(val1, val2, val3));
      neu._tag = node;
      neu.onWhat = BoundaryCondition::ON_VERTEX;
      allNeumann.push_back(neu);
    }
    else if(!strcmp(what, "EdgeForce")) {
      double val1, val2, val3;
      int edge;
      if(fscanf(f, "%d %lf %lf %lf", &edge, &val1, &val2, &val3) != 4) {
        fclose(f);
        return;
      }
      neumannBC neu;
      neu.g = new groupOfElements(1, edge);
      neu._f = new simpleFunction<SVector3>(SVector3(val1, val2, val3));
      neu._tag = edge;
      neu.onWhat = BoundaryCondition::ON_EDGE;
      allNeumann.push_back(neu);
    }
    else if(!strcmp(what, "FaceForce")) {
      double val1, val2, val3;
      int face;
      if(fscanf(f, "%d %lf %lf %lf", &face, &val1, &val2, &val3) != 4) {
        fclose(f);
        return;
      }
      neumannBC neu;
      neu.g = new groupOfElements(2, face);
      neu._f = new simpleFunction<SVector3>(SVector3(val1, val2, val3));
      neu._tag = face;
      neu.onWhat = BoundaryCondition::ON_FACE;
      allNeumann.push_back(neu);
    }
    else if(!strcmp(what, "VolumeForce")) {
      double val1, val2, val3;
      int volume;
      if(fscanf(f, "%d %lf %lf %lf", &volume, &val1, &val2, &val3) != 4) {
        fclose(f);
        return;
      }
      neumannBC neu;
      neu.g = new groupOfElements(3, volume);
      neu._f = new simpleFunction<SVector3>(SVector3(val1, val2, val3));
      neu._tag = volume;
      neu.onWhat = BoundaryCondition::ON_VOLUME;
      allNeumann.push_back(neu);
    }
    else if(!strcmp(what, "MeshFile")) {
      char name[245];
      if(fscanf(f, "%s", name) != 1) {
        fclose(f);
        return;
      }
      setMesh(name);
    }
    else if(!strcmp(what, "CutMeshPlane")) {
      double a, b, c, d;
      if(fscanf(f, "%lf %lf %lf %lf", &a, &b, &c, &d) != 4) {
        fclose(f);
        return;
      }
      int tag = 1;
      gLevelsetPlane ls(a, b, c, d, tag);
      pModel = pModel->buildCutGModel(&ls);
      pModel->writeMSH("cutMesh.msh");
    }
    else if(!strcmp(what, "CutMeshSphere")) {
      double x, y, z, r;
      if(fscanf(f, "%lf %lf %lf %lf", &x, &y, &z, &r) != 4) {
        fclose(f);
        return;
      }
      int tag = 1;
      gLevelsetSphere ls(x, y, z, r, tag);
      pModel = pModel->buildCutGModel(&ls);
      pModel->writeMSH("cutMesh.msh");
    }
    else if(!strcmp(what, "CutMeshMathExpr")) {
      char expr[256];
      if(fscanf(f, "%s", expr) != 1) {
        fclose(f);
        return;
      }
      std::string exprS(expr);
      int tag = 1;
      gLevelsetMathEval ls(exprS, tag);
      pModel = pModel->buildCutGModel(&ls);
      pModel->writeMSH("cutMesh.msh");
    }
    else {
      Msg::Error("Invalid input : '%s'", what);
    }
  }
  fclose(f);
}