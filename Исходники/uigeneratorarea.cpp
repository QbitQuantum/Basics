/*!
    Save project settings related to signal generation. The settings are
    stored in \a project.
*/
void UiGeneratorArea::saveProject(QSettings &project)
{
    GeneratorDevice* device = DeviceManager::instance()
            .activeDevice()->generatorDevice();

    project.remove("digitalGenerator");
    project.remove("analogGenerator");
    if (device != NULL) {

        if (device->maxNumDigitalSignals() > 0) {

            bool digEnabled = (subWindowList().indexOf(mDigitalWin) != -1);

            project.beginGroup("digitalGenerator");

            project.setValue("enabled", digEnabled);
            project.setValue("rate", mDigitalGenerator->rate());

            project.beginWriteArray("signals");

            QList<DigitalSignal*> digitalList = device->digitalSignals();
            for (int i = 0; i < digitalList.size(); i++) {
                DigitalSignal* s = digitalList.at(i);
                project.setArrayIndex(i);
                project.setValue("meta", s->toSettingsString());
            }

            project.endArray();

            project.endGroup();
        }

        if (device->maxNumAnalogSignals() > 0) {

            bool anEnabled  = (subWindowList().indexOf(mAnalogWin) != -1);

            project.beginGroup("analogGenerator");
            project.setValue("enabled", anEnabled);

            project.beginWriteArray("signals");

            QList<AnalogSignal*> analogList = device->analogSignals();
            for (int i = 0; i < analogList.size(); i++) {
                AnalogSignal* s = analogList.at(i);
                project.setArrayIndex(i);
                project.setValue("meta", s->toSettingsString());
            }

            project.endArray();

            project.endGroup();
        }

    }
}