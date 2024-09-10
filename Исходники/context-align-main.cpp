bool BamProcessor::init (const ContalignParams& p)
{
    read_cnt_ = proc_cnt_ = toolongs_ = unaligned_cnt_ = fail_cnt_ = nomd_cnt_ = realigned_cnt_ = modified_cnt_ = pos_adjusted_cnt_ = 0;
    log_diff_ = log_matr_ = log_base_ = false;

    p_ = &p;

    if (!*p.inbam ())
        ers << "Input file name not specified" << Throw;

    limit_ = p.limit ();
    skip_ = p.skip ();

    infile_.OpenForRead (p.inbam ());
    if (!infile_.IsOpen ())
        ers << p.inbam () << ThrowEx (FileNotFoundRerror);

    bool index_ok = false;
    if (*p.bamidx ())
    {
        index_ok = infile_.ReadBamIndex (p.bamidx ());
        if (!index_ok)
            warn << "Unable to open specified BAM index: " << p.bamidx () << ". Default index will be attempted" <<  std::endl;
    }
    if (!index_ok)
    {
        try
        {
            index_ok = infile_.ReadBamIndex ();
        }
        catch (std::exception& e)
        {
            // for some reason not converted into return status by libStatGen
        }
        if (!index_ok)
            warn << "Unable to open default BAM index for " << p.inbam () << std::endl;
    }
    if (*p.refname () || p.refno () != -1)
    {
        if (!index_ok)
            ers << "Reference section specified, but the BAM index could not be open." << Throw;
        if (*p.refname ())
        {
            if (p.endpos () != 0)
            {
                infile_.SetReadSection (p.refname (), p.begpos (), p.endpos ());
                info << "Read section set : " << p.refname () << ": " << p.begpos () << "-" << p.endpos () << std::endl;
            }
            else
            {
                infile_.SetReadSection (p.refname ());
                info << "Read section set : " << p.refname () << std::endl;
            }
        }
        else
        {
            if (p.endpos () != 0)
            {
                info << "Read section set : ref# " << p.refno () << ": " << p.begpos () << "-" << p.endpos () << std::endl;
                infile_.SetReadSection (p.refno (), p.begpos (), p.endpos ());
            }
            else
            {
                info << "Read section set : ref# " << p.refno () << std::endl;
                infile_.SetReadSection (p.refno ());
            }
        }
    }
    if (*p.outbam ())
    {
        if (!p.overwrite () && file_exists (p.outbam ()))
            ers << "Output file " << p.outbam () << " exists. Use --ov key to allow overwriting" << Throw;
        outfile_.OpenForWrite (p.outbam ());
        if (!outfile_.IsOpen ())
            ers << "Unable to open output file " << p.outbam () << std::endl;
    }
    if (*p.logfname ())
    {
        if (!p.overwrite () && file_exists (p.logfname ()))
            ers << "Log file " << p.logfname () << " exists. Use --ov key to allow overwriting" << Throw;
        logfile_.open (p.logfname (), std::fstream::out);
        if (!logfile_.is_open ())
            ers << "Unable to open log file " << p.logfname () << std::endl;

        time_t t = time (NULL);
        logfile_ << "Context-aware realigner log\nStarted at " << asctime (localtime (&t)) << "\nParameters:\n";
        logfile_ << *(p.parameters_);
        logfile_ << std::endl;
        log_base_ = p.logging ("base");
        log_diff_ = p.logging ("diff");
        log_matr_ = p.logging ("matr");
    }
    band_width_ = p.bwid ();

    switch (p.algo ())
    {
        case ContalignParams::TEMPL:
        {
            matrix_.configure (genstr::nucleotides.symbols (), genstr::nucleotides.size (), genstr::NegUnitaryMatrix <int, 4>().values ());
            gap_cost_.configure (p.gip (), p.gep ());
            taligner_.configure (&matrix_, &gap_cost_, &gap_cost_, &genstr::nn2num, &genstr::nn2num);
        }
        break;
        case ContalignParams::PLAIN:
        {
            batches_.reset (max_batch_no_);
            aligner_.init (MAX_SEQ_LEN, MAX_SEQ_LEN*MAX_BAND_WIDTH, p.gip (), p.gep (), p.mat (), -p.mis ());
            if (log_matr_)
                aligner_.set_log (logfile_);
            if (p.debug () > 5)
                aligner_.set_trace (true);
        }
        break;
        case ContalignParams::POLY:
        {
            batches_.reset (max_batch_no_);
            contalign_.init (MAX_SEQ_LEN, MAX_RSEQ_LEN, MAX_SEQ_LEN*MAX_BAND_WIDTH, p.gip (), p.gep (), p.mat (), -p.mis ());
            if (log_matr_)
                contalign_.set_log (logfile_);
            if (p.debug () > 5)
                contalign_.set_trace (true);
        }
        break;
        default:
        {
            ers << "Alignment algorithm " << p.algostr () << " not yet supported" << Throw;
        }
    }
    timer_.reset (DEFAULT_REPORT_IVAL, 1);
    return true;
}