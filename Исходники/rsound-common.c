static void print_help()
{
   printf("rsd - version %s - Copyright (C) 2010-2011 Hans-Kristian Arntzen\n", RSD_VERSION);
   printf("==========================================================================\n");
#ifdef _WIN32
   printf("Usage: rsd [ -p/--port | --bind | -R/--rate | -v/--verbose | --debug | -h/--help | -D/--daemon ]\n");
#else
#ifdef HAVE_SAMPLERATE
   printf("Usage: rsd [ -d/--device | -b/--backend | -p/--port | --bind | -R/--rate | -Q/--resampler | -D/--daemon | -v/--verbose | --debug | -h/--help | --single | --kill ]\n");
#else
   printf("Usage: rsd [ -d/--device | -b/--backend | -p/--port | --bind | -R/--rate | -D/--daemon | -v/--verbose | --debug | -h/--help | --single | --kill ]\n");
#endif
#endif
   printf("\n-d/--device: Specifies a device to use. This is backend specific.\n");
   printf("  Examples:\n\t-d hw:1,0\n\t-d /dev/audio\n\t-d system:playback_1,system:playback_2\n\t"
          "    Defaults to \"default\" for alsa and /dev/dsp for OSS\n");

   printf("\n-b/--backend: Specifies which audio backend to use.\n");
   printf("Supported backends: ");

#ifdef _PULSE
   printf("pulse ");
#endif
#ifdef _ALSA
   printf("alsa ");
#endif
#ifdef _OSS
   printf("oss ");
#endif
#ifdef _ROARVS
   printf("roar ");
#endif
#ifdef _AO
   printf("libao ");
#endif
#ifdef _PORTA
   printf("portaudio ");
#endif
#ifdef _JACK
   printf("jack ");
#endif
#ifdef _AL
   printf("openal ");
#endif
#ifdef _DS
   printf("dsound ");
#endif
#ifdef _MUROAR
   printf("muroar ");
#endif
#ifdef _COREAUDIO
   printf("coreaudio ");
#endif

   putchar('\n');
   putchar('\n');

   printf("-D/--daemon: Runs as daemon.\n");
#ifndef _WIN32
   printf("-p/--port: Defines which port to listen on.\n");
   printf("--single: Only allows a single connection at a time.\n");
   printf("--kill: Cleanly shuts downs the running rsd process.\n");
#endif
   printf("-R/--rate: Resamples all audio to defined samplerate before sending audio to the audio drivers. Mostly used if audio driver does not provide proper resampling.\n");
#ifdef HAVE_SAMPLERATE
   printf("-Q/--resampler: Value from 1 (worst) to 5 (best) (default: 3) defines quality of libsamplerate resampling.\n"); 
#endif
#ifdef HAVE_SYSLOG
   printf("-L/--syslog: Redirects all console output to syslog.\n");
#endif
   printf("--bind: Defines which address to bind to. Default is 0.0.0.0.\n");
   printf("\tExample: -p 18453. Defaults to port 12345.\n");
   printf("-v/--verbose: Enables verbosity\n");
   printf("-h/--help: Prints this help\n\n");
   printf("--debug: Enable more verbosity\n");
}