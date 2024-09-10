//---------------------------------------------------------------------------
AnsiString __fastcall TBolBradesco::GeraCampoLivre(void)
{
    AnsiString CampoLivre = Agencia.SubString(1,4) +
    Carteira + GetNumeroDocumento() +
    CodigoCedente.SubString(1,7) +
    "0";
    if(CampoLivre.Length() != 25)
     {
      throw Exception("Campo livre deve conter 25 caracteres para o Banco Bradesco.");
     }
    return(CampoLivre);
}