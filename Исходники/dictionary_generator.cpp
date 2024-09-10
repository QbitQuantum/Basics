  static int run(int argc, char **argv) {
    static const MeCab::Option long_options[] = {
      { "dicdir",  'd',  ".",   "DIR", "set DIR as dicdir(default \".\" )" },
      { "outdir",  'o',  ".",   "DIR", "set DIR as output dir" },
      { "model",   'm',  0,     "FILE",   "use FILE as model file" },
      { "version", 'v',  0,   0,  "show the version and exit"  },
      { "training-algorithm", 'a',  "crf",    "(crf|hmm)",
        "set training algorithm" },
      { "default-emission-cost", 'E', "4000", "INT",
        "set default emission cost for HMM" },
      { "default-transition-cost", 'T', "4000", "INT",
        "set default transition cost for HMM" },
      { "help",    'h',  0,   0,  "show this help and exit."      },
      { 0, 0, 0, 0 }
    };

    Param param;

    if (!param.open(argc, argv, long_options)) {
      std::cout << param.what() << "\n\n" <<  COPYRIGHT
                << "\ntry '--help' for more information." << std::endl;
      return -1;
    }

    if (!param.help_version()) return 0;

    ContextID cid;
    DecoderFeatureIndex fi;
    DictionaryRewriter rewrite;

    const std::string dicdir = param.get<std::string>("dicdir");
    const std::string outdir = param.get<std::string>("outdir");
    const std::string model = param.get<std::string>("model");

#define DCONF(file) create_filename(dicdir, std::string(file)).c_str()
#define OCONF(file) create_filename(outdir, std::string(file)).c_str()

    CHECK_DIE(param.load(DCONF(DICRC)))
        << "no such file or directory: " << DCONF(DICRC);

    std::string charset;
    {
      Dictionary dic;
      CHECK_DIE(dic.open(DCONF(SYS_DIC_FILE), "r"));
      charset = dic.charset();
      CHECK_DIE(!charset.empty());
    }

    int default_emission_cost = 0;
    int default_transition_cost = 0;

    std::string type = param.get<std::string>("training-algorithm");
    toLower(&type);

    if (type == "hmm") {
      default_emission_cost =
          param.get<int>("default-emission-cost");
      default_transition_cost =
          param.get<int>("default-transition-cost");
      CHECK_DIE(default_transition_cost > 0)
          << "default transition cost must be > 0";
      CHECK_DIE(default_emission_cost > 0)
          << "default transition cost must be > 0";
      param.set("identity-template", 1);
    }

    CharProperty property;
    CHECK_DIE(property.open(param));
    property.set_charset(charset.c_str());

    const std::string bos = param.get<std::string>("bos-feature");
    const int factor = param.get<int>("cost-factor");

    std::vector<std::string> dic;
    enum_csv_dictionaries(dicdir.c_str(), &dic);

    {
      CHECK_DIE(dicdir != outdir) <<
          "output directory = dictionary directory! "
          "Please specify different directory.";
      CHECK_DIE(!outdir.empty()) << "output directory is empty";
      CHECK_DIE(!model.empty()) << "model file is empty";
      CHECK_DIE(fi.open(param)) << fi.what();
      CHECK_DIE(factor > 0)   << "cost factor needs to be positive value";
      CHECK_DIE(!bos.empty()) << "bos-feature is empty";
      CHECK_DIE(dic.size()) << "no dictionary is found in " << dicdir;
      CHECK_DIE(rewrite.open(DCONF(REWRITE_FILE)));
    }

    gencid_bos(bos, &rewrite, &cid);
    gencid(DCONF(UNK_DEF_FILE), &rewrite, &cid);

    for (std::vector<std::string>::const_iterator it = dic.begin();
         it != dic.end();
         ++it) {
      gencid(it->c_str(), &rewrite, &cid);
    }

    std::cout << "emitting "
              << OCONF(LEFT_ID_FILE) << "/ "
              << OCONF(RIGHT_ID_FILE) << std::endl;

    cid.build();
    cid.save(OCONF(LEFT_ID_FILE), OCONF(RIGHT_ID_FILE));

    gendic(DCONF(UNK_DEF_FILE), OCONF(UNK_DEF_FILE), property,
           &rewrite, cid, &fi, true, factor, default_emission_cost);

    for (std::vector<std::string>::const_iterator it = dic.begin();
         it != dic.end();
         ++it) {
      std::string file =  *it;
      remove_pathname(&file);
      gendic(it->c_str(), OCONF(file.c_str()), property,
             &rewrite, cid, &fi, false, factor, default_emission_cost);
    }

    genmatrix(OCONF(MATRIX_DEF_FILE), cid, &fi,
              factor, default_transition_cost);

    copy(DCONF(CHAR_PROPERTY_DEF_FILE), OCONF(CHAR_PROPERTY_DEF_FILE));
    copy(DCONF(REWRITE_FILE), OCONF(REWRITE_FILE));
    copy(DCONF(DICRC), OCONF(DICRC));

    if (type == "crf")
      copy(DCONF(FEATURE_FILE), OCONF(FEATURE_FILE));

#undef OCONF
#undef DCONF

    std::cout <<  "\ndone!\n";

    return 0;
  }