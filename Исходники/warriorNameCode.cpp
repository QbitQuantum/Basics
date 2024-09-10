void AlpabetNumber (char letter, int& num)
{
     using std::tolower;
        letter = tolower(letter);
    switch (letter)
    {

case 'a':
case 'e':
    num = 1;
    break;
case 'i':
case 'l':
    num = 2;
    break;
case 'n':
case 'o':
    num = 3;
    break;
case 'r':
case 's':
    num = 4;
    break;
case 't':
case 'v':
    num = 5;
    break;
case 'u':
case 'd':
    num = 6;
    break;
case 'g':
case 'b':
    num = 7;
    break;
case 'c':
case 'm':
    num = 8;
    break;
case 'p':
case 'f':
    num = 9;
    break;
case 'h':
case 'w':
    num = 10;
    break;
case 'y':
case 'k':
    num = 10;
    break;
case 'j':
case 'x':
    num = 11;
    break;
case 'q':
case 'z':
    num=12;
    break;
}
}