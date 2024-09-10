App::DocumentObjectExecReturn *Sweep::execute(void)
{
    if (Sections.getSize() == 0)
        return new App::DocumentObjectExecReturn("No sections linked.");
    App::DocumentObject* spine = Spine.getValue();
    if (!(spine && spine->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId())))
        return new App::DocumentObjectExecReturn("No spine linked.");
    const std::vector<std::string>& subedge = Spine.getSubValues();

    TopoDS_Shape path;
    const Part::TopoShape& shape = static_cast<Part::Feature*>(spine)->Shape.getValue();
    if (!shape._Shape.IsNull()) {
        try {
            if (!subedge.empty()) {
                BRepBuilderAPI_MakeWire mkWire;
                for (std::vector<std::string>::const_iterator it = subedge.begin(); it != subedge.end(); ++it) {
                    TopoDS_Shape subshape = shape.getSubShape(it->c_str());
                    mkWire.Add(TopoDS::Edge(subshape));
                }
                path = mkWire.Wire();
            }
            else if (shape._Shape.ShapeType() == TopAbs_EDGE) {
                path = shape._Shape;
            }
            else if (shape._Shape.ShapeType() == TopAbs_WIRE) {
                BRepBuilderAPI_MakeWire mkWire(TopoDS::Wire(shape._Shape));
                path = mkWire.Wire();
            }
            else if (shape._Shape.ShapeType() == TopAbs_COMPOUND) {
                TopoDS_Iterator it(shape._Shape);
                for (; it.More(); it.Next()) {
                    if (it.Value().IsNull())
                        return new App::DocumentObjectExecReturn("In valid element in spine.");
                    if ((it.Value().ShapeType() != TopAbs_EDGE) &&
                        (it.Value().ShapeType() != TopAbs_WIRE)) {
                        return new App::DocumentObjectExecReturn("Element in spine is neither an edge nor a wire.");
                    }
                }

                Handle(TopTools_HSequenceOfShape) hEdges = new TopTools_HSequenceOfShape();
                Handle(TopTools_HSequenceOfShape) hWires = new TopTools_HSequenceOfShape();
                for (TopExp_Explorer xp(shape._Shape, TopAbs_EDGE); xp.More(); xp.Next())
                    hEdges->Append(xp.Current());

                ShapeAnalysis_FreeBounds::ConnectEdgesToWires(hEdges, Precision::Confusion(), Standard_True, hWires);
                int len = hWires->Length();
                if (len != 1)
                    return new App::DocumentObjectExecReturn("Spine is not connected.");
                path = hWires->Value(1);
            }
            else {
                return new App::DocumentObjectExecReturn("Spine is neither an edge nor a wire.");
            }
        }
        catch (Standard_Failure) {
            return new App::DocumentObjectExecReturn("Invalid spine.");
        }
    }

    try {
        TopTools_ListOfShape profiles;
        const std::vector<App::DocumentObject*>& shapes = Sections.getValues();
        std::vector<App::DocumentObject*>::const_iterator it;
        for (it = shapes.begin(); it != shapes.end(); ++it) {
            if (!(*it)->isDerivedFrom(Part::Feature::getClassTypeId()))
                return new App::DocumentObjectExecReturn("Linked object is not a shape.");
            TopoDS_Shape shape = static_cast<Part::Feature*>(*it)->Shape.getValue();
            if (shape.IsNull())
                return new App::DocumentObjectExecReturn("Linked shape is invalid.");

            // Extract first element of a compound
            if (shape.ShapeType() == TopAbs_COMPOUND) {
                TopoDS_Iterator it(shape);
                for (; it.More(); it.Next()) {
                    if (!it.Value().IsNull()) {
                        shape = it.Value();
                        break;
                    }
                }
            }
            // There is a weird behaviour of BRepOffsetAPI_MakePipeShell when trying to add the wire as is.
            // If we re-create the wire then everything works fine.
            // http://forum.freecadweb.org/viewtopic.php?f=10&t=2673&sid=fbcd2ff4589f0b2f79ed899b0b990648#p20268
            if (shape.ShapeType() == TopAbs_FACE) {
                TopoDS_Wire faceouterWire = ShapeAnalysis::OuterWire(TopoDS::Face(shape));
                profiles.Append(faceouterWire);
            }
            else if (shape.ShapeType() == TopAbs_WIRE) {
                BRepBuilderAPI_MakeWire mkWire(TopoDS::Wire(shape));
                profiles.Append(mkWire.Wire());
            }
            else if (shape.ShapeType() == TopAbs_EDGE) {
                BRepBuilderAPI_MakeWire mkWire(TopoDS::Edge(shape));
                profiles.Append(mkWire.Wire());
            }
            else if (shape.ShapeType() == TopAbs_VERTEX) {
                profiles.Append(shape);
            }
            else {
                return new App::DocumentObjectExecReturn("Linked shape is not a vertex, edge, wire nor face.");
            }
        }

        Standard_Boolean isSolid = Solid.getValue() ? Standard_True : Standard_False;
        Standard_Boolean isFrenet = Frenet.getValue() ? Standard_True : Standard_False;
        BRepBuilderAPI_TransitionMode transMode;
        switch (Transition.getValue()) {
            case 1: transMode = BRepBuilderAPI_RightCorner;
                break;
            case 2: transMode = BRepBuilderAPI_RoundCorner;
                break;
            default: transMode = BRepBuilderAPI_Transformed;
                break;
        }

        if (path.ShapeType() == TopAbs_EDGE) {
            BRepBuilderAPI_MakeWire mkWire(TopoDS::Edge(path));
            path = mkWire.Wire();
        }

        BRepOffsetAPI_MakePipeShell mkPipeShell(TopoDS::Wire(path));
        mkPipeShell.SetMode(isFrenet);
        mkPipeShell.SetTransitionMode(transMode);
        TopTools_ListIteratorOfListOfShape iter;
        for (iter.Initialize(profiles); iter.More(); iter.Next()) {
            mkPipeShell.Add(TopoDS_Shape(iter.Value()));
        }

        if (!mkPipeShell.IsReady())
            Standard_Failure::Raise("shape is not ready to build");
        mkPipeShell.Build();
        if (isSolid)
            mkPipeShell.MakeSolid();

        this->Shape.setValue(mkPipeShell.Shape());
        return App::DocumentObject::StdReturn;
    }
    catch (Standard_Failure) {
        Handle_Standard_Failure e = Standard_Failure::Caught();
        return new App::DocumentObjectExecReturn(e->GetMessageString());
    }
    catch (...) {
        return new App::DocumentObjectExecReturn("A fatal error occurred when making the sweep");
    }
}