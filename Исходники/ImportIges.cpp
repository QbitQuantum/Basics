int Part::ImportIgesParts(App::Document *pcDoc, const char* FileName)
{
    try {
        Base::FileInfo fi(FileName);
        // read iges file
        // http://www.opencascade.org/org/forum/thread_20801/
        IGESControl_Controller::Init();
        Interface_Static::SetIVal("read.surfacecurve.mode",3);

        // load data exchange message files
        Message_MsgFile::LoadFromEnv("CSF_XSMessage","IGES");

        // load shape healing message files
        Message_MsgFile::LoadFromEnv("CSF_SHMessageStd","SHAPEStd");

        IGESControl_Reader aReader;
        if (aReader.ReadFile((const Standard_CString)FileName) != IFSelect_RetDone)
            throw Base::Exception("Error in reading IGES");

        // check file conformity and output stats
        aReader.PrintCheckLoad(Standard_True,IFSelect_GeneralInfo);

#if 1
        std::string aName = fi.fileNamePure();
        Handle_Message_ProgressIndicator pi = new ProgressIndicator(100);
        pi->NewScope(100, "Reading IGES file...");
        pi->Show();
        aReader.WS()->MapReader()->SetProgress(pi);

        // make model
        aReader.ClearShapes();
        Standard_Integer nbRootsForTransfer = aReader.NbRootsForTransfer();
        aReader.TransferRoots();
        pi->EndScope();

        // put all other free-flying shapes into a single compound
        Standard_Boolean emptyComp = Standard_True;
        BRep_Builder builder;
        TopoDS_Compound comp;
        builder.MakeCompound(comp);

        Standard_Integer nbShapes = aReader.NbShapes();
        for (Standard_Integer i=1; i<=nbShapes; i++) {
            TopoDS_Shape aShape = aReader.Shape(i);
            if (!aShape.IsNull()) {
                if (aShape.ShapeType() == TopAbs_SOLID ||
                    aShape.ShapeType() == TopAbs_COMPOUND ||
                    aShape.ShapeType() == TopAbs_SHELL) {
                        App::DocumentObject* obj = pcDoc->addObject("Part::Feature", aName.c_str());
                        static_cast<Part::Feature*>(obj)->Shape.setValue(aShape);
                }
                else {
                    builder.Add(comp, aShape);
                    emptyComp = Standard_False;
                }
            }
        }
        if (!emptyComp) {
            std::string name = fi.fileNamePure();
            Part::Feature *pcFeature = static_cast<Part::Feature*>(pcDoc->addObject
                ("Part::Feature", name.c_str()));
            pcFeature->Shape.setValue(comp);
        }
#else
        // put all other free-flying shapes into a single compound
        Standard_Boolean emptyComp = Standard_True;
        BRep_Builder builder;
        TopoDS_Compound comp;
        builder.MakeCompound(comp);

        // get all entities
        Handle_TColStd_HSequenceOfTransient aRootList=aReader.GiveList("xst-transferrable-roots");
        Base::SequencerLauncher seq("Reading IGES file...", aRootList->Length());
        Standard_Integer j;
        for (j=1; j<=aRootList->Length(); j++) {
            seq.next();
            Handle(IGESData_IGESEntity) igesEntity = Handle(IGESData_IGESEntity)::DownCast(aRootList->Value(j));
            if (igesEntity.IsNull()) continue;
            // clear any old shape
            aReader.ClearShapes();

#ifdef _DEBUG
            std::string type = igesEntity->DynamicType()->Name();
            (void)type;
#endif
            
            // is it a group, singular sub-figure or solid?
            if (igesEntity->IsKind(STANDARD_TYPE(IGESBasic_Group)) ||
                igesEntity->IsKind(STANDARD_TYPE(IGESBasic_SingularSubfigure)) || 
                igesEntity->IsKind(STANDARD_TYPE(IGESSolid_ManifoldSolid))) {
                try {
                    if (aReader.TransferEntity(igesEntity)) {
                        if (aReader.NbShapes()>0) {
                            // get the shape
                            std::string aName = fi.fileNamePure();
                            if (igesEntity->HasShortLabel()) {
                                Handle(TCollection_HAsciiString) aLabel=igesEntity->ShortLabel();
                                aName = aLabel->ToCString();
                            }
                            TopoDS_Shape aShape=aReader.OneShape();
                            App::DocumentObject* obj = pcDoc->addObject("Part::Feature", aName.c_str());
                            obj->Label.setValue(aName);
                            static_cast<Part::Feature*>(obj)->Shape.setValue(aShape);
                            int iColor;
                            if (igesEntity->RankColor()>-1) {
                                iColor = igesEntity->RankColor();
                            }
                        }
                    }
                }
                catch (Standard_Failure) {
                }
            }
            // normal shapes
            else {
                try {
                    if (aReader.TransferEntity(igesEntity)) {
                        if (aReader.NbShapes()>0) {
                            TopoDS_Shape aShape=aReader.OneShape();
                            builder.Add(comp, aShape);
                            emptyComp = Standard_False;
                        }
                    }
                }
                catch (Standard_Failure) {
                }
            }
        }

        if (!emptyComp) {
            std::string name = fi.fileNamePure();
            Part::Feature *pcFeature = static_cast<Part::Feature*>(pcDoc->addObject
                ("Part::Feature", name.c_str()));
            pcFeature->Shape.setValue(comp);
        }
#endif
    }
    catch (Standard_Failure) {
        Handle(Standard_Failure) aFail = Standard_Failure::Caught();
        throw Base::Exception(aFail->GetMessageString());
    }

    return 0;
}