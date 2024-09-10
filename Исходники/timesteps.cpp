void TimeSteps::clear()
{
    Tools::ClassManager *cm = Tools::ClassManager::getInstance();
    vector<TimeStep *>::iterator tsIterator = timeSteps.begin();

    while (tsIterator != timeSteps.end())
    {
        TimeStep *timeStep = *tsIterator;

        if (timeStep != NULL)
        {
            timeStep->clear();
            cm->deleteObject(timeStep->getID());

            timeStep = NULL;
        }

        ++tsIterator;
    }

    timeSteps.clear();
}