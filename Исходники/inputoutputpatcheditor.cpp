void InputOutputPatchEditor::fillMappingTree()
{
    /* Disable check state change tracking when the tree is filled */
    disconnect(m_mapTree, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this, SLOT(slotMapItemChanged(QTreeWidgetItem*, int)));

    m_mapTree->clear();

    qDebug() << "[InputOutputPatchEditor] Fill tree for universe: " << m_universe;

    // Build a complete list of Input/Output plugins
    QStringList IOplugins = m_inputMap->pluginNames();
    foreach (QString out, m_outputMap->pluginNames())
        if (IOplugins.contains(out) == false)
            IOplugins.append(out);

    // cycle through available plugins
    foreach (QString pluginName, IOplugins)
    {
        quint32 inputId = 0;
        quint32 outputId = 0;
        QStringList inputs = m_inputMap->pluginInputs(pluginName);
        QStringList outputs = m_outputMap->pluginOutputs(pluginName);

        // 1st case: this plugin has no input or output
        if (inputs.length() == 0 && outputs.length() == 0)
        {
            QTreeWidgetItem* pitem = new QTreeWidgetItem(m_mapTree);
            pitem->setText(KMapColumnPluginName, pluginName);
            pitem->setText(KMapColumnDeviceName, KInputNone);
            pitem->setText(KMapColumnInputLine, QString("%1").arg(QLCIOPlugin::invalidLine()));
            pitem->setText(KMapColumnOutputLine, QString("%1").arg(QLCIOPlugin::invalidLine()));
        }
        else
        {
            // 2nd case: plugin with an input and maybe an output
            for (int l = 0; l < inputs.length(); l++)
            {
                quint32 uni = m_inputMap->mapping(pluginName, inputId);
                //qDebug() << "Plugin: " << pluginName << ", input: " << id << ", universe:" << uni;
                if (uni == InputMap::invalidUniverse() || uni == m_universe)
                {
                    QTreeWidgetItem* pitem = new QTreeWidgetItem(m_mapTree);
                    pitem->setText(KMapColumnPluginName, pluginName);
                    pitem->setText(KMapColumnDeviceName, inputs.at(l));
                    pitem->setFlags(pitem->flags() | Qt::ItemIsUserCheckable);
                    if (m_currentInputPluginName == pluginName && m_currentInput == inputId)
                        pitem->setCheckState(KMapColumnHasInput, Qt::Checked);
                    else
                        pitem->setCheckState(KMapColumnHasInput, Qt::Unchecked);
                    pitem->setTextAlignment(KMapColumnHasInput, Qt::AlignHCenter);
                    pitem->setText(KMapColumnInputLine, QString("%1").arg(inputId));
                    pitem->setText(KMapColumnOutputLine, QString("%1").arg(QLCIOPlugin::invalidLine()));
                    // check if this plugin has also an output
                    if (outputs.contains(inputs.at(l)))
                    {
                        quint32 outUni = m_outputMap->mapping(pluginName, outputId);
                        if (outUni == OutputMap::invalidUniverse() || outUni == m_universe)
                        {
                            if (m_currentOutputPluginName == pluginName && m_currentOutput == outputId)
                                pitem->setCheckState(KMapColumnHasOutput, Qt::Checked);
                            else
                                pitem->setCheckState(KMapColumnHasOutput, Qt::Unchecked);
                            pitem->setText(KMapColumnOutputLine, QString("%1").arg(outputId));
                            // add feedback
                            if (pluginName == "MIDI" || pluginName == "OSC")
                            {
                                if (m_currentFeedbackPluginName == pluginName && m_currentFeedback == outputId)
                                    pitem->setCheckState(KMapColumnHasFeedback, Qt::Checked);
                                else
                                    pitem->setCheckState(KMapColumnHasFeedback, Qt::Unchecked);
                            }
                        }
                        outputId++;
                    }
                }
                inputId++;
            }
            // 3rd case: output only plugins
            for (int o = 0; o < outputs.length(); o++)
            {
                if (inputs.contains(outputs.at(o)) == false)
                {
                    quint32 outUni = m_outputMap->mapping(pluginName, outputId);
                    if (outUni == OutputMap::invalidUniverse() || outUni == m_universe)
                    {
                        //qDebug() << "Plugin: " << pluginName << ", output: " << id << ", universe:" << outUni;
                        QTreeWidgetItem* pitem = new QTreeWidgetItem(m_mapTree);
                        pitem->setText(KMapColumnPluginName, pluginName);
                        pitem->setText(KMapColumnDeviceName, outputs.at(o));
                        pitem->setFlags(pitem->flags() | Qt::ItemIsUserCheckable);
                        if (m_currentOutputPluginName == pluginName && m_currentOutput == outputId)
                            pitem->setCheckState(KMapColumnHasOutput, Qt::Checked);
                        else
                            pitem->setCheckState(KMapColumnHasOutput, Qt::Unchecked);
                        // add feedback
                        if (pluginName == "MIDI" || pluginName == "OSC")
                        {
                            if (m_currentFeedbackPluginName == pluginName && m_currentFeedback == outputId)
                                pitem->setCheckState(KMapColumnHasFeedback, Qt::Checked);
                            else
                                pitem->setCheckState(KMapColumnHasFeedback, Qt::Unchecked);
                        }
                        pitem->setText(KMapColumnOutputLine, QString("%1").arg(outputId));
                        pitem->setText(KMapColumnInputLine, QString("%1").arg(QLCIOPlugin::invalidLine()));
                    }
                    outputId++;
                }
            }
        }
    }