void ObjUpdateMenuVerbs( HMENU hMenu )
{
    int cObjects;
    extern struct SEL       selCur;
    extern char szOPropMenuStr[];
    extern char szPPropMenuStr[];
    extern BOOL vfOutOfMemory;
    char szBuffer[cchMaxSz];
    char szWordOrder2[10], szWordOrder3[10];

    if (vfOutOfMemory)
    {
        EnableMenuItem(hMenu, EDITMENUPOS, MF_GRAYED|MF_BYPOSITION);
        return;
    }

    LoadString(hINSTANCE, IDSTRPopupVerbs, szWordOrder2, sizeof(szWordOrder2));
    LoadString(hINSTANCE, IDSTRSingleVerb, szWordOrder3, sizeof(szWordOrder3));

    DeleteMenu(hMenu, EDITMENUPOS, MF_BYPOSITION);

/** Cases: 
    0)  0 objects selected
    1)  1 object  selected
        a) object supports 0 verbs          "Edit <Object Class> Object"
        b) object supports more than 1 verb "<Object Class> Object" => verbs
    2)  more than 1 object selected         "Objects"

    Use the VerbMenu strings to determine the order in which these words
    should appear in the menu string (for localization).
**/

    /* how many objects are selected? */
    cObjects = ObjSetSelectionType(docCur,selCur.cpFirst, selCur.cpLim);

    /* must be only an object, not text in selection */
    if (cObjects == 1)
    {
        ObjCachePara(docCur,selCur.cpFirst);
        if (!ObjQueryCpIsObject(docCur,selCur.cpFirst))
            cObjects = 0;
    }

    if ((cObjects == -1) // error
        || (cObjects == 0)
        || (cObjects > 1))
    {
        wsprintf(szBuffer, "%s", (LPSTR)((cObjects > 1) ? szPPropMenuStr : szOPropMenuStr));
        InsertMenu(hMenu, EDITMENUPOS, MF_BYPOSITION,imiVerb,szBuffer);

        /*  
            Spec says if > 1 then optionally should enable if all servers 
            are of the same class.  I'm opting not to implement. (9.27.91) v-dougk
        */
        EnableMenuItem(hMenu, EDITMENUPOS, MF_GRAYED | MF_BYPOSITION);

#if 0
        else // > 1
        {