int
shNCursesInterface::getSpecialChar (SpecialKey *sk)
{
    int key = getChar ();
    switch (key) {
    case 27: *sk = kEscape; break;
    case ' ': *sk = kSpace; break;
    case KEY_ENTER: case 10: case 13: *sk = kEnter; break;
    case KEY_BACKSPACE: *sk = kBackSpace; break;
    case KEY_IC: *sk = kInsert; break;
    case KEY_DC: *sk = kDelete; break;
    case KEY_HOME:  case KEY_A1: *sk = kHome; break;
    case KEY_END:   case KEY_C1: *sk = kEnd; break;
    case KEY_PPAGE: case KEY_A3: *sk = kPgUp; break;
    case KEY_NPAGE: case KEY_C3: *sk = kPgDn; break;
    case KEY_UP: *sk = kUpArrow; break;
    case KEY_DOWN: *sk = kDownArrow; break;
    case KEY_LEFT: *sk = kLeftArrow; break;
    case KEY_RIGHT: *sk = kRightArrow; break;
    case KEY_B2: *sk = kCenter; break;
    default: *sk = kNoSpecialKey; break;
    }
    return key;
}