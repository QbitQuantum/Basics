int OCCTools::readSTEP(const char *filename, std::vector<OCCBase *>& shapes)
{
    try {
        STEPControl_Reader aReader;
        
        Interface_Static::SetCVal("xstep.cascade.unit","M");
        Interface_Static::SetIVal("read.step.nonmanifold", 1);
        
        if (aReader.ReadFile(filename) != IFSelect_RetDone) {
            StdFail_NotDone::Raise("Failed to read STEP file");
        }
        
        // Root transfers
        int nbr = aReader.NbRootsForTransfer();
        for (int n = 1; n<= nbr; n++) {
            aReader.TransferRoot(n);
        }
        
        // Collecting resulting entities
        int nbs = aReader.NbShapes();
        if (nbs == 0) return 1;
        
        for (int i=1; i<=nbs; i++) {
            const TopoDS_Shape& aShape = aReader.Shape(i);
            extractShape(aShape, shapes);
        }
    } catch(Standard_Failure &err) {
        Handle_Standard_Failure e = Standard_Failure::Caught();
        const Standard_CString msg = e->GetMessageString();
        //printf("ERROR: %s\n", e->GetMessageString());
        if (msg != NULL && strlen(msg) > 1) {
            setErrorMessage(msg);
        } else {
            setErrorMessage("Failed to read STEP file");
        }
        return 0;
    }
    return 1;
}