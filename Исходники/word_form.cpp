/******************************************************************
 Считывание описание узла BETH-дерева из текстового файла Словаря.
*******************************************************************/
void Word_Form::LoadTxt(
                        CompilationContext &context,
                        Macro_Parser &txtfile,
                        SynGram &gram
                       )
{
 val=Real1(100);
 score=0;
 iversion = seq_iversion++;

 // Сначала считываем определение класса и имя словарной статьи.
 const BethToken class_name = txtfile.read();
 entry_key=UNKNOWN_STATE;
 int iclass;

 // Если считанная лексема заключена в апострофы, то имеем дело
 // с сокращенным форматом: ?:строка. Этот формат применяется дл
 // описания лексемы, принадлежность которой к какому-либо классу
 // не очевидна или не важна, а важно лексическое представление.
 if( in_apostrophes(class_name.string()) )
  {
   name = RC_Lexem( new Lexem(strip_quotes(class_name.string())) );
   return;
  }

 if( class_name.string()==SOL_UNKNOWN_ENTRY_NAME )
  {
   // Только одна статья принадлежит особому классу UNKNOWN!
   // Эта статья может быть описана только как "?:?"

   if(
      txtfile.read().string()==sol_get_token(B_COLON) &&
      txtfile.read().string()==sol_get_token(B_UNKNOWN)
     )
    {
     const Word_Coord iuu = gram.FindEntryForm( class_name.string() );
     const SG_Entry& euu = gram.GetEntry(iuu.GetEntry());

     iclass=UNKNOWN_STATE;
     entry_key = euu.GetKey();
     return;
    }
  }

 // Пытаемся найти имя синтаксического класса в списке
 // уже загруженных в Словаре для синтаксической грамматики.
 if( (iclass=gram.FindClass(class_name.string()))==UNKNOWN )
  {
   // Класс не определен.
   //
   // Предполагаем, что задано лексическое содержимое некоторой
   // словоформы. Если такая словоформа лексически уникальна,
   // то мы сами можем восстановить пару класс:статья. В случае
   // множественности вариантов тяжесть ответственности ложитс
   // на пользователя.
   Word_Coord ie = gram.FindEntryForm( class_name.string() );

   if( ie.GetEntry()==UNKNOWN )
    {
     // Выводим сообщение о неверном имени синтаксического класса или
     // ненайденной словоформе.
     lem::Iridium::Print_Error(class_name,txtfile);
     gram.GetIO().merr().printf("Neither a class previously declared in grammar, nor an entry form\n");
     throw E_ParserError();
    }

   if( ie.GetEntry()!=UNKNOWN )
    {
     // Словоформа найдена!
     const SG_Entry& ef = gram.GetEntry(ie.GetEntry());
     entry_key = ef.GetKey();

     // Вероятно, следует также переслать координатные пары.
     const SG_EntryForm& eef = ef.forms()[ ie.GetForm() ];
     const CP_Array& dims = eef.coords();

     for( Container::size_type ii=0; ii<dims.size(); ii++ )
      {
       // Здесь немного наворочено - прямо использовать конструктор без
       // копирования в промежуточные поля нельзя из-за ошибки в
       // кодогенераторе Symantec C++ (появляется General Protection Fault).
       const GramCoordAdr ca = dims[ii].GetCoord();
       const int cs = dims[ii].GetState();
       pair.push_back( GramCoordEx( ca, cs, true ) );
      }

     // И наконец, пересылаем полное имя (лексическое содержимое) статьи.
//     icenter=0;
//     e_list.push_back( entry_key );
     name = RC_Lexem( const_cast<Lexem*>(&ef.GetName()), null_deleter() );
    }

   return;
  }

 const BSourceState back=txtfile.tellp();
 const BethToken t = txtfile.read();

 bool read_ofigparen=true;
 if( t.GetToken()==B_COLON )
  {
   // Считываем имя статьи, которое может в общем случае состоять
   // из нескольких лексем. Признаком окончания имени служит
   // открывающая фигурная скобка '{'.

   Lexem *mname = new Lexem( sol_read_multyname( gram.GetIO(), txtfile,B_OFIGPAREN) );

   // Преобразуем в мультилексему так, чтобы правильно распознавались
   // объявления имен типа "ЕЩ^Ё".
   gram.GetDict().GetLexAuto().TranslateLexem(*mname,false);
   mname->Translate( gram.GetDict().GetGraphGram(), 2 );

   //(*name) = mname;
   name = RC_Lexem( mname );

//   lexem_owner.resize(1);
//   lexem_owner.Nullify();

   read_ofigparen=false;

   // Пытаемся найти статью.
   if( *mname != sol_get_token(B_ANY) )
    {
     // Считан НЕ квантор всеобщности, так что это должно быть имя статьи.
     // Попытаемся найти статью среди уже загруженных, причем ищем с
     // критерием принадлежности определенному синтаксическому классу.

     const int ientry=gram.FindEntry2(*mname,iclass);

     // Нашли ?
     if( ientry==UNKNOWN )
      {
       // Нет! Выводим сообщение об неверном имени словарной статьи.
       lem::Iridium::Print_Error(txtfile);
       gram.GetIO().merr().printf(
                                  "The entry [%us:%us] is not previously declared in grammar\n"
                                  , gram.classes()[iclass].GetName().c_str()
                                  , mname->ToString().c_str()
                                 );
       throw E_ParserError();
      }

     // Запомним КЛЮЧ словарной статьи.
     entry_key=gram.GetEntry(ientry).GetKey();
    }
   else
    entry_key=ANY_STATE;
  }
 else
  {
   txtfile.seekp(back);
   entry_key=ANY_STATE;
  }

 bool load_precise=true;
 if( read_ofigparen )
  {
   const BSourceState back = txtfile.tellp();
   if( txtfile.read().GetToken()!=B_OFIGPAREN )
    {
     // Секции уточнения координат нет.
     txtfile.seekp(back);
     load_precise = false;
    }
  }

 if(load_precise)
  LoadPreciser(context,txtfile,gram,iclass);

 return;
}