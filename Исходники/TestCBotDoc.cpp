void CTestCBotDoc::OnTest()
{
    CBotProgram::DefineNum("WingedGrabber", 1);
    CBotProgram::DefineNum("TrackedGrabber", 2);
    CBotProgram::DefineNum("WheeledGrabber", 3);
    CBotProgram::DefineNum("LeggedGrabber", 4);
    CBotProgram::DefineNum("WingedShooter", 5);
    CBotProgram::DefineNum("TrackedShooter", 6);
    CBotProgram::DefineNum("WheeledShooter", 7);
    CBotProgram::DefineNum("LeggedShooter", 8);
    CBotProgram::DefineNum("WingedOrgaShooter", 9);
    CBotProgram::DefineNum("TrackedOrgaShooter", 10);
    CBotProgram::DefineNum("WheeledOrgaShooter", 11);
    CBotProgram::DefineNum("LeggedOrgaShooter", 12);
    CBotProgram::DefineNum("WingedSniffer", 13);
    CBotProgram::DefineNum("TrackedSniffer", 14);
    CBotProgram::DefineNum("WheeledSniffer", 14);
    CBotProgram::DefineNum("LeggedSniffer", 15);
    CBotProgram::DefineNum("Thumper", 16);
    CBotProgram::DefineNum("PhazerShooter", 17);
    CBotProgram::DefineNum("Recycler", 18);
    CBotProgram::DefineNum("Shielder", 19);
    CBotProgram::DefineNum("Subber", 20);
    CBotProgram::DefineNum("Me", 21);

    CBotProgram::DefineNum("TypeMarkPath", 111);

    OnFileSave();

//  CPerformDlg dlg;
//  dlg.m_Script = m_DocText;
//  dlg.DoModal();

    // défini la routine RetObject
    CBotProgram::AddFunction( "Radar", rRetObject, cRetObject );

    // ajoute une routine pour cette classe
    CBotProgram::AddFunction("Space", rSpace, cSpace);

    // défini la routine Test
    CBotProgram::AddFunction( "TEST", rTEST, cTEST );
    CBotProgram::AddFunction( "F", rF, cF );

    CBotProgram::AddFunction( "goto", rMove, cMove );
    CBotProgram::AddFunction( "fire", rTurn, cTurn );
    CBotProgram::AddFunction( "radar", rRadar, cRadar );

    // crée une instance de la classe "Bot" pour ce robot
    CBotVar*    pThisRobot = CBotVar::Create( "", CBotTypResult(CBotTypClass, "object") );
    pThisRobot->SetUserPtr( (void*)1 );
    pThisRobot->SetIdent( 1234 );

    delete m_pProg;
    // crée un objet programme associé à cette instance
    m_pProg = new CBotProgram(pThisRobot);

    // compile le programme
    CString         TextError;
    int             code, start, end;

    m_pEdit->GetWindowText(m_DocText);
    if (!m_pProg->Compile(m_DocText, m_Liste, (void*) 44))
    {
        m_pProg->GetError(code, start, end);
        delete m_pProg;
        m_pProg = NULL;

        delete pThisRobot;

        m_pEdit->SetSel( start, end );
        m_pEdit->SetFocus();                // met en évidence la partie avec problème

        TextError = CBotProgram::GivErrorText( code );
        AfxMessageBox( TextError );

        m_pEdit->SetFocus();
        return;
    }

    // exécute pour voir
    m_pProg->Start(m_Liste[0]);

    int mode = -1;

    if ( mode >= 0 ) {

    // sauve et restore à chaque pas possible
    while (!m_pProg->Run(NULL, 1))
    {
        const char* FunctionName;
        int         start1, end1;
        m_pProg->GetRunPos(FunctionName, start1, end1);
        if ( end1 <= 0 )
            m_pProg->GetRunPos(FunctionName, start1, end1);
        m_pEdit->SetSel(start1, end1);

if ( mode == 0 ) continue;

        FILE*   pf;
        pf =    fOpen( "TEST.CBO", "wb" );
        CBotClass::SaveStaticState(pf);
        m_pProg->SaveState(pf);
        fClose(pf);

if ( mode == 2 ) if (!m_pProg->Compile(m_DocText, m_Liste, (void*) 44))
    {
        m_pProg->GetError(code, start, end);
        delete m_pProg;
        m_pProg = NULL;

        delete pThisRobot;

        m_pEdit->SetSel( start, end );
        m_pEdit->SetFocus();                // met en évidence la partie avec problème

        TextError = CBotProgram::GivErrorText( code );
        AfxMessageBox( TextError );

        m_pEdit->SetFocus();
        return;
    }

        pf =    fOpen( "TEST.CBO", "rb" );
        CBotClass::RestoreStaticState(pf);
        m_pProg->RestoreState(pf);
        fClose(pf);

        int         start2, end2;
        m_pProg->GetRunPos(FunctionName, start2, end2);
        if ( end2 <= 0 )
            m_pProg->GetRunPos(FunctionName, start2, end2);

        if ( start1 != start2 || end1 != end2 )
            m_pProg->GetRunPos(FunctionName, start2, end2);
        m_pEdit->SetSel(start2, end2);
    }

    if (m_pProg->GetError(code, start, end))
    {
        m_pEdit->SetSel(start, end);
        TextError = CBotProgram::GivErrorText(code);
        AfxMessageBox(TextError);
    }
    return;}

    while (!m_pProg->Run(NULL, 0))
    {
        const char* FunctionName;
        int         start, end;
        m_pProg->GetRunPos(FunctionName, start, end);
        m_pEdit->SetSel(start, end);

        if ( FunctionName == NULL ) continue;
        CString info (FunctionName);
        CString sep  (":\n");

        int level = 0;
        const char* Name;
        while ( TRUE )
        {
            CBotVar* pVar = m_pProg->GivStackVars(Name, level--);
            if ( Name != FunctionName ) break;
            if ( pVar == NULL ) continue;
//          pVar->Maj(NULL, FALSE);
            while ( pVar != NULL )
            {
                info += sep;
                info += pVar->GivName() + CBotString(" = ") + pVar->GivValString();
                sep = ", ";
                pVar = pVar->GivNext();
            }
            sep = "\n";
        }
        if ( IDOK != AfxMessageBox(info, MB_OKCANCEL) ) break;

        if ( test == 1 )
        {
            test = 0;
            FILE*   pf;
            pf =    fOpen( "TEST.CBO", "wb" );
            m_pProg->SaveState(pf);
            fClose(pf);
        }

        if ( test == 2 )
        {
            test = 0;
            FILE*   pf;
            pf =    fOpen( "TEST.CBO", "rb" );
            m_pProg->RestoreState(pf);
            fClose(pf);
        }

        if ( test == 12 )
        {
            test = 0;
            FILE*   pf;
            pf =    fOpen( "TEST.CBO", "wb" );
            m_pProg->SaveState(pf);
            fClose(pf);

            pf =    fOpen( "TEST.CBO", "rb" );
            m_pProg->RestoreState(pf);
            fClose(pf);

            test = 13;
        }
    }

    if (m_pProg->GetError(code, start, end))
    {
        m_pEdit->SetSel(start, end);
        TextError = CBotProgram::GivErrorText(code);
        AfxMessageBox(TextError);
    }

    delete pThisRobot;
}