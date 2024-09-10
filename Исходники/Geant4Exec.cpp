 void createClientContext(const G4Event* evt)   {
   Geant4Event* e = new Geant4Event(evt,Geant4Random::instance());
   m_activeContext->setEvent(e);
 }