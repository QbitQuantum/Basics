static int
ge2d_ioctl(struct inode *inode, struct file *filp,
                 unsigned int cmd, unsigned long args)
{

	ge2d_context_t *context=(ge2d_context_t *)filp->private_data;
	void  __user* argp =(void __user*)args;
	config_para_t     ge2d_config;	
	ge2d_para_t  para ;
    config_para_ex_t  ge2d_config_ex;
	int  ret=0;    	

	if(!command_valid(cmd))  return -1;
	switch (cmd)
   	{
		case  GE2D_CONFIG:
		case  GE2D_SRCCOLORKEY:	
		copy_from_user(&ge2d_config,argp,sizeof(config_para_t));
		break;
		case  GE2D_CONFIG_EX:
		copy_from_user(&ge2d_config_ex,argp,sizeof(config_para_ex_t));
		break;
		case  GE2D_SET_COEF:
		case	  GE2D_ANTIFLICKER_ENABLE:	
		break;
		default :
		copy_from_user(&para,argp,sizeof(ge2d_para_t));	
		break;
		
   	}
	switch(cmd)
	{
		case GE2D_CONFIG:
		ret=ge2d_context_config(context,&ge2d_config) ;
	  	break;
		case GE2D_CONFIG_EX:
		ret=ge2d_context_config_ex(context,&ge2d_config_ex) ;
	  	break;
		case GE2D_SET_COEF:
		ge2d_wq_set_scale_coef(context,args&0xff,args>>16);
		break;
		case GE2D_ANTIFLICKER_ENABLE:
		ge2d_antiflicker_enable(context,args);	
		break;
    	  	case GE2D_SRCCOLORKEY:
		ge2dgen_src_key(context , ge2d_config.src_key.key_enable,ge2d_config.src_key.key_color, ge2d_config.src_key.key_mask,ge2d_config.src_key.key_mode);  //RGBA MODE		
		break;
		case GE2D_FILLRECTANGLE:
		amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"fill rect...,x=%d,y=%d,w=%d,h=%d,color=0x%x\r\n",
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.color);

            	fillrect(context,
                     para.src1_rect.x, para.src1_rect.y,
                     para.src1_rect.w, para.src1_rect.h,
                     para.color) ;	
		break;
		case GE2D_FILLRECTANGLE_NOBLOCK:
		amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"fill rect...,x=%d,y=%d,w=%d,h=%d,color=0x%x,noblk\r\n",
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.color);

            	fillrect_noblk(context,
                     para.src1_rect.x, para.src1_rect.y,
                     para.src1_rect.w, para.src1_rect.h,
                     para.color) ;	
		break;
		case GE2D_STRETCHBLIT:
		//stretch blit
            	amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"stretchblt...,x=%d,y=%d,w=%d,h=%d,dst.w=%d,dst.h=%d\r\n",
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.dst_rect.w, para.dst_rect.h);

            	stretchblt(context ,
                       para.src1_rect.x, para.src1_rect.y, para.src1_rect.w, para.src1_rect.h,
                       para.dst_rect.x,  para.dst_rect.y,  para.dst_rect.w,  para.dst_rect.h);	
		break;
		case GE2D_STRETCHBLIT_NOBLOCK:
		//stretch blit
            	amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"stretchblt...,x=%d,y=%d,w=%d,h=%d,dst.w=%d,dst.h=%d,noblk\r\n",
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.dst_rect.w, para.dst_rect.h);

            	stretchblt_noblk(context ,
                       para.src1_rect.x, para.src1_rect.y, para.src1_rect.w, para.src1_rect.h,
                       para.dst_rect.x,  para.dst_rect.y,  para.dst_rect.w,  para.dst_rect.h);	
		break;
		case GE2D_BLIT:
		//bitblt
            	amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"blit...\r\n");

            	bitblt(context ,
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.dst_rect.x, para.dst_rect.y);
           	break;
		case GE2D_BLIT_NOBLOCK:
		//bitblt
            	amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"blit...,noblk\r\n");

            	bitblt_noblk(context ,
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.dst_rect.x, para.dst_rect.y);
           	break;	
		case GE2D_BLEND:
		amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"blend ...\r\n");
		blend(context,
            		para.src1_rect.x, para.src1_rect.y,
            		para.src1_rect.w, para.src1_rect.h,
           		para.src2_rect.x, para.src2_rect.y,
           		para.src2_rect.w, para.src2_rect.h,
           		para.dst_rect.x, para.dst_rect.y,
           		para.dst_rect.w, para.dst_rect.h,
           		para.op) ;	
		break;
		case GE2D_BLEND_NOBLOCK:
		amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"blend ...,noblk\r\n");
		blend_noblk(context,
            		para.src1_rect.x, para.src1_rect.y,
            		para.src1_rect.w, para.src1_rect.h,
           		para.src2_rect.x, para.src2_rect.y,
           		para.src2_rect.w, para.src2_rect.h,
           		para.dst_rect.x, para.dst_rect.y,
           		para.dst_rect.w, para.dst_rect.h,
           		para.op) ;	
		break;
		case GE2D_BLIT_NOALPHA:
		//bitblt_noalpha
            	amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"blit_noalpha...\r\n");
            	bitblt_noalpha(context ,
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.dst_rect.x, para.dst_rect.y);	
		break;
		case GE2D_BLIT_NOALPHA_NOBLOCK:
		//bitblt_noalpha
            	amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"blit_noalpha...,noblk\r\n");
            	bitblt_noalpha_noblk(context ,
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.dst_rect.x, para.dst_rect.y);	
		break;
		case GE2D_STRETCHBLIT_NOALPHA:
		//stretch blit
            	amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"stretchblt_noalpha...,x=%d,y=%d,w=%d,h=%d,dst.w=%d,dst.h=%d\r\n",
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.dst_rect.w, para.dst_rect.h);

            	stretchblt_noalpha(context ,
                       para.src1_rect.x, para.src1_rect.y, para.src1_rect.w, para.src1_rect.h,
                       para.dst_rect.x,  para.dst_rect.y,  para.dst_rect.w,  para.dst_rect.h);	
		break;
		case GE2D_STRETCHBLIT_NOALPHA_NOBLOCK:
		//stretch blit
            	amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_LOW,"stretchblt_noalpha...,x=%d,y=%d,w=%d,h=%d,dst.w=%d,dst.h=%d,noblk\r\n",
                   para.src1_rect.x, para.src1_rect.y,
                   para.src1_rect.w, para.src1_rect.h,
                   para.dst_rect.w, para.dst_rect.h);

            	stretchblt_noalpha_noblk(context ,
                       para.src1_rect.x, para.src1_rect.y, para.src1_rect.w, para.src1_rect.h,
                       para.dst_rect.x,  para.dst_rect.y,  para.dst_rect.w,  para.dst_rect.h);	
		break;
	}
 	return ret;
}