int quicktime_read_asf(quicktime_t *file)
{
	quicktime_asf_t *asf = calloc(1, sizeof(quicktime_asf_t));
	int got_header = 0;
	int debug = 1;
	int i;

	file->asf = asf;
	quicktime_set_position(file, 16 + 14);
	
	while(1)
	{
		quicktime_guid_t guid;
		int64_t guid_size;
		int64_t guid_start = quicktime_position(file);

		bzero(&guid, sizeof(guid));
		quicktime_read_guid(file, &guid);
		guid_size = quicktime_read_int64_le(file);

		printf("quicktime_read_asf start=0x%llx size=0x%llx\n", guid_start, guid_size);

// Glitch
		if(guid_size < 24) return 1;
		
		
		if(!memcmp(&guid, &file_header, sizeof(guid)))
		{
			quicktime_guid_t leaf_guid;
			got_header = 1;
			quicktime_read_guid(file, &leaf_guid);
			asf->header.file_size = quicktime_read_int64_le(file);
			asf->header.create_time = quicktime_read_int64_le(file);
			asf->header.total_packets = quicktime_read_int64_le(file);
			asf->header.send_time = quicktime_read_int64_le(file);
			asf->header.play_time = quicktime_read_int64_le(file);
			asf->header.preroll = quicktime_read_int32_le(file);
			asf->header.ignore = quicktime_read_int32_le(file);
			asf->header.flags = quicktime_read_int32_le(file);
			asf->header.min_packet = quicktime_read_int32_le(file);
			asf->header.max_packet = quicktime_read_int32_le(file);
			asf->header.max_bitrate = quicktime_read_int32_le(file);
			asf->header.packet_size = asf->header.max_packet;
		}
		else
		if(!memcmp(&guid, &index_guid, sizeof(guid)))
		{
			quicktime_guid_t leaf_guid;
			int max;
			int count;
			int total_packets = 0;

// Leaf Guid
			quicktime_read_guid(file, &leaf_guid);
// indexed interval
			quicktime_read_int64_le(file);
// max
			max = quicktime_read_int32_le(file);
// count
			asf->index_size = quicktime_read_int32_le(file);
			asf->index = calloc(sizeof(quicktime_asfpacket_t), asf->index_size);

			for(i = 0; i < asf->index_size; i++)
			{
				asf->index[i].number = quicktime_read_int32_le(file);
				asf->index[i].count = quicktime_read_int16_le(file);
			}
		}
		else
		if(!memcmp(&guid, &stream_header, sizeof(guid)))
		{
			quicktime_asfstream_t *stream = 
				asf->streams[asf->total_streams++] = 
				new_asfstream();
			quicktime_guid_t leaf_guid;
			quicktime_read_guid(file, &leaf_guid);
			if(!memcmp(&leaf_guid, &audio_stream, sizeof(leaf_guid)))
				stream->is_audio = 1;
			else
			if(!memcmp(&leaf_guid, &video_stream, sizeof(leaf_guid)))
				stream->is_video = 1;
			else
			if(!memcmp(&leaf_guid, &ext_stream_embed_stream_header, sizeof(leaf_guid)))
				stream->is_ext_audio = 1;
			quicktime_read_guid(file, &leaf_guid);
			
			stream->total_size = quicktime_read_int64_le(file);
			stream->type_specific_size = quicktime_read_int32_le(file);
			quicktime_read_int32_le(file);
			stream->id = quicktime_read_int16_le(file) & 0x7f;
			quicktime_read_int32_le(file);
			if(stream->is_ext_audio)
			{
				quicktime_read_guid(file, &leaf_guid);
                if (!memcmp(&leaf_guid, &ext_stream_audio_stream, sizeof(leaf_guid)))
				{
                    stream->is_audio = 1;
					stream->is_ext_audio = 0;
                    quicktime_read_guid(file, &leaf_guid);
                    quicktime_read_int32_le(file);
                    quicktime_read_int32_le(file);
                    quicktime_read_int32_le(file);
                    quicktime_read_guid(file, &leaf_guid);
                    quicktime_read_int32_le(file);
                }
			}
			
			
			if(stream->is_audio)
			{
// Get WAV header
				stream->codec_tag = quicktime_read_int16_le(file);
				stream->channels = quicktime_read_int16_le(file);
				stream->samplerate = quicktime_read_int32_le(file);
				stream->bitrate = quicktime_read_int32_le(file);
				stream->block_align = quicktime_read_int16_le(file);
				if(stream->type_specific_size == 14)
					stream->bits_per_sample = 8;
				else
					stream->bits_per_sample = quicktime_read_int16_le(file);
				if(stream->type_specific_size > 16)
				{
					stream->extradata_size = quicktime_read_int16_le(file);
        			if (stream->extradata_size > 0) 
					{
            			if (stream->extradata_size > stream->type_specific_size - 18)
                			stream->extradata_size = stream->type_specific_size - 18;
            			stream->extradata = calloc(1, stream->extradata_size + 1024);
            			quicktime_read_data(file, stream->extradata, stream->extradata_size);
        			}
					else
            			stream->extradata_size = 0;
					
					if(stream->type_specific_size - stream->extradata_size - 18 > 0)
						quicktime_set_position(file,
							quicktime_position(file) + 
							stream->type_specific_size - 
							stream->extradata_size - 18);
				}

// Make fourcc from codec_tag and bits_per_sample
			}
			else
			if(stream->is_video)
			{
				int size1;
				int size2;
				quicktime_read_int32_le(file);
				quicktime_read_int32_le(file);
				quicktime_read_char(file);
				size1 = quicktime_read_int16_le(file);
				size2 = quicktime_read_int32_le(file);
				stream->width = quicktime_read_int32_le(file);
				stream->height = quicktime_read_int32_le(file);
				quicktime_read_int16_le(file);
				stream->bits_per_sample = quicktime_read_int16_le(file);
				stream->codec_tag = quicktime_read_int32_le(file);
				quicktime_set_position(file, quicktime_position(file) + 20);
				if(size1 > 40)
				{
					stream->extradata_size = size1 - 40;
					stream->extradata = calloc(1, stream->extradata_size + 1024);
					quicktime_read_data(file, stream->extradata, stream->extradata_size);
				}

// Make fourcc from codec_tag
				stream->fourcc[0] = (stream->codec_tag & 0xff);
				stream->fourcc[1] = (stream->codec_tag & 0xff00) >> 8;
				stream->fourcc[2] = (stream->codec_tag & 0xff0000) >> 16;
				stream->fourcc[3] = (stream->codec_tag & 0xff000000) >> 24;
			}
		}