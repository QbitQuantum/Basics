SetUpMenus()
  {
   /*================================================*/
   /* Get the Apple menu from the resource file, add */
   /* the names of available desk accessories, and   */
   /* install it at the end of the menu bar.         */
   /*================================================*/
   
   AppleMenu = GetMenu(AppleID);
   AddResMenu(AppleMenu,'DRVR');
   InsertMenu(AppleMenu,0);
   
   /*==============================================*/
   /* Get the File menu from the resource file and */
   /* install it at the end of the menu bar.       */
   /*==============================================*/
   
   FileMenu = GetMenu(FileID);
   InsertMenu(FileMenu,0);
   
   /*==============================================*/
   /* Get the Edit menu from the resource file and */
   /* install it at the end of the menu bar.       */
   /*==============================================*/
   
   EditMenu = GetMenu(EditID);
   InsertMenu(EditMenu,0);
   
   /*============================================*/
   /* Get the Buffer menu from the resource file */
   /* and install it at the end of the menu bar. */
   /*============================================*/
   
   BufferMenu = GetMenu(BufferID);
   InsertMenu(BufferMenu,0);
   
   /*===============================================*/
   /* Get the Execution menu from the resource file */
   /* and install it at the end of the menu bar.    */
   /*===============================================*/
   
   ExecutionMenu = GetMenu(ExecutionID);
   InsertMenu(ExecutionMenu,0);
   
   /*============================================*/
   /* Get the Watch menu from the resource file  */
   /* and install it at the end of the menu bar. */
   /*============================================*/
   
   WatchMenu = GetMenu(WatchID);
   InsertMenu(WatchMenu,0);
   
   /*============================================*/
   /* Get the Browse menu from the resource file */
   /* and install it at the end of the menu bar. */
   /*============================================*/
   
   BrowseMenu = GetMenu(BrowseID);
   InsertMenu(BrowseMenu,0);
   
   /*======================================*/
   /* Show the new menu bar on the screen. */
   /*======================================*/
   
   DrawMenuBar();
  }  