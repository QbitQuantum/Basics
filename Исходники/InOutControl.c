void OpenLock(u8 LockId, u8 Numer)
{
    u8 u8Remainder = LockId % 8;
    u8 u8Quotient = LockId / 8;
    u8 u8loop = Numer / 8;
    u8 i;

    if (LockId == 0xff)
    {
        u8Quotient = 0xff;
    }

    for(i = u8loop; i > 0; i--)
    {
       /* 第33 - 39、 41 - 47 路由于PCB布线问题，需要作以下调整。*/
       /* 32 33 34 35 36 37 38 39 */ 
       /* 32 39 38 37 36 35 34 33 */ //-- 实际被控制的线路

       /* 40 41 42 43 44 45 46 47 */
       /* 40 47 46 45 44 43 42 41 */ //-- 实际被控制的线路
       if (i == u8Quotient+1)
       {
            if (u8Quotient+1 == 5 || u8Quotient+1 == 6)
            {
                if (u8Remainder != 0)
                {
                    u8Remainder = 8 - u8Remainder;
                }
            }
        
            SPIByte(1<<u8Remainder);
       }
       else
       {
            SPIByte(0);
       }
    }

    __NOP();
    GPIO_SetBits(GPIOB,GPIO_Pin_11);
    // for(i = 0;i<1000;i++)
     {
    __NOP();
     }
    
    GPIO_ResetBits(GPIOB,GPIO_Pin_11);
}