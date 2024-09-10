void PianoKeyItem::setType(int val)
{
    type = val;
    QPainterPath path;

    switch(type) {
    case 0:
        path.moveTo(0,0);
        path.lineTo(0,   KEY_HEIGHT-2);
        path.lineTo(2.0, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH-2, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH, KEY_HEIGHT-2);
        path.lineTo(KEY_WIDTH, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 5/9, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 5/9, 0);
        break;
    case 1:
        path.moveTo(BKEY_WIDTH * 4/9, 0);
        path.lineTo(BKEY_WIDTH * 4/9, BKEY_HEIGHT);
        path.lineTo(0, BKEY_HEIGHT);
        path.lineTo(0,   KEY_HEIGHT-2);
        path.lineTo(2.0, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH-2, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH, KEY_HEIGHT-2);
        path.lineTo(KEY_WIDTH, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 4/9, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 4/9, 0);
        break;
    case 2:
        path.moveTo(BKEY_WIDTH * 5/9, 0);
        path.lineTo(BKEY_WIDTH * 5/9, BKEY_HEIGHT);
        path.lineTo(0,   BKEY_HEIGHT);
        path.lineTo(0,   KEY_HEIGHT-2);
        path.lineTo(2.0, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH-2, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH,  KEY_HEIGHT-2);
        path.lineTo(KEY_WIDTH,  BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH, 0);
        break;
    case 3:
        path.moveTo(BKEY_WIDTH * 4/9, 0);
        path.lineTo(BKEY_WIDTH * 4/9, BKEY_HEIGHT);
        path.lineTo(0, BKEY_HEIGHT);
        path.lineTo(0,   KEY_HEIGHT-2);
        path.lineTo(2.0, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH-2, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH, KEY_HEIGHT-2);
        path.lineTo(KEY_WIDTH, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 5/9, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 5/9, 0);
        break;
    case 4:
        path.moveTo(BKEY_WIDTH * 5/9, 0);
        path.lineTo(BKEY_WIDTH * 5/9, BKEY_HEIGHT);
        path.lineTo(0, BKEY_HEIGHT);
        path.lineTo(0,   KEY_HEIGHT-2);
        path.lineTo(2.0, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH-2, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH, KEY_HEIGHT-2);
        path.lineTo(KEY_WIDTH, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 4/9, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 4/9, 0);
        break;
    case 5:
        path.moveTo(0,0);
        path.lineTo(0,   KEY_HEIGHT-2);
        path.lineTo(2.0, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH-2, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH, KEY_HEIGHT-2);
        path.lineTo(KEY_WIDTH, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 4/9, BKEY_HEIGHT);
        path.lineTo(KEY_WIDTH - BKEY_WIDTH * 4/9, 0);
        break;
    case 6:
        path.moveTo(0,0);
        path.lineTo(0,   KEY_HEIGHT-2);
        path.lineTo(2.0, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH-2, KEY_HEIGHT);
        path.lineTo(KEY_WIDTH, KEY_HEIGHT-2);
        path.lineTo(KEY_WIDTH, 0);
        break;
    case 7:
        path.moveTo(0,0);
        path.lineTo(0,            BKEY_HEIGHT-1);
        path.lineTo(1.0,          BKEY_HEIGHT);
        path.lineTo(BKEY_WIDTH-1, BKEY_HEIGHT);
        path.lineTo(BKEY_WIDTH,   BKEY_HEIGHT-1);
        path.lineTo(BKEY_WIDTH, 0);
        break;
    default:
        break;
    }
    path.closeSubpath();
    setPath(path);
}