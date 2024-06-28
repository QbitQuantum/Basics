﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'mshtmcid.pas' rev: 34.00 (Windows)

#ifndef MshtmcidHPP
#define MshtmcidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------

namespace Mshtmcid
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const System::Int8 IDM_UNKNOWN = System::Int8(0x0);
static const System::Int8 IDM_ALIGNBOTTOM = System::Int8(0x1);
static const System::Int8 IDM_ALIGNHORIZONTALCENTERS = System::Int8(0x2);
static const System::Int8 IDM_ALIGNLEFT = System::Int8(0x3);
static const System::Int8 IDM_ALIGNRIGHT = System::Int8(0x4);
static const System::Int8 IDM_ALIGNTOGRID = System::Int8(0x5);
static const System::Int8 IDM_ALIGNTOP = System::Int8(0x6);
static const System::Int8 IDM_ALIGNVERTICALCENTERS = System::Int8(0x7);
static const System::Int8 IDM_ARRANGEBOTTOM = System::Int8(0x8);
static const System::Int8 IDM_ARRANGERIGHT = System::Int8(0x9);
static const System::Int8 IDM_BRINGFORWARD = System::Int8(0xa);
static const System::Int8 IDM_BRINGTOFRONT = System::Int8(0xb);
static const System::Int8 IDM_CENTERHORIZONTALLY = System::Int8(0xc);
static const System::Int8 IDM_CENTERVERTICALLY = System::Int8(0xd);
static const System::Int8 IDM_CODE = System::Int8(0xe);
static const System::Int8 IDM_DELETE = System::Int8(0x11);
static const System::Int8 IDM_FONTNAME = System::Int8(0x12);
static const System::Int8 IDM_FONTSIZE = System::Int8(0x13);
static const System::Int8 IDM_GROUP = System::Int8(0x14);
static const System::Int8 IDM_HORIZSPACECONCATENATE = System::Int8(0x15);
static const System::Int8 IDM_HORIZSPACEDECREASE = System::Int8(0x16);
static const System::Int8 IDM_HORIZSPACEINCREASE = System::Int8(0x17);
static const System::Int8 IDM_HORIZSPACEMAKEEQUAL = System::Int8(0x18);
static const System::Int8 IDM_INSERTOBJECT = System::Int8(0x19);
static const System::Int8 IDM_MULTILEVELREDO = System::Int8(0x1e);
static const System::Int8 IDM_SENDBACKWARD = System::Int8(0x20);
static const System::Int8 IDM_SENDTOBACK = System::Int8(0x21);
static const System::Int8 IDM_SHOWTABLE = System::Int8(0x22);
static const System::Int8 IDM_SIZETOCONTROL = System::Int8(0x23);
static const System::Int8 IDM_SIZETOCONTROLHEIGHT = System::Int8(0x24);
static const System::Int8 IDM_SIZETOCONTROLWIDTH = System::Int8(0x25);
static const System::Int8 IDM_SIZETOFIT = System::Int8(0x26);
static const System::Int8 IDM_SIZETOGRID = System::Int8(0x27);
static const System::Int8 IDM_SNAPTOGRID = System::Int8(0x28);
static const System::Int8 IDM_TABORDER = System::Int8(0x29);
static const System::Int8 IDM_TOOLBOX = System::Int8(0x2a);
static const System::Int8 IDM_MULTILEVELUNDO = System::Int8(0x2c);
static const System::Int8 IDM_UNGROUP = System::Int8(0x2d);
static const System::Int8 IDM_VERTSPACECONCATENATE = System::Int8(0x2e);
static const System::Int8 IDM_VERTSPACEDECREASE = System::Int8(0x2f);
static const System::Int8 IDM_VERTSPACEINCREASE = System::Int8(0x30);
static const System::Int8 IDM_VERTSPACEMAKEEQUAL = System::Int8(0x31);
static const System::Int8 IDM_JUSTIFYFULL = System::Int8(0x32);
static const System::Int8 IDM_BACKCOLOR = System::Int8(0x33);
static const System::Int8 IDM_BOLD = System::Int8(0x34);
static const System::Int8 IDM_BORDERCOLOR = System::Int8(0x35);
static const System::Int8 IDM_FLAT = System::Int8(0x36);
static const System::Int8 IDM_FORECOLOR = System::Int8(0x37);
static const System::Int8 IDM_ITALIC = System::Int8(0x38);
static const System::Int8 IDM_JUSTIFYCENTER = System::Int8(0x39);
static const System::Int8 IDM_JUSTIFYGENERAL = System::Int8(0x3a);
static const System::Int8 IDM_JUSTIFYLEFT = System::Int8(0x3b);
static const System::Int8 IDM_JUSTIFYRIGHT = System::Int8(0x3c);
static const System::Int8 IDM_RAISED = System::Int8(0x3d);
static const System::Int8 IDM_SUNKEN = System::Int8(0x3e);
static const System::Int8 IDM_UNDERLINE = System::Int8(0x3f);
static const System::Int8 IDM_CHISELED = System::Int8(0x40);
static const System::Int8 IDM_ETCHED = System::Int8(0x41);
static const System::Int8 IDM_SHADOWED = System::Int8(0x42);
static const System::Int8 IDM_FIND = System::Int8(0x43);
static const System::Int8 IDM_SHOWGRID = System::Int8(0x45);
static const System::Int8 IDM_OBJECTVERBLIST0 = System::Int8(0x48);
static const System::Int8 IDM_OBJECTVERBLIST1 = System::Int8(0x49);
static const System::Int8 IDM_OBJECTVERBLIST2 = System::Int8(0x4a);
static const System::Int8 IDM_OBJECTVERBLIST3 = System::Int8(0x4b);
static const System::Int8 IDM_OBJECTVERBLIST4 = System::Int8(0x4c);
static const System::Int8 IDM_OBJECTVERBLIST5 = System::Int8(0x4d);
static const System::Int8 IDM_OBJECTVERBLIST6 = System::Int8(0x4e);
static const System::Int8 IDM_OBJECTVERBLIST7 = System::Int8(0x4f);
static const System::Int8 IDM_OBJECTVERBLIST8 = System::Int8(0x50);
static const System::Int8 IDM_OBJECTVERBLIST9 = System::Int8(0x51);
static const System::Int8 IDM_OBJECTVERBLISTLAST = System::Int8(0x51);
static const System::Int8 IDM_CONVERTOBJECT = System::Int8(0x52);
static const System::Int8 IDM_CUSTOMCONTROL = System::Int8(0x53);
static const System::Int8 IDM_CUSTOMIZEITEM = System::Int8(0x54);
static const System::Int8 IDM_RENAME = System::Int8(0x55);
static const System::Int8 IDM_IMPORT = System::Int8(0x56);
static const System::Int8 IDM_NEWPAGE = System::Int8(0x57);
static const System::Int8 IDM_MOVE = System::Int8(0x58);
static const System::Int8 IDM_CANCEL = System::Int8(0x59);
static const System::Int8 IDM_FONT = System::Int8(0x5a);
static const System::Int8 IDM_STRIKETHROUGH = System::Int8(0x5b);
static const System::Int8 IDM_DELETEWORD = System::Int8(0x5c);
static const System::Int8 IDM_EXECPRINT = System::Int8(0x5d);
static const System::Int8 IDM_JUSTIFYNONE = System::Int8(0x5e);
static const System::Int8 IDM_TRISTATEBOLD = System::Int8(0x5f);
static const System::Int8 IDM_TRISTATEITALIC = System::Int8(0x60);
static const System::Int8 IDM_TRISTATEUNDERLINE = System::Int8(0x61);
static const System::Word IDM_FOLLOW_ANCHOR = System::Word(0x7d8);
static const System::Word IDM_INSINPUTIMAGE = System::Word(0x842);
static const System::Word IDM_INSINPUTBUTTON = System::Word(0x843);
static const System::Word IDM_INSINPUTRESET = System::Word(0x844);
static const System::Word IDM_INSINPUTSUBMIT = System::Word(0x845);
static const System::Word IDM_INSINPUTUPLOAD = System::Word(0x846);
static const System::Word IDM_INSFIELDSET = System::Word(0x847);
static const System::Word IDM_PASTEINSERT = System::Word(0x848);
static const System::Word IDM_REPLACE = System::Word(0x849);
static const System::Word IDM_EDITSOURCE = System::Word(0x84a);
static const System::Word IDM_BOOKMARK = System::Word(0x84b);
static const System::Word IDM_HYPERLINK = System::Word(0x84c);
static const System::Word IDM_UNLINK = System::Word(0x84d);
static const System::Word IDM_BROWSEMODE = System::Word(0x84e);
static const System::Word IDM_EDITMODE = System::Word(0x84f);
static const System::Word IDM_UNBOOKMARK = System::Word(0x850);
static const System::Word IDM_TOOLBARS = System::Word(0x852);
static const System::Word IDM_STATUSBAR = System::Word(0x853);
static const System::Word IDM_FORMATMARK = System::Word(0x854);
static const System::Word IDM_TEXTONLY = System::Word(0x855);
static const System::Word IDM_OPTIONS = System::Word(0x857);
static const System::Word IDM_FOLLOWLINKC = System::Word(0x858);
static const System::Word IDM_FOLLOWLINKN = System::Word(0x859);
static const System::Word IDM_VIEWSOURCE = System::Word(0x85b);
static const System::Word IDM_ZOOMPOPUP = System::Word(0x85c);
static const System::Word IDM_BASELINEFONT1 = System::Word(0x85d);
static const System::Word IDM_BASELINEFONT2 = System::Word(0x85e);
static const System::Word IDM_BASELINEFONT3 = System::Word(0x85f);
static const System::Word IDM_BASELINEFONT4 = System::Word(0x860);
static const System::Word IDM_BASELINEFONT5 = System::Word(0x861);
static const System::Word IDM_HORIZONTALLINE = System::Word(0x866);
static const System::Word IDM_LINEBREAKNORMAL = System::Word(0x867);
static const System::Word IDM_LINEBREAKLEFT = System::Word(0x868);
static const System::Word IDM_LINEBREAKRIGHT = System::Word(0x869);
static const System::Word IDM_LINEBREAKBOTH = System::Word(0x86a);
static const System::Word IDM_NONBREAK = System::Word(0x86b);
static const System::Word IDM_SPECIALCHAR = System::Word(0x86c);
static const System::Word IDM_HTMLSOURCE = System::Word(0x86d);
static const System::Word IDM_IFRAME = System::Word(0x86e);
static const System::Word IDM_HTMLCONTAIN = System::Word(0x86f);
static const System::Word IDM_TEXTBOX = System::Word(0x871);
static const System::Word IDM_TEXTAREA = System::Word(0x872);
static const System::Word IDM_CHECKBOX = System::Word(0x873);
static const System::Word IDM_RADIOBUTTON = System::Word(0x874);
static const System::Word IDM_DROPDOWNBOX = System::Word(0x875);
static const System::Word IDM_LISTBOX = System::Word(0x876);
static const System::Word IDM_BUTTON = System::Word(0x877);
static const System::Word IDM_IMAGE = System::Word(0x878);
static const System::Word IDM_OBJECT = System::Word(0x879);
static const System::Word IDM_1D = System::Word(0x87a);
static const System::Word IDM_IMAGEMAP = System::Word(0x87b);
static const System::Word IDM_FILE = System::Word(0x87c);
static const System::Word IDM_COMMENT = System::Word(0x87d);
static const System::Word IDM_SCRIPT = System::Word(0x87e);
static const System::Word IDM_JAVAAPPLET = System::Word(0x87f);
static const System::Word IDM_PLUGIN = System::Word(0x880);
static const System::Word IDM_PAGEBREAK = System::Word(0x881);
static const System::Word IDM_HTMLAREA = System::Word(0x882);
static const System::Word IDM_PARAGRAPH = System::Word(0x884);
static const System::Word IDM_FORM = System::Word(0x885);
static const System::Word IDM_MARQUEE = System::Word(0x886);
static const System::Word IDM_LIST = System::Word(0x887);
static const System::Word IDM_ORDERLIST = System::Word(0x888);
static const System::Word IDM_UNORDERLIST = System::Word(0x889);
static const System::Word IDM_INDENT = System::Word(0x88a);
static const System::Word IDM_OUTDENT = System::Word(0x88b);
static const System::Word IDM_PREFORMATTED = System::Word(0x88c);
static const System::Word IDM_ADDRESS = System::Word(0x88d);
static const System::Word IDM_BLINK = System::Word(0x88e);
static const System::Word IDM_DIV = System::Word(0x88f);
static const System::Word IDM_TABLEINSERT = System::Word(0x898);
static const System::Word IDM_RCINSERT = System::Word(0x899);
static const System::Word IDM_CELLINSERT = System::Word(0x89a);
static const System::Word IDM_CAPTIONINSERT = System::Word(0x89b);
static const System::Word IDM_CELLMERGE = System::Word(0x89c);
static const System::Word IDM_CELLSPLIT = System::Word(0x89d);
static const System::Word IDM_CELLSELECT = System::Word(0x89e);
static const System::Word IDM_ROWSELECT = System::Word(0x89f);
static const System::Word IDM_COLUMNSELECT = System::Word(0x8a0);
static const System::Word IDM_TABLESELECT = System::Word(0x8a1);
static const System::Word IDM_TABLEPROPERTIES = System::Word(0x8a2);
static const System::Word IDM_CELLPROPERTIES = System::Word(0x8a3);
static const System::Word IDM_ROWINSERT = System::Word(0x8a4);
static const System::Word IDM_COLUMNINSERT = System::Word(0x8a5);
static const System::Word IDM_HELP_CONTENT = System::Word(0x8ac);
static const System::Word IDM_HELP_ABOUT = System::Word(0x8ad);
static const System::Word IDM_HELP_README = System::Word(0x8ae);
static const System::Word IDM_REMOVEFORMAT = System::Word(0x8b6);
static const System::Word IDM_PAGEINFO = System::Word(0x8b7);
static const System::Word IDM_TELETYPE = System::Word(0x8b8);
static const System::Word IDM_GETBLOCKFMTS = System::Word(0x8b9);
static const System::Word IDM_BLOCKFMT = System::Word(0x8ba);
static const System::Word IDM_SHOWHIDE_CODE = System::Word(0x8bb);
static const System::Word IDM_TABLE = System::Word(0x8bc);
static const System::Word IDM_COPYFORMAT = System::Word(0x8bd);
static const System::Word IDM_PASTEFORMAT = System::Word(0x8be);
static const System::Word IDM_GOTO = System::Word(0x8bf);
static const System::Word IDM_CHANGEFONT = System::Word(0x8c0);
static const System::Word IDM_CHANGEFONTSIZE = System::Word(0x8c1);
static const System::Word IDM_CHANGECASE = System::Word(0x8c6);
static const System::Word IDM_SHOWSPECIALCHAR = System::Word(0x8c9);
static const System::Word IDM_SUBSCRIPT = System::Word(0x8c7);
static const System::Word IDM_SUPERSCRIPT = System::Word(0x8c8);
static const System::Word IDM_CENTERALIGNPARA = System::Word(0x8ca);
static const System::Word IDM_LEFTALIGNPARA = System::Word(0x8cb);
static const System::Word IDM_RIGHTALIGNPARA = System::Word(0x8cc);
static const System::Word IDM_REMOVEPARAFORMAT = System::Word(0x8cd);
static const System::Word IDM_APPLYNORMAL = System::Word(0x8ce);
static const System::Word IDM_APPLYHEADING1 = System::Word(0x8cf);
static const System::Word IDM_APPLYHEADING2 = System::Word(0x8d0);
static const System::Word IDM_APPLYHEADING3 = System::Word(0x8d1);
static const System::Word IDM_DOCPROPERTIES = System::Word(0x8d4);
static const System::Word IDM_ADDFAVORITES = System::Word(0x8d5);
static const System::Word IDM_COPYSHORTCUT = System::Word(0x8d6);
static const System::Word IDM_SAVEBACKGROUND = System::Word(0x8d7);
static const System::Word IDM_SETWALLPAPER = System::Word(0x8d8);
static const System::Word IDM_COPYBACKGROUND = System::Word(0x8d9);
static const System::Word IDM_CREATESHORTCUT = System::Word(0x8da);
static const System::Word IDM_PAGE = System::Word(0x8db);
static const System::Word IDM_SAVETARGET = System::Word(0x8dc);
static const System::Word IDM_SHOWPICTURE = System::Word(0x8dd);
static const System::Word IDM_SAVEPICTURE = System::Word(0x8de);
static const System::Word IDM_DYNSRCPLAY = System::Word(0x8df);
static const System::Word IDM_DYNSRCSTOP = System::Word(0x8e0);
static const System::Word IDM_PRINTTARGET = System::Word(0x8e1);
static const System::Word IDM_IMGARTPLAY = System::Word(0x8e2);
static const System::Word IDM_IMGARTSTOP = System::Word(0x8e3);
static const System::Word IDM_IMGARTREWIND = System::Word(0x8e4);
static const System::Word IDM_PRINTQUERYJOBSPENDING = System::Word(0x8e5);
static const System::Word IDM_SETDESKTOPITEM = System::Word(0x8e6);
static const System::Word IDM_CONTEXTMENU = System::Word(0x8e8);
static const System::Word IDM_GOBACKWARD = System::Word(0x8ea);
static const System::Word IDM_GOFORWARD = System::Word(0x8eb);
static const System::Word IDM_PRESTOP = System::Word(0x8ec);
static const System::Word IDM_GOTOCLIPBOARDADDRESS = System::Word(0x8ed);
static const System::Word IDM_GOTOCLIPBOARDTEXT = System::Word(0x8ee);
static const System::Word IDM_MP_MYPICS = System::Word(0x8ef);
static const System::Word IDM_MP_EMAILPICTURE = System::Word(0x8f0);
static const System::Word IDM_MP_PRINTPICTURE = System::Word(0x8f1);
static const System::Word IDM_CREATELINK = System::Word(0x8f2);
static const System::Word IDM_COPYCONTENT = System::Word(0x8f3);
static const System::Word IDM_LANGUAGE = System::Word(0x8f4);
static const System::Word IDM_GETPRINTTEMPLATE = System::Word(0x8f7);
static const System::Word IDM_SETPRINTTEMPLATE = System::Word(0x8f8);
static const System::Word IDM_TEMPLATE_PAGESETUP = System::Word(0x8fa);
static const System::Word IDM_REFRESH = System::Word(0x8fc);
static const System::Word IDM_STOPDOWNLOAD = System::Word(0x8fd);
static const System::Word IDM_ENABLE_INTERACTION = System::Word(0x8fe);
static const System::Word IDM_LAUNCHDEBUGGER = System::Word(0x906);
static const System::Word IDM_BREAKATNEXT = System::Word(0x907);
static const System::Word IDM_INSINPUTHIDDEN = System::Word(0x908);
static const System::Word IDM_INSINPUTPASSWORD = System::Word(0x909);
static const System::Word IDM_OVERWRITE = System::Word(0x90a);
static const System::Word IDM_PARSECOMPLETE = System::Word(0x90b);
static const System::Word IDM_HTMLEDITMODE = System::Word(0x90c);
static const System::Word IDM_REGISTRYREFRESH = System::Word(0x90d);
static const System::Word IDM_COMPOSESETTINGS = System::Word(0x90e);
static const System::Word IDM_SHOWALLTAGS = System::Word(0x917);
static const System::Word IDM_SHOWALIGNEDSITETAGS = System::Word(0x911);
static const System::Word IDM_SHOWSCRIPTTAGS = System::Word(0x912);
static const System::Word IDM_SHOWSTYLETAGS = System::Word(0x913);
static const System::Word IDM_SHOWCOMMENTTAGS = System::Word(0x914);
static const System::Word IDM_SHOWAREATAGS = System::Word(0x915);
static const System::Word IDM_SHOWUNKNOWNTAGS = System::Word(0x916);
static const System::Word IDM_SHOWMISCTAGS = System::Word(0x910);
static const System::Word IDM_SHOWZEROBORDERATDESIGNTIME = System::Word(0x918);
static const System::Word IDM_AUTODETECT = System::Word(0x919);
static const System::Word IDM_SCRIPTDEBUGGER = System::Word(0x91a);
static const System::Word IDM_GETBYTESDOWNLOADED = System::Word(0x91b);
static const System::Word IDM_NOACTIVATENORMALOLECONTROLS = System::Word(0x91c);
static const System::Word IDM_NOACTIVATEDESIGNTIMECONTROLS = System::Word(0x91d);
static const System::Word IDM_NOACTIVATEJAVAAPPLETS = System::Word(0x91e);
static const System::Word IDM_NOFIXUPURLSONPASTE = System::Word(0x91f);
static const System::Word IDM_EMPTYGLYPHTABLE = System::Word(0x920);
static const System::Word IDM_ADDTOGLYPHTABLE = System::Word(0x921);
static const System::Word IDM_REMOVEFROMGLYPHTABLE = System::Word(0x922);
static const System::Word IDM_REPLACEGLYPHCONTENTS = System::Word(0x923);
static const System::Word IDM_SHOWWBRTAGS = System::Word(0x924);
static const System::Word IDM_PERSISTSTREAMSYNC = System::Word(0x925);
static const System::Word IDM_SETDIRTY = System::Word(0x926);
static const System::Word IDM_RUNURLSCRIPT = System::Word(0x927);
static const System::Word IDM_DIRLTR = System::Word(0x92e);
static const System::Word IDM_DIRRTL = System::Word(0x92f);
static const System::Word IDM_BLOCKDIRLTR = System::Word(0x930);
static const System::Word IDM_BLOCKDIRRTL = System::Word(0x931);
static const System::Word IDM_INLINEDIRLTR = System::Word(0x932);
static const System::Word IDM_INLINEDIRRTL = System::Word(0x933);
static const System::Word IDM_ISTRUSTEDDLG = System::Word(0x934);
static const System::Word IDM_INSERTSPAN = System::Word(0x935);
static const System::Word IDM_LOCALIZEEDITOR = System::Word(0x936);
static const System::Word IDM_SAVEPRETRANSFORMSOURCE = System::Word(0x942);
static const System::Word IDM_VIEWPRETRANSFORMSOURCE = System::Word(0x943);
static const System::Word IDM_SCROLL_HERE = System::Word(0x94c);
static const System::Word IDM_SCROLL_TOP = System::Word(0x94d);
static const System::Word IDM_SCROLL_BOTTOM = System::Word(0x94e);
static const System::Word IDM_SCROLL_PAGEUP = System::Word(0x94f);
static const System::Word IDM_SCROLL_PAGEDOWN = System::Word(0x950);
static const System::Word IDM_SCROLL_UP = System::Word(0x951);
static const System::Word IDM_SCROLL_DOWN = System::Word(0x952);
static const System::Word IDM_SCROLL_LEFTEDGE = System::Word(0x953);
static const System::Word IDM_SCROLL_RIGHTEDGE = System::Word(0x954);
static const System::Word IDM_SCROLL_PAGELEFT = System::Word(0x955);
static const System::Word IDM_SCROLL_PAGERIGHT = System::Word(0x956);
static const System::Word IDM_SCROLL_LEFT = System::Word(0x957);
static const System::Word IDM_SCROLL_RIGHT = System::Word(0x958);
static const System::Word IDM_MULTIPLESELECTION = System::Word(0x959);
static const System::Word IDM_2D_POSITION = System::Word(0x95a);
static const System::Word IDM_2D_ELEMENT = System::Word(0x95b);
static const System::Word IDM_1D_ELEMENT = System::Word(0x95c);
static const System::Word IDM_ABSOLUTE_POSITION = System::Word(0x95d);
static const System::Word IDM_LIVERESIZE = System::Word(0x95e);
static const System::Word IDM_ATOMICSELECTION = System::Word(0x95f);
static const System::Word IDM_AUTOURLDETECT_MODE = System::Word(0x960);
static const System::Word IDM_IE50_PASTE = System::Word(0x961);
static const System::Word IDM_IE50_PASTE_MODE = System::Word(0x962);
static const System::Word IDM_GETIPRINT = System::Word(0x963);
static const System::Word IDM_DISABLE_EDITFOCUS_UI = System::Word(0x964);
static const System::Word IDM_RESPECTVISIBILITY_INDESIGN = System::Word(0x965);
static const System::Word IDM_CSSEDITING_LEVEL = System::Word(0x966);
static const System::Word IDM_UI_OUTDENT = System::Word(0x967);
static const System::Word IDM_UPDATEPAGESTATUS = System::Word(0x968);
static const System::Word IDM_IME_ENABLE_RECONVERSION = System::Word(0x969);
static const System::Word IDM_KEEPSELECTION = System::Word(0x96a);
static const System::Word IDM_UNLOADDOCUMENT = System::Word(0x96b);
static const System::Word IDM_OVERRIDE_CURSOR = System::Word(0x974);
static const System::Word IDM_PEERHITTESTSAMEINEDIT = System::Word(0x977);
static const System::Word IDM_TRUSTAPPCACHE = System::Word(0x979);
static const System::Word IDM_BACKGROUNDIMAGECACHE = System::Word(0x97e);
static const System::Word IDM_GETUSERACTIONTIME = System::Word(0x97f);
static const System::Word IDM_BEGINUSERACTION = System::Word(0x980);
static const System::Word IDM_ENDUSERACTION = System::Word(0x981);
static const System::Word IDM_SETCUSTOMCURSOR = System::Word(0x982);
static const System::Word IDM_FOLLOWLINKT = System::Word(0x983);
static const System::Word IDM_CARETBROWSINGMODE = System::Word(0x984);
static const System::Word IDM_STYLEMENU_SETNOSTYLE = System::Word(0x985);
static const System::Word IDM_STYLEMENU_GETNOSTYLE = System::Word(0x986);
static const System::Word IDM_STYLEMENU_GETPREFSTYLE = System::Word(0x987);
static const System::Word IDM_STYLEMENU_CHANGESELECTEDSTYLE = System::Word(0x988);
static const System::Word IDM_MEDIA_PLAYPAUSE = System::Word(0x989);
static const System::Word IDM_MEDIA_MUTEUNMUTE = System::Word(0x98a);
static const System::Word IDM_MEDIA_PLAY = System::Word(0x98b);
static const System::Word IDM_MEDIA_PAUSE = System::Word(0x98c);
static const System::Word IDM_MEDIA_STOP = System::Word(0x98d);
static const System::Word IDM_MEDIA_FULLSCREEN_TOGGLE = System::Word(0x98e);
static const System::Word IDM_MEDIA_FULLSCREEN_EXIT = System::Word(0x98f);
static const System::Word IDM_MEDIA_VOLUME_UP = System::Word(0x990);
static const System::Word IDM_MEDIA_VOLUME_DOWN = System::Word(0x991);
static const System::Word IDM_MEDIA_SEEK_TO_START = System::Word(0x992);
static const System::Word IDM_MEDIA_SEEK_TO_END = System::Word(0x993);
static const System::Word IDM_MEDIA_SEEK_FWD_SMALL = System::Word(0x994);
static const System::Word IDM_MEDIA_SEEK_BACK_SMALL = System::Word(0x995);
static const System::Word IDM_MEDIA_SEEK_FWD_LARGE = System::Word(0x996);
static const System::Word IDM_MEDIA_SEEK_BACK_LARGE = System::Word(0x997);
static const System::Word IDM_MEDIA_RATE_FASTER = System::Word(0x998);
static const System::Word IDM_MEDIA_RATE_SLOWER = System::Word(0x999);
static const System::Word IDM_MEDIA_SHOWCONTROLS_TOGGLE = System::Word(0x99a);
static const System::Word IDM_MEDIA_ZOOMMODE_TOGGLE = System::Word(0x99b);
static const System::Word IDM_MEDIA_FRAMESTEP_FWD = System::Word(0x99c);
static const System::Word IDM_MEDIA_FRAMESTEP_BACK = System::Word(0x99d);
static const System::Word IDM_MEDIA_MUTE = System::Word(0x99e);
static const System::Word IDM_MEDIA_UNMUTE = System::Word(0x99f);
static const System::Word IDM_MEDIA_SHOW_AUDIO_ACCESS = System::Word(0x9a0);
static const System::Word IDM_MEDIA_SHOW_SUBTITLE_ACCESS = System::Word(0x9a1);
static const System::Word IDM_MEDIA_PLAYRATE0 = System::Word(0x9b0);
static const System::Word IDM_MEDIA_PLAYRATE1 = System::Word(0x9b1);
static const System::Word IDM_MEDIA_PLAYRATE2 = System::Word(0x9b2);
static const System::Word IDM_MEDIA_PLAYRATE3 = System::Word(0x9b3);
static const System::Word IDM_MEDIA_PLAYRATE4 = System::Word(0x9b4);
static const System::Word IDM_MEDIA_PLAYRATE5 = System::Word(0x9b5);
static const System::Word IDM_MEDIA_PLAYRATE6 = System::Word(0x9b6);
static const System::Word IDM_MEDIA_PLAYRATE7 = System::Word(0x9b7);
static const System::Word IDM_MEDIA_PLAYRATE8 = System::Word(0x9b8);
static const System::Word IDM_MEDIA_PLAYRATE9 = System::Word(0x9b9);
static const System::Word IDM_PASTECONTENTONLY = System::Word(0x9c4);
static const System::Word IDM_PASTETEXTONLY = System::Word(0x9c5);
static const System::Word IDM_DEFAULTBLOCK = System::Word(0x179e);
static const System::Word IDM_MIMECSET__FIRST__ = System::Word(0xe19);
static const System::Word IDM_MIMECSET__LAST__ = System::Word(0xe73);
static const System::Word IDM_MENUEXT_FIRST__ = System::Word(0xe74);
static const System::Word IDM_MENUEXT_LAST__ = System::Word(0xe94);
static const System::Word IDM_MENUEXT_COUNT = System::Word(0xe95);
static const System::Word IDM_ADDCONSOLEMESSAGERECEIVER = System::Word(0xed8);
static const System::Word IDM_REMOVECONSOLEMESSAGERECEIVER = System::Word(0xed9);
static const System::Word IDM_STARTDIAGNOSTICSMODE = System::Word(0xeda);
static const System::Word IDM_GETSCRIPTENGINE = System::Word(0xedb);
static const System::Word IDM_ADDDEBUGCALLBACKRECEIVER = System::Word(0xedc);
static const System::Word IDM_REMOVEDEBUGCALLBACKRECEIVER = System::Word(0xedd);
static const System::Word IDM_DEFAULTPARAGRAPHSEPARATOR = System::Word(0xf3c);
static const System::Word IDM_BEGINUNDOUNIT = System::Word(0xf3d);
static const System::Word IDM_ENDUNDOUNIT = System::Word(0xf3e);
static const System::Word IDM_CLEARUNDO = System::Word(0xf3f);
static const System::Word IDM_INSPECTELEMENT = System::Word(0xf40);
static const System::Word IDM_OPEN = System::Word(0x7d0);
static const System::Word IDM_NEW = System::Word(0x7d1);
static const System::Int8 IDM_SAVE = System::Int8(0x46);
static const System::Int8 IDM_SAVEAS = System::Int8(0x47);
static const System::Word IDM_SAVECOPYAS = System::Word(0x7d2);
static const System::Word IDM_PRINTPREVIEW = System::Word(0x7d3);
static const System::Word IDM_SHOWPRINT = System::Word(0x7da);
static const System::Word IDM_SHOWPAGESETUP = System::Word(0x7db);
static const System::Int8 IDM_PRINT = System::Int8(0x1b);
static const System::Word IDM_PAGESETUP = System::Word(0x7d4);
static const System::Word IDM_SPELL = System::Word(0x7d5);
static const System::Word IDM_PASTESPECIAL = System::Word(0x7d6);
static const System::Word IDM_CLEARSELECTION = System::Word(0x7d7);
static const System::Int8 IDM_PROPERTIES = System::Int8(0x1c);
static const System::Int8 IDM_REDO = System::Int8(0x1d);
static const System::Int8 IDM_UNDO = System::Int8(0x2b);
static const System::Int8 IDM_SELECTALL = System::Int8(0x1f);
static const System::Int8 IDM_ZOOMPERCENT = System::Int8(0x32);
static const System::Int8 IDM_GETZOOM = System::Int8(0x44);
static const System::Word IDM_STOP = System::Word(0x85a);
static const System::Int8 IDM_COPY = System::Int8(0xf);
static const System::Int8 IDM_CUT = System::Int8(0x10);
static const System::Int8 IDM_PASTE = System::Int8(0x1a);
static const System::Int8 CMD_ZOOM_PAGEWIDTH = System::Int8(-1);
static const System::Int8 CMD_ZOOM_ONEPAGE = System::Int8(-2);
static const System::Int8 CMD_ZOOM_TWOPAGES = System::Int8(-3);
static const System::Int8 CMD_ZOOM_SELECTION = System::Int8(-4);
static const System::Int8 CMD_ZOOM_FIT = System::Int8(-5);
static const System::Int8 IDM_CONTEXT = System::Int8(0x1);
static const System::Int8 IDM_HWND = System::Int8(0x2);
static const System::Word IDM_NEW_TOPLEVELWINDOW = System::Word(0x1b8a);
static const System::Word IDM_PRESERVEUNDOALWAYS = System::Word(0x17a1);
static const System::Word IDM_PERSISTDEFAULTVALUES = System::Word(0x1bbc);
static const System::Word IDM_PROTECTMETATAGS = System::Word(0x1bbd);
static const System::Word IDM_GETFRAMEZONE = System::Word(0x1795);
static const System::Word IDM_REFRESH_THIS = System::Word(0x179a);
static const System::Word IDM_MENUEXT_PLACEHOLDER = System::Word(0x179f);
static const System::Word IDM_FIRE_PRINTTEMPLATEUP = System::Word(0x3a98);
static const System::Word IDM_FIRE_PRINTTEMPLATEDOWN = System::Word(0x3a99);
static const System::Word IDM_SETPRINTHANDLES = System::Word(0x3a9a);
static const System::Word IDM_CLEARAUTHENTICATIONCACHE = System::Word(0x3a9b);
static const System::Word IDM_GETUSERINITFLAGS = System::Word(0x3a9c);
static const System::Word IDM_GETDOCDLGFLAGS = System::Word(0x3a9d);
static const System::Word IDM_OLEWINDOWSTATECHANGED = System::Word(0x3a9e);
static const System::Word IDM_ACTIVEXINSTALLSCOPE = System::Word(0x3a9f);
static const System::Word IDM_SETSESSIONDOCUMENTMODE = System::Word(0x3aa0);
static const System::Word IDM_GETSESSIONDOCUMENTMODE = System::Word(0x3aa1);
static const System::Word IDM_SETPROFILINGONSTART = System::Word(0x3aa2);
static const System::Word IDM_GETPROFILINGONSTART = System::Word(0x3aa3);
static const System::Word IDM_SETSCRIPTCONSOLE = System::Word(0x3aa4);
static const System::Word IDM_SETNAVIGATEEVENTSINK = System::Word(0x3aa5);
static const System::Word IDM_SETDEVTOOLBARCONSOLE = System::Word(0x3aa8);
static const System::Word IDM_POPSTATEEVENT = System::Word(0x3aa9);
static const System::Word IDM_SETPARTIALLAYOUTSTATUS = System::Word(0x3aad);
static const System::Word IDM_GETPARTIALLAYOUTSTATUS = System::Word(0x3aae);
static const System::Word IDM_ADDPARTIALTESTSTEPCOUNT = System::Word(0x3aaf);
static const System::Word IDM_SETL9QUIRKSEMULATIONENABLED = System::Word(0x3ab0);
static const System::Word IDM_GETL9QUIRKSEMULATIONENABLED = System::Word(0x3ab1);
static const System::Word IDM_GETDEFAULTZOOMLEVEL = System::Word(0x3ab3);
static const System::Word IDM_GETELEMENTBOUNDINGBOX = System::Word(0x3ab4);
static const System::Word IDM_SETGEOLOCATIONCONSENT = System::Word(0x3ab5);
static const System::Word IDM_ACTIVEXFILTERINGENABLED = System::Word(0x3ab6);
static const System::Word IDM_SHARE = System::Word(0x3ab7);
static const System::Word IDM_SETAPPCACHESIZECONSENT = System::Word(0x3ab8);
static const System::Word IDM_SHAREAPPCACHEEVENT = System::Word(0x3ab9);
static const System::Word IDM_SETINDEXDBSIZECONSENT = System::Word(0x3aba);
static const System::Word IDM_GETPRINTMANAGERDOCSOURCE = System::Word(0x3abe);
static const System::Word IDM_SETEXTRAHEADERS = System::Word(0x3abf);
static const System::Word IDM_SETACCESSIBILITYNAME = System::Word(0x3ac0);
static const System::Word IDM_UPDATESETTINGSFROMREGISTRY = System::Word(0x3ac1);
static const System::Word IDM_PERFORMEDITACTIVATION = System::Word(0x3ac2);
static const System::Word IDM_SETDEFAULTBACKGROUNDCOLOR = System::Word(0x3ac3);
static const System::Word IDM_GETDEFAULTBACKGROUNDCOLOR = System::Word(0x3ac4);
static const System::Word IDM_NOTIFYZOOMANDSCROLLANIMATIONEND = System::Word(0x3ac5);
static const System::Word IDM_NOTIFYCONTEXTMENUDISMISSED = System::Word(0x3ac6);
static const System::Word IDM_SETPAGEACTIONALLOWEDFLAGS = System::Word(0x3afc);
static const System::Word IDM_INVOKEFLIPAHEADTARGET = System::Word(0x3b60);
static const System::Word IDM_ENABLEFLIPAHEADTARGET = System::Word(0x3b61);
static const System::Word IDM_DEBUGGERDYNAMICATTACH = System::Word(0x3b62);
static const System::Word IDM_DEBUGGERDYNAMICDETACH = System::Word(0x3b63);
static const System::Word IDM_DEBUGGERDYNAMICATTACHSOURCERUNDOWN = System::Word(0x3b64);
static const System::Word IDM_GETDEBUGGERSTATE = System::Word(0x3b65);
static const System::Word IDM_SELECTIONSEARCH = System::Word(0x3b66);
static const System::Word IDM_SHOWSHAREUI = System::Word(0x3b67);
}	/* namespace Mshtmcid */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSHTMCID)
using namespace Mshtmcid;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MshtmcidHPP
