void _setMat33Translation(b2Mat33& mat, b2Vec2 t)
{
    mat.SetZero();
    mat.ex.x = 1;
    mat.ey.y = 1;
    mat.ez.x = t.x;
    mat.ez.y = t.y;
    mat.ez.z = 1;
}