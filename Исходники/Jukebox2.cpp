void Jukebox2::PlayRandomSound(FatReader &dir){
  //Serial.print("OMG!");
  int count = 0;
  FatReader tempFile;
  dir_t dirBuf;     // buffer for directory reads
  int r = random(1,fileCount(dir));
  dir.rewind();
  while (dir.readDir(dirBuf) > 0) {    // Read every file in the directory one at a time
    //Serial.print("LOL!");
    //Serial.println(r);
      // Skip it if not a subdirectory and not a .WAV file
    if (!DIR_IS_SUBDIR(dirBuf)
         && strncmp_P((char *)&dirBuf.name[8], PSTR("WAV"), 3)) {
      continue;
    }

    if (!tempFile.open(vol, dirBuf)) {        // open the file in the directory
      Serial.print("file.open failed");          // something went wrong
    }

    if (tempFile.isDir()) {                   // check if we opened a new directory

    }
    else
    {
      count++;
      if(count == r){
        Serial.println("found a sound!");
        PlaySound(dirBuf);
        dir.rewind();
        return;
      }
    }

  }
  Serial.println("Never found a sound!");
  Serial.print("Rand was:");
  Serial.println(r);
}