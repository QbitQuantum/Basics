double Puckering::CalculateTheta()
{
    _Theta = acos( sqrt(_nAtomsInv)*_qz / _Q );
    return _Theta;
}