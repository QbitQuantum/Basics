void UserContainer::setPermanent( const af::MCGeneral & usr, bool permanent, MonitorContainer * monitoring)
{
   std::string username( usr.getName());
   std::string hostname( usr.getHostName());

   //
   // Try to find user with provided name in container to edit permanent property
   //
   UserContainerIt usersIt( this);
   for(UserAf *user = usersIt.user(); user != NULL; usersIt.next(), user = usersIt.user())
   {
      if( username == user->getName())
      {
         bool changed = false;
         if( user->getHostName() != hostname )
         {
            user->setHostName( hostname);
            changed = true;
         }

         // set permanent property if it differ
         if( user->isPermanent() != permanent)
         {
            changed = true;
            user->setPermanent( permanent);
            if( permanent) AFCommon::QueueDBAddItem( user);
            else AFCommon::QueueDBDelItem( user);
         }

         if( changed && monitoring)
         {
            monitoring->addEvent( af::Msg::TMonitorUsersChanged, user->getId());
         }

         // return if user exists in container
         return;
      }
   }
   //
   //    User with provided name does not exist container
   //
   if( permanent == false)
   {
      // Error: user to unset permanent does not exist
      AFERRAR("UserContainer::setPermanent: No user \"%s\" founded.\n", username.c_str());
      return;
   }
   //
   //    Create a new permanent user and put him to database
   //
   UserAf *user = new UserAf( username, hostname);
   if( addUser( user) == 0)
   {
      delete user;
      AFERRAR("UserContainer::setPermanent: Can't add user \"%s\" node to container.", username.c_str());
      return;
   }
   user->setPermanent( true);
   AFCommon::QueueDBAddItem( user);
   if( monitoring) monitoring->addEvent( af::Msg::TMonitorUsersAdd, user->getId());
   return;
}