SALOME_WNT_EXPORT
  TopoDS_Shape ImportIGES (const TCollection_AsciiString& theFileName,
                       const TCollection_AsciiString& theFormatName,
                       TCollection_AsciiString&       theError,
		               const TDF_Label&               theShapeLabel)
  {
    IGESControl_Reader aReader;
    TopoDS_Shape aResShape;
    Interface_Static::SetCVal("xstep.cascade.unit","M");
    try {
      IFSelect_ReturnStatus status = aReader.ReadFile(theFileName.ToCString());

      if (status == IFSelect_RetDone) {

        if( theFormatName == "IGES_UNIT" ) {
	  Handle(IGESData_IGESModel) aModel = 
	    Handle(IGESData_IGESModel)::DownCast(aReader.Model());
	  gp_Pnt P(1.0,0.0,0.0);
	  if(!aModel.IsNull()) {
	    Handle(TCollection_HAsciiString) aUnitName = 
	      aModel->GlobalSection().UnitName();
	    //cout<<"aUnitName = "<<aUnitName->ToCString()<<endl;
	    //cout<<"aUnitFlag = "<<aModel->GlobalSection().UnitFlag()<<endl;
	    if( aUnitName->String()=="MM" ) {
	      P = gp_Pnt(0.001,0.0,0.0);
	    }
	    else if( aUnitName->String()=="CM" ) {
	      P = gp_Pnt(0.01,0.0,0.0);
	    }
	  }
	  BRep_Builder B;
	  TopoDS_Vertex V;
	  B.MakeVertex(V,P,1.e-7);
	  aResShape = V;
	  return aResShape;
	}
	if( theFormatName == "IGES_SCALE" ) {
	  //cout<<"need re-scale a model"<<endl;
	  // set UnitFlag to 'meter'
	  Handle(IGESData_IGESModel) aModel = 
	    Handle(IGESData_IGESModel)::DownCast(aReader.Model());
	  if(!aModel.IsNull()) {
	    IGESData_GlobalSection aGS = aModel->GlobalSection();
	    aGS.SetUnitFlag(6);
	    aModel->SetGlobalSection(aGS);
	  }
	}

        MESSAGE("ImportIGES : all Geometry Transfer");
        //OCC 5.1.2 porting
        //     aReader.Clear();
        //     aReader.TransferRoots(false);
        aReader.ClearShapes();
        aReader.TransferRoots();

        MESSAGE("ImportIGES : count of shapes produced = " << aReader.NbShapes());
        aResShape = aReader.OneShape();

        // BEGIN: Store names of sub-shapes from file
        Handle(Interface_InterfaceModel) Model = aReader.WS()->Model();
        Handle(XSControl_TransferReader) TR = aReader.WS()->TransferReader();
        if (!TR.IsNull()) {
          Handle(Transfer_TransientProcess) TP = /*TransientProcess();*/TR->TransientProcess();
          Standard_Integer nb = Model->NbEntities();
          for (Standard_Integer i = 1; i <= nb; i++) {
            Handle(IGESData_IGESEntity) ent = Handle(IGESData_IGESEntity)::DownCast(Model->Value(i));
            if (ent.IsNull() || ! ent->HasName()) continue;

            // find target shape
            Handle(Transfer_Binder) binder = TP->Find(ent);
            if (binder.IsNull()) continue;
            TopoDS_Shape S = TransferBRep::ShapeResult(binder);
            if (S.IsNull()) continue;

            // create label and set shape
            TDF_Label L;
            TDF_TagSource aTag;
            L = aTag.NewChild(theShapeLabel);
            TNaming_Builder tnBuild (L);
            tnBuild.Generated(S);

            // set a name
            TCollection_AsciiString string = ent->NameValue()->String();
            string.LeftAdjust();
            string.RightAdjust();
            TCollection_ExtendedString str (string);
            TDataStd_Name::Set(L, str);
          }
        }
        // END: Store names
      } else {
//        switch (status) {
//        case IFSelect_RetVoid:
//          theError = "Nothing created or No data to process";
//          break;
//        case IFSelect_RetError:
//          theError = "Error in command or input data";
//          break;
//        case IFSelect_RetFail:
//          theError = "Execution was run, but has failed";
//          break;
//        case IFSelect_RetStop:
//          theError = "Execution has been stopped. Quite possible, an exception was raised";
//          break;
//        default:
//          break;
//        }
        theError = "Wrong format of the imported file. Can't import file.";
	aResShape.Nullify();
      }
    }
    catch(Standard_Failure) {
      Handle(Standard_Failure) aFail = Standard_Failure::Caught();
      theError = aFail->GetMessageString();
      aResShape.Nullify();
    }
    return aResShape;
  }