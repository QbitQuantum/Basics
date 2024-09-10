/** 
 * @Spim1 standard mode read NorFlash function
 * @param  
 * @return none
 * @note
 * -Spim1 standard mode read NorFlash
 */
void Spim1ReadNorFlashStdMode(UINT32 start_add, UINT8 *data_buf, UINT32 read_len)
{
     UINT32 read_addr;
	 UINT32 tmplen, total_len = 0;
	 
	 UINT8 ins_buf[4];
	 
	 while (total_len < read_len)
	 {
		tmplen = read_len - total_len;
		if (tmplen > FLASH_PAGE_SIZE)
		{
			tmplen = FLASH_PAGE_SIZE;
		}
		
		read_addr = start_add + total_len;
		ins_buf[0]= read_data;
		ins_buf[1]=(UINT8)((read_addr>>16) & 0x000000ff); 
		ins_buf[2]=(UINT8)((read_addr>>8) & 0x000000ff);
		ins_buf[3]=(UINT8)((read_addr>>0) & 0x000000ff);
		
		Spim1CheckNorFlashBusy();
		
		Spim1SetCsLow();
		Spim1SendData(0, ins_buf, 4);
		
		Spim1RecvData(0, data_buf + total_len, tmplen);
		Spim1SetCsHigh();
		
		
		read_addr = start_add + total_len;
		ins_buf[0]= read_data;
		ins_buf[1]=(UINT8)((read_addr>>16) & 0x000000ff); 
		ins_buf[2]=(UINT8)((read_addr>>8) & 0x000000ff);
		ins_buf[3]=(UINT8)((read_addr>>0) & 0x000000ff);
		
		Spim1CheckNorFlashBusy();
		
		Spim1SetCsLow();
		Spim1SendData(0, ins_buf, 4);
		Memset(data_buf, 0, tmplen);
		Spim1RecvData(0, data_buf + total_len, tmplen);
		Spim1SetCsHigh();
		
		total_len += tmplen; 
	 }	 
}