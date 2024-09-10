void Desk::readDesk (bool read_sizes)
   {
   QFile oldfile;
   QFile file (_dir + DESK_FNAME);
   QString fname;

   // if there is a maxdesk.ini file, rename it to the official name
   fname = _dir + "/maxdesk.ini";
   oldfile.setName (fname);
   if (!oldfile.exists ())
      {
      fname = _dir + "/MaxDesk.ini";
      oldfile.setName (fname);
      }
   if (oldfile.exists ())
      {
      // if we have the official file, just remove this one
      if (file.exists ())
         oldfile.remove ();
      else
         oldfile.rename (_dir + DESK_FNAME);
      }

   QTextStream stream (&file);
   QString line;
   bool files = false;
   File *f;
   int pos;

   if (file.open (QIODevice::ReadOnly)) while (!stream.atEnd())
      {
      line = stream.readLine(); // line of text excluding '\n'

//      printf( "%s\n", line.latin1() );
      if (line [0] == '[')
         {
         files = line == "[Files]";
         continue;
         }

      // add a new file
      pos = line.find ('=');
      if (files && pos != -1)
         {
         QString fname = line.left (pos);

         QFile test (_dir + fname);
         if (!test.exists ())
            continue;

         if (!addToExistingFile (fname))
            {
            f = createFile (_dir, fname);
            line = line.mid (pos + 1);
            f->decodeFile (line, read_sizes);
            _files << f;
            }
         }
      }

   // advance the position past these
   advance ();
   }