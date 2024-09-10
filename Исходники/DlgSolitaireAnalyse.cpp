void CDlgSolitaireAnalyse::OnBnClickedButton5()
{
	UpdateData(true);
   CString csErr;
   int res = myD->loaddeck( "*.txt" );

   switch ( res ) {
      case 0:
         return;
      case 1:
         break;
      case -1:
         csErr.LoadStringA(IDS_SOLITAIRE_COULD_NOT_LOAD_DECK);
         MessageBox( csErr );
         return;
      case -2:
         csErr.LoadStringA(IDS_SOLITAIRE_COULD_NOT_LOAD_DECK);
         MessageBox( csErr );
         return;
   };
//   myD->readdeck( "LastFinaldeck" );
	kartenanzahl=myD->anzahl-3;
	kartenanzahlneu=kartenanzahl+3;
	gefundenesDeck=myD->getDeck();
	zwischendeck=gefundenesDeck;
	schluesselstrom="";
	Initialdeck="";
	enablebut(false);
	hinten.EnableWindow(true);
	vorne.EnableWindow(true);
	waehlen.EnableWindow(true);
	entschluesseln.EnableWindow(false);
	schluesselerzeugen.EnableWindow(false);
	m_kartenanzahl.EnableWindow(false);
	UpdateData(false);
}