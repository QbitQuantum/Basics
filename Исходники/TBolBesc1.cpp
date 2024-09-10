//---------------------------------------------------------------------------
AnsiString __fastcall TBolBesc::CalculaDV2Chave25(AnsiString AChave)
{
  int Digito;
  Digito = 0;
  int Soma = 0;
  int Multiplicador = 2;
  for (int i = AChave.Length(); i > 0; i--)
   {
    Soma = Soma + StrToInt(AChave[i]) * Multiplicador;
    Multiplicador++;
    if (Multiplicador > 7)
     Multiplicador = 2;
   }
  int Resto = (Soma % 11);
  if(Resto==0)
   Digito=0;
  else
   if (Resto == 1)
    {
     int Pos24 = StrToInt( AChave[AChave.Length()] );
     if(Pos24 == 9)
      Pos24 = 0;
     else
      Pos24 = Pos24 + 1;
     AChave = AChave.SubString(1, 23) + IntToStr(Pos24);
     return CalculaDV2Chave25(AChave);
    }
   else// (Resto > 1)
    {
     Digito = 11 - Resto;
    }

  Digito = Digito + 2;
  if(Digito == 10)
   Digito = 0;
  if(Digito == 11)
   Digito = 1;
  return IntToStr(Digito);
}