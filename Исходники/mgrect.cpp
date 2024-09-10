void MgBaseRect::_output(MgPath& path) const
{
    path.moveTo(_points[0]);
    path.linesTo(3, _points + 1);
    path.closeFigure();
}