//spi basic read/write function
u8 EF_spiFlashRW(u8 data)
{
	while( DMA_Tx_Busy == 1) __nop();
	while( SPI_GetFlagStatus(SPIFLASH_SPI,SPI_I2S_FLAG_TXE)==RESET ) 		__nop();
	SPI_SendData(SPIFLASH_SPI,(u16)data);
	while( SPI_GetFlagStatus(SPIFLASH_SPI,SPI_I2S_FLAG_RXNE)==RESET ) 	__nop();
	return (u8)SPI_ReceiveData(SPIFLASH_SPI);
}