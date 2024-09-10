/*************************************************
*Writer:	YasirLiang
*Date: 2016/2/17
*Name:control_matrix_recv_pro_byte_msg
*Func: proccess byte recv matrix message:write byte data to file as so far(17-2-2017);后期可能修改
*Param:none 
*return value:none
***************************************************/
bool control_matrix_recv_pro_byte_msg( /*thost_upper_cmpt_msg *pmsg, */uint8_t save_char )
{
	bool bret = false;
	uint8_t save_ch = save_char;
	if( gmatrix_save_msg_fd != NULL )
	{
		if( Fwrite( gmatrix_save_msg_fd, &save_ch, 1, 1 ) == 1 );
		{
			Fflush( gmatrix_save_msg_fd );
			bret = true;
		}
	}

	return bret;
}