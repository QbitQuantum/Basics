/****************************************************************************
 Загружаем из текстового файла множество символьных строк. Если слово
 только одно, то оно может идти непосредственно. Если необходимо определить
 несколько слов, то они заключаются в фигурные скобочки.
 Форматы:
         1. лексема
         2. { лексема лексема ... лексема }

 Второй формат охватывает также и первый, если в фигурных скобочках указать
 только одну лексему. Способ хранения в обоих случаях одинаков!
*****************************************************************************/
void UCStringSet::LoadTxt( const Sol_IO &io, Macro_Parser &txtfile )
{
 BethToken t = txtfile.read();

 if( t.GetToken()!=B_OFIGPAREN )
  {
   // Первый формат.
   push_back(t.c_str());
  }
 else
  {
   // Второй формат.
   while( !txtfile.eof() )
    {
     if( txtfile.eof() )
      {
       Print_Error(t,txtfile);
       io.merr().printf(
                        "End of file has been reached before "
                        "set of lexems completely loaded\n"
                       );
       LEM_STOPIT;
      }

     t = txtfile.read();

     if( t.GetToken()==B_CFIGPAREN )
      break;

     push_back(t.string());
     weight.push_back(1);
    }
  }

 return;
}