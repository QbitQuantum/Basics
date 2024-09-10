void InputWindowAction::common()
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}