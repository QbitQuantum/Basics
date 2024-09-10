// base for window size quantization, R orientation channels, and feature window size (_W, _W)
Objectness::Objectness(DataSetVOC &voc, double base, int W, int NSS)
    : _voc(voc)
    , _base(base)
    , _W(W)
    , _NSS(NSS)
    , _logBase(log(_base))
    , _minT(cvCeil(log(10.)/_logBase))
    , _maxT(cvCeil(log(500.)/_logBase))
    , _numT(_maxT - _minT + 1)
    , _Clr(MAXBGR)
{
    setColorSpace(_Clr);
}