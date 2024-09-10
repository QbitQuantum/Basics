void
SoXtMaterialList::selectionCallback(// private
  int materialid)
{
  materialid--; // get index
  SoXtMaterialDirectory * data = common->getMaterialDirectory();

  assert(materialid >= 0 &&
          materialid < data->groups[data->current]->numMaterials);
  const char * materialdata =
    data->groups[data->current]->materials[materialid]->data;

  SoInput reader;
  if (data->flags & SOXT_BUILTIN_MATERIALS) {
    reader.setBuffer((void *) materialdata, strlen(materialdata));
  } else {
    if (! reader.openFile(materialdata, FALSE)) {
      SoDebugError::postWarning("SoXtMaterialList::selectionCallback",
        "could not open file: \"%s\"", materialdata);
      return;
    }
  }

  SoNode * material = NULL;
  if (! SoDB::read(&reader, material)) {
    SoDebugError::postWarning("SoXtMaterialList::selectionCallback",
      "failed to read material");
    return;
  }
  if (! material) {
    SoDebugError::postWarning("SoXtMaterialList::selectionCallback",
      "read returned no data");
    return;
  }
  material->ref();
  if (! material->isOfType(SoMaterial::getClassTypeId())) {
    SoDebugError::postWarning("SoXtMaterialList::selectionCallback",
      "not a material node!");
    material->unref();
    return;
  }
  common->invokeCallbacks((SoMaterial *) material);
  material->unref();
} // selectionCallback()