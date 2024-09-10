      /* print to stdout the midi input devices on your win32 system.. */
      virtual void printInDevices()
      {
         MIDIINCAPS     mic;
         unsigned long    iNumDevs, i;

         /* Get the number of MIDI In devices in this computer */
         iNumDevs = midiInGetNumDevs();

         /* Go through all of those devices, displaying their names */
         for (i = 0; i < iNumDevs; i++)
         {
             /* Get info about the next device */
             if (!midiInGetDevCaps(i, &mic, sizeof(MIDIINCAPS)))
             {
                 /* Display its Device ID and name */
                 printf("Device ID #%u: %s\r\n", i, mic.szPname);
             }
         }

      }