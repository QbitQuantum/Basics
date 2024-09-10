RIGHT_TYPE askForAdminRight(void){
  /*!  
   * \todo Perhaps also other rights for ui applications
   * 
   * \brief When an ui command has no right for the required application, admin password will be asked.
   */
  PRINT("You has no right for this command! Password for admin: ");
  char input[10] = {0};
    unsigned char hashvalue[HASH_SIZE];
    for(int j = 0; j < 3; j++){
      int input_size = SCAN("%s", input);
      /*!
       *  The hash value of the admin password is stored, so that, it is difficult for attacker to missuse the admin password
       *  \todo configure the hash value
       */
      //sha_construction.func((const unsigned char *)input, input_size, hashvalue);
      //if(0==memcmp(ADMIN_PASSWORD_HASH, hashvalue, sha_construction.size)){
      // TODO change admin password hash value
      if(0==memcmp(input, ADMIN_PASSWORD_HASH, 1)){
        return ADMIN_RIGHT;
      }else{
  PRINT("Password error! Try again %d/3: ",j+1);
        
      }
  }
  return NO_RIGHT;
}