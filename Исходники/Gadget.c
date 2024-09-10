struct Gadget *CreateAllGadgets(piObject *o)
{
	struct Gadget *g=NULL;
	piObject *go;
	struct Node_Window *nw;

	piGetAttr(o,OBJ_Node,(ULONG *)&nw);

	nw->nw_Gadgets=NULL;
	if(nw->nw_PageGadget==0 && GUI.gui_Mode==MODE_TEST)
	{
		if(nw->nw_MyFlags&MYWA_BBottomSlider)
		{
			g=CreateContext(&nw->nw_Gadgets);
			unless(nw->nw_Object[0]=NewObject(NULL, BUTTONGCLASS,
//				ICA_TARGET, ICTARGET_IDCMP,
				GA_RelVerify,TRUE,
				GA_Image, gui_LeftImage,
				GA_RelRight, 1-(IM_WIDTH(gui_LeftImage)+IM_WIDTH(gui_SizeImage)+IM_WIDTH(gui_RightImage)),
				GA_RelBottom, 1-(IM_HEIGHT(gui_LeftImage)),
				GA_BottomBorder,TRUE,
				GA_Previous,(ULONG *)g,
				(nw->nw_Flags&WFLG_GIMMEZEROZERO) ? GA_GZZGadget : TAG_IGNORE,TRUE,
				GA_ID, GD_LEFTBUTTON,
				TAG_DONE)) return NULL;
			g=(struct Gadget *)nw->nw_Object[0];
			unless(nw->nw_Object[1]=NewObject(NULL, BUTTONGCLASS,
//				ICA_TARGET, ICTARGET_IDCMP,
				GA_RelVerify,TRUE,
				GA_Image, gui_RightImage,
				GA_RelRight, 1-(IM_WIDTH(gui_RightImage)+IM_WIDTH(gui_SizeImage)),
				GA_RelBottom, 1-(IM_HEIGHT(gui_RightImage)),
				GA_BottomBorder,TRUE,
				GA_Previous,(ULONG *)g,
				(nw->nw_Flags&WFLG_GIMMEZEROZERO) ? GA_GZZGadget : TAG_IGNORE,TRUE,
				GA_ID, GD_RIGHTBUTTON,
				TAG_DONE)) return NULL;
			g=(struct Gadget *)nw->nw_Object[1];
			unless(nw->nw_Object[2]=NewObject(NULL, PROPGCLASS,
//				ICA_TARGET, ICTARGET_IDCMP,
				GA_RelVerify,TRUE,
				PGA_Freedom, FREEHORIZ,
				PGA_NewLook, TRUE,
				PGA_Borderless, ((DrawInfo->dri_Flags & DRIF_NEWLOOK) && DrawInfo->dri_Depth != 1),
				GA_Left, 3,
				GA_RelBottom, -(IM_HEIGHT(gui_SizeImage)-3),
				GA_RelWidth, -(4+IM_WIDTH(gui_LeftImage)+IM_WIDTH(gui_RightImage)+IM_WIDTH(gui_SizeImage)+1),
				GA_Height, IM_HEIGHT(gui_SizeImage)-4,
				GA_BottomBorder, TRUE,
				GA_Previous,(ULONG *)g,
				(nw->nw_Flags&WFLG_GIMMEZEROZERO) ? GA_GZZGadget : TAG_IGNORE,TRUE,
				GA_ID, GD_HORIZBUTTON,
				PGA_Total, 1,
				PGA_Visible, 1,
				TAG_DONE)) return NULL;
			g=(struct Gadget *)nw->nw_Object[2];
		}
		else
		{