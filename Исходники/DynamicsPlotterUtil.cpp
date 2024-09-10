	/**
	 *
	 * The neuronsWithActivationChange parameter can be used to collect all DoubelValues that correspond
	 * to activation values of neurons. These neurons have to be collected in each DymnamcisPlotter in
	 * variable DynamcisPlotter::mNeuronsWithActivationsToTransfer to be handled correctly, if the
	 * activation of a neuron should be varied during an analyzer run. Otherwise the varied activations
	 * are immediately overwritten by the newly calculated activations at the first network update.
	 *
	 * If this method is used to collect elements that will NOT be changed during analyzer runs,
	 * then the last parameter MUST be empty. Othewise activations of neurons collected in this way
	 * will be treated differently compared to the other neurons in the network. This may lead to
	 * unexpected and erroneous behavior.
	 *
	 * @param specifierLists a list of stringlists, containing the single specifications of DoubleValues.
	 * @param networkElements the list of objects that are considered to find the specified DoubleValue object.
	 * @param neuronsWithActivationChange (optional) list to collect all activation values that are going to be changed during a run.
	 */
	QList< QList<DoubleValue*> > DynamicsPlotterUtil::getElementValues(QList<QStringList> const &specifierLists,
																	   QList<NeuralNetworkElement*> const &networkElements,
																	   QList<Neuron*> *neuronsWithActivationChange)
	{
		QList< QList<DoubleValue*> > plotElements, emptyList;
		emptyList = QList< QList<DoubleValue*> >();

		for(int listNr = 0; listNr < specifierLists.size(); ++listNr) {
			QList<DoubleValue*> elementValues;

			QStringList specifierList = specifierLists.at(listNr);
			for(int specifierNr = 0; specifierNr < specifierList.size(); ++specifierNr) {

				QString specifier = specifierList.at(specifierNr);
				if(specifier.isEmpty()) {
					reportProblem("DynamicsPlotterUtil::getElementValues : Empty specifier!");
					return emptyList;
				}

				QStringList parameters = specifier.split(":");
				if(parameters.size() < 2 || parameters.size() > 3) {
					reportProblem("DynamicsPlotterUtil::getElementValues : Invalid specifier ["+specifier+"]!");
					return emptyList;
				}

				if(parameters.first() == "all") {
					QList<DoubleValue*> netValues;
					DoubleValue* elementValue;
					QString parameter = specifier.remove("all:");

					for(int elemNr = 0; elemNr < networkElements.size(); ++elemNr) {
						NeuralNetworkElement* networkElement = networkElements.at(elemNr);
						elementValue = getElementValue(parameter, networkElement, neuronsWithActivationChange);

						if(elementValue != 0) {
							netValues.append(elementValue);
						}
					}

					elementValues.append(netValues);

				} else {
					DoubleValue* elementValue;
					elementValue = getElementValue(specifier, networkElements, neuronsWithActivationChange);

					if(elementValue == 0) {
						reportProblem("DynamicsPlotterUtil::getElementValues : Could not find a value "
									  "for element specifier ["+specifier+"]!");
						return emptyList;
					}

					elementValues.append(elementValue);

				}
			}

			plotElements.append(elementValues);
		}

		return plotElements;
	}