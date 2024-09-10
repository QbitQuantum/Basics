Group* SceneParser::parseTriangleMesh() {
  char token[MAX_PARSER_TOKEN_LENGTH];
  char filename[MAX_PARSER_TOKEN_LENGTH];
  // get the filename
  getToken(token); assert (!strcmp(token, "{"));
  getToken(token); assert (!strcmp(token, "obj_file"));
  getToken(filename); 
  getToken(token); assert (!strcmp(token, "}"));
  const char *ext = &filename[strlen(filename)-4];
  assert(!strcmp(ext,".obj"));
  // read it once, get counts
  FILE *file = fopen(filename,"r");
  assert (file != NULL);
  int vcount = 0; int fcount = 0;
  while (1) {
    int c = fgetc(file);
    if (c == EOF) { break;
    } else if (c == 'v') { 
      assert(fcount == 0); float v0,v1,v2;
      fscanf (file,"%f %f %f",&v0,&v1,&v2);
      vcount++; 
    } else if (c == 'f') {
      int f0,f1,f2;
      fscanf (file,"%d %d %d",&f0,&f1,&f2);
      fcount++; 
    } // otherwise, must be whitespace
  }
  fclose(file);
  // make arrays
  Vec3f *verts = new Vec3f[vcount];
  Group *answer = new Group(fcount);
  // read it again, save it
  file = fopen(filename,"r");
  assert (file != NULL);
  int new_vcount = 0; int new_fcount = 0;
  while (1) {
    int c = fgetc(file);
    if (c == EOF) { break;
    } else if (c == 'v') { 
      assert(new_fcount == 0); float v0,v1,v2;
      fscanf (file,"%f %f %f",&v0,&v1,&v2);
      verts[new_vcount] = Vec3f(v0,v1,v2);
      new_vcount++; 
    } else if (c == 'f') {
      assert (vcount == new_vcount);
      int f0,f1,f2;
      fscanf (file,"%d %d %d",&f0,&f1,&f2);
      // indexed starting at 1...
      assert (f0 > 0 && f0 <= vcount);
      assert (f1 > 0 && f1 <= vcount);
      assert (f2 > 0 && f2 <= vcount);
      assert (current_material != NULL);
      Triangle *t = new Triangle(verts[f0-1],verts[f1-1],verts[f2-1],current_material);
      answer->addObject(new_fcount,t);
      new_fcount++; 
    } // otherwise, must be whitespace
  }
  delete [] verts;
  assert (fcount == new_fcount);
  assert (vcount == new_vcount);
  fclose(file);
  return answer;
}