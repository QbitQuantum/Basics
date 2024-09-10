void OgrWriter::_writePartial(ElementProviderPtr& provider, const ConstElementPtr& e)
{
  if (_translator.get() == 0)
  {
    throw HootException("You must call open before attempting to write.");
  }

  if (e->getTags().getInformationCount() > 0)
  {
    // There is probably a cleaner way of doing this.
    // convertToGeometry calls  getGeometryType which will throw an exception if it gets a relation
    // that it doesn't know about. E.g. "route", "superroute", " turnlanes:turns" etc

    shared_ptr<Geometry> g;

    try
    {
      g = ElementConverter(provider).convertToGeometry(e);
    }
    catch (IllegalArgumentException& err)
    {
      LOG_WARN("Error converting geometry: " << err.getWhat() << " (" << e->toString() << ")");
      g.reset((GeometryFactory::getDefaultInstance()->createEmptyGeometry()));
    }

    /*
    LOG_DEBUG("After conversion to geometry, element is now a " <<
             g->getGeometryType() );
    */

    Tags t = e->getTags();
    t["error:circular"] = QString::number(e->getCircularError());
    t["hoot:status"] = e->getStatusString();
    for (Tags::const_iterator it = e->getTags().begin(); it != e->getTags().end(); ++it)
    {
      if (t[it.key()] == "")
      {
        t.remove(it.key());
      }
    }

    vector<ScriptToOgrTranslator::TranslatedFeature> tf = _translator->translateToOgr(t,
      e->getElementType(), g->getGeometryTypeId());

    // only write the feature if it wasn't filtered by the translation script.
    for (size_t i = 0; i < tf.size(); i++)
    {
      OGRLayer* layer = _getLayer(tf[i].tableName);
      if (layer != 0)
      {
        _addFeature(layer, tf[i].feature, g);
      }
    }
  }
}