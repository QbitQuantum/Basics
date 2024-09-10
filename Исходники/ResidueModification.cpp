  void ResidueModification::setSourceClassification(const String & classification)
  {
    String c = classification;
    c.toLower();
    if (c == "artifact" || c == "artefact") // unimod uses Artefact (BE) not Artifact (AE)
    {
      classification_ = ARTIFACT;
      return;
    }
    if (c == "natural")
    {
      classification_ = NATURAL;
      return;
    }
    if (c == "hypothetical")
    {
      classification_ = HYPOTHETICAL;
      return;
    }
    if (c == "post-translational")
    {
      classification_ = POSTTRANSLATIONAL;
      return;
    }
    if (c == "multiple")
    {
      classification_ = MULTIPLE;
      return;
    }
    if (c == "chemical derivative")
    {
      classification_ = CHEMICAL_DERIVATIVE;
      return;
    }
    if (c == "isotopic label")
    {
      classification_ = ISOTOPIC_LABEL;
      return;
    }
    if (c == "pre-translational")
    {
      classification_ = PRETRANSLATIONAL;
      return;
    }
    if (c == "other glycosylation")
    {
      classification_ = OTHER_GLYCOSYLATION;
      return;
    }
    if (c == "n-linked glycosylation")
    {
      classification_ = NLINKED_GLYCOSYLATION;
      return;
    }
    if (c == "aa substitution")
    {
      classification_ = AA_SUBSTITUTION;
      return;
    }
    if (c == "other")
    {
      classification_ = OTHER;
      return;
    }
    if (c == "non-standard residue")
    {
      classification_ = NONSTANDARD_RESIDUE;
      return;
    }
    if (c == "co-translational")
    {
      classification_ = COTRANSLATIONAL;
      return;
    }
    if (c == "o-linked glycosylation")
    {
      classification_ = OLINKED_GLYCOSYLATION;
      return;
    }

    classification_ = UNKNOWN;

    //cerr << "ResidueModification: Unknown source classification '" << classification << "'" << endl;
    return;
  }