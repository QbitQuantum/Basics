// LibView
//---------------------------------------------------------------------------
LibView::LibView() : GameTemplateView()
{
    setSearchName("LibView");
    setTitle("Lib Stats");
    setSubTitle(" - F5");

    setAllowResize(false);
    setAllowMove(true);
    setDisplayStatusBar(false);
    setVisible(false);

    moveTo(0, 0);
    resize(325, 375);

    addButtonCenterText(iXY((getClientRect().getSize().x / 3) * 0, 0), getClientRect().getSize().x / 3, "Surface", "", bSurfaceInfo);
    addButtonCenterText(iXY((getClientRect().getSize().x / 3) * 1, 0), getClientRect().getSize().x / 3, "Particles", "", bParticleInfo);
    addButtonCenterText(iXY((getClientRect().getSize().x / 3) * 2, 0), getClientRect().getSize().x / 3, "Environment", "", bEnvironmentInfo);

    checkBoxAllowParticleGeneration = new CheckBox();
    checkBoxAllowParticleGeneration->setLabel("Allow Particle Generation");
    checkBoxAllowParticleGeneration->setLocation(0, 15);
    checkBoxAllowParticleGeneration->setState(Particle2D::getCreateParticles());
    add(checkBoxAllowParticleGeneration);

    checkBoxAllowTimeSlice = new CheckBox();
    checkBoxAllowTimeSlice->setLabel("Allow Time Slice");
    checkBoxAllowTimeSlice->setLocation(0, 30);
    checkBoxAllowTimeSlice->setState(gTimeSliceFlag);
    add(checkBoxAllowTimeSlice);

    checkBoxAllowSpanBlitting = new CheckBox();
    checkBoxAllowSpanBlitting->setLabel("Allow Blended Span Blitting");
    checkBoxAllowSpanBlitting->setLocation(0, 45);
    checkBoxAllowSpanBlitting->setState(allowSpanBlitting);
    add(checkBoxAllowSpanBlitting);

    checkBoxParticlesCanHaveSmoke = new CheckBox();
    checkBoxParticlesCanHaveSmoke->setLabel("Allow Explosion Particle Smoke");
    checkBoxParticlesCanHaveSmoke->setLocation(0, 60);
    checkBoxParticlesCanHaveSmoke->setState(ParticleInterface::gParticlesCanHaveSmoke);
    add(checkBoxParticlesCanHaveSmoke);

    checkBoxSolidColorExplosionParticles = new CheckBox();
    checkBoxSolidColorExplosionParticles->setLabel("Solid Color Explosion Particles");
    checkBoxSolidColorExplosionParticles->setLocation(0, 75);
    checkBoxSolidColorExplosionParticles->setState(ParticleInterface::gSolidColorExplosionParticles);
    add(checkBoxSolidColorExplosionParticles);

    checkBoxParticleInterfaceSim = new CheckBox();
    checkBoxParticleInterfaceSim->setLabel("Particle Interface Sim");
    checkBoxParticleInterfaceSim->setLocation(0, 90);
    checkBoxParticleInterfaceSim->setState(ParticleInterface::gTestSim);
    add(checkBoxParticleInterfaceSim);

    checkBoxSolidBackground = new CheckBox();
    checkBoxSolidBackground->setLabel("Solid Background");
    checkBoxSolidBackground->setLocation(0, 105);
    checkBoxSolidBackground->setState(GameView::gDrawSolidBackground);
    add(checkBoxSolidBackground);

    checkBoxDrawExplosionParticleCount = new CheckBox();
    checkBoxDrawExplosionParticleCount->setLabel("Draw Explosion Particle Count");
    checkBoxDrawExplosionParticleCount->setLocation(0, 120);
    checkBoxDrawExplosionParticleCount->setState(ParticleInterface::gDrawExplosionParticleCount);
    add(checkBoxDrawExplosionParticleCount);

} // end LibView::LibView