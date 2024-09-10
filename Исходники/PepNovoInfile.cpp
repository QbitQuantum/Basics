  String PepNovoInfile::handlePTMs_(const String& modification, const bool variable)
  {
    String locations, key, type;

    ResidueModification::TermSpecificity ts = ModificationsDB::getInstance()->getModification(modification).getTermSpecificity();
    String origin = ModificationsDB::getInstance()->getModification(modification).getOrigin();
    double mass = ModificationsDB::getInstance()->getModification(modification).getDiffMonoMass();
    String full_name = ModificationsDB::getInstance()->getModification(modification).getFullName();
    String full_id = ModificationsDB::getInstance()->getModification(modification).getFullId();


    if (variable)
    {
      type = "OPTIONAL";
    }
    else
    {
      type = "FIXED";
    }

    switch (ts)
    {
    case ResidueModification::C_TERM: locations = "C_TERM";
      break;

    case ResidueModification::N_TERM: locations = "N_TERM";
      break;

    case ResidueModification::ANYWHERE: locations = "ALL";
      break;

    default: throw Exception::InvalidValue(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION, "Invalid term specificity", String(ts));
    }

    if (ts == ResidueModification::C_TERM)
    {
      key = "$";
    }
    else if (ts == ResidueModification::N_TERM)
    {
      key = "^";
    }

    //cout<<"origin: "<<origin<<"    loc: "<<locations<<endl;
    if ((ts == ResidueModification::C_TERM) && (origin == "X"))
    {
      origin = "C_TERM";
    }
    else if ((ts == ResidueModification::N_TERM) && (origin == "X"))
    {
      origin = "N_TERM";
    }
    else
    {
      key = origin;
    }

    if (mass >= 0)
    {
      key += "+" + String(Math::round(mass));
    }
    else
    {
      key += String(Math::round(mass));
    }

    String line = "";
    line += origin.toUpper();
    line += "\t";
    line += mass;
    line += "\t";
    line += type;
    line += "\t";
    line += locations;
    line += "\t";
    line += key;
    line += "\t";
    line += full_name;

    mods_and_keys_[key] = full_id;

    return line;
  }