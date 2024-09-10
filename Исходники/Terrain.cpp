Terrain::Terrain(void) {
  _width = 1024;
  _height = 1024;

  ifstream textFile("height.dat");
  if(!textFile.is_open()) {
    cerr << "Error whilst reading heightmap" << endl;
    EndGame(1);
  } else {
    for(int z = 0; z < 1024; z++) {
      getline(textFile, _line);
      if(_line.empty()) {
        break;
      }
      for(int x = 0; x < 1024; x++) {
        pos = _line.find(' ');
        if(pos == string::npos) {
          break;
        }
        string _line2(_line, 0, pos);
        stringstream strh(_line2);
        strh >> _heightData[z][x];
        _line.erase(0,pos+1);
      }
    }
    textFile.close();
  }

  glGenTextures(1, &_tex);
  glBindTexture(GL_TEXTURE_2D, _tex);
  // GL_MODULATE for correct lighting and shit, not really needed because of shaders.
  // When the texture area is small, bilinear filter the closest mipmap.
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  // When texture area is large, bilinear filter the original.
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if(glfwLoadTexture2D("terrain1.tga", GLFW_BUILD_MIPMAPS_BIT) != GL_TRUE) {
    cerr << "Error while reading the terrain texture!" << endl;
    EndGame(1);
  }

  // Calculate the normals.
  _normals = new Vec3f*[_height];
  Vec3f** normals2 = new Vec3f*[_height];
  for(int i = 0; i < _height; i++) {
    _normals[i] = new Vec3f[_width];
    normals2[i] = new Vec3f[_width];
  }

  // Rough normals.
  for(int z = 0; z < _height; z++) {
    for(int x = 0; x < _width; x++) {
      Vec3f sum(0.0, 0.0, 0.0);

      Vec3f down;
      if(z > 0) {
        down = Vec3f(0.0, GetHeight(x, z-1) - GetHeight(x, z), -1.0);
      }
      Vec3f up;
      if(z < _height-1) {
        up = Vec3f(0.0, GetHeight(x, z+1) - GetHeight(x,z), 1.0);
      }
      Vec3f left;
      if(x > 0) {
        left = Vec3f(-1.0, GetHeight(x-1, z) - GetHeight(x,z), 0.0);
      }
      Vec3f right;
      if(x < _width-1) {
        right = Vec3f(1.0, GetHeight(x+1, z) - GetHeight(x,z), 0.0);
      }

      if(x > 0 && z > 0) { 
        sum += down.Cross(left).Normalize();
      }
      if(x > 0 && z < _height-1) {
        sum += left.Cross(up).Normalize();
      }
      if(x < _width-1 && z < _height-1) {
        sum += up.Cross(right).Normalize();
      }
      if(x < _width-1 && z > 0) {
        sum += right.Cross(down).Normalize();
      }

      normals2[x][z] = sum;
    }
  }

  // Smooth notmals.
  const float FALLOUT_RATIO = 0.5f;
  for(int z = 0; z < _height; z++) {
    for(int x = 0; x < _width; x++) {
      Vec3f sum = normals2[x][z];

      if(x > 0) {
        sum += normals2[x-1][z] * FALLOUT_RATIO;
      }
      if(x < _width-1) {
        sum += normals2[x+1][z] * FALLOUT_RATIO;
      }
      if(z > 0) {
        sum += normals2[x][z-1] * FALLOUT_RATIO;
      }
      if(z < _height-1) {
        sum += normals2[x][z+1] * FALLOUT_RATIO;
      }
      if(sum.Magnitude() == 0) {
        sum = Vec3f(0.0, 1.0, 0.0);
      }
      _normals[x][z] = sum;
    }
  }

  // Delete the first array.
  for(int i = 0; i < _height; i++) {
    delete [] normals2[i];
  }
  delete [] normals2;
}