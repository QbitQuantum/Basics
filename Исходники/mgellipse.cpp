void MgEllipse::_output(MgPath& path) const
{
    path.moveTo(_bzpts[0]);
    path.beziersTo(12, _bzpts + 1);
    path.closeFigure();
}