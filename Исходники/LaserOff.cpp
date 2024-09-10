int main()
{
	OpenTVicPort();

        WritePort(0x2050,0x00);

	CloseTVicPort();
        return(0);
}