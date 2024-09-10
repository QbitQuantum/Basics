GLDemo::GLDemo(int argc, char* argv[])
        : Application(&argc, &argv)
{
    appWindow()->setCustomCompose(true);
    setLayout(new VBoxLayout());

    _glesExample = new GLTri();
    _glesExample->setConstraints(ExpandingConstraint, ExpandingConstraint);
    addWidget(_glesExample);

    Frame* controls = new Frame();
    controls->setConstraints(ExpandingConstraint, MinimumConstraint);
    addWidget(controls);
    controls->setLayout(new HBoxLayout());

    _xSlider = new Slider();
    controls->addWidget(_xSlider);
    _xSlider->setRange(0, 360);
    _xSlider->sigValueChanged.connect(sigc::mem_fun(_glesExample, &GLTri::setX));

    _ySlider = new Slider();
    controls->addWidget(_ySlider);
    _ySlider->setRange(0, 360);
    _ySlider->sigValueChanged.connect(sigc::mem_fun(_glesExample, &GLTri::setY));

    _fps = new FPSCalculator();
}