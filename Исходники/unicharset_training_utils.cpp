// Helper sets the character attribute properties and sets up the script table.
// Does not set tops and bottoms.
void SetupBasicProperties(bool report_errors, bool decompose,
                          UNICHARSET* unicharset) {
  for (int unichar_id = 0; unichar_id < unicharset->size(); ++unichar_id) {
    // Convert any custom ligatures.
    const char* unichar_str = unicharset->id_to_unichar(unichar_id);
    for (int i = 0; UNICHARSET::kCustomLigatures[i][0] != nullptr; ++i) {
      if (!strcmp(UNICHARSET::kCustomLigatures[i][1], unichar_str)) {
        unichar_str = UNICHARSET::kCustomLigatures[i][0];
        break;
      }
    }

    // Convert the unichar to UTF32 representation
    std::vector<char32> uni_vector = UNICHAR::UTF8ToUTF32(unichar_str);

    // Assume that if the property is true for any character in the string,
    // then it holds for the whole "character".
    bool unichar_isalpha = false;
    bool unichar_islower = false;
    bool unichar_isupper = false;
    bool unichar_isdigit = false;
    bool unichar_ispunct = false;

    for (char32 u_ch : uni_vector) {
      if (u_isalpha(u_ch)) unichar_isalpha = true;
      if (u_islower(u_ch)) unichar_islower = true;
      if (u_isupper(u_ch)) unichar_isupper = true;
      if (u_isdigit(u_ch)) unichar_isdigit = true;
      if (u_ispunct(u_ch)) unichar_ispunct = true;
    }

    unicharset->set_isalpha(unichar_id, unichar_isalpha);
    unicharset->set_islower(unichar_id, unichar_islower);
    unicharset->set_isupper(unichar_id, unichar_isupper);
    unicharset->set_isdigit(unichar_id, unichar_isdigit);
    unicharset->set_ispunctuation(unichar_id, unichar_ispunct);

    tesseract::IcuErrorCode err;
    unicharset->set_script(unichar_id, uscript_getName(
        uscript_getScript(uni_vector[0], err)));

    const int num_code_points = uni_vector.size();
    // Obtain the lower/upper case if needed and record it in the properties.
    unicharset->set_other_case(unichar_id, unichar_id);
    if (unichar_islower || unichar_isupper) {
      std::vector<char32> other_case(num_code_points, 0);
      for (int i = 0; i < num_code_points; ++i) {
        // TODO(daria): Ideally u_strToLower()/ustrToUpper() should be used.
        // However since they deal with UChars (so need a conversion function
        // from char32 or UTF8string) and require a meaningful locale string,
        // for now u_tolower()/u_toupper() are used.
        other_case[i] = unichar_islower ? u_toupper(uni_vector[i]) :
          u_tolower(uni_vector[i]);
      }
      std::string other_case_uch = UNICHAR::UTF32ToUTF8(other_case);
      UNICHAR_ID other_case_id =
          unicharset->unichar_to_id(other_case_uch.c_str());
      if (other_case_id != INVALID_UNICHAR_ID) {
        unicharset->set_other_case(unichar_id, other_case_id);
      } else if (unichar_id >= SPECIAL_UNICHAR_CODES_COUNT && report_errors) {
        tprintf("Other case %s of %s is not in unicharset\n",
                other_case_uch.c_str(), unichar_str);
      }
    }

    // Set RTL property and obtain mirror unichar ID from ICU.
    std::vector<char32> mirrors(num_code_points, 0);
    for (int i = 0; i < num_code_points; ++i) {
      mirrors[i] = u_charMirror(uni_vector[i]);
      if (i == 0) {  // set directionality to that of the 1st code point
        unicharset->set_direction(unichar_id,
                                  static_cast<UNICHARSET::Direction>(
                                      u_charDirection(uni_vector[i])));
      }
    }
    std::string mirror_uch = UNICHAR::UTF32ToUTF8(mirrors);
    UNICHAR_ID mirror_uch_id = unicharset->unichar_to_id(mirror_uch.c_str());
    if (mirror_uch_id != INVALID_UNICHAR_ID) {
      unicharset->set_mirror(unichar_id, mirror_uch_id);
    } else if (report_errors) {
      tprintf("Mirror %s of %s is not in unicharset\n",
              mirror_uch.c_str(), unichar_str);
    }

    // Record normalized version of this unichar.
    std::string normed_str;
    if (unichar_id != 0 &&
        tesseract::NormalizeUTF8String(
            decompose ? tesseract::UnicodeNormMode::kNFKD
                      : tesseract::UnicodeNormMode::kNFKC,
            tesseract::OCRNorm::kNormalize, tesseract::GraphemeNorm::kNone,
            unichar_str, &normed_str) &&
        !normed_str.empty()) {
      unicharset->set_normed(unichar_id, normed_str.c_str());
    } else {
      unicharset->set_normed(unichar_id, unichar_str);
    }
    ASSERT_HOST(unicharset->get_other_case(unichar_id) < unicharset->size());
  }
  unicharset->post_load_setup();
}