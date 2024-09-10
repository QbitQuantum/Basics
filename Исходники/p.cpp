void P::buildText( Cell* cell )
{
    cell->addByte( 0xFA );
    if( cell->textFull() )
        printError( ERR1_LARGEPAGE );
}