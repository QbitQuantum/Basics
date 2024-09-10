int GModel::readPLY2(const std::string &name)
{
  FILE *fp = Fopen(name.c_str(), "r");
  if(!fp){
    Msg::Error("Unable to open file '%s'", name.c_str());
    return 0;
  }

  std::vector<MVertex*> vertexVector;
  std::map<int, std::vector<MElement*> > elements[5];

  char buffer[256];
  int elementary = getMaxElementaryNumber(-1) + 1;
  int nbv, nbf;
  while(!feof(fp)) {
    if(!fgets(buffer, sizeof(buffer), fp)) break;
    if(buffer[0] != '#'){ // skip comments
      sscanf(buffer, "%d", &nbv);
      if(!fgets(buffer, sizeof(buffer), fp)) break;
      sscanf(buffer, "%d", &nbf);
      Msg::Info("%d vertices", nbv);
      Msg::Info("%d triangles", nbf);
      vertexVector.resize(nbv);
      for(int i = 0; i < nbv; i++) {
	if(!fgets(buffer, sizeof(buffer), fp)) break;
	double x, y, z;
	int nb = sscanf(buffer, "%lf %lf %lf", &x, &y, &z);
	if (nb !=3){
	  if(!fgets(buffer, sizeof(buffer), fp)) break;
	  sscanf(buffer, "%lf",  &y);
	  if(!fgets(buffer, sizeof(buffer), fp)) break;
	  sscanf(buffer, "%lf",  &z);
	}
	vertexVector[i] = new MVertex(x, y, z);
      }
      for(int i = 0; i < nbf; i++) {
	if(!fgets(buffer, sizeof(buffer), fp)) break;
	int n[3], nbe;
	int nb = sscanf(buffer, "%d %d %d %d", &nbe, &n[0], &n[1], &n[2]);
	if (nb !=4){
	  if(!fgets(buffer, sizeof(buffer), fp)) break;
	  sscanf(buffer, "%d",  &n[0]);
	  if(!fgets(buffer, sizeof(buffer), fp)) break;
	  sscanf(buffer, "%d",  &n[1]);
	  if(!fgets(buffer, sizeof(buffer), fp)) break;
	  sscanf(buffer, "%d",  &n[2]);
	}
	std::vector<MVertex*> vertices;
	if(!getVertices(3, n, vertexVector, vertices)){ fclose(fp); return 0; }
	elements[0][elementary].push_back(new MTriangle(vertices));
      }
    }
  }

  for(int i = 0; i < (int)(sizeof(elements) / sizeof(elements[0])); i++)
    _storeElementsInEntities(elements[i]);
  _associateEntityWithMeshVertices();
  _storeVerticesInEntities(vertexVector);

  fclose(fp);
  return 1;
}