void XmlWorldBuilder::parseTranslation(Room* r, TiXmlElement* e) {
  float s = 10.f, u = 0.f, kd = 0.f;
  e->QueryFloatAttribute("speed", &s);
  e->QueryFloatAttribute("start", &u);
  e->QueryFloatAttribute("dampen", &kd);
  Translation* z = new Translation(
      parseVector(e->FirstChildElement("x0")),
      parseVector(e->FirstChildElement("x1")),
      s, u, kd);
  const char* mode = e->Attribute("mode");
  if (mode != NULL) {
    std::string modeString = mode;
    if (modeString == "one-way") {
      z->setMode(Translation::ONE_WAY);
    } else if (modeString == "reset") {
      z->setMode(Translation::RESET);
    }
  }
  const char* name = e->Attribute("name");
  if (name != NULL) {
    transforms_[name] = z;
  }
  activeTransforms_.push_back(z);
  parseRoomObjects(r, e);
  activeTransforms_.pop_back();
  r->addTransform(z);
}