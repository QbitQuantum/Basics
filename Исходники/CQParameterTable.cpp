void ParameterTable::updateTable(const CReactionInterface & ri, const CModel & model)
{
  //first get the units strings
  CFindDimensions units(ri.getFunction(), model.getQuantityUnitEnum() == CModel::dimensionlessQuantity,
                        model.getVolumeUnitEnum() == CModel::dimensionlessVolume,
                        model.getTimeUnitEnum() == CModel::dimensionlessTime,
                        model.getAreaUnitEnum() == CModel::dimensionlessArea,
                        model.getLengthUnitEnum() == CModel::dimensionlessLength
                       );
  units.setUseHeuristics(true);
  units.setMolecularitiesForMassAction(ri.getChemEqInterface().getMolecularity(CFunctionParameter::SUBSTRATE),
                                       ri.getChemEqInterface().getMolecularity(CFunctionParameter::PRODUCT));
  units.findDimensions(ri.isMulticompartment());

  size_t i, imax = ri.size();
  size_t j, jmax;
  size_t rowCounter = 0;

  QStringList qsl;

  QColor subsColor(255, 210, 210);
  QColor prodColor(210, 255, 210);
  QColor modiColor(250, 250, 190);
  QColor paraColor(210, 210, 255);
  QColor volColor(210, 210, 255);
  QColor timeColor(210, 210, 210);

  CFunctionParameter::Role usage;
  QString qUsage;
  QColor color;
  const std::vector<std::string> * metabNames;

  mIndex2Line.resize(imax);
  mLine2Index.clear();

  this->setRowCount(0);
  this->setRowCount((int)(imax * 2));

  for (i = 0; i < imax; ++i)
    {
      rowCounter++;
      mIndex2Line[i] = rowCounter;

      // set the stuff that is different for the specific usages
      usage = ri.getUsage(i);
      qUsage = FROM_UTF8(CFunctionParameter::RoleNameDisplay[usage]);

      switch (usage)
        {
          case CFunctionParameter::SUBSTRATE:
            color = subsColor;
            break;

          case CFunctionParameter::PRODUCT:
            color = prodColor;
            break;

          case CFunctionParameter::MODIFIER:
            color = modiColor;
            break;

          case CFunctionParameter::PARAMETER:
            color = paraColor;
            break;

          case CFunctionParameter::VOLUME:
            color = volColor;
            break;

          case CFunctionParameter::TIME:
            color = timeColor;
            break;

          case CFunctionParameter::VARIABLE:
            color = QColor(255, 20, 20);
            break;

          default:
            qUsage = "unknown";
            color = QColor(255, 20, 20);
            break;
        }

      // add first column
      QTableWidgetItem * pItem = new ColorTableItem(color, qUsage);

      if (usage == CFunctionParameter::SUBSTRATE) pItem->setIcon(CQIconResource::icon(CQIconResource::reactionSubstrate));

      if (usage == CFunctionParameter::PRODUCT) pItem->setIcon(CQIconResource::icon(CQIconResource::reactionProduct));

      if (usage == CFunctionParameter::MODIFIER) pItem->setIcon(CQIconResource::icon(CQIconResource::reactionModifier));

      setItem((int) rowCounter, 0, pItem);

      // add second column
      pItem = new ColorTableItem(color, FROM_UTF8(ri.getParameterName(i)));

      if ((usage != CFunctionParameter::PARAMETER)
          && (usage != CFunctionParameter::VOLUME)
          && (usage != CFunctionParameter::TIME))
        {
          if (ri.isLocked(i))
            pItem->setIcon(CQIconResource::icon(CQIconResource::locked));
          else
            pItem->setIcon(CQIconResource::icon(CQIconResource::unlocked));
        }

      setItem((int) rowCounter, 1, pItem);

      // add third column
      pItem = new ColorTableItem(color, "");

      if (usage == CFunctionParameter::PARAMETER)
        {
          pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
          pItem->setCheckState(ri.isLocalValue(i) ? Qt::Unchecked : Qt::Checked);
        }

      setItem((int) rowCounter, 2, pItem);

      // add units column
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      pItem = new ColorTableItem(color, FROM_UTF8(" " + units.getDimensions()[i].getDisplayString(pDataModel)));
      setItem((int) rowCounter, 4, pItem);

      // add a line for a metabolite Parameter
      if ((usage == CFunctionParameter::SUBSTRATE)
          || (usage == CFunctionParameter::PRODUCT)
          || (usage == CFunctionParameter::MODIFIER))
        {
          // get the list of possible metabs (for the combo box)
          if (usage == CFunctionParameter::MODIFIER) //get all metabs; modifiers are never locked
            vectorOfStrings2QStringList(getListOfAllMetabNames(model, ri), qsl);
          else //only get the modifiers from the ChemEq
            {
              if (!ri.isLocked(i))
                vectorOfStrings2QStringList(ri.getListOfMetabs(usage), qsl);
            }

          metabNames = &(ri.getMappings(i));

          if (!ri.isVector(i))
            {
              if (ri.isLocked(i))
                {
                  pItem = new ColorTableItem(color, FROM_UTF8((*metabNames)[0]));
                  setItem((int) rowCounter, 3, pItem);
                }
              else
                {
                  QComboBox * pComboBox = new QComboBox();
                  pComboBox->addItems(qsl);
                  pComboBox->setBackgroundColor(color);
                  pComboBox->setCurrentText(FROM_UTF8(unQuote((*metabNames)[0])));

                  setCellWidget((int) rowCounter, 3, pComboBox);
                }
            }
          else
            {
              if (ri.isLocked(i))
                {
                  pItem = new ColorTableItem(color, "");
                  setItem((int) rowCounter, 3, pItem);
                }
              else // this should not happen
                {
                  QComboBox * pComboBox = new QComboBox();
                  pComboBox->addItems(qsl);
                  pComboBox->setBackgroundColor(color);
                  pComboBox->setCurrentText("add species");

                  setCellWidget((int) rowCounter, 3, pComboBox);
                }

              // add lines for vector parameters
              jmax = metabNames->size();
              setRowCount(rowCount() + (int) jmax);

              for (j = 0; j < jmax; ++j)
                {
                  ++rowCounter;
                  pItem = new ColorTableItem(color, FROM_UTF8((*metabNames)[j]));
                  setItem((int) rowCounter, 3, pItem);
                }
            }
        }
      // add a line for a kinetic parameter
      else if (usage == CFunctionParameter::PARAMETER)
        {
          if (ri.isLocalValue(i))
            {
              pItem = new ColorTableItem(color, QString::number(ri.getLocalValue(i)));
              setItem((int) rowCounter, 3, pItem);
            }
          else //global parameter
            {
              QComboBox * pComboBox = new QComboBox();
              pComboBox->addItems(getListOfAllGlobalParameterNames(model));
              pComboBox->setBackgroundColor(color);
              pComboBox->setCurrentText(FROM_UTF8(ri.getMapping(i)));

              setCellWidget((int) rowCounter, 3, pComboBox);
            }
        }
      // add a line for a kinetic parameter
      else if (usage == CFunctionParameter::VOLUME)
        {
          QComboBox * pComboBox = new QComboBox();
          pComboBox->addItems(getListOfAllCompartmentNames(model));
          pComboBox->setBackgroundColor(color);
          pComboBox->setCurrentText(FROM_UTF8(ri.getMapping(i)));

          setCellWidget((int) rowCounter, 3, pComboBox);
        }
      // add a line for time
      else if (usage == CFunctionParameter::TIME)
        {
          pItem = new ColorTableItem(color, "");
          setItem((int) rowCounter, 3, pItem);
        }
      // add a line for an unknown role
      else
        {
          pItem = new ColorTableItem(color, QString::number(ri.getLocalValue(i)));
          setItem((int) rowCounter, 3, pItem);
        }

      resizeRowToContents((int) rowCounter);

      //mLine2Index

      ++rowCounter;
    }

  this->resizeColumnsToContents();
}