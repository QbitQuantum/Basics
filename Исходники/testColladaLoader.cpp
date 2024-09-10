void printXForm(OSG::SceneGraphPrinter *sgp, OSG::NodeCore *core)
{
    OSG::Transform *xform = dynamic_cast<OSG::Transform *>(core);

    sgp->indentStream() << "matrix:\n" << xform->getMatrix();
}