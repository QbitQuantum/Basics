extern int output_mp4(struct mp4_context_t* mp4_context,
                      unsigned int const* trak_sample_start,
                      unsigned int const* trak_sample_end,
                      struct bucket_t** buckets,
                      struct mp4_split_options_t* options)
{
  unsigned int i;

  uint64_t mdat_start = mp4_context->mdat_atom.start_;
  uint64_t mdat_size = mp4_context->mdat_atom.size_;
  int64_t offset;

  struct moov_t* moov = mp4_context->moov;
  unsigned char* moov_data = mp4_context->moov_data;

  uint64_t moov_size;

  long moov_time_scale = moov->mvhd_->timescale_;
  uint64_t skip_from_start = UINT64_MAX;
  uint64_t end_offset = 0;

  uint64_t moov_duration = 0;

#if 1
  uint64_t new_mdat_start = 0;
  {
    static char const free_data[] = {
      0x0, 0x0, 0x0,  42, 'f', 'r', 'e', 'e',
      'v', 'i', 'd', 'e', 'o', ' ', 's', 'e',
      'r', 'v', 'e', 'd', ' ', 'b', 'y', ' ',
      'm', 'o', 'd', '_', 'h', '2', '6', '4',
      '_', 's', 't', 'r', 'e', 'a', 'm', 'i',
      'n', 'g'
    };
    uint32_t size_of_header = (uint32_t)mp4_context->ftyp_atom.size_ +
                              sizeof(free_data);
    unsigned char* buffer = (unsigned char*)malloc(size_of_header);

    if(mp4_context->ftyp_atom.size_)
    {
      _fseeki64(mp4_context->infile, mp4_context->ftyp_atom.start_, SEEK_SET);
      if(fread(buffer, (off_t)mp4_context->ftyp_atom.size_, 1, mp4_context->infile) != 1)
      {
        MP4_ERROR("%s", "Error reading ftyp atom\n");
        free(buffer);
        return 0;
      }
    }

    // copy free data
    memcpy(buffer + mp4_context->ftyp_atom.size_, free_data,
           sizeof(free_data));

    if(options->output_format == OUTPUT_FORMAT_MP4)
    {
      struct bucket_t* bucket = bucket_init_memory(buffer, size_of_header);
      bucket_insert_tail(buckets, bucket);
    }
    free(buffer);

    new_mdat_start += size_of_header;
  }

  new_mdat_start += mp4_context->moov_atom.size_;
#endif

  offset = new_mdat_start - mp4_context->mdat_atom.start_;
  // subtract old moov size
  offset -= mp4_context->moov_atom.size_;

  for(i = 0; i != moov->tracks_; ++i)
  {
    struct trak_t* trak = moov->traks_[i];
    struct stbl_t* stbl = trak->mdia_->minf_->stbl_;

    unsigned int start_sample = trak_sample_start[i];
    unsigned int end_sample = trak_sample_end[i];

    trak_update_index(mp4_context, trak, start_sample, end_sample);

    if(trak->samples_size_ == 0)
    {
      MP4_WARNING("Trak %u contains no samples. Maybe a fragmented file?", i);
      return 1;
    }

    {
      uint64_t skip =
        trak->samples_[start_sample].pos_ - trak->samples_[0].pos_;
      if(skip < skip_from_start)
        skip_from_start = skip;
      MP4_INFO("Trak can skip %llu bytes\n", skip);

      if(end_sample != trak->samples_size_)
      {
        uint64_t end_pos = trak->samples_[end_sample].pos_;
        if(end_pos > end_offset)
          end_offset = end_pos;
        MP4_INFO("New endpos=%llu\n", end_pos);
        MP4_INFO("Trak can skip %llu bytes at end\n",
               mdat_start + mdat_size - end_offset);
      }
    }

    {
      // fixup trak (duration)
      uint64_t trak_duration = stts_get_duration(stbl->stts_);
      long trak_time_scale = trak->mdia_->mdhd_->timescale_;
      {
        uint64_t duration = trak_time_to_moov_time(trak_duration,
          moov_time_scale, trak_time_scale);
        trak->mdia_->mdhd_->duration_= trak_duration;
        trak->tkhd_->duration_ = duration;
        MP4_INFO("trak: new_duration=%llu\n", duration);

        if(duration > moov_duration)
          moov_duration = duration;
      }
    }

//      MP4_INFO("stco.size=%d, ", read_int32(stbl->stco_ + 4));
//      MP4_INFO("stts.size=%d samples=%d\n", read_int32(stbl->stts_ + 4), stts_get_samples(stbl->stts_));
//      MP4_INFO("stsz.size=%d\n", read_int32(stbl->stsz_ + 8));
//      MP4_INFO("stsc.samples=%d\n", stsc_get_samples(stbl->stsc_));
  }
  moov->mvhd_->duration_ = moov_duration;
  MP4_INFO("moov: new_duration=%.2f seconds\n", moov_duration / (float)moov_time_scale);

  // subtract bytes we skip at the front of the mdat atom
  offset -= skip_from_start;

  MP4_INFO("%s", "moov: writing header\n");

  moov_write(moov, moov_data);
  moov_size = read_32(moov_data);

  // add new moov size
  offset += moov_size;

  MP4_INFO("shifting offsets by %llu\n", offset);
  moov_shift_offsets_inplace(moov, offset);

  // traffic shaping: create offsets for each second
  create_traffic_shaping(moov,
                         trak_sample_start,
                         trak_sample_end,
                         offset,
                         options);

#ifdef COMPRESS_MOOV_ATOM
  if(!options->client_is_flash)
  {
    compress_moov(mp4_context, moov, moov_data, &moov_size);
  }
#endif

  mdat_start += skip_from_start;
  if(end_offset != 0)
  {
    mdat_size = end_offset;
  }
  mdat_size -= skip_from_start;

  bucket_insert_tail(buckets, bucket_init_memory(moov_data, moov_size));

  {
    struct mp4_atom_t mdat_atom;
    mdat_atom.type_ = FOURCC('m', 'd', 'a', 't');
    mdat_atom.short_size_ = 0; // TODO: use original small/wide mdat box

    if(options->adaptive)
    {
      // empty mdat atom
      mdat_atom.size_ = ATOM_PREAMBLE_SIZE;
    }
    else
    {
      mdat_atom.size_ = mdat_size;
    }

    {
      unsigned char buffer[32];
      int mdat_header_size = mp4_atom_write_header(buffer, &mdat_atom);
      bucket_insert_tail(buckets,
        bucket_init_memory(buffer, mdat_header_size));

      if(mdat_atom.size_ - mdat_header_size)
      {
        bucket_insert_tail(buckets,
          bucket_init_file(mdat_start + mdat_header_size,
                           mdat_atom.size_ - mdat_header_size));
      }
    }
  }

  return 1;
}