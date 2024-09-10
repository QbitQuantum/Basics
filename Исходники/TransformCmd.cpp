void TransformCmd::setPointW(int index, const MgMotion* sender)
{
    Point2d point = sender->point * sender->view->xform()->displayToWorld();
    
    if (index > 0) {
        float a = (point - _origin).angle2();
        float len = _origin.distanceTo(point);
        a = floorf(0.5f + a * _M_R2D / 5) * 5 * _M_D2R;
        len = floorf(0.5f + len / 5) * 5;
        _axis[index == 1 ? 0 : 1].setAngleLength(a, len);
        
        Matrix2d mat(_axis[0], _axis[1], _origin * sender->view->xform()->worldToModel());
        mat *= _xfFirst.inverse();
        mat = sender->view->shapes()->modelTransform() * mat;
        
        sender->view->xform()->setModelTransform(mat);
        sender->view->regen();
    } else {
        _origin = point;
        sender->view->redraw(true);
    }
}