string MeshShapeItemImpl::toURDF()
{
    ostringstream ss;
    ss << "<link name=\"" << self->name() << "\">" << endl;
    Affine3 relative;
    JointItem* parentjoint = dynamic_cast<JointItem*>(self->parentItem());
    if (parentjoint) {
        Affine3 parent, child;
        parent.translation() = parentjoint->translation;
        parent.linear() = parentjoint->rotation;
        child.translation() = self->translation;
        child.linear() = self->rotation;
        relative = parent.inverse() * child;
    } else {
        relative.translation() = self->translation;
        relative.linear() = self->rotation;
    }
    for (int i=0; i < 2; i++) {
        if (i == 0) {
            ss << " <visual>" << endl;
        } else {
            ss << " <collision>" << endl;
        }
        if (i == 0) {
            ss << " </visual>" << endl;
        } else {
            ss << " </collision>" << endl;
        }
    }
    return ss.str();
}