int StepShape::read(const char* fileName)
{
    STEPControl_Reader aReader;

    Base::FileInfo fi(fileName);

    if (!fi.exists()) {
        std::stringstream str;
        str << "File '" << fileName << "' does not exist!";
        throw Base::FileException(str.str().c_str());
    }

    if (aReader.ReadFile((Standard_CString)fileName) != IFSelect_RetDone) {
        throw Base::FileException("Cannot open STEP file");
    }

    //Standard_Integer ic = Interface_Static::IVal("read.precision.mode"); 
    //Standard_Real rp = Interface_Static::RVal("read.maxprecision.val"); 
    //Standard_Integer ic = Interface_Static::IVal("read.maxprecision.mode"); 
    //Standard_Integer mv = Interface_Static::IVal("read.stdsameparameter.mode"); 
    //Standard_Integer rp = Interface_Static::IVal("read.surfacecurve.mode"); 
    //Standard_Real era = Interface_Static::RVal("read.encoderegularity.angle"); 
    //Standard_Integer ic = Interface_Static::IVal("read.step.product.mode"); 
    //Standard_Integer ic = Interface_Static::IVal("read.step.product.context");
    //Standard_Integer ic = Interface_Static::IVal("read.step.shape.repr"); 
    //Standard_Integer ic = Interface_Static::IVal("read.step.assembly.level");
    //Standard_Integer ic = Interface_Static::IVal("read.step.shape.relationship");
    //Standard_Integer ic = Interface_Static::IVal("read.step.shape.aspect"); 

    Handle(TColStd_HSequenceOfTransient) list = aReader.GiveList(); 

    //Use method StepData_StepModel::NextNumberForLabel to find its rank with the following:
    //Standard_CString label = "#...";
    Handle(StepData_StepModel) model = aReader.StepModel();
    //rank = model->NextNumberForLabe(label, 0, Standard_False);

    Handle(Message_PrinterOStream) mstr = new Message_PrinterOStream();
    Handle(Message_Messenger) msg = new Message_Messenger(mstr);

    std::cout << "dump of step header:" << std::endl;

    model->DumpHeader(msg);

    for(int nent=1;nent<=model->NbEntities();nent++) {
      Handle(Standard_Transient) entity=model->Entity(nent);
      
      std::cout << "label entity " << nent << ":" ;
      model->PrintLabel(entity,msg);
      std::cout << ";"<< entity->DynamicType()->Name() << std::endl;
    }

    return 0;
}