static PyObject * importer(PyObject *self, PyObject *args)
{
    char* Name;
    char* DocName=0;
    if (!PyArg_ParseTuple(args, "s|s",&Name,&DocName))
        return 0;

    PY_TRY {
        //Base::Console().Log("Insert in Part with %s",Name);
        Base::FileInfo file(Name);

        App::Document *pcDoc = 0;
        if (DocName) {
            pcDoc = App::GetApplication().getDocument(DocName);
        }
        if (!pcDoc) {
            pcDoc = App::GetApplication().newDocument("Unnamed");
        }

        Handle(XCAFApp_Application) hApp = XCAFApp_Application::GetApplication();
        Handle(TDocStd_Document) hDoc;
        hApp->NewDocument(TCollection_ExtendedString("MDTV-CAF"), hDoc);

        if (file.hasExtension("stp") || file.hasExtension("step")) {
            try {
                STEPCAFControl_Reader aReader;
                aReader.SetColorMode(true);
                aReader.SetNameMode(true);
                aReader.SetLayerMode(true);
                QString fn = QString::fromUtf8(Name);
                if (aReader.ReadFile((const char*)fn.toLocal8Bit()) != IFSelect_RetDone) {
                    PyErr_SetString(PyExc_Exception, "cannot read STEP file");
                    return 0;
                }

                Handle_Message_ProgressIndicator pi = new Part::ProgressIndicator(100);
                aReader.Reader().WS()->MapReader()->SetProgress(pi);
                pi->NewScope(100, "Reading STEP file...");
                pi->Show();
                aReader.Transfer(hDoc);
                pi->EndScope();
            }
            catch (OSD_Exception) {
                Handle_Standard_Failure e = Standard_Failure::Caught();
                Base::Console().Error("%s\n", e->GetMessageString());
                Base::Console().Message("Try to load STEP file without colors...\n");

                Part::ImportStepParts(pcDoc,Name);
                pcDoc->recompute();
            }
        }
        else if (file.hasExtension("igs") || file.hasExtension("iges")) {
            try {
                IGESControl_Controller::Init();
                Interface_Static::SetIVal("read.surfacecurve.mode",3);
                IGESCAFControl_Reader aReader;
                aReader.SetColorMode(true);
                aReader.SetNameMode(true);
                aReader.SetLayerMode(true);
                QString fn = QString::fromUtf8(Name);
                if (aReader.ReadFile((const char*)fn.toLocal8Bit()) != IFSelect_RetDone) {
                    PyErr_SetString(PyExc_Exception, "cannot read IGES file");
                    return 0;
                }

                Handle_Message_ProgressIndicator pi = new Part::ProgressIndicator(100);
                aReader.WS()->MapReader()->SetProgress(pi);
                pi->NewScope(100, "Reading IGES file...");
                pi->Show();
                aReader.Transfer(hDoc);
                pi->EndScope();
            }
            catch (OSD_Exception) {
                Handle_Standard_Failure e = Standard_Failure::Caught();
                Base::Console().Error("%s\n", e->GetMessageString());
                Base::Console().Message("Try to load IGES file without colors...\n");

                Part::ImportIgesParts(pcDoc,Name);
                pcDoc->recompute();
            }
        }
        else {
            PyErr_SetString(PyExc_Exception, "no supported file format");
            return 0;
        }

        ImportOCAFExt ocaf(hDoc, pcDoc, file.fileNamePure());
        ocaf.loadShapes();
        pcDoc->recompute();
    }
    catch (Standard_Failure) {