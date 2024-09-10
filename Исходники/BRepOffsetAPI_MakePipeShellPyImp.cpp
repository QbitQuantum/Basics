PyObject* BRepOffsetAPI_MakePipeShellPy::generated(PyObject *args)
{
    PyObject *shape;
    if (!PyArg_ParseTuple(args, "O!",&Part::TopoShapePy::Type,&shape))
        return 0;
    const TopoDS_Shape& s = static_cast<Part::TopoShapePy*>(shape)->getTopoShapePtr()->_Shape;
    const TopTools_ListOfShape& list = this->getBRepOffsetAPI_MakePipeShellPtr()->Generated(s);

    Py::List shapes;
    TopTools_ListIteratorOfListOfShape it;
    for (it.Initialize(list); it.More(); it.Next()) {
        const TopoDS_Shape& s = it.Value();
        shapes.append(Py::asObject(new TopoShapePy(new TopoShape(s))));
    }
    return Py::new_reference_to(shapes);
}