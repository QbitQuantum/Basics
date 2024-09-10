//---------------------------------------------------------------------------
bool __fastcall TRawPrint::FechaDispositivo(void)
{
 bool Retorno = true;

 try
  {
   if (DispAberto)
    {
     if (PaginaAberta)
      {
       if(!EndPagePrinter(hPrinter))
        Erro("Erro ao Finalizar Página");

       if(!EndDocPrinter(hPrinter))
        Erro("Erro ao Finalizar Documento");
       else
        {
         if(!ClosePrinter(hPrinter))
          {
           Erro("Erro ao Fechar a Impressora");
           Retorno = false;
          }
          DispAberto = false;
        }
      }
    }
  }
 catch(Exception & E)
  {
   Erro("Erro ao Fechar a Impressora.\r\n\r\n" + E.Message + "\r\n");
  }
 return Retorno;
};