void Rankwave::gen_waves (Addsynth *D, float fsamp, float fbase, float *scale)
{
    Pipewave::initstatic (fsamp);

    fbase *=  D->_fn / (D->_fd * scale [9]);
    for (int i = _n0; i <= _n1; i++)
    {
	_pipes [i - _n0].genwave (D, i - _n0, fsamp, ldexpf (fbase * scale [i % 12], i / 12 - 5));
    }
    _modif = true;
}