KS_RESULT LoadDupl(KscServerBase* Server, PltString &ImpString)
/*****************************************************************************/
{
        /*
        *        Variablen
        */
        int                exit_status;
        size_t         i,j;            // Laufvariablen
        char        path[32];       // Hilfsstring

    InstanceItems*        pinst;
    LinksItems*                pLinks;

    PltString       VerbName;   // Name der Verbindung
    PltString       NewName;    // Neuen Name der Verbindung
    PltString       Assoc;      // Assoziations-Identifier
    
        yydebug = 0;
        current_line = 0;

    size_t    Count;            // Merker : Anzahl der Verbindungen
    KS_RESULT err;              // Ergebnis des Dienstes
    
    struct yy_buffer_state* buf;
    
        /*
        *        check option settings
        */

    if(!Server)
            return KS_ERR_SERVERUNKNOWN;

        if(!ImpString.len() ) {
                return KS_ERR_OK;
        }

        ppar = (Dienst_param*)malloc(sizeof(Dienst_param));
        if(!ppar) {
                return OV_ERR_HEAPOUTOFMEMORY;
        }
        ppar->Instance = 0;
        ppar->Set_Inst_Var = 0;
        ppar->DelInst = 0;
        ppar->OldLibs = 0;
        ppar->NewLibs = 0;
        ppar->Links = 0;
        ppar->UnLinks = 0;


        /*
        *   Eingabe parsen
        */
        buf = yy_scan_string( (char*)(const char*)ImpString );
    exit_status =  yyparse();
    yy_delete_buffer( buf );

    /* String geparst ? */
        if(exit_status != EXIT_SUCCESS) {
            memfre(ppar);
            free(ppar);
        fb_parser_freestrings();
        
        return KS_ERR_BADPARAM;
    }


///////////////////////////////////////////////////////////////////////////////
//  Es muessen Namen der Verbindungen geaendert werden                       //
///////////////////////////////////////////////////////////////////////////////

    sprintf(path, "/%s/",FB_CONN_CONTAINER);

    /* Anzahl der Verbindungen ermitteln */
    pinst = ppar->Instance;
    Count = 0;
    
    while(pinst) {

        if( !strncmp(pinst->Inst_name, path, 4) ) {
            // Verbindung gefunden
            Count++;
        }
        pinst = pinst->next;
    }
    
    PltArray<char*> Verbindung(Count);
    if(Verbindung.size() != Count) {
        // Out of memory ?
        err = OV_ERR_HEAPOUTOFMEMORY;
        goto EXIT_FNC;
    }
    // Array initialisieren
    for(j = 0; j < Count; j++) {
        Verbindung[j] = 0;
    }
    
    // Gibt es Verbindungen ?
    if(Count) {
        
        // Dann erzeugen wir neuen Name fuer Verbindungs-Objekt.
        GenerateComConName(Assoc);      // Neuen Name der Verbindung erzeugen
        NewName = path;
        NewName += Assoc;

        /* Verbindung-Namen aendern */
        pinst = ppar->Instance;
        j = 0;
        
        while(pinst) {
            char* ph;
            
            if( !strncmp(pinst->Inst_name, path, 4) ) {
                // Verbindung gefunden
                VerbName = pinst->Inst_name;    // Name der Verbindung merken

                ph = (char*)malloc(NewName.len() + 33);
                if(!ph) {
                    // Out of memory
                    for(i = 0; i < j; i++) {
                        if(Verbindung[i]) free(Verbindung[i]);
                    }
                    err = OV_ERR_HEAPOUTOFMEMORY;
                    goto EXIT_FNC;
                }
            
                // Neuen Name kopieren
                sprintf(ph, "%s%d", (const char*)NewName, j);

                pinst->Inst_name = ph;
                
                // String merken
                Verbindung[j] = ph;
                j++;
                
                for(i = 0; i < 2; i++) {
                    switch(i) {
                        case 0:
                            // Link "outputcon" suchen
                            Assoc = "outputcon";
                            break;
                        default:
                            // Link "inputcon" suchen
                            Assoc = "inputcon";
                            break;
                    }
                
                        pLinks = ppar->Links;
                        while(  (pLinks) ) {
                            if( (VerbName == pLinks->children->child_path) &&
                                (Assoc == pLinks->child_role) ) {
                                    break;
                             }
                            pLinks = pLinks->next;
                        }
                        if(!pLinks) {
                        // Link nicht gefunden
                        for(i = 0; i < j; i++) {
                            if(Verbindung[i]) free(Verbindung[i]);
                        }
                        err = KS_ERR_BADPARAM;
                        goto EXIT_FNC;
                        }

                        // Neuen Name in Link-String merken
                        pLinks->children->child_path = ph;
                    
                } // Links suchen
                } // if Verb. gefunden
            
                pinst = pinst->next;    // Naechste Instance
            
        } // while Instanzen
    } // if Verbindungen vorhanden
    
    // Alle Verbindungen und Links umbennant.
    // Instanzen anlegen :
    
    VerbName = "";
    err = import_eval(Server, ppar, VerbName);

    // Neue erzeugte Strings freigeben
    for(i = 0; i < Count; i++) {
        if(Verbindung[i]) free(Verbindung[i]);
    }
    
EXIT_FNC:
        memfre(ppar);
        free(ppar);
    fb_parser_freestrings();

    return err;
}