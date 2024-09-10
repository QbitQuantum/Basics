void TrackComponent::mouseDown(const MouseEvent &e) {

	ModifierKeys modifiers = ModifierKeys::getCurrentModifiersRealtime();

    int posX;
	// check the mod keys ..
	if (modifiers.isPopupMenu() || modifiers.isCtrlDown())
	{
		ScopedPointer<PopupMenu> trackMenu_ = new PopupMenu();
		trackMenu_->clear();
		trackMenu_->addCommandItem(&_commands, MainWindow::showMixer);
		trackMenu_->addItem(1, "Add Region", true);
        MouseEvent ev = e.getEventRelativeTo(this);
        for(auto region : _regionComponents)
        {
            posX = ev.x;
            region->setBroughtToFrontOnMouseClick(true);
            if(region->getPositionX() < posX && posX < (region->getPositionX() + region->getRegionWidth()))
            {
                trackMenu_->addItem(2, "Remove Region", true);
            }
        }
        switch (trackMenu_->show())
        {
            case 1:
            {
                FileChooser chooser("Select an audio file to add...",
                                    File::nonexistent,
                                    "*.wav; *aif; *.flac");
                if (chooser.browseForFileToOpen()) {
                    File audioFile(chooser.getResult());
                    const String fileString = audioFile.getFullPathName();
                    String format;
                    if (fileString.contains(".wav"))
                        format = "WAV";
                    else if (fileString.contains(".aif") || fileString.contains(".aiff"))
                        format = "AIFF";
                    else if (fileString.contains(".flac"))
                        format = "FLAC";
                    AudioFormatManager formatManager;
                    formatManager.registerBasicFormats();
                    
                    AudioFormatReader* reader = formatManager.createReaderFor(audioFile);
                    Audio::Region* region = new Audio::SampleRegion(reader, 1, &audioFile);
                    Point<int> position = e.getPosition();
                    int x = position.getX();
                    
                    if (x > _mixerOffset)
                    {
                        int64 samplesRange = secondsToSamples(100, _sampleRate);
                        int64 positionSamples = pixelsToSamples(x - _mixerOffset, 100 * _pixelsPerClip, samplesRange);
                        
                        _track->add(positionSamples, region);
                        createRegionGUI(x, region, formatManager, audioFile);
                        getParentComponent()->resized();
                    }
                    else if (x < _mixerOffset)
                    {
                        _track->add(0, region);
                        createRegionGUI(_mixerOffset, region, formatManager, audioFile);
                        getParentComponent()->resized();
                    }
                }
            }
                break;
            case 2:
            {
                CriticalSection critical;
                critical.enter();
                for(size_t i = 0; i < _regionComponents.size(); ++i)
                {
                    
                    Rectangle<int> bounds_ = _regionComponents.at(i)->getBounds();
					posX = ev.x;
                    if((int)_regionComponents.at(i)->getPositionX() < posX && posX < ((int)_regionComponents.at(i)->getPositionX() + (int)_regionComponents.at(i)->getRegionWidth()))
                    {
                        _track->remove(_regionComponents.at(i)->getRegion(), _posX.at(i));
                        std::vector<RegionComponent*>::iterator regit = _regionComponents.begin() + i;
                        RegionComponent* component = _regionComponents.at(i);
                        removeChildComponent(_regionComponents.at(i));
                        _regionComponents.erase(regit);
                        delete component;
                        _regions.erase(_posX.at(i));
                        std::vector<int64>::iterator posit = _posX.begin() + i;;
                        _posX.erase(posit);
                        std::vector<int64>::iterator sampsit = _sizeSamps.begin() + i;;
                        _sizeSamps.erase(sampsit);
                    }
                }
                critical.exit();
            }
            default:
                break;
        }
    }
}