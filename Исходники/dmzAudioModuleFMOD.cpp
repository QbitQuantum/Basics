dmz::Boolean
dmz::AudioModuleFMOD::get_mute_all_state (Boolean &mute) {

   Boolean result (False);

   if (_system) {

      FMOD::ChannelGroup *masterChannelGroup (0);
      FMOD_RESULT fmodResult = _system->getMasterChannelGroup (&masterChannelGroup);

      if (masterChannelGroup &&
            _error_check ("Getting master channel group", fmodResult)) {

         fmodResult = masterChannelGroup->getMute (&mute);

         if (_error_check ("Getting mute state for all sounds", fmodResult)) {

            result = True;
         }
      }
   }

   return result;
}