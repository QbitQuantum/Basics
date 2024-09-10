static int hex2int( QChar hexchar )
{
    int v;
    if ( hexchar.isDigit() )
	v = hexchar.digitValue();
    else if ( hexchar >= 'A' && hexchar <= 'F' )
	v = hexchar.cell() - 'A' + 10;
    else if ( hexchar >= 'a' && hexchar <= 'f' )
	v = hexchar.cell() - 'a' + 10;
    else
	v = -1;
    return v;
}