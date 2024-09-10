  String XQuestResultXMLFile::getxQuestBase64EncodedSpectrum_(const PeakSpectrum& spec, String header)
  {
    std::vector<String> in_strings;
    StringList sl;

    double precursor_mz = 0;
    double precursor_z = 0;
    if (spec.getPrecursors().size() > 0)
    {
      precursor_mz = Math::roundDecimal(spec.getPrecursors()[0].getMZ(), -9);
      precursor_z = spec.getPrecursors()[0].getCharge();
    }

    // header lines
    if (!header.empty()) // common or xlinker spectrum will be reported
    {
      sl.push_back(header + "\n"); // e.g. GUA1372-S14-A-LRRK2_DSS_1A3.03873.03873.3.dta,GUA1372-S14-A-LRRK2_DSS_1A3.03863.03863.3.dta
      sl.push_back(String(precursor_mz) + "\n");
      sl.push_back(String(precursor_z) + "\n");
    }
    else // light or heavy spectrum will be reported
    {
      sl.push_back(String(precursor_mz) + "\t" + String(precursor_z) + "\n");
    }

    PeakSpectrum::IntegerDataArray charges;
    if (spec.getIntegerDataArrays().size() > 0)
    {
      charges = spec.getIntegerDataArrays()[0];
    }

    // write peaks
    for (Size i = 0; i != spec.size(); ++i)
    {
      String s;
      s += String(Math::roundDecimal(spec[i].getMZ(), -9)) + "\t";
      s += String(spec[i].getIntensity()) + "\t";

      if (charges.size() > 0)
      {
        s += String(charges[i]);
      }
      else
      {
        s += "0";
      }

      s += "\n";

      sl.push_back(s);
    }

    String out;
    out.concatenate(sl.begin(), sl.end(), "");
    in_strings.push_back(out);

    String out_encoded;
    Base64().encodeStrings(in_strings, out_encoded, false, false);
    String out_wrapped;
    wrap_(out_encoded, 76, out_wrapped);
    return out_wrapped;
  }