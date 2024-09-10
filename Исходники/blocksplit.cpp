int main(int argc, char* argv[]) {
    namespace po = boost::program_options;

    std::vector<std::string> files, samples;

    std::string regions_bed = "";
    std::string targets_bed = "";
    std::string out_bed = "";

    // limits
    std::string chr = "";
    int64_t start = -1;
    int64_t end = -1;

    int64_t rlimit = -1;
    int64_t message = -1;
    int64_t window = 30;
    bool apply_filters = false;

    int nblocks = 32;
    int nvars = 100;

    bool verbose = false;

    try
    {
        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("version", "Show version")
            ("input-file", po::value<std::vector<std::string> >(), "The input VCF/BCF file(s) (use file:sample to specify a sample)")
            ("output,o", po::value<std::string>(), "Write a bed file giving the locations of overlapping blocks (use - for stdout).")
            ("regions,R", po::value<std::string>(), "Use a bed file for getting a subset of regions (traversal via tabix).")
            ("targets,T", po::value<std::string>(), "Use a bed file for getting a subset of targets (streaming the whole file, ignoring things outside the bed regions).")
            ("location,l", po::value<std::string>(), "The location / subset.")
            ("limit-records,L", po::value<int64_t>(), "Maximum number of records to process")
            ("message-every,m", po::value<int64_t>(), "Print a message every N records.")
            ("window,w", po::value<int64_t>(), "Overlap window length.")
            ("nblocks", po::value<int>(), "Maximum number of blocks to break into (32).")
            ("nvars", po::value<int>(), "Minimum number of variants per block (100).")
            ("apply-filters,f", po::value<bool>(), "Apply filtering in VCF.")
            ("verbose", po::value<bool>(), "Verbose output.")
        ;

        po::positional_options_description popts;
        popts.add("input-file", -1);

        po::options_description cmdline_options;
        cmdline_options
            .add(desc)
        ;

        po::variables_map vm;
        
        po::store(po::command_line_parser(argc, argv).
                  options(cmdline_options).positional(popts).run(), vm);
        po::notify(vm); 

        if (vm.count("version")) 
        {
            std::cout << "blocksplit version " << HAPLOTYPES_VERSION << "\n";
            return 0;
        }

        if (vm.count("help")) 
        {
            std::cout << desc << "\n";
            return 1;
        }

        if (vm.count("input-file"))
        {
            std::vector<std::string> fs = vm["input-file"].as< std::vector<std::string> >();

            for(std::string const & s : fs)
            {
                std::vector<std::string> v;
                stringutil::split(s, v, ":");
                std::string filename, sample = "";

                // in case someone passes a ":"
                assert(v.size() > 0);

                filename = v[0];

                if(v.size() > 1)
                {
                    sample = v[1];
                }

                files.push_back(filename);
                samples.push_back(sample);         
            }
        }

        if(files.size() == 0)
        {
            error("Please specify at least one input file.");
        }

        if (vm.count("output"))
        {
            out_bed = vm["output"].as< std::string >();
        }
        else
        {
            out_bed = "-";
        }

        if (vm.count("regions"))
        {
            regions_bed = vm["regions"].as< std::string >();
        }

        if (vm.count("targets"))
        {
            targets_bed = vm["targets"].as< std::string >();
        }

        if (vm.count("verbose"))
        {
            verbose = vm["verbose"].as<bool>();
        }

        if (vm.count("location"))
        {
            stringutil::parsePos(vm["location"].as< std::string >(), chr, start, end);
        }

        if (vm.count("limit-records"))
        {
            rlimit = vm["limit-records"].as< int64_t >();
        }

        if (vm.count("message-every"))
        {
            message = vm["message-every"].as< int64_t >();
        }

        if (vm.count("apply-filters"))
        {
            apply_filters = vm["apply-filters"].as< bool >();
        }

        if (vm.count("window"))
        {
            window = vm["window"].as< int64_t >();
        }

        if (vm.count("nblocks"))
        {
            nblocks = vm["nblocks"].as< int >();
        }

        if (vm.count("nvars"))
        {
            nvars = vm["nvars"].as< int >();
        }

    } 
    catch (po::error & e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch(std::runtime_error & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch(std::logic_error & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    try
    {
        VariantReader r;

        if(regions_bed != "")
        {
            r.setRegions(regions_bed.c_str(), true);
        }
        if(targets_bed != "")
        {
            r.setTargets(targets_bed.c_str(), true);
        }

        std::list<int> sids;
        for(size_t i = 0; i < files.size(); ++i)
        {
            sids.push_back(r.addSample(files[i].c_str(), samples[i].c_str()));
        }

        r.setApplyFilters(apply_filters);

        bool stop_after_chr_change = false;
        if(chr != "")
        {
            r.rewind(chr.c_str(), start);
            stop_after_chr_change = true;
        }

        int64_t rcount = 0;
        int64_t last_end = -1;
        int64_t vars = 0, total_vars = 0;

        struct Breakpoint
        {
            std::string chr; 
            int64_t pos;
            int64_t vars;
        };

        std::list< Breakpoint > breakpoints;

        const auto add_bp = [&breakpoints, nvars, nblocks, &chr, &vars, verbose](int64_t bp)
        {
            if (vars > int64_t(nvars))
            {
                if(verbose)
                {
                    std::cerr << "Break point at " << chr << ":" << bp << " (" << vars << " variants)" << "\n";
                }
                breakpoints.push_back(Breakpoint{chr, bp, vars});
                vars = 0;
            }
        };

        std::string firstchr;

        while(r.advance(true, false))
        {
            if(rlimit != -1)
            {
                if(rcount >= rlimit)
                {
                    break;
                }
            }

            Variants & v = r.current();
            if(end != -1 && ( (v.pos > end) || (chr != "" && v.chr != chr)) )
            {
                break;
            }
            if(stop_after_chr_change && chr != "" && v.chr != chr)
            {
                break;
            }
            chr = v.chr;
            if (firstchr.size() == 0)
            {
                firstchr = chr;
            }

            // 
            if(chr != "" && v.chr != chr)
            {
                last_end = -1;
            }

            if(message > 0 && (rcount % message) == 0)
            {
                std::cerr << "From " << chr << ":" << last_end << " (" 
                          << breakpoints.size() << " bps, " << vars << " vars)" 
                          << " -- " << v << "\n";
            }

            bool call_this_pos = false;

            for(int s : sids)
            {
                Call & c = v.calls[s];
                gttype gtt = getGTType(c);
                if(!(gtt == gt_homref || gtt == gt_unknown))
                {
                    call_this_pos = true;
                    break;
                }
                if (int(v.ambiguous_alleles.size()) > s && !v.ambiguous_alleles[s].empty())
                {
                    call_this_pos = true;
                    break;                    
                }
            }

            if(!call_this_pos)
            {
                continue;
            }
            vars++;
            total_vars++;

            if(last_end >= 0 && v.pos > last_end + window) // can split here
            {
                add_bp(last_end);
            }
            last_end = std::max(last_end, v.pos + v.len - 1);

            ++rcount;
        }

        // write blocks
        std::ostream * outputfile = NULL;

        if(out_bed == "-" || out_bed == "")
        {
            outputfile = &std::cout;
        }
        else
        {
            if(verbose)
            {
                std::cerr << "Writing to " << out_bed << "\n";
            }
            outputfile = new std::ofstream(out_bed.c_str());
        }

        chr = firstchr;
        // TODO - the correct thing to do here would be to use start = 0
        // but bcftools / htslib don't like bed coordinates with start 0 
        // We should fix this in htslib, and then change it here (currently,
        // this will miss variants starting at the first coordinate of the 
        // chromosome)
        int64_t start = 1;
        int64_t vpb = 0;
        int64_t target_vpb = std::max(int64_t(nvars), total_vars / (2*nblocks));

        if(end <= 0)
        {
            end = std::numeric_limits<int>::max();
        }

        for (auto & b : breakpoints)
        {
            if (chr != b.chr)
            {
                *outputfile << chr << "\t" << start << "\t" << std::max(start + window + 1, end) << "\n";
                chr = b.chr;
                start = 1;
                vpb = 0;
            }
            vpb += b.vars;
            if(vpb > target_vpb)
            {
                *outputfile << chr << "\t" << start << "\t" << b.pos + window + 1 << "\n";
                start = b.pos + window + 1;
                vpb = 0;
            }
        }
        if(chr != "")
        {
            *outputfile << chr << "\t" << start << "\t" << std::max(start + window + 1, end) << "\n"; 
        }

        if(out_bed != "-" && out_bed != "")
        {
            delete outputfile;
        }
    }
    catch(std::runtime_error & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch(std::logic_error & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}