/********************************************
* NAME: vbi_cc_init
*       init cc parameters and set callback fucn of vpo_isr to excute push user data for cc using
*
* Returns : BOOL
*              1 		: RET_FAILURE
*              0		: RET_SUCCESS
* Parameter     				Flow    Description
* ------------------------------------------------------------------------------
* None
* ------------------------------------------------------------------------------
* Additional information:
******************************************/
__ATTRIBUTE_REUSE_
INT32 vbi_cc_init()
{
	struct vbi_device *dev;
	struct vbi_m3327_private *tp;
	void *priv_mem;
	
	g_vbi_m3327_name = (char *)ccvbi_m3327_name;
	
	dev = dev_alloc(g_vbi_m3327_name,HLD_DEV_TYPE_VBI,sizeof(struct vbi_device));
	if (dev == NULL)
	{
		VBI_PRINTF("Error: Alloc video vbiplay device error!\n");
		return RET_FAILURE;
	}
	/* Alloc structure space of private */
	priv_mem = (void *)MALLOC(sizeof(struct vbi_m3327_private));
	if (priv_mem == NULL)
	{
		dev_free(dev);
		VBI_PRINTF("Alloc vbiplay device prive memory error!/n");
		return RET_FAILURE;
	}
	MEMSET(priv_mem, 0, sizeof(struct vbi_m3327_private));
	
	g_vbi_priv = dev->priv =  tp = (struct vbi_m3327_private *)priv_mem;

	ccg_vbi27_pconfig_par = &(g_vbi_priv->config_par);
	ccg_vbi27_ttx_by_osd = &(g_vbi_priv->ttx_by_osd);
	ccg_vbi27_cc_by_osd = &(g_vbi_priv->cc_by_osd);
	//======================================
#ifdef CC_BY_OSD
	ccg_vbi27_dtvcc_by_osd=&(g_vbi_priv->dtvcc_by_osd);//hbchen
#endif
	//======================================
	/*according the macro , config the VBI driver*/
  //vbi_data_array = (struct vbi_data_array_t *)MALLOC((VBI_QUEUE_DEPTH)*sizeof(struct vbi_data_array_t));
  //MEMSET(vbi_data_array, 0, (VBI_QUEUE_DEPTH)*sizeof(struct vbi_m3327_private));	
	

	*ccg_vbi27_ttx_by_osd = FALSE;
	g_vbi_priv->init_ttx_decoder = NULL;

#ifdef	CC_BY_OSD
	*ccg_vbi27_cc_by_osd = TRUE;
	g_vbi_priv->init_cc_decoder = vbi_m3327_init_cc_decoder;
	g_vbi_priv->vbi_line21_push_by_cc = vbi_line21_push;
	g_vbi_priv->vbi_line21_push_by_dtvcc = vbi_line21_push_dtvcc;//xing for DTVCC
#else
	*ccg_vbi27_cc_by_osd = FALSE;
#endif


#ifdef	CC_BY_VBI
	ccg_vbi27_pconfig_par->cc_by_vbi = TRUE;
#else
	ccg_vbi27_pconfig_par->cc_by_vbi = FALSE;
#endif

	//dev->setoutput = vbi_m3327_setoutput;

	dev->next = NULL;
       dev->flags = 0;
	/* Function point init */
	dev->init = vbi_cc_init;

	dev->open = vbi_cc_open;
	dev->close = NULL;
	dev->request_write = NULL;
	dev->update_write = NULL;
	dev->setoutput = ccvbi_m3327_setoutput;
	dev->start = NULL;
	dev->stop = NULL;

	/* Add this device to queue */
	if(dev_register(dev) != RET_SUCCESS)
	{
		VBI_PRINTF("Error: Register vbiplay device error!\n");
		FREE(priv_mem);
		dev_free(dev);
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}