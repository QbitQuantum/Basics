void SG_ComplexLink::LoadPoint( Macro_Parser &txtfile, SynGram &gram, lem::UFString &entry )
{
 BethToken t = txtfile.read();

 if( t.GetToken()==B_ENTRY )
  {
   // Особый формат entry Класс:Статья { уточнение }
   // преобразуется в ключ статьи и возвращается в виде #ключ
   UCString class0 = txtfile.read().string();
   const int ic0 = class0==L"?" ? ANY_STATE : gram.FindClass(class0);
   if( ic0==UNKNOWN ) 
    {
     Print_Error( txtfile );
     gram.GetIO().merr().printf( "Unknown class %us\n", class0.c_str() );
     throw E_BaseException();
    }

   txtfile.read_it( B_COLON );
   UCString entry0 = sol_read_multyname( gram.GetIO(), txtfile, B_OFIGPAREN );
   entry0.strip(L'"');
   entry0.trim();

   // Может быть задана дополнительная фильтрующая координата
   Solarix::CP_Array coords0;
   coords0.LoadTxt( txtfile, gram );
   
   if( gram.IsOmonym(ic0,lem::to_upper(entry0)) && coords0.empty() )
    {
     Print_Error( txtfile );
     gram.GetIO().merr().printf( "Omonym %us:%us requires the coordinate array\n", class0.c_str(), entry0.c_str() );
     throw E_BaseException();
    }

   const int ie0 = coords0.empty() ? gram.FindEntry(entry0,ic0,false) : gram.FindEntryOmonym(entry0,ic0,coords0);
   if( ie0==UNKNOWN ) 
    {
     Print_Error( txtfile );
     gram.GetIO().merr().printf( "Unknown entry %us:%us\n", class0.c_str(), entry0.c_str() );
     throw E_BaseException();
    }

   const int ekey = gram.GetEntry(ie0).GetKey();
   entry = lem::format_str( L"#%d", ekey );

   return;
  }

 bool figparen = t.GetToken()==B_OFIGPAREN;

 if( !figparen )
  txtfile.seekp(t);
 
 entry.reserve(128);

 if( t.string()==L'@' )
  {
   entry = L'@';
   t = txtfile.read();
  }

 while( !txtfile.eof() )
  {
   BethToken t = txtfile.read();
   if( figparen && t.GetToken()==B_CFIGPAREN )
    break;
   
   if( !entry.empty() )
    entry.Add_Dirty(L' ');

   UFString ts( t.GetFullStr() );
   ts.strip(L'"');
   entry.Add_Dirty( ts );

   if( !figparen )
    break;
  }

 entry.calc_hash();

 if( entry.front()==L'@' )
  {
   // Спецсимвол @ заставляет запомнить строку в виде "как есть"
   entry.remove(0);
   entry.trim();
  }
 else
  {
   entry.strip(L'"');
   gram.GetDict().GetLexAuto().TranslateLexem(entry,true);
  }

 return;
}