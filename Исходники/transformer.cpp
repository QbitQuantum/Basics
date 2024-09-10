void Transformer::transform(const File& in, const File& out,
        const log4cxx::Filter::PatternList& patterns)
{
    //
    //   if no patterns just copy the file
    //
    if (patterns.size() == 0) {
        copyFile(in, out);
    } else {
   Pool p;
        apr_pool_t* pool = p.getAPRPool();
 
        //
        //   write the regex's to a temporary file since they
        //      may get mangled if passed as parameters
        //
        std::string regexName;
        Transcoder::encode(in.getPath(), regexName);
        regexName.append(".sed");
        createSedCommandFile(regexName, patterns, pool);


        //
        //  prepare to launch sed
        //
        //
        apr_procattr_t* attr = NULL;
        apr_status_t stat = apr_procattr_create(&attr, pool);
        assert(stat == APR_SUCCESS);

        stat = apr_procattr_io_set(attr, APR_NO_PIPE, APR_FULL_BLOCK,
                             APR_FULL_BLOCK);
        assert(stat == APR_SUCCESS);

        //
        //   find the program on the path
        //
        stat = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
        assert(stat == APR_SUCCESS);

        //
        //   build the argument list
        //      using Q as regex separator on s command
        //
        const char** args = (const char**)
          apr_palloc(pool, 5 * sizeof(*args));
        int i = 0;

        //
        //   not well documented
        //     but the first arg is a duplicate of the executable name
        //
        args[i++] = "sed";


        std::string regexArg("-f");
        regexArg.append(regexName);
        args[i++] = apr_pstrdup(pool, regexArg.c_str());

        //
        //    specify the input file
        args[i++] = Transcoder::encode(in.getPath(), p);
        args[i] = NULL;



        //
        //    set the output stream to the filtered file
        //
        apr_file_t* child_out;
        apr_int32_t flags = APR_FOPEN_READ | APR_FOPEN_WRITE |
            APR_FOPEN_CREATE | APR_FOPEN_TRUNCATE;
        stat = out.open(&child_out, flags, APR_OS_DEFAULT, p);
        assert(stat == APR_SUCCESS);

        stat =  apr_procattr_child_out_set(attr, child_out, NULL);
        assert(stat == APR_SUCCESS);

        //
        //   redirect the child's error stream to this processes' error stream
        //
        apr_file_t* child_err;
        stat = apr_file_open_stderr(&child_err, pool);
        assert(stat == 0);
        stat =  apr_procattr_child_err_set(attr, child_err, NULL);
        assert(stat == APR_SUCCESS);



        apr_proc_t pid;
        stat = apr_proc_create(&pid,"sed", args, NULL, attr, pool);
        if (stat != APR_SUCCESS) {
            puts("Error invoking sed, sed must be on the path in order to run unit tests");
        }
        assert(stat == APR_SUCCESS);

        apr_proc_wait(&pid, NULL, NULL, APR_WAIT);
        stat = apr_file_close(child_out);
        assert(stat == APR_SUCCESS);
     }


}