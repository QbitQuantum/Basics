/**
 * @brief SpectrogramData::append Appends data to spectrogram
 * @param obj UAVO with new data
 * @return
 */
bool SpectrogramData::append(UAVObject* multiObj)
{
    QDateTime NOW = QDateTime::currentDateTime(); //TODO: Upgrade this to show UAVO time and not system time

    // Check to make sure it's the correct UAVO
    if (uavObjectName == multiObj->getName()) {

        // Only run on UAVOs that have multiple instances
        if (multiObj->isSingleInstance())
            return false;

        //Instantiate object manager
        UAVObjectManager *objManager;

        ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
        Q_ASSERT(pm != NULL);
        objManager = pm->getObject<UAVObjectManager>();
        Q_ASSERT(objManager != NULL);


        // Get list of object instances
        QVector<UAVObject*> list = objManager->getObjectInstancesVector(multiObj->getName());

        // Remove a row's worth of data.
        unsigned int spectrogramWidth = list.size();

        // Check that there is a full window worth of data. While GCS is starting up, the size of
        // multiple instance UAVOs is 1, so it's possible for spurious data to come in before
        // the flight controller board has had time to initialize the UAVO size.
        if (spectrogramWidth != windowWidth){
            qDebug() << "Incomplete data set in" << multiObj->getName() << "." << uavFieldName <<  "spectrogram: " << spectrogramWidth << " samples provided, but expected " << windowWidth;
            return false;
        }

        //Initialize vector where we will read out an entire row of multiple instance UAVO
        QVector<double> values;

        timeDataHistory->append(NOW.toTime_t() + NOW.time().msec() / 1000.0);
        UAVObjectField* multiField =  multiObj->getField(uavFieldName);
        Q_ASSERT(multiField);
        if (multiField ) {

            // Get the field of interest
            foreach (UAVObject *obj, list) {
                UAVObjectField* field =  obj->getField(uavFieldName);

                double currentValue = valueAsDouble(obj, field, haveSubField, uavSubFieldName) * pow(10, scalePower);

                double vecVal = currentValue;
                //Normally some math would go here, modifying vecVal before appending it to values
                // .
                // .
                // .


                // Second to last step, see if autoscale is turned on and if the value exceeds the maximum for the scope.
                if ( zMaximum == 0 &&  vecVal > rasterData->interval(Qt::ZAxis).maxValue()){
                    // Change scope maximum and color depth
                    rasterData->setInterval(Qt::ZAxis, QwtInterval(0, vecVal) );
                    autoscaleValueUpdated = vecVal;
                }
                // Last step, assign value to vector
                values += vecVal;
            }

            while (timeDataHistory->back() - timeDataHistory->front() > timeHorizon){
                timeDataHistory->pop_front();
                zDataHistory->remove(0, fminl(spectrogramWidth, zDataHistory->size()));
            }

            // Doublecheck that there are the right number of samples. This can occur if the "field" assert fails
            if(values.size() == (int) windowWidth){
                *zDataHistory << values;
            }

            return true;
        }
    }