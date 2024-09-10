void CPathTrack :: Project( CPathTrack *pstart, CPathTrack *pend, Vector *origin, float dist )
{
	if ( pstart && pend )
	{
		Vector dir = (pend->pev->origin - pstart->pev->origin);
		dir = dir.Normalize();
		*origin = pend->pev->origin + dir * dist;
	}
}