void	CInifile::w_u64			( LPCSTR S, LPCSTR L, u64				V, LPCSTR comment )
{
    string128 temp;
#ifndef _EDITOR
    _ui64toa_s			(V, temp, sizeof(temp), 10);
#else
    _ui64toa			(V, temp, 10);
#endif
    w_string			(S,L,temp,comment);
}