/****************************************************************************
 *  FUNCTION: main() - local routine                                        *
 ****************************************************************************/
int main(int argc, char *argv[])
    {
    int key_entered, Ch;

    intro();

    /* Set all 16 buffers to 0 */
    for (Ch = 0; Ch < 4; Ch++)
	   OUTPORT(base + (Ch * 2), Cal(0x000, Ch));

    inb(base+0xA);    // set automatic update mode
    inb(base+0XF);    // release zero latch

    do
	{
	CLRSCR();
	write_DAC();
	CPRINTF("\n\nWould you like to output another value (Y or N)?\n");
	key_entered = GETCH();
	} while((key_entered != 'N') && (key_entered != 'n'));

    /* Set all 16 buffers to 0 */
    for (Ch = 0; Ch < 4; Ch++)
	   OUTPORT(base + (Ch * 2), Cal(0x000, Ch));

    CLRSCR();
    PUTS("DA12-16 Sample1 complete.");
    } /* end main */