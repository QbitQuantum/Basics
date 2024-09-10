std::string LoadMtl (
  std::map<std::string, int>& material_map,
  std::vector<material_t>& materials,
  std::istream& inStream)
{
  material_map.clear();
  std::stringstream err;

  material_t material;

  int maxchars = 8192;  // Alloc enough size.
  std::vector<char> buf(maxchars);  // Alloc enough size.
  while (inStream.peek() != -1) {
    inStream.getline(&buf[0], maxchars);

    std::string linebuf(&buf[0]);

    // Trim newline '\r\n' or '\n'
    if (linebuf.size() > 0) {
      if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
    }
    if (linebuf.size() > 0) {
      if (linebuf[linebuf.size()-1] == '\r') linebuf.erase(linebuf.size()-1);
    }

    // Skip if empty line.
    if (linebuf.empty()) {
      continue;
    }

    // Skip leading space.
    const char* token = linebuf.c_str();
    token += strspn(token, " \t");

    assert(token);
    if (token[0] == '\0') continue; // empty line

    if (token[0] == '#') continue;  // comment line

    // new mtl
    if ((0 == strncmp(token, "newmtl", 6)) && isSpace((token[6]))) {
      // flush previous material.
      if (!material.name.empty())
      {
          material_map.insert(std::pair<std::string, int>(material.name, materials.size()));
          materials.push_back(material);
      }

      // initial temporary material
      InitMaterial(material);

      // set new mtl name
      char namebuf[4096];
      token += 7;
      sscanf(token, "%s", namebuf);
      material.name = namebuf;
      continue;
    }

    // ambient
    if (token[0] == 'K' && token[1] == 'a' && isSpace((token[2]))) {
      token += 2;
      float r, g, b;
      parseFloat3(r, g, b, token);
      material.ambient[0] = r;
      material.ambient[1] = g;
      material.ambient[2] = b;
      continue;
    }

    // diffuse
    if (token[0] == 'K' && token[1] == 'd' && isSpace((token[2]))) {
      token += 2;
      float r, g, b;
      parseFloat3(r, g, b, token);
      material.diffuse[0] = r;
      material.diffuse[1] = g;
      material.diffuse[2] = b;
      continue;
    }

    // specular
    if (token[0] == 'K' && token[1] == 's' && isSpace((token[2]))) {
      token += 2;
      float r, g, b;
      parseFloat3(r, g, b, token);
      material.specular[0] = r;
      material.specular[1] = g;
      material.specular[2] = b;
      continue;
    }

    // transmittance
    if (token[0] == 'K' && token[1] == 't' && isSpace((token[2]))) {
      token += 2;
      float r, g, b;
      parseFloat3(r, g, b, token);
      material.transmittance[0] = r;
      material.transmittance[1] = g;
      material.transmittance[2] = b;
      continue;
    }

    // ior(index of refraction)
    if (token[0] == 'N' && token[1] == 'i' && isSpace((token[2]))) {
      token += 2;
      material.ior = parseFloat(token);
      continue;
    }

    // emission
    if(token[0] == 'K' && token[1] == 'e' && isSpace(token[2])) {
      token += 2;
      float r, g, b;
      parseFloat3(r, g, b, token);
      material.emission[0] = r;
      material.emission[1] = g;
      material.emission[2] = b;
      continue;
    }

    // shininess
    if(token[0] == 'N' && token[1] == 's' && isSpace(token[2])) {
      token += 2;
      material.shininess = parseFloat(token);
      continue;
    }

    // illum model
    if (0 == strncmp(token, "illum", 5) && isSpace(token[5])) {
      token += 6;
      material.illum = parseInt(token);
      continue;
    }

    // dissolve
    if ((token[0] == 'd' && isSpace(token[1]))) {
      token += 1;
      material.dissolve = parseFloat(token);
      continue;
    }
    if (token[0] == 'T' && token[1] == 'r' && isSpace(token[2])) {
      token += 2;
      material.dissolve = parseFloat(token);
      continue;
    }

    // ambient texture
    if ((0 == strncmp(token, "map_Ka", 6)) && isSpace(token[6])) {
      token += 7;
      material.ambient_texname = token;
      continue;
    }

    // diffuse texture
    if ((0 == strncmp(token, "map_Kd", 6)) && isSpace(token[6])) {
      token += 7;
      material.diffuse_texname = token;
      continue;
    }

    // specular texture
    if ((0 == strncmp(token, "map_Ks", 6)) && isSpace(token[6])) {
      token += 7;
      material.specular_texname = token;
      continue;
    }

    // normal texture
    if ((0 == strncmp(token, "map_Ns", 6)) && isSpace(token[6])) {
      token += 7;
      material.normal_texname = token;
      continue;
    }

    // unknown parameter
    const char* _space = strchr(token, ' ');
    if(!_space) {
      _space = strchr(token, '\t');
    }
    if(_space) {
      int len = _space - token;
      std::string key(token, len);
      std::string value = _space + 1;
      material.unknown_parameter.insert(std::pair<std::string, std::string>(key, value));
    }
  }
  // flush last material.
  material_map.insert(std::pair<std::string, int>(material.name, materials.size()));
  materials.push_back(material);

  return err.str();
}