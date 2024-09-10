void GObject::sendToBack() {
   GCompound *parent = getParent();
   if (parent != NULL) parent->sendToBack(this);
}