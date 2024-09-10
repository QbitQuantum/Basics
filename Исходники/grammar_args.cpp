OD grammar_args::options()
{
    namespace po = boost::program_options;
    using std::string;
    using boost::bind;
    using boost::ref;
    using namespace graehl;
    OD od("grammar options");
    od.add_options()
        ("grammar-archive,g", defaulted_value(&grammar_archive),
         "archived translation rules grammar")
        ( "grammar-format,f"
        , defaulted_value(&grammar_format),
          "legal values: brf, archive(default), fat-archive, "
          "text-archive, fat-text-archive"
        )
        ("weight-file,w"
        ,po::value<string>()->notifier(bind(&weights_from_file,ref(*this),_1))
        ,"file with feature and lm exponents (weights), "
         "single or multiple lines of: a:-1,b:2.5")
        ("weight-string"
        ,po::value<string>()->notifier(bind(&weights_from_string,ref(*this),_1))
        ,"same format as weights file; completely overrides any --weight-file")
        ("verbose-non-numeric", defaulted_value(&verbose),
         "complain to STDERR about nonnumeric rule attributes")
        ("final-weights-to", defaulted_value(&final_weights_to),
         "print weights finally used here (same format as weight-string/file)")
        ;
    OD prior_opts("Heuristic (English) per-tag prior probability options");
    prior_opts.add_options()
        ("prior-file", defaulted_value(&prior_file),
         "file with alternating <tag> <count> e.g. NP 123478.  virtual tags ignored")
        ("prior-floor-prob", defaulted_value(&prior_floor_prob),
         "minimum probability for missing or low-count tags")
        ("prior-bonus-count", defaulted_value(&prior_bonus_count),
         "give every tag that appears in prior-file this many extra counts (before normalization)")
        ("weight-prior", defaulted_value(&weight_tag_prior),
         "raise prior prob to this power for rule heuristic")
        ("tag-prior-bonus", defaulted_value(&grammar.tag_prior_bonus),
         "constant prior multiplied into (nonvirtual) tag heuristic.  greater than 1 <=>  favor tags more than virtuals")
        ;
   od.add(prior_opts);
   OD feature_opts("(nonnumeric) feature options");
   feature_opts.add_options()
       ("keep-text-features",defaulted_value(&keep_texts),
        "Keep the unused nonnumeric features in memory")
       ("keep-align",defaulted_value(&keep_align),
        "parse the 'align' attribute for word/variable alignments")
       ;
   od.add(feature_opts);
   return od;
}