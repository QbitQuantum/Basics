void writePlainText(wstring input, map<wstring, char> alphabetMap){
    char previousCharacter = NULL;
    wstring currentMorse = (L"");

    for(int x = 0; x < input.length(); x++){

        if((previousCharacter == ' ' && input[x] != ' ') || (previousCharacter != ' ' && input[x] == ' ')){
            cout << alphabetMap[currentMorse];
            currentMorse = L"";
        } else if (x == (input.length()- 1)){
            currentMorse += input[x];
            cout << alphabetMap[currentMorse];
            break;
        }

        currentMorse += input[x];
        previousCharacter = input[x]; // for comparison
    }

    cout << endl << endl;
}