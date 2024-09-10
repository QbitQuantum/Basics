// SPI basic Read/Write function
u8 SPI_RW_Byte(SPI_TypeDef* SPIx,unsigned char Byte)
{
		while( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)   	  __nop();
		SPI_I2S_SendData(SPIx, Byte);
		while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)  	  __nop();
		return SPI_I2S_ReceiveData(SPIx);
}