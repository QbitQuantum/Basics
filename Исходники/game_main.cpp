int game_init(int argc, char** argv)
{
    x = 0;
    y = 0;

    int width, height;

    width = 16;
    height = 24;

    g_sprite.data = new unsigned char[width*height];
    g_sprite.width = width;
    g_sprite.height = height;

    memset(g_sprite.data, 13, width*height);

    g_sprite.data[0] = 255;
    g_sprite.data[width-1]= 255;
    g_sprite.data[(height-1)*width] = 255;
    g_sprite.data[width-1 +(height-1)*width] = 255;

    g_framebuffer.width = 320;
    g_framebuffer.height = 240;
    g_framebuffer.data = (unsigned char*)vga_getFrameBuffer();
    /*
        int i, flags;
    char key;
    unsigned char* screen_buf = (unsigned char*)0xA0000;
    unsigned int x, y;

    vga_setMode(0x0013);

    screen_buf[0] = 10;
    screen_buf[1] = 10;


    
    // initialze screen buffer 
        for ( x = 0; x < 320; x++ )    {
        for ( y = 0; y < 200; y++) {
            screen_buf[y*320 +x] = y%256;
        }
      } */
    
    return 0;
}