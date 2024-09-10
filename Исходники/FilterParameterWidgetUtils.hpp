    static void PopulateDataContainerComboBox(AbstractFilter* filter, FilterParameter* filterParameter,
                                              QComboBox* dcCombo, DataContainerArrayProxy& dcaProxy)
    {
      FilterParameterType* fp = dynamic_cast<FilterParameterType*>(filterParameter);
      assert(fp != NULL);
      DataContainerArray::Pointer dca = filter->getDataContainerArray();
      // Populate the DataContainerArray Combo Box with all the DataContainers
      QList<DataContainerProxy> dcList = dcaProxy.dataContainers.values();
      QListIterator<DataContainerProxy> iter(dcList);
      dcCombo->clear();
      QVector<unsigned int> defVec = fp->getDefaultGeometryTypes();
      while(iter.hasNext() )
      {
        DataContainerProxy dcProxy = iter.next();
        DataContainer::Pointer dc = dca->getDataContainer(dcProxy.name);
        IGeometry::Pointer geom = IGeometry::NullPointer();
        uint32_t geomType = 999;
        if (NULL != dc.get()) { geom = dc->getGeometry(); }
        if (NULL != geom.get()) { geomType = geom->getGeometryType(); }
        dcCombo->addItem(dcProxy.name);

        if (defVec.isEmpty() == false)
        {
          if (defVec.contains(geomType) == false)
          {
            QStandardItemModel* model = qobject_cast<QStandardItemModel*>(dcCombo->model());
            if (NULL != model)
            {
              QStandardItem* item = model->item(dcCombo->findText(dcProxy.name));
              if (NULL != item)
              {
                item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
              }
            }
          }
        }
      }
    }