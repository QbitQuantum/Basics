/************************************************************************
 Собственно, загрузка содержимого тела секции Автомата. Дабы позволить
 производным классам автоматов разпознавать и загружать свои собственные
 структуры данных сверх того, что распознает и загружает наш класс,
 вызывается виртуальный метод ProcessLexem.
*************************************************************************/
void Automaton::load(
                     Macro_Parser &txtfile,
                     const Binarization_Options &options
                    )
{
 bool looping=true;
 while( looping )
  {
   if( txtfile.eof() )
    {
     Print_Error(txtfile);
     GetIO().merr().printf(
                           "End of file has been reached before Automaton [%us] section completely loaded\n"
                           , GetName().c_str()
                          );
     throw E_ParserError();
    }

   const BethToken t=txtfile.read();

   if( !ProcessLexem(t,txtfile,options) )
    {
     switch(t.GetToken())
      {
       case B_CRITERION:
        if( param!=NULL )
         param->LoadTxt( GetIO(), txtfile );
        break;

       case B_CFIGPAREN:
        looping=false;
        break;

       default:
        {
         const BSourceState back=txtfile.tellp();

         if( param!=NULL )
          {
           if( txtfile.read().GetToken()==B_EQUAL )
            {
             txtfile.seekp( t.GetBegin() );
             param->LoadTxt(GetIO(),txtfile);
             break;
            }
          }
         else
          {
           LEM_STOPIT;
          }

         txtfile.seekp(back);

         // Нераспознанная лексема.
         GetIO().merr().printf( "\nIncorrect lexem [%us]\n", t.string().c_str() );
         Print_Error(t,txtfile);
         throw E_ParserError();
        }
      }
    }
  }

 return;
}