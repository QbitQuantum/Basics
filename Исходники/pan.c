/*
 * 	Name		:   pan_get_key()
 *	Description	:   Get a input code
 *	Parameter	:	struct pan_device *dev		: Device get code from
 *					UINT32 timeout				: Timeout mode
 *	Return		:	UINT32 						: Return code
 *
 */
struct pan_key * pan_get_key(struct pan_device *dev, UINT32 timeout)
{
	while (1)
	{
	    if (pan_rx_buff_head != pan_rx_buff_tail)
		{
			break;
		}
		if (timeout != OSAL_WAIT_FOREVER_TIME)
		{
			if (timeout-- == 0)
			{
				return NULL;
			}
		}
		osal_task_sleep(1);
	}

	MEMCPY(&panel_key, pan_rx_buff[pan_rx_buff_tail], sizeof(struct pan_key));
	pan_rx_buff_tail++;
    pan_rx_buff_tail %= PAN_RX_BUFF_SIZE;

	return &panel_key;
}