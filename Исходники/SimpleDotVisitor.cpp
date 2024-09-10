void SimpleDotVisitor::handle(osg::Node &node, osg::StateSet &stateset, int parentID, int childID)
{
    drawEdge(parentID, childID, "dashed");
}