void RenameHTML (void)
{
 char ch;

 int i;
 struct ffblk ffblk;
 int done;

 unsigned files_renamed = 0;

 done = findfirst("*.htm*",&ffblk,0);
// done = findfirst("f:\\zzz\\*.htm*",&ffblk,0);
 printf ("\n\r");

 while (!done)
 {
  Text.resize(0);
  FileName.resize(0);
  PageName.resize(0);
  DestName.resize(0);
  TitleName.resize(0);
  H1Name.resize(0);
  H2Name.resize(0);
  H3Name.resize(0);

//  FileName += "f:\\zzz\\";
  FileName += ffblk.ff_name;

  if (LoadFromFile (FileName) == -1)
  {
   done = findnext(&ffblk);
   continue;
  }

  if (Text.length() < 2) continue;

//  DestName += "f:\\zzz\\";

  FindTitle (TTB,TTE);
  TitleName  += Result;

  FindTitle (H1B,H1E);
  H1Name     += Result;

  FindTitle (H2B,H2E);
  H2Name     += Result;

  FindTitle (H3B,H3E);
  H3Name     += Result;

  if (TitleName.length() + H1Name.length() + H2Name.length() + H3Name.length() > 5)
  {

   if (TitleName.length() > 1) PageName += TitleName;
   if (H1Name.length() > 1)    PageName += '-'+H1Name;
   if (H2Name.length() > 1)    PageName += '-'+H2Name;
   if (H3Name.length() > 1)    PageName += '-'+H3Name;

/*
   printf ("\n\r------------------------------------------\n\r");
   printf ("Original File Name : %s\n\r",FileName.c_str());

   if (TitleName.length() > 1)
   {
    printf ("Title : %s\n\r\n\r",TitleName.c_str());
    PageName += TitleName;
   }

   if (H1Name.length() > 1)
   {
    printf ("Header 1 : %s\n\r",H1Name.c_str());
    printf ("to include press [ Enter ]\n\r");
    ch = getch();
    if (ch == '\xd') PageName += '-'+H1Name;
    else
    if (ch == 0) getch();
   }

   if (H2Name.length() > 1)
   {
    printf ("Header 2 : %s\n\r",H2Name.c_str());
    printf ("to include press [ Enter ]\n\r");
    ch = getch();
    if (ch == '\xd') PageName += '-'+H2Name;
    else
    if (ch == 0) getch();
   }

   if (H3Name.length() > 1)
   {
    printf ("Header 3 : %s\n\r",H3Name.c_str());
    printf ("to include press [ Enter ]\n\r");
    ch = getch();
    if (ch == '\xd') PageName += '-'+H3Name;
    else
    if (ch == 0) getch();
   }
*/
   if (PageName.length() > 240) PageName.resize(240);

   KillNotAllowed (PageName);
   DestName += PageName + ".hhttmmll";

//   printf ("New File Name      : %s\n\r",DestName.c_str());
//   printf ("----------------------------------------------\n\r");

   if (rename (FileName.c_str(),DestName.c_str()) == -1)
    printf ("Cannot rename \n\r'%s' to \n\r'%s' \n\r",FileName.c_str(),DestName.c_str());
   else
   ++files_renamed;
  }
  done = findnext(&ffblk);
 }
 printf ("\n\r[%d] file(s) renamed",files_renamed);
}