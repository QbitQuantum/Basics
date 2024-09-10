void AudioTest1::init()
{
    uart = Uart::getInstance();
    uart->init((volatile uint32_t *)UART_BASE);
    uart->puts("AudioTest1 StartUp...\r\n");
    i2cBus = new I2C((volatile uint32_t *)SND_I2C_SCL_BASE, (volatile uint32_t *)SND_I2C_SDA_BASE);
    soundCard = new SoundCard(i2cBus, (volatile uint32_t *)AUDIO_IF_0_BASE);
    soundCard->init();
}