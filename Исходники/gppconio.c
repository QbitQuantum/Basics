void _setcursortype(int type)
{
    unsigned cursor_shape;
    switch (type)
    {
        case _NOCURSOR:
            cursor_shape = 0x0700;
            break;
        case _SOLIDCURSOR:
            cursor_shape = 0x0007;
            break;
/*      case _NORMALCURSOR: */
        default:
            cursor_shape = 0x0607;
            break;
    }
    setcursor(cursor_shape);
}