//---------------------------------------------------------------------------//
// OnCommand
//
//---------------------------------------------------------------------------//
void CFXMessage::OnCommand(TCommand *pComm)
{
  CEffect::OnCommand(pComm);

  if (!Stricmp(pComm->pComm, "Down"))
    SetEstado(ST_BAJANDO);
  else if (!Stricmp(pComm->pComm, "Up"))
    SetEstado(ST_SUBIENDO);
}