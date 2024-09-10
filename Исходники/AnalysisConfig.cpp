void AnalysisConfig::processBinString(vector<pair<float,float> >& binSet, string& inputString)
{
    binSet.clear();

  // Define a regex expression to use to match strings of (float, float) format and a size variable to pass as the size of the resulting match.
    TRegexp numPairRegex("\\(-?[0-9]+\\.?[0-9]?,-?[0-9]+\\.?[0-9]?\\)");
    int* matchLength = new int;

  // Get list of bin strings from input string.
    vector<string> binStrings;
    getListFromString(inputString, binStrings);

  // Extract number information from list of bin strings (Should have format: (i,j) ).
    for(auto& binStr : binStrings)
    {
      // Check if the bin string is a formatted properly.
        *matchLength = 0;
        if(numPairRegex.Index(binStr, matchLength) != 0 || (unsigned int)(*matchLength) != binStr.length())
        { // If the regex expression doesn't find itself in the string *OR* the matched string isn't the full length of the input string...
            cout << "  ERROR (AnalysisConfig::processBinString)\n: Bin string does not have (p,q) format: " << binStr << endl << endl;
            return;     // KICK
        }

        float binMin, binMax;
        TString numStr = "";
        string::iterator it=binStr.begin()+1;

      // Extract bin minimum value
        do{ numStr+=*(it++); } while( it != binStr.end() && *it != ',');
        binMin = numStr.Atof();

     // Extract bin maximum value
        numStr = ""; it++;  // Reset bin number string and move past the comma
        do{ numStr+=*(it++); } while( it != binStr.end() && *it != ')');
        binMax = numStr.Atof();

      // Add pair to bin set.
        binSet.push_back({binMin, binMax});
    }
}