void AddThread::writeSettings()
{
    QSettings settings;
    settings.remove(GROUP_ADD_THREAD);
    settings.beginGroup(GROUP_ADD_THREAD);
      settings.setValue( KEY_GEOMETRY, this->geometry() );
      settings.setValue( KEY_START, checkBoxStart->isChecked() );
    settings.endGroup();
    settings.beginGroup(ThreadManager::GROUP_THREADS);
      settings.remove(ThreadManager::SUB_GROUP_DEFAULT);
      settings.beginGroup(ThreadManager::SUB_GROUP_DEFAULT);
        ImageboardThread::writeParameters(settings, defParam);
      settings.endGroup();
    settings.endGroup();
}