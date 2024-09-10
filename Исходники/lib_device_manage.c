/* Select NIM Device from Device List */
struct nim_device* dev_select_nim(UINT32 sub_type, UINT32 status, struct nim_config *config)
{
    	UINT8 i;
    	struct dev_manag_dev *dev_list = NULL;
    	struct nim_device *ret_dev = NULL;
    	struct nim_config *pnim_info = NULL;

    	ENTER_DEV_MUTEX();
    	dev_list = &dev_manag_list[0];
    	for(i=0; i < DEV_MAX_CNT; i++)
    	{
        	if((dev_list[i].hld_type==HLD_DEV_TYPE_NIM)&&(dev_list[i].sub_type==sub_type)&&(dev_list[i].status&status))
        	{
            		//Check whether NIM Config Info Match or not
            		if((config!=NULL)&&(dev_list[i].config!=0))
            		{
                		pnim_info = (struct nim_config *)(dev_list[i].config);
                		if(0==MEMCMP(config, pnim_info, sizeof(struct nim_config)))
                    			ret_dev = (struct nim_device*)dev_list[i].dev_handle;
            		}
            		else
                		ret_dev = (struct nim_device*)dev_list[i].dev_handle;
           		break;
		}
    	}
    	LEAVE_DEV_MUTEX();   
    	return ret_dev;
}