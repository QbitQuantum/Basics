void
Tangente (Token ** Pila)
{

  Token *Operando = EntornoEjecucion_BuscaSimbolo (*Pila);
  if (Buzon.GetHuboError ())
    return;
  if (NoEsReal (Operando))
    {
      BorrarTokenSiEsVariable (Operando);
      return;
    }

  long double ValorDominio = Operando->GetDatoReal ();
  BorrarTokenSiEsVariable (Operando);
  ValorDominio = Estado.AngulosEnGrados ? ValorDominio * M_PI / 180.0L :
    ValorDominio;
  long double ValorSeno = sinl (ValorDominio);
  long double ValorCoseno = cosl (ValorDominio);
  long double ValorRetorno;
  if (fabsl (ValorSeno) == 1.0L)
    {
      Buzon.Error (LLAMADO_DE_FUNCION_NO_VALIDO);
      return;
    }
  else if (ValorCoseno == 1.0L)
    ValorRetorno = 0.0L;
  else
    ValorRetorno = tanl (ValorDominio);
  if (Buzon.GetHuboError ())
    return;
  Token *TokenRetorno = ConsigueToken (ValorRetorno);
  if (Buzon.GetHuboError ())
    return;
  delete Desapila (Pila);
  Apila (Pila, TokenRetorno);
  if (FueraDeRango (TokenRetorno))
    return;
  return;
}