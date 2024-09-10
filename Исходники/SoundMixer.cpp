ILXSoundMixer::ILXSoundMixer(int argc, char* argv[])
        : Application(&argc, &argv, AppOptions(OptDaleAuto | OptSound)),
          _soundComponent(NULL),
          _music(NULL),
          _bandSliderFont(NULL)
{
    setMargin(20);
    setLayout(new VBoxLayout());

    _bandSliderFont = new Font("Sans", 8);

    HBoxLayout* volStuff = new HBoxLayout();
    addWidget(volStuff);
    TabPanel* panel = new TabPanel();
    volStuff->addWidget(panel);

    //**********
    HBoxLayout* volHBox = new HBoxLayout();
    panel->addTab(volHBox, "Volume Control");

    GridLayout* volGrid = new GridLayout(8, 3);
    volHBox->addWidget(volGrid);
    volGrid->addWidget(new Label("Master Volume:"), 0, 0, 0, 3);

    _masterVolume = new Slider();
    _masterVolume->setRange(0, 1);
    _masterVolume->setValue(SoundDFB::getMasterVolume());
    _masterVolume->setStep(0.1);
    _masterVolume->setPageStep(0.2);
    _masterVolume->setUpdateMode(Slider::UponRelease);
    _masterVolume->sigValueChanged.connect(sigc::mem_fun(this, &ILXSoundMixer::changeMasterVolume));
    volGrid->addWidget(_masterVolume, 1, 0, 0, 2);

    _mute = new PushButton("Mute");
    _mute->setXConstraint(FixedConstraint);
    volGrid->addWidget(_mute, 1, 2);
    _mute->sigClicked.connect(sigc::mem_fun(this, &ILXSoundMixer::mute));

    volGrid->addWidget(new Label("Sound Effects:"), 2, 0, 0, 3);
    _effectsVolume = new Slider();
    _effectsVolume->setRange(0, 1);
    _effectsVolume->setValue(1);
    _effectsVolume->setStep(0.1);
    _effectsVolume->setPageStep(0.2);
    _effectsVolume->setUpdateMode(Slider::UponRelease);
    _effectsVolume->sigValueChanged.connect(sigc::mem_fun(this, &ILXSoundMixer::changeEffectsVolume));
    volGrid->addWidget(_effectsVolume, 3, 0, 0, 2);

    volGrid->addWidget(new Label("Balance:"), 4, 0, 0, 3);

    volGrid->addWidget(new Label("Front"), 5, 0);
    Slider* frSlider = new Slider();
    frSlider->setValue(50);
    volGrid->addWidget(frSlider, 5, 1);
    volGrid->addWidget(new Label("Rear"), 5, 2);

    volGrid->addWidget(new Label("Left"), 6, 0);
    Slider* lrSlider = new Slider();
    lrSlider->setValue(50);
    volGrid->addWidget(lrSlider, 6, 1);
    volGrid->addWidget(new Label("Right"), 6, 2);

    volGrid->addWidget(new Spacer(Vertical), 7, 0);

    GroupBox* volMeter = new GroupBox("Meter");
    VBoxLayout* volMeterLayout = new VBoxLayout();
    volMeterLayout->setHorizontalAlignment(Alignment::Center);
    volMeter->setLayout(volMeterLayout);
    volMeter->setXConstraint(FixedConstraint);
    volStuff->addWidget(volMeter);
    VolumeMeter* meter = new VolumeMeter();
    volMeter->addWidget(meter);
    volHBox->addWidget(volMeter);

    //*********
    VBoxLayout* eqBox = new VBoxLayout();
    panel->addTab(eqBox, "Equalizer");

    HBoxLayout* buttons = new HBoxLayout();
    buttons->addWidget(new CheckBox("EQ Enabled"));
    buttons->addWidget(new Spacer(Horizontal));
    buttons->addWidget(new PushButton("Load Preset"));
    buttons->addWidget(new PushButton("Save Preset"));
    PushButton* testSound = new PushButton("Test");
    testSound->sigClicked.connect(sigc::mem_fun(this, &ILXSoundMixer::playTestSound));
    buttons->addWidget(testSound);
    eqBox->addWidget(buttons);

    HBoxLayout* rowLevels = new HBoxLayout();
    rowLevels->setYConstraint(ExpandingConstraint);
    rowLevels->addWidget(new BandSlider("50Hz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("100Hz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("156Hz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("220Hz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("311Hz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("440Hz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("622Hz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("880Hz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("1.25KHz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("1.75KHz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("2.5KHz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("3.5KHz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("5KHz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("10KHz", _bandSliderFont));
    rowLevels->addWidget(new BandSlider("20KHz", _bandSliderFont));
    eqBox->addWidget(rowLevels);

#if ILIXI_HAVE_COMPOSITOR
    DaleDFB::comaGetComponent("SoundMixer", &_soundComponent);
    if (_soundComponent)
        _soundComponent->Listen(_soundComponent, SoundMixer::VolumeChanged, volumeListener, this);
#endif
    _music = new Music(ILIXI_DATADIR"soundmixer/test.wav");
    _music->setRepeat(true);

}