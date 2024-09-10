void TranslatedTagCountVisitor::visit(ElementType type, long id)
{
  shared_ptr<const Element> e = _map->getElement(type, id);

  if (e->getTags().getInformationCount() > 0)
  {
    shared_ptr<Geometry> g = ElementConverter(_map->shared_from_this()).convertToGeometry(e);

    Tags t = e->getTags();
    t["error:circular"] = QString::number(e->getCircularError());
    t["hoot:status"] = e->getStatusString();

    // remove all the empty tags.
    for (Tags::const_iterator it = e->getTags().begin(); it != e->getTags().end(); ++it)
    {
      if (t[it.key()] == "")
      {
        t.remove(it.key());
      }
    }

    QString layerName;
    vector<ScriptToOgrTranslator::TranslatedFeature> f = _translator->translateToOgr(t,
      e->getElementType(), g->getGeometryTypeId());

    // only write the feature if it wasn't filtered by the translation script.
    for (size_t i = 0; i < f.size(); i++)
    {
      _countTags(f[i].feature);
    }
  }
}