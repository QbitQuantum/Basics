void PreferencesDialog::loadPreferences() {
    
    MyAvatar* myAvatar = DependencyManager::get<AvatarManager>()->getMyAvatar();
    Menu* menuInstance = Menu::getInstance();

    _displayNameString = myAvatar->getDisplayName();
    ui.displayNameEdit->setText(_displayNameString);

    ui.collisionSoundURLEdit->setText(myAvatar->getCollisionSoundURL());

    ui.sendDataCheckBox->setChecked(!menuInstance->isOptionChecked(MenuOption::DisableActivityLogger));

    ui.snapshotLocationEdit->setText(Snapshot::snapshotsLocation.get());

    ui.scriptsLocationEdit->setText(qApp->getScriptsLocation());

    ui.pupilDilationSlider->setValue(myAvatar->getHead()->getPupilDilation() *
                                     ui.pupilDilationSlider->maximum());
    
    auto dde = DependencyManager::get<DdeFaceTracker>();
    ui.ddeEyeClosingThresholdSlider->setValue(dde->getEyeClosingThreshold() * 
                                              ui.ddeEyeClosingThresholdSlider->maximum());

    ui.faceTrackerEyeDeflectionSider->setValue(FaceTracker::getEyeDeflection() *
                                               ui.faceTrackerEyeDeflectionSider->maximum());
    
    auto faceshift = DependencyManager::get<Faceshift>();
    ui.faceshiftHostnameEdit->setText(faceshift->getHostname());

    auto audio = DependencyManager::get<AudioClient>();
    MixedProcessedAudioStream& stream = audio->getReceivedAudioStream();

    ui.dynamicJitterBuffersCheckBox->setChecked(stream.getDynamicJitterBuffers());
    ui.staticDesiredJitterBufferFramesSpin->setValue(stream.getDesiredJitterBufferFrames());
    ui.maxFramesOverDesiredSpin->setValue(stream.getMaxFramesOverDesired());
    ui.useStdevForJitterCalcCheckBox->setChecked(stream.getUseStDevForJitterCalc());
    ui.windowStarveThresholdSpin->setValue(stream.getWindowStarveThreshold());
    ui.windowSecondsForDesiredCalcOnTooManyStarvesSpin->setValue(
            stream.getWindowSecondsForDesiredCalcOnTooManyStarves());
    ui.windowSecondsForDesiredReductionSpin->setValue(stream.getWindowSecondsForDesiredReduction());
    ui.repetitionWithFadeCheckBox->setChecked(stream.getRepetitionWithFade());

    ui.outputBufferSizeSpinner->setValue(audio->getOutputBufferSize());

    ui.outputStarveDetectionCheckBox->setChecked(audio->getOutputStarveDetectionEnabled());
    ui.outputStarveDetectionThresholdSpinner->setValue(audio->getOutputStarveDetectionThreshold());
    ui.outputStarveDetectionPeriodSpinner->setValue(audio->getOutputStarveDetectionPeriod());

    ui.realWorldFieldOfViewSpin->setValue(DependencyManager::get<AvatarManager>()->getMyAvatar()->getRealWorldFieldOfView());

    ui.fieldOfViewSpin->setValue(qApp->getFieldOfView());
    
    ui.leanScaleSpin->setValue(myAvatar->getLeanScale());
    
    ui.avatarScaleSpin->setValue(myAvatar->getScale());
    
    ui.maxOctreePPSSpin->setValue(qApp->getMaxOctreePacketsPerSecond());

    ui.oculusUIAngularSizeSpin->setValue(qApp->getApplicationCompositor().getHmdUIAngularSize());

    SixenseManager& sixense = SixenseManager::getInstance();
    ui.sixenseReticleMoveSpeedSpin->setValue(sixense.getReticleMoveSpeed());
    ui.invertSixenseButtonsCheckBox->setChecked(sixense.getInvertButtons());

    // LOD items
    auto lodManager = DependencyManager::get<LODManager>();
    ui.desktopMinimumFPSSpin->setValue(lodManager->getDesktopLODDecreaseFPS());
    ui.hmdMinimumFPSSpin->setValue(lodManager->getHMDLODDecreaseFPS());
}