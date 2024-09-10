void TargetingSystem::drawTargetingBoxes() {
  double m[16];
  Camera::get().getMatrix(m);
  List<Object> *list = ObjectMgr::get().getList();
  if (list) {
    ListElement<Object> *le = list->getCurrent();
    list->resetList();
    glPointSize(3.0f);
    while (1) {
      Object *obj = list->currentElement();
      if (obj->getID() == currentTarget)
        drawBox(obj, (glRGBA) {0.0f,1.0f,0.0f,1.0f}, m);
      else if (!(obj->getObjectType() == "missile"
          || obj->getObjectType() == "gravitywell"
          || obj->getObjectType() == "object")) {
        if (obj->getFactionID() == parent->getFactionID())
          drawBox(obj, (glRGBA) {1.0f,1.0f,1.0f,1.0f}, m);
        else
          drawBox(obj, (glRGBA) {1.0f,0.0f,0.0f,1.0f}, m);
      }
      if (!list->nextElement())
        break;
    }

    list->setCurrent(le);
  }
}