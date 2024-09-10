bool
RawInput::open (const std::string &name, ImageSpec &newspec,
                const ImageSpec &config)
{
    int ret;

    // open the image
    if ( (ret = m_processor.open_file(name.c_str()) ) != LIBRAW_SUCCESS) {
        error ("Could not open file \"%s\", %s", name.c_str(), libraw_strerror(ret));
        return false;
    }

    if ( (ret = m_processor.unpack() ) != LIBRAW_SUCCESS) {
        error ("Could not unpack \"%s\", %s",name.c_str(), libraw_strerror(ret));
        return false;
    }

    // Forcing the Libraw to adjust sizes based on the capture device orientation
    m_processor.adjust_sizes_info_only();
 
    // Set file information
    m_spec = ImageSpec(m_processor.imgdata.sizes.iwidth,
                       m_processor.imgdata.sizes.iheight,
                       3, // LibRaw should only give us 3 channels
                       TypeDesc::UINT16);

    // Output 16 bit images
    m_processor.imgdata.params.output_bps = 16;

    // Set the gamma curve to Linear
    m_spec.attribute("oiio:ColorSpace","Linear");
    m_processor.imgdata.params.gamm[0] = 1.0;
    m_processor.imgdata.params.gamm[1] = 1.0;

    // Disable exposure correction (unless config "raw:auto_bright" == 1)
    m_processor.imgdata.params.no_auto_bright =
        ! config.get_int_attribute("raw:auto_bright", 0);
    // Use camera white balance if "raw:use_camera_wb" is not 0
    m_processor.imgdata.params.use_camera_wb =
        config.get_int_attribute("raw:use_camera_wb", 1);
    // Turn off maximum threshold value (unless set to non-zero)
    m_processor.imgdata.params.adjust_maximum_thr =
        config.get_float_attribute("raw:adjust_maximum_thr", 0.0f);

    // Use camera matrix (if config "raw:use_camera_matrix" is not 0)
    m_processor.imgdata.params.use_camera_matrix =
        config.get_int_attribute("raw:use_camera_matrix", 0);


    // Check to see if the user has explicitly set the output colorspace primaries
    std::string cs = config.get_string_attribute ("raw:ColorSpace", "sRGB");
    if (cs.size()) {
        static const char *colorspaces[] = { "raw",
                                             "sRGB",
                                             "Adobe",
                                             "Wide",
                                             "ProPhoto",
                                             "XYZ", NULL
                                             };

        size_t c;
        for (c=0; c < sizeof(colorspaces) / sizeof(colorspaces[0]); c++)
            if (cs == colorspaces[c])
                break;
        if (cs == colorspaces[c])
            m_processor.imgdata.params.output_color = c;
        else {
            error("raw:ColorSpace set to unknown value");
            return false;
        }
        // Set the attribute in the output spec
        m_spec.attribute("raw:ColorSpace", cs);
    } else {
        // By default we use sRGB primaries for simplicity
        m_processor.imgdata.params.output_color = 1;
        m_spec.attribute("raw:ColorSpace", "sRGB");
    }

    // Exposure adjustment
    float exposure = config.get_float_attribute ("raw:Exposure", -1.0f);
    if (exposure >= 0.0f) {
        if (exposure < 0.25f || exposure > 8.0f) {
            error("raw:Exposure invalid value. range 0.25f - 8.0f");
            return false;
        }
        m_processor.imgdata.params.exp_correc = 1; // enable exposure correction
        m_processor.imgdata.params.exp_shift = exposure; // set exposure correction
        // Set the attribute in the output spec
        m_spec.attribute ("raw:Exposure", exposure);
    }

    // Interpolation quality
    // note: LibRaw must be compiled with demosaic pack GPL2 to use
    // demosaic algorithms 5-9. It must be compiled with demosaic pack GPL3 for 
    // algorithm 10. If either of these packs are not includeded, it will silently use option 3 - AHD
    std::string demosaic = config.get_string_attribute ("raw:Demosaic");
    if (demosaic.size()) {
        static const char *demosaic_algs[] = { "linear",
                                               "VNG",
                                               "PPG",
                                               "AHD",
                                               "DCB",
                                               "Modified AHD",
                                               "AFD",
                                               "VCD",
                                               "Mixed",
                                               "LMMSE",
                                               "AMaZE",
                                               // Future demosaicing algorithms should go here
                                               NULL
                                               };
        size_t d;
        for (d=0; d < sizeof(demosaic_algs) / sizeof(demosaic_algs[0]); d++)
            if (demosaic == demosaic_algs[d])
                break;
        if (demosaic == demosaic_algs[d])
            m_processor.imgdata.params.user_qual = d;
        else if (demosaic == "none") {
#ifdef LIBRAW_DECODER_FLATFIELD
            // See if we can access the Bayer patterned data for this raw file
            libraw_decoder_info_t decoder_info;
            m_processor.get_decoder_info(&decoder_info);
            if (!(decoder_info.decoder_flags & LIBRAW_DECODER_FLATFIELD)) {
                error("Unable to extract unbayered data from file \"%s\"", name.c_str());
                return false;
            }

#endif
            // User has selected no demosaicing, so no processing needs to be done
            m_process = false;

            // The image width and height may be different now, so update with new values
            // Also we will only be reading back a single, bayered channel
            m_spec.width = m_processor.imgdata.sizes.raw_width;
            m_spec.height = m_processor.imgdata.sizes.raw_height;
            m_spec.nchannels = 1;
            m_spec.channelnames.clear();
            m_spec.channelnames.push_back("R");

            // Also, any previously set demosaicing options are void, so remove them
            m_spec.erase_attribute("oiio:Colorspace", TypeDesc::STRING);
            m_spec.erase_attribute("raw:Colorspace", TypeDesc::STRING);
            m_spec.erase_attribute("raw:Exposure", TypeDesc::STRING);

        }
        else {
            error("raw:Demosaic set to unknown value");
            return false;
        }
        // Set the attribute in the output spec
        m_spec.attribute("raw:Demosaic", demosaic);
    } else {
        m_processor.imgdata.params.user_qual = 3;
        m_spec.attribute("raw:Demosaic", "AHD");
    }

    // Metadata

    const libraw_image_sizes_t &sizes (m_processor.imgdata.sizes);
    m_spec.attribute ("PixelAspectRatio", (float)sizes.pixel_aspect);
    // FIXME: sizes. top_margin, left_margin, raw_pitch, flip, mask?

    const libraw_iparams_t &idata (m_processor.imgdata.idata);
    if (idata.make[0])
        m_spec.attribute ("Make", idata.make);
    if (idata.model[0])
        m_spec.attribute ("Model", idata.model);
    // FIXME: idata. dng_version, is_foveon, colors, filters, cdesc

    const libraw_colordata_t &color (m_processor.imgdata.color);
    m_spec.attribute("Exif:Flash", (int) color.flash_used);
    if (color.model2[0])
        m_spec.attribute ("Software", color.model2);

    // FIXME -- all sorts of things in this struct

    const libraw_imgother_t &other (m_processor.imgdata.other);
    m_spec.attribute ("Exif:ISOSpeedRatings", (int) other.iso_speed);
    m_spec.attribute ("ExposureTime", other.shutter);
    m_spec.attribute ("Exif:ShutterSpeedValue", -log2f(other.shutter));
    m_spec.attribute ("FNumber", other.aperture);
    m_spec.attribute ("Exif:ApertureValue", 2.0f * log2f(other.aperture));
    m_spec.attribute ("Exif:FocalLength", other.focal_len);
    struct tm * m_tm = localtime(&m_processor.imgdata.other.timestamp);
    char datetime[20];
    strftime (datetime, 20, "%Y-%m-%d %H:%M:%S", m_tm);
    m_spec.attribute ("DateTime", datetime);
    // FIXME: other.shot_order
    // FIXME: other.gpsdata
    if (other.desc[0])
        m_spec.attribute ("ImageDescription", other.desc);
    if (other.artist[0])
        m_spec.attribute ("Artist", other.artist);

    // FIXME -- thumbnail possibly in m_processor.imgdata.thumbnail

    read_tiff_metadata (name);

    // Copy the spec to return to the user
    newspec = m_spec;
    return true;
}