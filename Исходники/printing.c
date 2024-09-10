/* modify by Suttipong Kanakakorn Tue  08-29-1989  23:53:53 */
void printing(void)
{
    extern int blankskip();
    extern int pic_print;
    int i,j   ;
    int printquit;
    char st[5] ;
    char s[500] ;
    char p[500] ;
    char scol   ;
    if (graphicprint==YES)        /* if print in graphic mode */
       initializebufferandfont(); /* allocate graphic buffer and load font */
    scol=7;
    dispstrhgc("¡ÓÅÑ§¾ÔÁ¾ì COPY·Õè :     ",10-scol,12,0);
    dispstrhgc("  Ë¹éÒ·Õè :     ",30-scol,12,0);
    dispstrhgc("  ºÃÃ·Ñ´·Õè :     ",43-scol,12,0);
    dispstrhgc("  ËÂØ´ªÑèÇ¤ÃÒÇ <P> àÅÔ¡¾ÔÁ¾ì <Q>",58-scol,12,BOLDATTR);
    printquit = NO;
    PrinterInitialize();                     /* initialize printer */
    PrinterMasterSelectMode(0);              /*  Set to 10 Cpi */
    for (i=1; i<=copytoprint; i++) {
        linespace = find_line_space();
        PrinterSetFormLenghtInch(pagelength);
        seekbeginline();
        /*
        itoa(i,st,10);
        dispstrhgc("     ",25 - scol,12,0);
        dispstrhgc(st,30 - strlen(st) - scol,12,2);
        */
        dispprintf(25 - scol, 12 ,2, "%5d", i);
        curpage = pagenumberoffset;
        /*
        itoa(curpage,st,10);
        dispstrhgc("     ",38 - scol ,12,0);
        dispstrhgc(st,43 - strlen(st) - scol ,12,2);
        */
        dispprintf(38 - scol, 12, 0, "%5d", curpage);
        curline = 0;
        pic_print = NO;
        while ((fgets(s,500,fp) != NULL) && (printquit==NO)) {
            strfilter(s,0x8d);         /* delete 0x8d */
            strcpy(p,s);
            j=0;
            while ((p[j]<32) && (p[j]!=NULL)) j++;
            if (p[j] == '.') {    /* -to allow free format.       */
                dotcommand(&p[j]); /* do dotcommand then read next */
                if (newpage == YES) {  /* page break dotcmd (.pa ,.cp) found */
                    newpage = NO;      /* reset pagebreak status */
                    /*
                    PrinterSkipLine(((29+1)-(locpagetitle!=0)-(locheading!=0)
                                   -(locfooting!=0)-curline)*2 );
                    */
                    skip_line((userlineperpage+1) - curline);
                    curline = 0   ;
                    printtitle(footing,locfooting);
                    PrinterFormFeed();
                    if (curpage >= pageend-pagebegin+pagenumberoffset) break;
                    pagewait(0);  /* finish each page */
                    curpage++     ;
                    /*
                    itoa(curpage,st,10);
                    dispstrhgc("     ",38 - scol ,12,0);
                    dispstrhgc(st,43 - strlen(st) - scol ,12,2);
                    */
                    dispprintf(38 - scol, 12, 0, "%5d", curpage);
                }
	    } else {  /* Not dot commands */
                if (mailmergeflag == YES) {
                    mailmerge(s,p);
                    strcpy(s,p);
                }
                if (stdcode == NO) {
                    contostd(s);   /* convert from ku to so-mo-or */
                }
                marginset(s);      /* set left-right margin */
                if  (curline == 0)  {
                    printtitle(heading,locheading);
                    sprintf(p,pageformat,curpage);
                    printtitle(p,locpagetitle);
                    curline++;     /* begin curline = 1  */
                }
                /*
                itoa(curline,st,10);
                dispstrhgc("     ",53 - scol ,12,0);
                dispstrhgc(st,58 - strlen(st) - scol ,12,2);
                dispstrhgc(blankline,2,13,0);
                */
                dispprintf(53 - scol, 12, 0, "%5d", curline);
		dispprintf(2, 13, NORMALATTR, "%77s", " ");  /* Clear Line */
		dispprintf(2, 13, 0, "%-77.77s", s);         /* Disp CurLine */
/*
                dispstrhgc(extbarprinting ? "*":"-",1,1,REVERSEATTR);
*/
                preprinterloadline(s);
                curline++;
                if (curline > userlineperpage) {
                    curline = 0   ;
                    printtitle(footing,locfooting);
                    PrinterFormFeed();
                    if (curpage >= pageend-pagebegin+pagenumberoffset)
                        break;
                    pagewait(0);  /* finish each page */
                    curpage++     ;
                    itoa(curpage,st,10);
                    dispstrhgc("     ",38 - scol ,12,0);
                    dispstrhgc(st,43 - strlen(st) - scol ,12,2);
                }
                linewait(&printquit);
            }  /* end case of non-dotcommand  */
        }     /* end while */
        if (curline != 0) {
            /*
            PrinterSkipLine(((29+1)-(locpagetitle!=0)-(locheading!=0)
                          -(locfooting!=0)-curline) *2 ); /* skip to bottom */
            */
            skip_line((userlineperpage+1) - curline);
            printtitle(footing,locfooting);
            PrinterFormFeed();
        }
        fseek(fp,0L,SEEK_SET);  /* rewind file pointer */
        if (printquit==YES) break; /* exit for loop */
        pagewait(1);  /* finish each copy */
    }