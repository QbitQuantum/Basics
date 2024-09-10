int gmx_densorder(int argc,char *argv[])
{
    static const char *desc[] = {
        "A small program to reduce a two-phase density distribution", 
        "along an axis, computed over a MD trajectory",
        "to 2D surfaces fluctuating in time, by a fit to",
        "a functional profile for interfacial densities",
        "A time-averaged spatial representation of the" ,
        "interfaces can be output with the option -tavg" 
    };
  
    /* Extra arguments - but note how you always get the begin/end
     * options when running the program, without mentioning them here!
     */
  
    output_env_t oenv;
    t_topology *top;
    char       title[STRLEN],**grpname;
    int        ePBC, *ngx;
    static real binw=0.2;
    static real binwz=0.05;
    static real dens1=0.00;
    static real dens2=1000.00;
    static int ftorder=0;
    static int nsttblock=100;
    static int axis= 2;
    static char *axtitle="Z";
    static int ngrps=1;
    atom_id **index; /* Index list for single group*/
    int xslices, yslices, zslices, tblock;
    static gmx_bool bGraph=FALSE;
    static gmx_bool bCenter = FALSE;
    static gmx_bool bFourier=FALSE;
    static gmx_bool bRawOut=FALSE;
    static gmx_bool bOut=FALSE;
    static gmx_bool b1d=FALSE;
    static int nlevels=100;
    /*Densitymap - Densmap[t][x][y][z]*/
    real ****Densmap=NULL;
    /* Surfaces surf[t][surf_x,surf_y]*/
    t_interf ***surf1, ***surf2;

    static const char *meth[]={NULL,"bisect","functional",NULL};
    int eMeth;	

    char **graphfiles, **rawfiles, **spectra; /* Filenames for xpm-surface maps, rawdata and powerspectra */
    int nfxpm,nfraw, nfspect; /* # files for interface maps and spectra = # interfaces */
 
    t_pargs pa[] = {
        { "-1d", FALSE, etBOOL, {&b1d},
          "Pseudo-1d interface geometry"},
        { "-bw",FALSE,etREAL,{&binw},
          "Binwidth of density distribution tangential to interface"},
        { "-bwn", FALSE, etREAL, {&binwz},
          "Binwidth of density distribution normal to interface"},
        { "-order", FALSE, etINT,{&ftorder},
          "Order of Gaussian filter, order 0 equates to NO filtering"},
        {"-axis", FALSE, etSTR,{&axtitle},
         "Axis Direction - X, Y or Z"},
        {"-method",FALSE ,etENUM,{meth},
         "Interface location method"},
        {"-d1", FALSE, etREAL,{&dens1},
         "Bulk density phase 1 (at small z)"},
        {"-d2", FALSE, etREAL,{&dens2},
         "Bulk density phase 2 (at large z)"},
        { "-tblock",FALSE,etINT,{&nsttblock},
          "Number of frames in one time-block average"},
        { "-nlevel", FALSE,etINT, {&nlevels},
          "Number of Height levels in 2D - XPixMaps"}
    };


    t_filenm fnm[] = {
        { efTPX, "-s",  NULL, ffREAD },   /* this is for the topology */
        { efTRX, "-f", NULL, ffREAD },      /* and this for the trajectory */
        { efNDX, "-n", NULL, ffREAD}, /* this is to select groups */
        { efDAT, "-o", "Density4D",ffOPTWR}, /* This is for outputting the entire 4D densityfield in binary format */
        { efOUT, "-or", NULL,ffOPTWRMULT}, /* This is for writing out the entire information in the t_interf arrays */
        { efXPM, "-og" ,"interface",ffOPTWRMULT},/* This is for writing out the interface meshes - one xpm-file per tblock*/ 
        { efOUT, "-Spect","intfspect",ffOPTWRMULT}, /* This is for the trajectory averaged Fourier-spectra*/		
    };
  
#define NFILE asize(fnm)

    CopyRight(stderr,argv[0]);

    /* This is the routine responsible for adding default options,
     * calling the X/motif interface, etc. */
    parse_common_args(&argc,argv,PCA_CAN_TIME | PCA_CAN_VIEW,
                      NFILE,fnm,asize(pa),pa,asize(desc),desc,0,NULL,&oenv);


    eMeth=nenum(meth);	
    bFourier=opt2bSet("-Spect",NFILE,fnm);
    bRawOut=opt2bSet("-or",NFILE,fnm);
    bGraph=opt2bSet("-og",NFILE,fnm);
    bOut=opt2bSet("-o",NFILE,fnm);
    top=read_top(ftp2fn(efTPX,NFILE,fnm),&ePBC);
    snew(grpname,ngrps);
    snew(index,ngrps);
    snew(ngx,ngrps);

/* Calculate axis */
    axis = toupper(axtitle[0]) - 'X';

    get_index(&top->atoms,ftp2fn_null(efNDX,NFILE,fnm),ngrps,ngx,index,grpname);

    density_in_time(ftp2fn(efTRX,NFILE,fnm),index,ngx,ngrps,binw,binwz,nsttblock,&Densmap,&xslices,&yslices,&zslices,&tblock,top,ePBC,axis,bCenter,b1d,oenv);

    if(ftorder>0)
    {
        filterdensmap(Densmap,xslices,yslices,zslices,tblock,2*ftorder+1);
    }

    if (bOut)
    {
        outputfield(opt2fn("-o",NFILE,fnm),Densmap,xslices,yslices,zslices,tblock);
    }

    interfaces_txy(Densmap,xslices,yslices,zslices,tblock,binwz,eMeth,dens1,dens2,&surf1,&surf2,oenv);

    if(bGraph)
    {

        /*Output surface-xpms*/
        nfxpm=opt2fns(&graphfiles,"-og",NFILE,fnm);
        if(nfxpm!=2)
        {
            gmx_fatal(FARGS,"No or not correct number (2) of output-files: %d",nfxpm);
        }
        writesurftoxpms(surf1, surf2, tblock,xslices,yslices,zslices,binw,binwz,graphfiles,zslices);
    }


	


/*Output raw-data*/
    if (bRawOut)
    {
        nfraw=opt2fns(&rawfiles,"-or",NFILE,fnm);
        if(nfraw!=2)
        {
            gmx_fatal(FARGS,"No or not correct number (2) of output-files: %d",nfxpm);
        }
        writeraw(surf1,surf2,tblock,xslices,yslices,rawfiles);
    }



    if(bFourier)
    {
        nfspect=opt2fns(&spectra,"-Spect",NFILE,fnm);
        if(nfspect!=2)
        {
            gmx_fatal(FARGS,"No or not correct number (2) of output-file-series: %d"
                      ,nfspect);
        }
        powerspectavg_intf(surf1, surf2, tblock,xslices,yslices,spectra);
    }

    sfree(Densmap);
    if(bGraph || bFourier || bRawOut)
    {
        sfree(surf1);
        sfree(surf2);
    }

    thanx(stderr);
    return 0;
}