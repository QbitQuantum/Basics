SFXSound* SFXSound::_create( SFXDevice *device, SFXProfile *profile )
{
   AssertFatal( profile, "SFXSound::_create() - Got a null profile!" );

   SFXDescription* desc = profile->getDescription();
   if ( !desc )
   {
      Con::errorf( "SFXSound::_create() - Profile has null description!" );
      return NULL;
   }

   // Create the sound and register it.
   
   SFXSound* sound = new SFXSound( profile, desc );
   sound->registerObject();
   
   // Initialize the buffer.

   SFXBuffer* buffer = profile->getBuffer();
   if( !buffer )
   {
      sound->deleteObject();

      Con::errorf( "SFXSound::_create() - Could not create device buffer!" );
      return NULL;
   }
   
   sound->_setBuffer( buffer );
   
   // The sound is a console object... register it.
   
   
   #ifdef DEBUG_SPEW
   Platform::outputDebugString( "[SFXSound] new sound '%i' with profile '%i' (\"%s\")",
      sound->getId(), profile->getId(), profile->getName() );
   #endif
   
   // Hook up reloading.
   
   profile->getChangedSignal().notify( sound, &SFXSound::_onProfileChanged );

   return sound;
}