static char *GetOP( BYTE Num )
  {
    SetFlags( op_flags[ Num ] );
 return opmap1[Num];
}