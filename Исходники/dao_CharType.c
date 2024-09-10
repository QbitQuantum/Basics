static void dao_isblank( DaoProcess *proc, DaoValue *P[], int N )
{
	DaoProcess_PutInteger( proc, isblank( DaoValue_TryGetInteger( P[0] ) ) );
}