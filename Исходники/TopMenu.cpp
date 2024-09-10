int topMenu::sizeNickName(QString name)
{
    QChar lyrics;
    int ASCII = 0;
    int space = 0;

    space = 20;

    for (int var = 0; var < name.length(); ++var)
    {
        lyrics = name.at(var).toAscii();
        ASCII = lyrics.toAscii();

        if(ASCII >= 65 && ASCII <= 90)
            space += 9;
        else
            space += 7;

        space--;
    }
    return  space;
}