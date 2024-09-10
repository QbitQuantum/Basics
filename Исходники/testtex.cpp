static void
test_plain_texture ()
{
    std::cerr << "Testing 2d texture " << filenames[0] << ", output = " 
              << output_filename << "\n";
    const int nchannels = 4;
    ImageSpec outspec (output_xres, output_yres, nchannels, TypeDesc::HALF);
    if (! dataformatname.empty()) {
        if (dataformatname == "uint8")
            outspec.set_format (TypeDesc::UINT8);
        else if (dataformatname == "int8")
            outspec.set_format (TypeDesc::INT8);
        else if (dataformatname == "uint10") {
            outspec.attribute ("oiio:BitsPerSample", 10);
            outspec.set_format (TypeDesc::UINT16);
        }
        else if (dataformatname == "uint12") {
            outspec.attribute ("oiio:BitsPerSample", 12);
            outspec.set_format (TypeDesc::UINT16);
        }
        else if (dataformatname == "uint16")
            outspec.set_format (TypeDesc::UINT16);
        else if (dataformatname == "int16")
            outspec.set_format (TypeDesc::INT16);
        else if (dataformatname == "half")
            outspec.set_format (TypeDesc::HALF);
        else if (dataformatname == "float")
            outspec.set_format (TypeDesc::FLOAT);
        else if (dataformatname == "double")
            outspec.set_format (TypeDesc::DOUBLE);
        outspec.channelformats.clear ();
    }
    ImageBuf image (output_filename, outspec);
    ImageBufAlgo::zero (image);

    Imath::M33f scale;  scale.scale (Imath::V2f (0.5, 0.5));
    Imath::M33f rot;    rot.rotate (radians(30.0f));
    Imath::M33f trans;  trans.translate (Imath::V2f (0.35f, 0.15f));
    Imath::M33f xform = scale * rot * trans;
    xform.invert();

    TextureOptions opt;
    opt.sblur = blur;
    opt.tblur = blur;
    opt.swidth = width;
    opt.twidth = width;
    opt.nchannels = nchannels;
    
    float localfill = (fill >= 0.0f) ? fill : 1.0f;
    opt.fill = localfill;
    if (missing[0] >= 0)
        opt.missingcolor.init ((float *)&missing, 0);
//    opt.interpmode = TextureOptions::InterpSmartBicubic;
//    opt.mipmode = TextureOptions::MipModeAniso;
    TextureOptions::parse_wrapmodes (wrapmodes.c_str(), opt.swrap, opt.twrap);

    TextureOpt opt1;
    opt1.sblur = blur;
    opt1.tblur = blur;
    opt1.swidth = width;
    opt1.twidth = width;
    opt1.nchannels = nchannels;
    opt1.fill = localfill;
    if (missing[0] >= 0)
        opt1.missingcolor = (float *)&missing;
    TextureOpt::parse_wrapmodes (wrapmodes.c_str(), opt1.swrap, opt1.twrap);

    int shadepoints = blocksize*blocksize;
    float *s = ALLOCA (float, shadepoints);
    float *t = ALLOCA (float, shadepoints);
    Runflag *runflags = ALLOCA (Runflag, shadepoints);
    float *dsdx = ALLOCA (float, shadepoints);
    float *dtdx = ALLOCA (float, shadepoints);
    float *dsdy = ALLOCA (float, shadepoints);
    float *dtdy = ALLOCA (float, shadepoints);
    float *result = ALLOCA (float, shadepoints*nchannels);
    
    ustring filename = ustring (filenames[0]);
    TextureSystem::Perthread *perthread_info = texsys->get_perthread_info ();
    TextureSystem::TextureHandle *texture_handle = texsys->get_texture_handle (filename);

    for (int iter = 0;  iter < iters;  ++iter) {
        if (iters > 1 && filenames.size() > 1) {
            // Use a different filename for each iteration
            int texid = std::min (iter, (int)filenames.size()-1);
            filename = ustring (filenames[texid]);
            std::cerr << "iter " << iter << " file " << filename << "\n";
        }

        // Iterate over blocks
        for (int by = 0, b = 0;  by < output_yres;  by+=blocksize) {
            for (int bx = 0;  bx < output_xres;  bx+=blocksize, ++b) {
                // Trick: switch to other textures on later iterations, if any
                if (iters == 1 && filenames.size() > 1) {
                    // Use a different filename from block to block
                    filename = ustring (filenames[b % (int)filenames.size()]);
                }

                // Process pixels within a block.  First save the texture warp
                // (s,t) and derivatives into SIMD vectors.
                int idx = 0;
                for (int y = by; y < by+blocksize; ++y) {
                    for (int x = bx; x < bx+blocksize; ++x) {
                        if (x < output_xres && y < output_yres) {
                            if (nowarp) {
                                s[idx] = (float)x/output_xres * sscale + offset[0];
                                t[idx] = (float)y/output_yres * tscale + offset[1];
                                dsdx[idx] = 1.0f/output_xres * sscale;
                                dtdx[idx] = 0;
                                dsdy[idx] = 0;
                                dtdy[idx] = 1.0f/output_yres * tscale;
                            } else if (tube) {
                                float xt = float(x)/output_xres - 0.5f;
                                float dxt_dx = 1.0f/output_xres;
                                float yt = float(y)/output_yres - 0.5f;
                                float dyt_dy = 1.0f/output_yres;
                                float theta = atan2f (yt, xt);
                                // See OSL's Dual2 for partial derivs of
                                // atan2, hypot, and 1/x
                                float denom = 1.0f / (xt*xt + yt*yt);
                                float dtheta_dx = yt*dxt_dx * denom;
                                float dtheta_dy = -xt*dyt_dy * denom;
                                s[idx] = 4.0f * theta / (2.0f * M_PI);
                                dsdx[idx] = 4.0f * dtheta_dx / (2.0f * M_PI);
                                dsdy[idx] = 4.0f * dtheta_dy / (2.0f * M_PI);
                                float h = hypot(xt,yt);
                                float dh_dx = xt*dxt_dx / h;
                                float dh_dy = yt*dyt_dy / h;
                                h *= M_SQRT2;
                                dh_dx *= M_SQRT2; dh_dy *= M_SQRT2;
                                float hinv = 1.0f / h;
                                t[idx] = hinv;
                                dtdx[idx] = hinv * (-hinv * dh_dx);
                                dtdy[idx] = hinv * (-hinv * dh_dy);
                            } else {
                                Imath::V3f coord = warp ((float)x/output_xres,
                                                         (float)y/output_yres,
                                                         xform);
                                coord.x *= sscale;
                                coord.y *= tscale;
                                coord += offset;
                                Imath::V3f coordx = warp ((float)(x+1)/output_xres,
                                                          (float)y/output_yres,
                                                          xform);
                                coordx.x *= sscale;
                                coordx.y *= tscale;
                                coordx += offset;
                                Imath::V3f coordy = warp ((float)x/output_xres,
                                                          (float)(y+1)/output_yres,
                                                          xform);
                                coordy.x *= sscale;
                                coordy.y *= tscale;
                                coordy += offset;
                                s[idx] = coord[0];
                                t[idx] = coord[1];
                                dsdx[idx] = coordx[0] - coord[0];
                                dtdx[idx] = coordx[1] - coord[1];
                                dsdy[idx] = coordy[0] - coord[0];
                                dtdy[idx] = coordy[1] - coord[1];
                            }
                            runflags[idx] = RunFlagOn;
                        } else {
                            runflags[idx] = RunFlagOff;
                        }
                        ++idx;
                    }
                }

                // Call the texture system to do the filtering.
                bool ok;
                if (blocksize == 1) {
                    if (use_handle)
                        ok = texsys->texture (texture_handle, perthread_info, opt1,
                                              s[0], t[0], dsdx[0], dtdx[0],
                                              dsdy[0], dtdy[0], result);
                    else
                        ok = texsys->texture (filename, opt1,
                                              s[0], t[0], dsdx[0], dtdx[0],
                                              dsdy[0], dtdy[0], result);
                } else {
                    ok = texsys->texture (filename, opt, runflags, 0,
                                          shadepoints, Varying(s), Varying(t),
                                          Varying(dsdx), Varying(dtdx),
                                          Varying(dsdy), Varying(dtdy), result);
                }
                if (! ok) {
                    std::string e = texsys->geterror ();
                    if (! e.empty())
                        std::cerr << "ERROR: " << e << "\n";
                }
                for (int i = 0;  i < shadepoints*nchannels;  ++i)
                    result[i] *= scalefactor;

                // Save filtered pixels back to the image.
                idx = 0;
                for (int y = by; y < by+blocksize; ++y) {
                    for (int x = bx; x < bx+blocksize; ++x) {
                        if (runflags[idx]) {
                            image.setpixel (x, y, result + idx*nchannels);
                        }
                        ++idx;
                    }
                }
            }
        }

        if (resetstats) {
            std::cout << texsys->getstats(2) << "\n";
            texsys->reset_stats ();
        }
    }
    
    if (! image.save ()) 
        std::cerr << "Error writing " << output_filename 
                  << " : " << image.geterror() << "\n";
}