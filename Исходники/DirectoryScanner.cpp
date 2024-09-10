      void DirectoryScanner::computeFile(db::Watchfolder folder,File & file/*, db::Preset preset, std::string outdir*/) {
        //db::HiveDb db=org::esb::hive::DatabaseService::getDatabase();
        try {
          
          litesql::DataSource<db::MediaFile> filelist = litesql::select<db::MediaFile > (folder.getDatabase(), db::MediaFile::Filename == file.getFileName() && db::MediaFile::Path == file.getFilePath());
          if(filelist.count()==0){
          if (file.isFile()) {
            LOGDEBUG("new file found:" << file.getPath());
            //const char * filename = 0;
            db::MediaFile mediafile = _importer.import(file);
            if (mediafile.id > 0 ) {

              int id = org::esb::hive::JobUtil::createJob(mediafile, folder.preset().get().one(), folder.outfolder);
              //db::Job pre = litesql::select<db::Job > (db, db::Job::Id == id).one();
              //jobcreator(fileid,p, outdir);
            }
          }

          }
        } catch (litesql::NotFound ex) {

        }
      }