/*****************************************
 * Creates a Name object on the heap and *
 * reads the first and second names from *
 * stdin.                                *
 * The freenodes() function takes care   *
 * of releasing the memory for names.    *
 *****************************************/
Name *readname(void)
{
  Name *pName = malloc(sizeof(Name));
  printf_s("Enter the first name: ");
  fgets(pName->first, FIRST_MAX, stdin);
  size_t len = strnlen_s(pName->first, FIRST_MAX);
  if(pName->first[len - 1] == '\n')                   // If there's a newline at the end 
    pName->first[len - 1] = '\0';                     // overwrite it.

  printf_s("Enter the second name: ");
  fgets(pName->second, SECOND_MAX, stdin);
  len = strnlen_s(pName->second, SECOND_MAX);
  if(pName->second[len - 1] == '\n')                  // If there's a newline at the end
    pName->second[len - 1] = '\0';                    // overwrite it.
  return pName;
}