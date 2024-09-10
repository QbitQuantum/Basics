void SequenceJob::prepareCapture()
{
    activeChip->setBatchMode(!preview);

    activeCCD->setFITSDir(fitsDir);

    activeCCD->setISOMode(timeStampPrefixEnabled);

    activeCCD->setSeqPrefix(fullPrefix);

    if (activeChip->isBatchMode())
        activeCCD->updateUploadSettings();

    if (isoIndex != -1)
    {
        if (isoIndex != activeChip->getISOIndex())
             activeChip->setISOIndex(isoIndex);
    }

    if (targetFilter != -1 && activeFilter != NULL)
    {
        if (targetFilter == currentFilter)
            //emit prepareComplete();
            filterReady = true;
        else
        {
            filterReady = false;

            // Post Focus on Filter change
            filterPostFocusReady = !Options::autoFocusOnFilterChange();

            activeFilter->runCommand(INDI_SET_FILTER, &targetFilter);
        }
    }


    if (enforceTemperature && targetTemperature != currentTemperature)
    {
        temperatureReady = false;
        activeCCD->setTemperature(targetTemperature);
    }

    if (temperatureReady && filterReady)
        emit prepareComplete();

}