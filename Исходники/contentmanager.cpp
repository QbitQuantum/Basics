   IContent* ContentManager::load(const String& name)
   {
      IContent* presult = NULL;

      String path = name + UTEXT(".c2d");
      path.toLower();

      File* pfile = FileSystem::getInstance().open(path, File::ERead | File::EBinary);
      if ( pfile != NULL )
      {
         Uuid uuid;
         FileReaderStream stream(*pfile);
         uuid.read(stream);

         ContentModule* pmodule = findModule(uuid);
         if ( pmodule != NULL )
         {
            ContentReader& reader = pmodule->getReader();
            reader.setContentManager(*this);
            reader.setGraphicsDevice(mpDevice);
            reader.setPhysicsSimulator(mpSimulator);
            reader.setSoundManager(mpSoundManager);

            presult = reader.read(stream);
            if ( presult != NULL )
            {
               presult->setFilename(name);
            }
         }
      }

      return presult;
   }