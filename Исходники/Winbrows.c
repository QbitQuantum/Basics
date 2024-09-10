static Void local doDestroy_Classes() {
   if (Nodes) free(Nodes);
   Nodes = NULL;
   LastNode = 0;
   DestroyCursor(cBrowse.hMoveClassCursor);
   hWndClasses=NULL;
}