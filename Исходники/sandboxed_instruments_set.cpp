bool SandboxedInstrumentsSet::onClassifierClassificationDone(IClassifierInputSet* input_set,
                                                             unsigned int image,
                                                             unsigned int original_image,
                                                             const coordinates_t& position,
                                                             const Classifier::tClassificationResults& results,
                                                             Instrument::tClassificationError error)
{
    // Assertions
    assert(input_set);

    if (_sandbox.nbPlugins() == 0)
        return true;

    if (getLastError() != ERROR_NONE)
        return false;

    _outStream << "< EVENT_CLASSIFIER_CLASSIFICATION_DONE " << image << " "
               << original_image << " " << position.x << " " << position.y
               << " " << error << " " << results.size() << " ..." << endl;

    CommunicationChannel* pChannel = _sandbox.channel();

    _pInputSetProxy = new SandboxInputSetProxy(input_set, *pChannel);

    // Save the context (in case of crash)
    std::ostringstream str;

    dim_t image_size = input_set->imageSize(image);

	str << "Method: onClassifierClassificationDone" << endl
        << "Parameters:" << endl
        << "    - Image:                #" << image << " (" << image_size.width << "x" << image_size.height << " pixels)" << endl
        << "    - Original image:       #" << original_image << endl
        << "    - ROI extent:           " << input_set->roiExtent() << " pixels" << endl
        << "    - ROI position:         (" << position.x << ", " << position.y << ")" << endl
        << "    - Number of labels:     " << input_set->nbLabels() << endl
        << "    - Number of heuristics: " << input_set->nbHeuristics() << endl
        << "    - Number of features:   " << input_set->nbFeaturesTotal() << endl
        << "    - Number of results:    " << results.size() << endl
        << "    - Error:                ";
    
    switch (error)
    {
        case Instrument::CLASSIFICATION_ERROR_NONE:                 str << "None"; break;
        case Instrument::CLASSIFICATION_ERROR_FALSE_ALARM:          str << "False alarm"; break;
        case Instrument::CLASSIFICATION_ERROR_FALSE_REJECTION:      str << "False rejection"; break;
        case Instrument::CLASSIFICATION_ERROR_WRONG_CLASSIFICATION: str << "Wrong classification"; break;
    }

    str << endl;

	_strContext = str.str();

    // Send the command to the child
    pChannel->startPacket(SANDBOX_EVENT_INSTRUMENTS_CLASSIFIER_CLASSIFICATION_DONE);
    pChannel->add(image);
    pChannel->add(original_image);
    pChannel->add(position.x);
    pChannel->add(position.y);
    pChannel->add((unsigned int) error);
    pChannel->add((unsigned int) results.size());

    Classifier::tClassificationResults::const_iterator iter, iterEnd;
    for (iter = results.begin(), iterEnd = results.end(); iter != iterEnd; ++iter)
    {
        pChannel->add(iter->first);
        pChannel->add(iter->second);
    }

    pChannel->sendPacket();

    // Wait the response
    bool result = pChannel->good();
    if (result)
        result = _sandbox.waitResponse();
    
    delete _pInputSetProxy;
    _pInputSetProxy = 0;

    if (_lastError == ERROR_NONE)
        _lastError = (pChannel->getLastError() == ERROR_CHANNEL_SLAVE_CRASHED) ? ERROR_INSTRUMENT_CRASHED : ERROR_NONE;

    return result;
}