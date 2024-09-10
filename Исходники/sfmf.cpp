	video_writer::video_writer(
		std::wstring& target_path, IMFMediaTypePtr& audio_media_type, ID3D11DeviceContext2Ptr& context, ID3D11Texture2DPtr& texture
		/*, unsigned int width, unsigned int height*/) : target_path_(target_path), audio_media_type_(audio_media_type), context_(context), texture_(texture)
	{
		D3D11_TEXTURE2D_DESC desc = {};
		texture->GetDesc(&desc);
		width_ = desc.Width;
		height_ = desc.Height;

		const unsigned int WIDTH = width_;
		const unsigned int HEIGHT = height_;
		const unsigned int BITRATE = 3000000;
		const unsigned int ASPECT_NUM = 1;
		const unsigned int ASPECT_DENOM = 1;
		const unsigned long  BPP_IN = 32;
		const unsigned long cbMaxLength = WIDTH * HEIGHT * BPP_IN / 8;
		const unsigned int ONE_SECOND = RATE_NUM / RATE_DENOM;
		const unsigned int FRAME_NUM = 10 * ONE_SECOND;

		samples_per_second = 44100;
		average_bytes_per_second = 24000;
		channel_count = 2;
		bits_per_sample = 16;

		// 入力ストリームから SinkWriterを生成する

		CHK(MFCreateFile(MF_FILE_ACCESSMODE::MF_ACCESSMODE_WRITE, MF_FILE_OPENMODE::MF_OPENMODE_DELETE_IF_EXIST, MF_FILE_FLAGS::MF_FILEFLAGS_NONE, target_path.c_str(), &byte_stream_));

		CHK(MFCreateAttributes(&attr_, 10));
		CHK(attr_->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, true));
		CHK(attr_->SetUINT32(MF_READWRITE_DISABLE_CONVERTERS, false));
		CHK(attr_->SetUINT32(MF_SINK_WRITER_DISABLE_THROTTLING, true));




		IMFSinkWriterPtr sinkWriter;

		CHK(MFCreateSinkWriterFromURL(L".mp4", byte_stream_.Get(), attr_.Get(), &sinkWriter));
		CHK(sinkWriter.As(&sink_writer_));
		//CHK(MFCreateSinkWriterFromURL(L".mp4", byte_stream_.Get(), attr_.Get(), &sink_writer_));



		//   
		// 出力メディアタイプのセットアップ   
		//   

		// ビデオ

		CHK(MFCreateMediaType(&media_type_out_));
		CHK(media_type_out_->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
		CHK(media_type_out_->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264));
		CHK(media_type_out_->SetUINT32(MF_MT_MPEG2_PROFILE, eAVEncH264VProfile_Main));
		//CHK(media_type_out_->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32));   
		CHK(media_type_out_->SetUINT32(MF_MT_AVG_BITRATE, BITRATE));
		CHK(media_type_out_->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive));
		CHK(MFSetAttributeSize(media_type_out_.Get(), MF_MT_FRAME_SIZE, WIDTH, HEIGHT));
		CHK(MFSetAttributeRatio(media_type_out_.Get(), MF_MT_FRAME_RATE, RATE_NUM, RATE_DENOM));
		CHK(MFSetAttributeRatio(media_type_out_.Get(), MF_MT_PIXEL_ASPECT_RATIO, ASPECT_NUM, ASPECT_DENOM));

		CHK(sink_writer_->AddStream(media_type_out_.Get(), &stream_index_));




		IMFTransformPtr mft;
		//IMFRateSupportPtr ptr;

		//CHK(sink_writer_->GetServiceForStream(stream_index_, MF_RATE_CONTROL_SERVICE, __uuidof(IMFRateSupport), &ptr));

		// オーディオ

		CHK(MFCreateMediaType(&media_type_out_audio_));
		CHK(media_type_out_audio_->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio));
		CHK(media_type_out_audio_->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_AAC));
		CHK(media_type_out_audio_->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, samples_per_second));
		CHK(media_type_out_audio_->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, bits_per_sample));
		CHK(media_type_out_audio_->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS, channel_count));
		CHK(media_type_out_audio_->SetUINT32(MF_MT_AUDIO_AVG_BYTES_PER_SECOND, average_bytes_per_second));
		CHK(media_type_out_audio_->SetUINT32(MF_MT_AUDIO_BLOCK_ALIGNMENT, 1));
		CHK(sink_writer_->AddStream(media_type_out_audio_.Get(), &stream_index_audio_));

		//   
		// 入力メディアタイプのセットアップ  
		//   

		// ビデオ

		CHK(MFCreateMediaType(&media_type_in_));
		CHK(media_type_in_->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
		CHK(media_type_in_->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32));
		CHK(media_type_in_->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive));
		CHK(MFSetAttributeSize(media_type_in_.Get(), MF_MT_FRAME_SIZE, WIDTH, HEIGHT));
		CHK(MFSetAttributeRatio(media_type_in_.Get(), MF_MT_FRAME_RATE, RATE_NUM, RATE_DENOM));
		CHK(MFSetAttributeRatio(media_type_in_.Get(), MF_MT_PIXEL_ASPECT_RATIO, ASPECT_NUM, ASPECT_DENOM));

		// エンコーダーのセットアップ
		//prop_variant prop;
		//IPropertyStorePtr pPropertyStore;
		//IMFAttributesPtr pEncoderParameters;

		//CHK(PSCreateMemoryPropertyStore(__uuidof(IPropertyStore), (void**) &pPropertyStore));

		//prop.value().vt = VT_BOOL;
		//prop.value().boolVal = VARIANT_FALSE;
		//CHK(pPropertyStore->SetValue(MFPKEY_VBRENABLED, prop.value()));
		//prop.value().vt = VT_I4;
		//prop.value().lVal = 100;
		//CHK(pPropertyStore->SetValue(MFPKEY_VBRQUALITY, prop.value()));

		//CHK(MFCreateAttributes(&pEncoderParameters, 5));
		//CHK(attr_->SetUnknown(MF_SINK_WRITER_ENCODER_CONFIG, pPropertyStore.Get()));

		CHK(sink_writer_->SetInputMediaType(stream_index_, media_type_in_.Get(), nullptr /*pEncoderParameters.Get()*/));

		// オーディオ

		CHK(MFCreateMediaType(&media_type_in_audio_));
		//CHK(media_type_in_audio_->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio));
		//CHK(media_type_in_audio_->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM));
		//CHK(media_type_in_audio_->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, bits_per_sample));
		//CHK(media_type_in_audio_->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, samples_per_second));
		//CHK(media_type_in_audio_->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS, channel_count));
		audio_media_type_->CopyAllItems(media_type_in_audio_.Get());
		CHK(sink_writer_->SetInputMediaType(stream_index_audio_, media_type_in_audio_.Get(), NULL));

		// ハードウェアエンコーダが使われているかの確認

		{
			IMFTransformPtr transform;
			ICodecAPIPtr codec;
			GUID guid;

			CHK(sink_writer_->GetServiceForStream(stream_index_, GUID_NULL, IID_IMFTransform, &transform));

			IMFAttributesPtr attributes;
			CHK(transform->GetAttributes(&attributes));
			UINT32 l = 0;
			std::wstring str;
			bool use_hw = false;
			HRESULT hr = attributes->GetStringLength(MFT_ENUM_HARDWARE_URL_Attribute, &l);
			if (SUCCEEDED(hr))
			{
				str.reserve(l + 1);
				hr = attributes->GetString(MFT_ENUM_HARDWARE_URL_Attribute, (LPWSTR) str.data(), l + 1, &l);
				if (SUCCEEDED(hr)){
					use_hw = true;
					DOUT2(L"/////// HARDWARE ENCODE IS USED. ////\n");
				}
			}
		}

		//   
		// 出力開始  
		//   

		CHK(sink_writer_->BeginWriting());

		//   
		// メディア・サンプルの作成   
		//   

		CHK(MFCreateSample(&sample_));
		video_sample_time_ = 0;
		CHK(sample_->SetSampleDuration(hnsSampleDuration));

		//   
		// メディア・バッファの生成と、メディア・サンプルへの追加    
		//   

		CHK(MFCreateAlignedMemoryBuffer(cbMaxLength, MF_16_BYTE_ALIGNMENT, &buffer_));// 16 byteアラインメント
		CHK(buffer_->SetCurrentLength(cbMaxLength));
		CHK(sample_->AddBuffer(buffer_.Get()));

		//
		// 読み込みテクスチャをマップ
		sf::map<> map(context,texture, 0, D3D11_MAP_READ, 0);
		copy_image_.reset(new video_writer::copy_image(width_, height_, map.row_pitch()));
		copy_func_ = (copy_func_t)copy_image_->getCode();

	}