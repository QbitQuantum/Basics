void FindSequenceDialog::aaSubSearch ( const wxString &s , int start , int dir , wxString rf )
	{
	int a ;
	wxChar codon[4] ;
	codon[3] = 0 ;
	wxString res ;
	wxArrayInt ai ;
    TVector *v = c->vec ;
    wxString sub = getQuery() ;
    int ostart = start < 0 ? 2 : 0 ;
    
    res.Alloc ( s.length() / 3 + 10 ) ;
    ai.Alloc ( s.length() / 3 + 10 ) ;
    
    if ( start < 0 )
    	{
	    for ( start = -start ; start + 3 < s.length() ; start += 3 ) ;
    	}
   	
	for ( a = start ; a + dir * 2 >= 0 && a + dir * 2 < s.length() ; a += dir * 3 )
		{
 		codon[0] = s.GetChar ( a ) ;
 		codon[1] = s.GetChar ( a + dir ) ;
 		codon[2] = s.GetChar ( a + dir * 2 ) ;

        wxChar c2 = codonhash[codon] ;
        if ( c2 < 'A' ) c2 = codonhash[codon] = v->dna2aa ( codon ) . GetChar ( 0 ) ;
        res += c2 ;

		ai.Add ( a ) ;
		}    
		
	a = subsearch ( res , sub , 0 ) ;
	//a = res.Find ( sub ) ;
	while ( a != -1 )
		{
  		if ( lb->GetCount() > FIND_MAX ) return ;
		int from = ai[a] + 1 - ostart ;
		int to = ai[a+sub.length()-1] + dir * 2 + 1 - ostart ;
		if ( from > to ) { int z = from ; from = to ; to = z ; }
		wxString msg = rf.BeforeFirst ( '\t' ) ;
      lb->Append ( wxString::Format ( _T("%s: %s (%d-%d)") ,
                          txt("amino_acid").c_str() ,
                          msg.c_str() ,
                          from , to ) ) ;
      vi.Add ( -1 ) ;
		res.SetChar ( a , '_' ) ; // Invalidating
		a = subsearch ( res , sub , a+1 ) ;
//		a = res.Find ( sub ) ;
		}    
	}    