// constructor dynamically allocates space for first and last name and 
// uses strcpy to copy first and last names into the object
Employee::Employee( const char * const first, const char * const last )
{
   firstName = new char[ strlen( first ) + 1 ]; // create space
   strcpy( firstName, first ); // copy first into object

   lastName = new char[ strlen( last ) + 1 ]; // create space
   strcpy( lastName, last ); // copy first into object

   count++; // increment static count of employees

   cout << "Employee constructor for " << firstName
      << ' ' << lastName << " called." << endl;
} // end Employee constructor