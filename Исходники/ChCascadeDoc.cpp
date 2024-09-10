bool ChCascadeDoc::Load_STEP(const char* filename) {
    STEPCAFControl_Reader cafreader;

    if (!Interface_Static::SetCVal("xstep.cascade.unit", "M"))
        GetLog() << "\n\n ERROR SETTING 'M' UNITS!!!..   \n\n\n";

    IFSelect_ReturnStatus aStatus = cafreader.ReadFile(filename);

    if (aStatus == IFSelect_RetDone) {
        Standard_Boolean aRes = cafreader.Transfer((*doc));
        return true;
    }
    return false;
}