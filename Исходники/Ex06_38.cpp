// guessGame generates numbers between 1 and 1000 and checks user's guess
void guessGame()
{
   int answer; // randomly generated number
   int guess; // user's guess
   char response; // 'y' or 'n' response to continue game

   // loop until user types 'n' to quit game
   do 
   {
      // generate random number between 1 and 1000
      // 1 is shift, 1000 is scaling factor
      answer = 1 + rand() % 1000;

      // prompt for guess
      cout << "I have a number between 1 and 1000.\n" 
         << "Can you guess my number?\n" 
         << "Please type your first guess." << endl << "? ";
      cin >> guess;

      // loop until correct number
      while ( !isCorrect( guess, answer ) ) 
         cin >> guess;      

      // prompt for another game
      cout << "\nExcellent! You guessed the number!\n"
         << "Would you like to play again (y or n)? ";
      cin >> response;

      cout << endl;
   } while ( response == 'y' );
} // end function guessGame