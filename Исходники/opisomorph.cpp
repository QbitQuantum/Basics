bool MakeQueriesFromMolInFile(vector<OBQuery*>& queries, const std::string& filename, int* pnAtoms, bool noH)
{
    OBMol patternMol;
    patternMol.SetIsPatternStructure();
    OBConversion patternConv;
    OBFormat* pFormat;
    //Need to distinguish between filename and SMARTS. Not infallable...
    if( filename.empty() ||
        filename.find('.')==string::npos ||
        !(pFormat = patternConv.FormatFromExt(filename.c_str())) ||
        !patternConv.SetInFormat(pFormat) ||
        !patternConv.ReadFile(&patternMol, filename) ||
        patternMol.NumAtoms()==0)
      return false;

    if(noH)
      patternMol.DeleteHydrogens();

    do
    {
      *pnAtoms = patternMol.NumHvyAtoms();
      queries.push_back(CompileMoleculeQuery(&patternMol));
    }while(patternConv.Read(&patternMol));
    return true;
}