void OWVector4::transform(OWMatrix4* m)
{
    OWVector4* tempV = m->multiply(*this);
    _x = tempV->getX();
    _y = tempV->getY();
    _z = tempV->getZ();
    _w = tempV->getW();
    delete tempV;
}