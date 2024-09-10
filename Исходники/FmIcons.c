void changeDTIconProc(XtPointer awp, int conf)
{
 DTIconRec *dticon = ((AppSpecRec *) awp)->win.dticon;

 XTFREE(awp);
 dticons_blocked = False;
 if (conf == YES) {
     XtDestroyWidget(dticon->app.form);
     if (dticon->app.loaded)  freeIcon(dticon->app.icon_pm);
     if (dticon->label_mask != None)
	 freePixmap(dticon->label_mask);
     if (dticon->drop_pixmap != None)
	 freePixmap(dticon->drop_pixmap);
     dticon->app.objType = getObjectType(dticon->app.push_action);
     readApplicationIcon(getAnyShell(), &dticon->app, ERR_POPUP);
     displayDTIcon(dticon);
     if (resources.auto_save)  writeDTIcons(True);
 }
}