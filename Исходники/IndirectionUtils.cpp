void moveGlobalVariableInitializer(GlobalVariable &OrigGV,
                                   ValueToValueMapTy &VMap,
                                   ValueMaterializer *Materializer,
                                   GlobalVariable *NewGV) {
  assert(OrigGV.hasInitializer() && "Nothing to move");
  if (!NewGV)
    NewGV = cast<GlobalVariable>(VMap[&OrigGV]);
  else
    assert(VMap[&OrigGV] == NewGV &&
           "Incorrect global variable mapping in VMap.");
  assert(NewGV->getParent() != OrigGV.getParent() &&
         "moveGlobalVariableInitializer should only be used to move "
         "initializers between modules");

  NewGV->setInitializer(MapValue(OrigGV.getInitializer(), VMap, RF_None,
                                 nullptr, Materializer));
}