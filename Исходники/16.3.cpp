int main()
{
    using std::cout;
    using std::cin;
    using std::endl;
    using std::tolower;
    std::srand(std::time(0));
    char play;
    cout << "Will you play a word game? <y/n>: ";
    cin >> play;
    play = tolower(play);
    if (play == 'y')
    {
        string target = worldlist[rand() % NUM];
        int length = target.length();
        string attempt = string(length, '-');
        string badchars;
        int guess = 6;
        cout << "Guess my secret word. It has " << length << " letters, and you guess one letter at a time.\nYou get " << guess << " wrong guesses.\n";
        cout << "Your word: " << attempt << endl;
        while (guess > 0 && target != attempt)
        {
            char letter;
            cout << "Guess a letter: ";
            cin >> letter;
            if (badchars.find(letter) != string::npos || attempt.find(letter) != string::npos)
            {
                cout << "You have already guessed that. Try again.\n";
                continue;
            }
            unsigned int loc = target.find(letter);
            if (loc == string::npos)
            {
                cout << "Oh, bad guess!\n";
                badchars += letter;
                guess--;
            }
            else
            {
                cout << "Good guess!\n";
                attempt[loc] = letter;
                loc = target.find(letter, loc + 1);
                while (loc != string::npos)
                {
                    attempt[loc] = letter;
                    loc = target.find(letter, loc + 1);
                }
            }
            cout << "Your word is " << attempt << endl;
            if (attempt != target)
            {
                if (badchars.length() > 0)
                {
                    cout << "Bad choice: " << badchars << endl;
                    cout << guess << " bad guessed left.\n";
                }
            }
        }
        if (guess > 0)
        {
            cout << "That's right.\n";
        }
        else
        {
            cout << "Sorry, the word is " << target << ".\n";
            cout << "Will you play another? <y/n> ";
            cin >> play;
            play = towlower(play);
        }
    }