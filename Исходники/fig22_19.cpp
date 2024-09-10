int main()
{
   cout << "According to islower:\n"
      << ( islower( 'p' ) ? "p is a" : "p is not a" )    
      << " lowercase letter\n"
      << ( islower( 'P' ) ? "P is a" : "P is not a" ) 
      << " lowercase letter\n"
      << ( islower( '5' ) ? "5 is a" : "5 is not a" ) 
      << " lowercase letter\n"
      << ( islower( '!' ) ? "! is a" : "! is not a" ) 
      << " lowercase letter\n";

   cout << "\nAccording to isupper:\n"
      << ( isupper( 'D' ) ? "D is an" : "D is not an" ) 
      << " uppercase letter\n"
      << ( isupper( 'd' ) ? "d is an" : "d is not an" ) 
      << " uppercase letter\n"
      << ( isupper( '8' ) ? "8 is an" : "8 is not an" ) 
      << " uppercase letter\n"
      << ( isupper('$') ? "$ is an" : "$ is not an" ) 
      << " uppercase letter\n";

   cout << "\nu converted to uppercase is " 
      << static_cast< char >( toupper( 'u' ) )
      << "\n7 converted to uppercase is " 
      << static_cast< char >( toupper( '7' ) ) 
      << "\n$ converted to uppercase is " 
      << static_cast< char >( toupper( '$' ) ) 
      << "\nL converted to lowercase is " 
      << static_cast< char >( tolower( 'L' ) ) << endl;
   return 0;
} // end main