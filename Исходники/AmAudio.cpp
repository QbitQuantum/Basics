// returns 0 if everything's OK
// return -1 if error
int  AmAudioFile::open(const string& filename, OpenMode mode, bool is_tmp)
{
    close();

    AmAudioFileFormat* f_fmt = fileName2Fmt(filename);
    if(!f_fmt){
	ERROR("while trying to the format of '%s'\n",filename.c_str());
	return -1;
    }
    fmt.reset(f_fmt);

    open_mode = mode;
    this->close_on_exit = true;

    if(!is_tmp){
	fp = fopen(filename.c_str(),mode == AmAudioFile::Read ? "r" : "w+");
	if(!fp){
	    if(mode == AmAudioFile::Read)
		ERROR("file not found: %s\n",filename.c_str());
	    else
		ERROR("could not create/overwrite file: %s\n",filename.c_str());
	    return -1;
	}
    } else {
	
	fp = tmpfile();
	if(!fp){
	    ERROR("could not create temporary file: %s\n",strerror(errno));
	}
    }

    amci_file_desc_t fd;
    int ret = -1;

    if(open_mode == AmAudioFile::Write){

 	if (f_fmt->channels<0 || f_fmt->rate<0) {
	    if (f_fmt->channels<0)
		ERROR("channel count must be set for output file.\n");
	    if (f_fmt->rate<0)
		ERROR("sampling rate must be set for output file.\n");
	    close();
	    return -1;
 	}
    }

    fd.subtype = f_fmt->getSubtypeId();
    fd.sample = f_fmt->sample;
    fd.channels = f_fmt->channels;
    fd.rate = f_fmt->rate;

    if( iofmt->open && !(ret = (*iofmt->open)(fp,&fd,mode, f_fmt->getHCodecNoInit())) ) {
	if (mode == AmAudioFile::Read) {
	    f_fmt->setSubtypeId(fd.subtype);
	    f_fmt->sample = fd.sample;
	    f_fmt->channels = fd.channels;
	    f_fmt->rate = fd.rate;
	}
	begin = ftell(fp);
    }
    else {
	if(!iofmt->open)
	    ERROR("no open function\n");
	else
	    ERROR("open returned %d\n",ret);
	close();
	return ret;
    }

//     if(open_mode == AmAudioFile::Write){

// 	DBG("After open:\n");
// 	DBG("fmt::subtype = %i\n",f_fmt->getSubtypeId());
// 	DBG("fmt::sample = %i\n",f_fmt->sample);
// 	DBG("fmt::channels = %i\n",f_fmt->channels);
// 	DBG("fmt::rate = %i\n",f_fmt->rate);
//     }

    return ret;
}