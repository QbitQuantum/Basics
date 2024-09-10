Transformer* CreateGraphicFunc::get_transformer(AttributeList* al) {
  static int transform_symid = symbol_add("transform");

  AttributeValue* transformv = nil;
  Transformer* rel = nil;
  AttributeValueList* avl = nil;
  if (al && 
      (transformv=al->find(transform_symid)) && 
      transformv->is_array() && 
      (avl=transformv->array_val()) &&
      avl->Number()==6) {
    float a00, a01, a10, a11, a20, a21;
    Iterator it;
    avl->First(it); a00=avl->GetAttrVal(it)->float_val();
    avl->Next(it); a01=avl->GetAttrVal(it)->float_val();
    avl->Next(it); a10=avl->GetAttrVal(it)->float_val();
    avl->Next(it); a11=avl->GetAttrVal(it)->float_val();
    avl->Next(it); a20=avl->GetAttrVal(it)->float_val();
    avl->Next(it); a21=avl->GetAttrVal(it)->float_val();
    rel = new Transformer(a00, a01, a10, a11, a20, a21);
  } else {
    rel = ((OverlayViewer*)_ed->GetViewer())->GetRel();
    if (rel != nil) {
      rel = new Transformer(rel);
      rel->Invert();
    }
  }
  return rel;
  
}