void
TeamsWindow::DoDrag(
     WORD hDragInfo
) {
     char           filename[128];
     unsigned short usNumOfFiles;
     unsigned short i;
     short          index;
     POINT          pt;
     BOOL           drop_ok = FALSE;

     usNumOfFiles = DragQueryFile((HDROP) hDragInfo, -1, NULL, 0);

     if (DragQueryPoint((HDROP) hDragInfo, &pt)) {
          short     x = pt.x;
          short     y = pt.y;

          x /= usMiniCarWidth;
          y /= usMiniCarHeight;

          index = (y * TEAMS_NUM_X) + x;

          for (i = 0; i < usNumOfFiles; i++) {
               (void) DragQueryFile((HDROP) hDragInfo, i, filename, sizeof(filename));

               ASSERT(index >= 0 && index < GP_EXE_NUM_TEAMS);
               if (index >= 0 && index < GP_EXE_NUM_TEAMS) {
                    FrameActiveTeam(index);
                    usSelectedTeam = index;
                    if (SendMessage(Parent(), IDE_DESIGN_TEAM_SELECT, usSelectedTeam, 0L)) {
                         UpdateMemoryImage();
                    }
                    (void) SendMessage(Parent(), IDE_CBAR_TEAM_SELECT, usSelectedTeam, 0L);

                    /*
                    ** Now load new car colours.
                    */
                    drop_ok = (BOOL) SendMessage(Parent(), IDE_DESIGN_LOAD, 0, (LONG) (void *) filename);
                    UpdateMemoryImage();
               }

               /*
               ** Wrap to next time on a multi-file drop.
               */
               if (drop_ok && ++index >= GP_EXE_NUM_TEAMS) {
                    index = 0;
               }
          }
     }
}