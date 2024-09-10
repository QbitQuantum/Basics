/* check if we are still running and fill out the position 
	return == 0 we're still walking ... else we have reached a point */
inline int
ai_checkpos (_player * pl, _point * pos)
{
    _pointf _p;

    _p.x = CUTINT (pl->pos.x);
    _p.y = CUTINT (pl->pos.y);

    pos->x = rintf (pl->pos.x);
    pos->y = rintf (pl->pos.y);

    return ((_p.x < 0.15f || _p.x > 0.85f) && (_p.y < 0.15f || _p.y > 0.85f));
};