void setGraphicsObject(RLMachine& machine, RLOperation* op, int obj,
                       GraphicsObject& gobj) {
  GraphicsSystem& graphics = machine.system().graphics();

  int fgbg;
  if (!op->getProperty(P_FGBG, fgbg))
    fgbg = OBJ_FG;

  int parentobj;
  if (op->getProperty(P_PARENTOBJ, parentobj)) {
    GraphicsObject& parent = graphics.getObject(fgbg, parentobj);
    ensureIsParentObject(parent, graphics.objectLayerSize());
    static_cast<ParentGraphicsObjectData&>(parent.objectData()).
        setObject(obj, gobj);
  } else {
    graphics.setObject(fgbg, obj, gobj);
  }
}