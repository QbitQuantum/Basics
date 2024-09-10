int Part::ImportStepParts(App::Document *pcDoc, const char* Name)
{
    STEPControl_Reader aReader;
    TopoDS_Shape aShape;
    Base::FileInfo fi(Name);

    if (!fi.exists()) {
        std::stringstream str;
        str << "File '" << Name << "' does not exist!";
        throw Base::Exception(str.str().c_str());
    }
    std::string encodednamestr = encodeFilename(std::string(Name));
    const char * encodedname = encodednamestr.c_str();

    if (aReader.ReadFile((Standard_CString)encodedname) != 
            IFSelect_RetDone) {
        throw Base::Exception("Cannot open STEP file");
    }

    Handle_Message_ProgressIndicator pi = new ProgressIndicator(100);
    aReader.WS()->MapReader()->SetProgress(pi);
    pi->NewScope(100, "Reading STEP file...");
    pi->Show();

    // Root transfers
    Standard_Integer nbr = aReader.NbRootsForTransfer();
    //aReader.PrintCheckTransfer (failsonly, IFSelect_ItemsByEntity);
    for (Standard_Integer n = 1; n<= nbr; n++) {
        Base::Console().Log("STEP: Transferring Root %d\n",n);
        aReader.TransferRoot(n);
    }
    pi->EndScope();

    // Collecting resulting entities
    Standard_Integer nbs = aReader.NbShapes();
    if (nbs == 0) {
        throw Base::Exception("No shapes found in file ");
    }
    else {
        //Handle(StepData_StepModel) Model = aReader.StepModel();
        //Handle_XSControl_WorkSession ws = aReader.WS();
        //Handle_XSControl_TransferReader tr = ws->TransferReader();

        std::map<int, Quantity_Color> hash_col;
        //ReadColors(aReader.WS(), hash_col);
        //ReadNames(aReader.WS());

        for (Standard_Integer i=1; i<=nbs; i++) {
            Base::Console().Log("STEP:   Transferring Shape %d\n",i);
            aShape = aReader.Shape(i);

            // load each solid as an own object
            TopExp_Explorer ex;
            for (ex.Init(aShape, TopAbs_SOLID); ex.More(); ex.Next())
            {
                // get the shape 
                const TopoDS_Solid& aSolid = TopoDS::Solid(ex.Current());

                std::string name = fi.fileNamePure();
                //Handle_Standard_Transient ent = tr->EntityFromShapeResult(aSolid, 3);
                //if (!ent.IsNull()) {
                //    name += ws->Model()->StringLabel(ent)->ToCString();
                //}

                Part::Feature *pcFeature;
                pcFeature = static_cast<Part::Feature*>(pcDoc->addObject("Part::Feature", name.c_str()));
                pcFeature->Shape.setValue(aSolid);

                // This is a trick to access the GUI via Python and set the color property
                // of the associated view provider. If no GUI is up an exception is thrown
                // and cleared immediately
                std::map<int, Quantity_Color>::iterator it = hash_col.find(aSolid.HashCode(INT_MAX));
                if (it != hash_col.end()) {
                    try {
                        Py::Object obj(pcFeature->getPyObject(), true);
                        Py::Object vp(obj.getAttr("ViewObject"));
                        Py::Tuple col(3);
                        col.setItem(0, Py::Float(it->second.Red()));
                        col.setItem(1, Py::Float(it->second.Green()));
                        col.setItem(2, Py::Float(it->second.Blue()));
                        vp.setAttr("ShapeColor", col);
                        //Base::Console().Message("Set color to shape\n");
                    }
                    catch (Py::Exception& e) {
                        e.clear();
                    }
                }
            }
            // load all non-solids now
            for (ex.Init(aShape, TopAbs_SHELL, TopAbs_SOLID); ex.More(); ex.Next())
            {
                // get the shape 
                const TopoDS_Shell& aShell = TopoDS::Shell(ex.Current());

                std::string name = fi.fileNamePure();
                //Handle_Standard_Transient ent = tr->EntityFromShapeResult(aShell, 3);
                //if (!ent.IsNull()) {
                //    name += ws->Model()->StringLabel(ent)->ToCString();
                //}

                Part::Feature *pcFeature = static_cast<Part::Feature*>(pcDoc->addObject("Part::Feature", name.c_str()));
                pcFeature->Shape.setValue(aShell);
            }

            // put all other free-flying shapes into a single compound
            Standard_Boolean emptyComp = Standard_True;
            BRep_Builder builder;
            TopoDS_Compound comp;
            builder.MakeCompound(comp);

            for (ex.Init(aShape, TopAbs_FACE, TopAbs_SHELL); ex.More(); ex.Next()) {
                if (!ex.Current().IsNull()) {
                    builder.Add(comp, ex.Current());
                    emptyComp = Standard_False;
                }
            }
            for (ex.Init(aShape, TopAbs_WIRE, TopAbs_FACE); ex.More(); ex.Next()) {
                if (!ex.Current().IsNull()) {
                    builder.Add(comp, ex.Current());
                    emptyComp = Standard_False;
                }
            }
            for (ex.Init(aShape, TopAbs_EDGE, TopAbs_WIRE); ex.More(); ex.Next()) {
                if (!ex.Current().IsNull()) {
                    builder.Add(comp, ex.Current());
                    emptyComp = Standard_False;
                }
            }
            for (ex.Init(aShape, TopAbs_VERTEX, TopAbs_EDGE); ex.More(); ex.Next()) {
                if (!ex.Current().IsNull()) {
                    builder.Add(comp, ex.Current());
                    emptyComp = Standard_False;
                }
            }

            if (!emptyComp) {
                std::string name = fi.fileNamePure();
                Part::Feature *pcFeature = static_cast<Part::Feature*>(pcDoc->addObject
                    ("Part::Feature", name.c_str()));
                pcFeature->Shape.setValue(comp);
            }
        }
    }

    return 0;
}