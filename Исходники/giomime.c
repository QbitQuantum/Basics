unichar_t *GIOguessMimeType(const unichar_t *path,int isdir) {
    unichar_t *pt;

    if ( isdir )
return( dir );
    path = u_GFileNameTail(path);
    pt = u_strrchr(path,'.');

    if ( pt==NULL ) {
	if ( uc_strmatch(path,"makefile")==0 || uc_strmatch(path,"makefile~")==0 )
return( textmake );
	else if ( uc_strmatch(path,"core")==0 )
return( core );
    } else if ( uc_strmatch(pt,".text")==0 || uc_strmatch(pt,".txt")==0 ||
	    uc_strmatch(pt,".text~")==0 || uc_strmatch(pt,".txt~")==0 )
return( textplain );
    else if ( uc_strmatch(pt,".c")==0 || uc_strmatch(pt,".h")==0 ||
	    uc_strmatch(pt,".c~")==0 || uc_strmatch(pt,".h~")==0 )
return( textc );
    else if ( uc_strmatch(pt,".java")==0 || uc_strmatch(pt,".java~")==0 )
return( textjava );
    else if ( uc_strmatch(pt,".css")==0 || uc_strmatch(pt,".css~")==0 )
return( textcss );
    else if ( uc_strmatch(pt,".html")==0 || uc_strmatch(pt,".htm")==0 ||
	    uc_strmatch(pt,".html~")==0 || uc_strmatch(pt,".htm~")==0 )
return( texthtml );
    else if ( uc_strmatch(pt,".xml")==0 || uc_strmatch(pt,".xml~")==0 )
return( textxml );
    else if ( uc_strmatch(pt,".pfa")==0 || uc_strmatch(pt,".pfb")==0 ||
	    uc_strmatch(pt,".pt3")==0 || uc_strmatch(pt,".cff")==0 )
return( textpsfont );
    else if ( uc_strmatch(pt,".sfd")==0 )
return( sfdfont );
    else if ( uc_strmatch(pt,".ttf")==0 )
return( fontttf );
    else if ( uc_strmatch(pt,".otf")==0 || uc_strmatch(pt,".otb")==0 ||
	    uc_strmatch(pt,".gai")==0 )
return( fontotf );
    else if ( uc_strmatch(pt,".cid")==0 )
return( fontcid );
    else if ( uc_strmatch(pt,".ps")==0 || uc_strmatch(pt,".eps")==0 )
return( textps );
    else if ( uc_strmatch(pt,".bdf")==0 )
return( textbdffont );
    else if ( uc_strmatch(pt,".pdf")==0 )
return( pdf );
    else if ( uc_strmatch(pt,".gif")==0 )
return( imagegif );
    else if ( uc_strmatch(pt,".png")==0 )
return( imagepng );
    else if ( uc_strmatch(pt,".svg")==0 )
return( imagesvg );
    else if ( uc_strmatch(pt,".jpeg")==0 || uc_strmatch(pt,".jpg")==0 )
return( imagejpeg );
    else if ( uc_strmatch(pt,".mov")==0 || uc_strmatch(pt,".movie")==0 )
return( videoquick );
    else if ( uc_strmatch(pt,".wav")==0 )
return( audiowav );
    else if ( uc_strmatch(pt,".o")==0 || uc_strmatch(pt,".obj")==0 )
return( object );
    else if ( uc_strmatch(pt,".bin")==0 )
return( macbin );
    else if ( uc_strmatch(pt,".hqx")==0 )
return( machqx );
    else if ( uc_strmatch(pt,".dfont")==0 )
return( macdfont );
    else if ( uc_strmatch(pt,".gz")==0 || uc_strmatch(pt,".tgz")==0 ||
	    uc_strmatch(pt,".Z")==0 || uc_strmatch(pt,".zip")==0 ||
	    uc_strmatch(pt,".bz2")==0 || uc_strmatch(pt,".tbz")==0 ||
	    uc_strmatch(pt,".rpm")==0 )
return( compressed );
    else if ( uc_strmatch(pt,".tar")==0 )
return( tar );
    else if ( uc_strmatch(pt,".pcf")==0 )
return( fontpcf );
    else if ( uc_strmatch(pt,".snf")==0 )
return( fontsnf );

return( unknown );
}