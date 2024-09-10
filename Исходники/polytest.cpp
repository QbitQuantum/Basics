/*
**  Hide memory clean up.
*/
static
void
FASTCALL
POLYGONFILL_DestroyEdgeList(FILL_EDGE_LIST* list)
{
  int i;
  if ( list )
  {
    if ( list->Edges )
    {
      for ( i = 0; i < list->Count; i++ )
      {
	if ( list->Edges[i] )
	  EngFreeMem ( list->Edges[i] );
      }
      EngFreeMem ( list->Edges );
    }
    EngFreeMem ( list );
  }
}