/*----------------------------------------------------------------------
|   main
+---------------------------------------------------------------------*/
int
main(int argc, char** argv)
{
    if (argc < 2) {
        PrintUsageAndExit();
    }
    
    // default options
    Options.verbose                = false;
    Options.input                  = NULL;
    Options.init_segment_name      = AP4_SPLIT_DEFAULT_INIT_SEGMENT_NAME;
    Options.media_segment_name     = AP4_SPLIT_DEFAULT_MEDIA_SEGMENT_NAME;
    Options.pattern_params         = AP4_SPLIT_DEFAULT_PATTERN_PARAMS;
    Options.start_number           = 1;
    Options.track_id               = 0;
    Options.audio_only             = false;
    Options.video_only             = false;
    Options.init_only              = false;
    Options.track_filter           = 0;
    
    // parse command line
    AP4_Result result;
    char** args = argv+1;
    while (const char* arg = *args++) {
        if (!strcmp(arg, "--verbose")) {
            Options.verbose = true;
        } else if (!strcmp(arg, "--init-segment")) {
            if (*args == NULL) {
                fprintf(stderr, "ERROR: missing argument after --init-segment option\n");
                return 1;
            }
            Options.init_segment_name = *args++;
        } else if (!strcmp(arg, "--media-segment")) {
            if (*args == NULL) {
                fprintf(stderr, "ERROR: missing argument after --media-segment option\n");
                return 1;
            }
            Options.media_segment_name = *args++;
        } else if (!strcmp(arg, "--pattern-parameters")) {
            if (*args == NULL) {
                fprintf(stderr, "ERROR: missing argument after --pattern-params option\n");
                return 1;
            }
            Options.pattern_params = *args++;
        } else if (!strcmp(arg, "--track-id")) {
            Options.track_id = strtoul(*args++, NULL, 10);
        } else if (!strcmp(arg, "--start-number")) {
            Options.start_number = strtoul(*args++, NULL, 10);
        } else if (!strcmp(arg, "--init-only")) {
            Options.init_only = true;
        } else if (!strcmp(arg, "--audio")) {
            Options.audio_only = true;
        } else if (!strcmp(arg, "--video")) {
            Options.video_only = true;
        } else if (Options.input == NULL) {
            Options.input = arg;
        } else {
            fprintf(stderr, "ERROR: unexpected argument\n");
            return 1;
        }
    }

    // check args
    if (Options.input == NULL) {
        fprintf(stderr, "ERROR: missing input file name\n");
        return 1;
    }
    if ((Options.audio_only && (Options.video_only || Options.track_id)) ||
        (Options.video_only && (Options.audio_only || Options.track_id)) ||
        (Options.track_id   && (Options.audio_only || Options.video_only))) {
        fprintf(stderr, "ERROR: --audio, --video and --track-id options are mutualy exclusive\n");
        return 1;
    }
    if (strlen(Options.pattern_params) < 1) {
        fprintf(stderr, "ERROR: --pattern-params argument is too short\n");
        return 1;
    }
    if (strlen(Options.pattern_params) > 2) {
        fprintf(stderr, "ERROR: --pattern-params argument is too long\n");
        return 1;
    }
    const char* cursor = Options.pattern_params;
    while (*cursor) {
        if (*cursor != 'I' && *cursor != 'N') {
            fprintf(stderr, "ERROR: invalid pattern parameter '%c'\n", *cursor);
            return 1;
        }
        ++cursor;
    }
    
	// create the input stream
    AP4_ByteStream* input = NULL;
    result = AP4_FileByteStream::Create(Options.input, AP4_FileByteStream::STREAM_MODE_READ, input);
    if (AP4_FAILED(result)) {
        fprintf(stderr, "ERROR: cannot open input (%d)\n", result);
        return 1;
    }
    
    // get the movie
    AP4_File* file = new AP4_File(*input, AP4_DefaultAtomFactory::Instance, true);
    AP4_Movie* movie = file->GetMovie();
    if (movie == NULL) {
        fprintf(stderr, "no movie found in file\n");
        return 1;
    }
    
    // filter tracks if required
    if (Options.audio_only) {
        AP4_Track* track = movie->GetTrack(AP4_Track::TYPE_AUDIO);
        if (track == NULL) {
            fprintf(stderr, "--audio option specified, but no audio track found\n");
            return 1;
        }
        Options.track_filter = track->GetId();
    } else if (Options.video_only) {
        AP4_Track* track = movie->GetTrack(AP4_Track::TYPE_VIDEO);
        if (track == NULL) {
            fprintf(stderr, "--video option specified, but no video track found\n");
            return 1;
        }
        Options.track_filter = track->GetId();
    } else if (Options.track_id) {
        AP4_Track* track = movie->GetTrack(Options.track_id);
        if (track == NULL) {
            fprintf(stderr, "--track-id option specified, but no such track found\n");
            return 1;
        }
        Options.track_filter = track->GetId();
    }
    
    // save the init segment
    AP4_ByteStream* output = NULL;
    result = AP4_FileByteStream::Create(Options.init_segment_name, AP4_FileByteStream::STREAM_MODE_WRITE, output);
    if (AP4_FAILED(result)) {
        fprintf(stderr, "ERROR: cannot open output file (%d)\n", result);
        return 1;
    }
    AP4_FtypAtom* ftyp = file->GetFileType(); 
    if (ftyp) {
        result = ftyp->Write(*output);
        if (AP4_FAILED(result)) {
            fprintf(stderr, "ERROR: cannot write ftyp segment (%d)\n", result);
            return 1;
        }
    }
    if (Options.track_filter) {
        AP4_MoovAtom* moov = movie->GetMoovAtom();
        
        // only keep the 'trak' atom that we need
        AP4_List<AP4_Atom>::Item* child = moov->GetChildren().FirstItem();
        while (child) {
            AP4_Atom* atom = child->GetData();
            child = child->GetNext();
            if (atom->GetType() == AP4_ATOM_TYPE_TRAK) {
                AP4_TrakAtom* trak = (AP4_TrakAtom*)atom;
                AP4_TkhdAtom* tkhd = (AP4_TkhdAtom*)trak->GetChild(AP4_ATOM_TYPE_TKHD);
                if (tkhd && tkhd->GetTrackId() != Options.track_filter) {
                    atom->Detach();
                    delete atom;
                }
            }
        }

        // only keep the 'trex' atom that we need
        AP4_ContainerAtom* mvex = AP4_DYNAMIC_CAST(AP4_ContainerAtom, moov->GetChild(AP4_ATOM_TYPE_MVEX));
        if (mvex) {
            child = mvex->GetChildren().FirstItem();
            while (child) {
                AP4_Atom* atom = child->GetData();
                child = child->GetNext();
                if (atom->GetType() == AP4_ATOM_TYPE_TREX) {
                    AP4_TrexAtom* trex = AP4_DYNAMIC_CAST(AP4_TrexAtom, atom);
                    if (trex && trex->GetTrackId() != Options.track_filter) {
                        atom->Detach();
                        delete atom;
                    }
                }
            }
        }
    }
    result = movie->GetMoovAtom()->Write(*output);
    if (AP4_FAILED(result)) {
        fprintf(stderr, "ERROR: cannot write init segment (%d)\n", result);
        return 1;
    }
        
    AP4_Atom* atom = NULL;
    unsigned int track_id = 0;
    for (;!Options.init_only;) {
        // process the next atom
        result = AP4_DefaultAtomFactory::Instance.CreateAtomFromStream(*input, atom);
        if (AP4_FAILED(result)) break;
        
        if (atom->GetType() == AP4_ATOM_TYPE_MOOF) {
            AP4_ContainerAtom* moof = AP4_DYNAMIC_CAST(AP4_ContainerAtom, atom);

            unsigned int traf_count = 0;
            AP4_ContainerAtom* traf = NULL;
            do {
                traf = AP4_DYNAMIC_CAST(AP4_ContainerAtom, moof->GetChild(AP4_ATOM_TYPE_TRAF, traf_count));
                if (traf == NULL) break;
                AP4_TfhdAtom* tfhd = AP4_DYNAMIC_CAST(AP4_TfhdAtom, traf->GetChild(AP4_ATOM_TYPE_TFHD));
                if (tfhd == NULL) {
                    fprintf(stderr, "ERROR: invalid media format\n");
                    return 1;                    
                }
                track_id = tfhd->GetTrackId();
                traf_count++;
            } while (traf);
    
            // check if this fragment has more than one traf
            if (traf_count > 1) {
                if (Options.audio_only) {
                    fprintf(stderr, "ERROR: --audio option incompatible with multi-track fragments");
                    return 1;
                }
                if (Options.video_only) {
                    fprintf(stderr, "ERROR: --video option incompatible with multi-track fragments");
                    return 1;
                }
                track_id = 0;
            }
            
            // open a new file for this fragment
            if (output) {
                output->Release();
                output = NULL;
            }
            char segment_name[4096];
            if (Options.track_filter == 0 || Options.track_filter == track_id) {
                AP4_UI64 p[2] = {0,0};
                unsigned int params_len = strlen(Options.pattern_params);
                for (unsigned int i=0; i<params_len; i++) {
                    if (Options.pattern_params[i] == 'I') {
                        p[i] = track_id;
                    } else if (Options.pattern_params[i] == 'N') {
                        p[i] = NextFragmentIndex(track_id)+Options.start_number;
                    }
                }
                switch (params_len) {
                    case 1:
                        sprintf(segment_name, Options.media_segment_name, p[0]);
                        break;
                    case 2:
                        sprintf(segment_name, Options.media_segment_name, p[0], p[1]);
                        break;
                    default:
                        segment_name[0] = 0;
                        break;
                }
                result = AP4_FileByteStream::Create(segment_name, AP4_FileByteStream::STREAM_MODE_WRITE, output);
                if (AP4_FAILED(result)) {
                    fprintf(stderr, "ERROR: cannot open output file (%d)\n", result);
                    return 1;
                }
            }
        }
        
        // write the atom
        if (output && atom->GetType() != AP4_ATOM_TYPE_MFRA) {
            atom->Write(*output);
        }
        delete atom;
    }

    // cleanup
    delete file;
    if (input) input->Release();
    if (output) output->Release();
    
    return 0;
}