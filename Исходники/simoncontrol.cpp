/**
 * @brief Constructor
 *
 * Sets the activitionstate to true
 *
 *	@author Peter Grasch
 */
SimonControl::SimonControl(QWidget *parent) : QObject (parent)
{
  setStatus(SimonControl::Disconnected);
  
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(connected()), this, SLOT(connectedToServer()));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));

  QObject::connect(RecognitionControl::getInstance(), SIGNAL(connectionError(QString)), this, SLOT(slotConnectionError(QString)));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(simondSystemError(QString)), this, SLOT(slotSimondSystemError(QString)));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(synchronisationError(QString)), this, SLOT(slotSynchronisationError(QString)));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(recognitionError(QString,QString)), this, SLOT(slotRecognitionError(QString,QString)));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(compilationError(QString,QString)), this, SLOT(slotCompilationError(QString,QString)));

  QObject::connect(RecognitionControl::getInstance(), SIGNAL(simondSystemWarning(QString)), this, SLOT(slotSimondSystemWarning(QString)));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(synchronisationWarning(QString)), this, SLOT(slotSynchronisationWarning(QString)));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(recognitionWarning(QString)), this, SLOT(slotRecognitionWarning(QString)));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(compilationWarning(QString)), this, SLOT(slotCompilationWarning(QString)));

  QObject::connect(RecognitionControl::getInstance(), SIGNAL(loggedIn()), this, SLOT(loggedIn()));

  QObject::connect(RecognitionControl::getInstance(), SIGNAL(recognised(RecognitionResultList)), this, SLOT(wordRecognised(RecognitionResultList)));
  QObject::connect(RecognitionControl::getInstance(), SIGNAL(recognitionStatusChanged(RecognitionControl::RecognitionStatus)), this, SLOT(recognitionStatusChanged(RecognitionControl::RecognitionStatus)));

  QObject::connect(ScenarioManager::getInstance(), SIGNAL(deactivatedScenarioListChanged()), this, SIGNAL(deactivatedScenarioListChanged()));
  QObject::connect(this, SIGNAL(deactivatedScenarioListChanged()), RecognitionControl::getInstance(), SLOT(sendDeactivatedScenarioList()));
  QObject::connect(ContextManager::instance(), SIGNAL(sampleGroupChanged(QStringList)), RecognitionControl::getInstance(), SLOT(sendDeactivatedSampleGroups(QStringList)));
  ContextManager::instance()->getSampleGroupCondition()->loadSampleGroupContext();

  ActionManager::getInstance();                   // initializing action manager
  SimonTTS::getInstance();                   // initializing TTS system for dbus interface

  if (!ScenarioManager::getInstance()->init()) {
    KMessageBox::error(0, i18n("Could not initialize scenarios and shadow dictionary."));
    if (!ScenarioManager::getInstance()->getCurrentScenario()) {
      kDebug() << "Aborting due to fatal error while loading scenarios";
      exit(-1); // this is fatal
    }
  }

  connect(SoundServer::getInstance(), SIGNAL(error(QString)), this, SLOT(slotSoundError(QString)));
}