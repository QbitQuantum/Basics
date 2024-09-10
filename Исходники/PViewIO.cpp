bool PView::readMSH(const std::string &fileName, int fileIndex)
{
  FILE *fp = Fopen(fileName.c_str(), "rb");
  if(!fp){
    Msg::Error("Unable to open file '%s'", fileName.c_str());
    return false;
  }

  GModel *model = GModel::current();
  if(model->empty()){
    Msg::Error("Model is empty: please load a mesh before loading the dataset");
    fclose(fp);
    return false;
  }

  char str[256] = "XXX";
  int index = -1;
  bool binary = false, swap = false;

  while(1) {

    while(str[0] != '$'){
      if(!fgets(str, sizeof(str), fp) || feof(fp))
        break;
    }

    if(feof(fp))
      break;

    if(!strncmp(&str[1], "MeshFormat", 10)) {
      double version;
      if(!fgets(str, sizeof(str), fp)){ fclose(fp); return false; }
      int format, size;
      if(sscanf(str, "%lf %d %d", &version, &format, &size) != 3){
        fclose(fp);
        return false;
      }
      if(format){
        binary = true;
        Msg::Info("View data is in binary format");
        int one;
        if(fread(&one, sizeof(int), 1, fp) != 1){ fclose(fp); return 0; }
        if(one != 1){
          swap = true;
          Msg::Info("Swapping bytes from binary file");
        }
      }
    }
    else if(!strncmp(&str[1], "InterpolationScheme", 19)){
      std::string name;
      if(!fgets(str, sizeof(str), fp)){ fclose(fp); return false; }
      name = ExtractDoubleQuotedString(str, sizeof(str));
      Msg::Info("Reading interpolation scheme '%s'", name.c_str());
      PViewData::removeInterpolationScheme(name);
      int numTypes;
      if(fscanf(fp, "%d", &numTypes) != 1){ fclose(fp); return false; }
      for(int i = 0; i < numTypes; i++){
        int type, numMatrices;
        if(fscanf(fp, "%d %d", &type, &numMatrices) != 2){ fclose(fp); return false; }
        for(int j = 0; j < numMatrices; j++){
          int m, n;
          if(fscanf(fp, "%d %d", &m, &n) != 2){ fclose(fp); return false; }
          fullMatrix<double> mat(m, n);
          for(int k = 0; k < m; k++){
            for(int l = 0; l < n; l++){
              double d;
              if(fscanf(fp, "%lf", &d) != 1){ fclose(fp); return false; }
              mat.set(k, l, d);
            }
          }
          PViewData::addMatrixToInterpolationScheme(name, type, mat);
        }
      }
    }
    else if(!strncmp(&str[1], "NodeData", 8) ||
            !strncmp(&str[1], "ElementData", 11) ||
            !strncmp(&str[1], "ElementNodeData", 15)) {
      index++;
      if(fileIndex < 0 || fileIndex == index){
        PViewDataGModel::DataType type;
        if(!strncmp(&str[1], "NodeData", 8))
          type = PViewDataGModel::NodeData;
        else if(!strncmp(&str[1], "ElementData", 11))
          type = PViewDataGModel::ElementData;
        else
          type = PViewDataGModel::ElementNodeData;
        int numTags;
        // string tags
        std::string viewName, interpolationScheme;
        if(!fgets(str, sizeof(str), fp)){ fclose(fp); return false; }
        if(sscanf(str, "%d", &numTags) != 1){ fclose(fp); return false; }
        for(int i = 0; i < numTags; i++){
          if(!fgets(str, sizeof(str), fp)){ fclose(fp); return false; }
          if(i == 0)
            viewName = ExtractDoubleQuotedString(str, sizeof(str));
          else if(i == 1)
            interpolationScheme = ExtractDoubleQuotedString(str, sizeof(str));
        }
        // double tags
        double time = 0.;
        if(!fgets(str, sizeof(str), fp)){ fclose(fp); return false; }
        if(sscanf(str, "%d", &numTags) != 1){ fclose(fp); return false; }
        for(int i = 0; i < numTags; i++){
          if(!fgets(str, sizeof(str), fp)){ fclose(fp); return false; }
          if(i == 0){
            if(sscanf(str, "%lf", &time) != 1){ fclose(fp); return false; }
          }
        }
        // integer tags
        int timeStep = 0, numComp = 0, numEnt = 0, partition = 0;
        if(!fgets(str, sizeof(str), fp)){ fclose(fp); return false; }
        if(sscanf(str, "%d", &numTags) != 1){ fclose(fp); return false; }
        for(int i = 0; i < numTags; i++){
          if(!fgets(str, sizeof(str), fp)){ fclose(fp); return false; }
          if(i == 0){
            if(sscanf(str, "%d", &timeStep) != 1){ fclose(fp); return false; }
          }
          else if(i == 1){
            if(sscanf(str, "%d", &numComp) != 1){ fclose(fp); return false; }
          }
          else if(i == 2){
            if(sscanf(str, "%d", &numEnt) != 1){ fclose(fp); return false; }
          }
          else if(i == 3){
            if(sscanf(str, "%d", &partition) != 1){ fclose(fp); return false; }
          }
        }
        // either get existing viewData, or create new one
        PView *p = getViewByName(viewName, timeStep, partition);
        PViewDataGModel *d = 0;
        if(p) d = dynamic_cast<PViewDataGModel*>(p->getData());
        bool create = d ? false : true;
        if(create) d = new PViewDataGModel(type);
        if(!d->readMSH(viewName, fileName, fileIndex, fp, binary, swap, timeStep,
                       time, partition, numComp, numEnt, interpolationScheme)){
          Msg::Error("Could not read data in msh file");
          if(create) delete d;
          fclose(fp);
          return false;
        }
        else{
          d->setName(viewName);
          d->setFileName(fileName);
          d->setFileIndex(index);
          if(create) new PView(d);
        }
      }
    }

    do {
      if(!fgets(str, sizeof(str), fp) || feof(fp))
        break;
    } while(str[0] != '$');
  }

  fclose(fp);
  return true;
}