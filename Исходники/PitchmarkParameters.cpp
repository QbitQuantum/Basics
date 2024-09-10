void PitchmarkParameters::save(const boost::filesystem::wpath& path)
{
  GenericDocument< UTF16<> > doc;
  Document::AllocatorType& allocator = doc.GetAllocator();
  doc.SetObject();
  doc.AddMember(L"filename", StringRef(filename.c_str()), allocator);
  doc.AddMember(L"sub_fade_start", sub_fade_start, allocator);
  doc.AddMember(L"base_pitch", base_pitch, allocator);
  {
    GenericValue< UTF16<> > base_vowel_wav(kObjectType);
    base_vowel_wav.AddMember(L"filename", StringRef(base_vowel_wav_filename.c_str()), allocator);
    base_vowel_wav.AddMember(L"from", base_vowel_wav_from, allocator);
    base_vowel_wav.AddMember(L"to", base_vowel_wav_to, allocator);
    doc.AddMember(L"base_vowel_wav", base_vowel_wav, allocator);
  }
  {
    GenericValue< UTF16<> > prefix_vowel_wav(kObjectType);
    prefix_vowel_wav.AddMember(L"filename", StringRef(prefix_vowel_wav_filename.c_str()), allocator);
    prefix_vowel_wav.AddMember(L"from", prefix_vowel_wav_from, allocator);
    prefix_vowel_wav.AddMember(L"to", prefix_vowel_wav_to, allocator);
    doc.AddMember(L"prefix_vowel_wav", prefix_vowel_wav, allocator);
  }
  {
    GenericValue< UTF16<> > tmp_val(kArrayType);
    for (size_t i=0; i<pitchmark_points.size(); i++) {
      tmp_val.PushBack(pitchmark_points[i], allocator);
    }
    doc.AddMember(L"pitchmark_points", tmp_val, allocator);
  }

  GenericStringBuffer< UTF16<> > buffer;
  PrettyWriter<GenericStringBuffer< UTF16<> >, UTF16<>, ASCII<> > writer(buffer);
  doc.Accept(writer);

  boost::filesystem::wofstream ofs(path, ios_base::trunc);
  ofs << buffer.GetString();
}