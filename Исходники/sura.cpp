string getInput() //gets a line of text that the user enters and returns that line, lowercase
{
    string input;
    getline(cin, input);
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}