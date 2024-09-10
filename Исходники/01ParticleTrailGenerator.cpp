 virtual void keyPressed(const KeyEventUnrecPtr e)
 {
     if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
     {
         TutorialWindow->closeWindow();
     }
     else
     {
         switch(e->getKey())
         {
             case KeyEvent::KEY_B:
                 {	// check if the burst generator is null
                     if(ExampleBurstGen == NULL)
                     {
                         ExampleBurstGen = OSG::BurstParticleGenerator::create();
                         ExampleBurstGen->setPositionDistribution(createPositionDistribution());
                         ExampleBurstGen->setBurstAmount(20);
                         ExampleBurstGen->setVelocityDistribution(createVelocityDistribution());
                         ExampleBurstGen->setNormalDistribution(createNormalDistribution());
                         ExampleBurstGen->setLifespanDistribution(createLifespanDistribution());
                         ExampleBurstGen->setSizeDistribution(createSizeDistribution());
                     }
                     // attach the burst generator
                     ExampleParticleSystem->pushToGenerators(ExampleBurstGen);
                 }
                 break;
             case KeyEvent::KEY_P:
                 {	// increase trail resolution
                     ExampleTrailGenerator->setTrailResolution(ExampleTrailGenerator->getTrailResolution() * 0.70 + 0.0001);
                     std::cout << "Trail Resolution:  " << ExampleTrailGenerator->getTrailResolution() << std::endl;
                     break;
                 }
             case KeyEvent::KEY_L:
                 {	// decrease trail resolution
                     ExampleTrailGenerator->setTrailResolution(ExampleTrailGenerator->getTrailResolution() * 1.25);
                     std::cout << "Trail Resolution:  " << ExampleTrailGenerator->getTrailResolution() << std::endl;
                     break;
                 }
             case KeyEvent::KEY_O:
                 {	// increase trail length
                     ExampleTrailGenerator->setTrailLength(ExampleTrailGenerator->getTrailLength() * 1.25 + 0.1);
                     std::cout << "Trail Length:  " << ExampleTrailGenerator->getTrailLength() << std::endl;
                     break;
                 }
             case KeyEvent::KEY_K:
                 {	// decrease trail length
                     ExampleTrailGenerator->setTrailLength(ExampleTrailGenerator->getTrailLength() * 0.7);
                     std::cout << "Trail Length:  " << ExampleTrailGenerator->getTrailLength() << std::endl;
                     break;
                 }
             case KeyEvent::KEY_I:
                 {	// toggle lines/points as trail draw method
                     ExampleTrailGenerator->setDrawMethod((ExampleTrailGenerator->getDrawMethod() == SimpleParticleTrailGenerator::LINES)?
                                                          (SimpleParticleTrailGenerator::POINTS):(SimpleParticleTrailGenerator::LINES));
                     break;
                 }
             case KeyEvent::KEY_J:
                 {	// toggle trail length method
                     ExampleTrailGenerator->setTrailLengthMethod((ExampleTrailGenerator->getTrailLengthMethod() == ParticleTrailGenerator::NUM_POINTS)?
                                                                 (ParticleTrailGenerator::TIME):(ParticleTrailGenerator::NUM_POINTS));
                     std::cout << "Trail Length: " << (ExampleTrailGenerator->getTrailLengthMethod() == ParticleTrailGenerator::NUM_POINTS ? "Num Pts":"Time") << std::endl;
                     break;
                 }
             case KeyEvent::KEY_Y:
                 {	// toggle trail spacing method
                     ExampleTrailGenerator->setTrailResolutionMethod((ExampleTrailGenerator->getTrailResolutionMethod() == ParticleTrailGenerator::TIME_SPACING)?
                                                                     (ParticleTrailGenerator::DISTANCE_SPACING):(ParticleTrailGenerator::TIME_SPACING));
                     std::cout << "Trail resolution: " <<(ExampleTrailGenerator->getTrailResolutionMethod() == ParticleTrailGenerator::TIME_SPACING ? "Time Spacing" : "Distance Spacing") << std::endl;
                     break;
                 }
             case KeyEvent::KEY_V:
                 {
                     mgr->getRenderAction()->setVolumeDrawing(!mgr->getRenderAction()->getVolumeDrawing());
                 }
         }
     }
 }