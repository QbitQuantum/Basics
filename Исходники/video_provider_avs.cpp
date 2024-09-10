AvisynthVideoProvider::AvisynthVideoProvider(agi::fs::path const& filename, std::string const& colormatrix)
{
	agi::acs::CheckFileRead(filename);

	std::lock_guard<std::mutex> lock(avs.GetMutex());

#ifdef _WIN32
	if (agi::fs::HasExtension(filename, "avi")) {
		// Try to read the keyframes before actually opening the file as trying
		// to open the file while it's already open can cause problems with
		// badly written VFW decoders
		AVIFileInit();

		PAVIFILE pfile;
		long hr = AVIFileOpen(&pfile, filename.c_str(), OF_SHARE_DENY_WRITE, 0);
		if (hr) {
			warning = "Unable to open AVI file for reading keyframes:\n";
			switch (hr) {
				case AVIERR_BADFORMAT:
					warning += "The file is corrupted, incomplete or has an otherwise bad format.";
					break;
				case AVIERR_MEMORY:
					warning += "The file could not be opened because of insufficient memory.";
					break;
				case AVIERR_FILEREAD:
					warning += "An error occurred reading the file. There might be a problem with the storage media.";
					break;
				case AVIERR_FILEOPEN:
					warning += "The file could not be opened. It might be in use by another application, or you do not have permission to access it.";
					break;
				case REGDB_E_CLASSNOTREG:
					warning += "There is no handler installed for the file extension. This might indicate a fundamental problem in your Video for Windows installation, and can be caused by extremely stripped Windows installations.";
					break;
				default:
					warning += "Unknown error.";
					break;
			}
			goto file_exit;
		}

		PAVISTREAM ppavi;
		if (hr = AVIFileGetStream(pfile, &ppavi, streamtypeVIDEO, 0)) {
			warning = "Unable to open AVI video stream for reading keyframes:\n";
			switch (hr) {
				case AVIERR_NODATA:
					warning += "The file does not contain a usable video stream.";
					break;
				case AVIERR_MEMORY:
					warning += "Not enough memory.";
					break;
				default:
					warning += "Unknown error.";
					break;
			}
			goto file_release;
		}

		AVISTREAMINFO avis;
		if (FAILED(AVIStreamInfo(ppavi,&avis,sizeof(avis)))) {
			warning = "Unable to read keyframes from AVI file:\nCould not get stream information.";
			goto stream_release;
		}

		for (size_t i = 0; i < avis.dwLength; i++) {
			if (AVIStreamIsKeyFrame(ppavi, i))
				keyframes.push_back(i);
		}

		// If every frame is a keyframe then just discard the keyframe data as it's useless
		if (keyframes.size() == (size_t)avis.dwLength)
			keyframes.clear();

		// Clean up
stream_release:
		AVIStreamRelease(ppavi);
file_release:
		AVIFileRelease(pfile);
file_exit:
		AVIFileExit();
	}
#endif

	try {
		auto script = Open(filename);

		// Check if video was loaded properly
		if (!script.IsClip() || !script.AsClip()->GetVideoInfo().HasVideo())
			throw VideoNotSupported("No usable video found");

		vi = script.AsClip()->GetVideoInfo();
		if (!vi.IsRGB()) {
			/// @todo maybe read ColorMatrix hints for d2v files?
			AVSValue args[2] = { script, "Rec601" };
			bool force_bt601 = OPT_GET("Video/Force BT.601")->GetBool() || colormatrix == "TV.601";
			bool bt709 = vi.width > 1024 || vi.height >= 600;
			if (bt709 && (!force_bt601 || colormatrix == "TV.709")) {
				args[1] = "Rec709";
				colorspace = "TV.709";
			}
			else
				colorspace = "TV.601";
			const char *argnames[2] = { 0, "matrix" };
			script = avs.GetEnv()->Invoke("ConvertToRGB32", AVSValue(args, 2), argnames);
		}
		else
			colorspace = "None";

		RGB32Video = avs.GetEnv()->Invoke("Cache", script).AsClip();
		vi = RGB32Video->GetVideoInfo();
		fps = (double)vi.fps_numerator / vi.fps_denominator;
	}
	catch (AvisynthError const& err) {
		throw VideoOpenError("Avisynth error: " + std::string(err.msg));
	}
}