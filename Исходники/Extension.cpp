  void XtalOptExtension::reemitMoleculeChanged(Structure *s) {
    // Make copy of Xtal to pass to editor
    Xtal *newXtal = NULL;
    MolecularXtal *newMXtal = NULL;
    if (MolecularXtal *sAsMXtal = qobject_cast<MolecularXtal *>(s)) {
      newXtal = newMXtal = new MolecularXtal();
      *newMXtal = *sAsMXtal;
      // Clean up the submolecules
      newMXtal->wrapAtomsToCell();
      QList<SubMolecule*> subs = newMXtal->subMolecules();
      for (QList<SubMolecule*>::iterator it = subs.begin(),
           it_end = subs.end(); it != it_end; ++it) {
        (*it)->makeCoherent();
      }
    }
    else {
      newXtal = new Xtal (*qobject_cast<Xtal*>(s));
    }
    // Reset filename to something unique
    newXtal->setFileName(s->fileName() + "/usermodified.cml");

    // Check for weirdness
    if (newXtal->numAtoms() != 0 && !newXtal->atom(0)) {
      qWarning() << "XtalOptExtension::reemitMoleculeChanged: Molecule is invalid (bad atoms) -- not sending to GLWidget";
      return;
    }
    if (GS_ISNAN(newXtal->getA()) ||
        GS_ISNAN(newXtal->getB()) ||
        GS_ISNAN(newXtal->getC()) ||
        GS_ISNAN(newXtal->getAlpha()) ||
        GS_ISNAN(newXtal->getBeta()) ||
        GS_ISNAN(newXtal->getGamma())) {
      qWarning() << "XtalOptExtension::reemitMoleculeChanged: Molecule is invalid (cell param is nan) -- not sending to GLWidget";
      return;
    }

    emit moleculeChanged(newXtal, Extension::DeleteOld);

    // If the draw tool is currently selected, switch to navigate
    Avogadro::Tool *currentTool =
        GLWidget::current()->toolGroup()->activeTool();
    if (currentTool->identifier().compare("Draw") == 0) {
      GLWidget::current()->toolGroup()->setActiveTool("Navigate");
    }
  }