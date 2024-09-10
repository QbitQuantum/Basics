void FOE_writebuffer(uint8_t data)
{
//    char                 buf[64];

    if(ESCvar.fbufposition < FOE_PAGESIZE)
    {
        ESCvar.fposition++;
        fbuffer[ESCvar.fbufposition++] = data;
    }
    else
    {
        if(!ESCvar.fbufstate)
        {
            m25px0_sector_erase(drv_m25px0_1, ESCvar.fposition - FOE_PAGESIZE);
            while (m25px0_status(drv_m25px0_1) & 0x0001) __nop();
//            terminal_putchar(drv_terminal_1,'+');
//            sprintf(buf,"%i\n\r",ESCvar.fposition);
//            uart8_write(drv_uart8_1,buf,strlen(buf));
        }
        m25px0_program_page(drv_m25px0_1, ESCvar.fposition - FOE_PAGESIZE, &fbuffer[0], FOE_PAGESIZE);
        while (m25px0_status(drv_m25px0_1) & 0x0001) __nop();
//        terminal_putchar(drv_terminal_1,'-');
//        sprintf(buf,"%i\n\r",ESCvar.fbufstate);
//        uart8_write(drv_uart8_1,buf,strlen(buf));

        ESCvar.fbufposition = 0;
//        if(++ESCvar.fbufstate >= PAGESPERBLOCK)
//            ESCvar.fbufstate = 0;
        ESCvar.fbufstate++;
        ESCvar.fposition++;
        fbuffer[ESCvar.fbufposition++] = data;
    }
}