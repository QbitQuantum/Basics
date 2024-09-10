    static void execute_js(const QString &js, const QStringList &args, const justice_cmd &cmd) {
        QByteArray r_key = cmd.m_rbuf_key.toUtf8();
        QByteArray w_key = cmd.m_wbuf_key.toUtf8();
        QByteArray info_key = cmd.m_info_key.toUtf8();
        QString TestCount;
        int cnt = args.length();
        QByteArray ref_args[cnt];
        for (int i = 0; i != cnt; i++)
            ref_args[i] = args[i].toUtf8();

        char *argv[3 + cnt];
        char *envp[10];
        char path[] = "node";

        QByteArray script = js.toUtf8();
        argv[0] = path;
        argv[1] = script.data();
        for (int i = 0; i != cnt; i++)
            argv[2 + i] = ref_args[i].data();
        argv[2 + cnt] = NULL;

        envp[0] = r_key.data();
        envp[1] = w_key.data();
        envp[2] = info_key.data();
        envp[3] = NULL;


        if( Command_test_enable == 1 )
        {

            argv[0] = path;
            //argv[1] = "/home/justice/justice-script/execute/1.js";
            argv[1] = "/home/justice/justice-script/command/blocks.js";
            argv[2] = NULL;

            envp[3] = admin_str;
            envp[4] = buff;

            sprintf( Count_str , "TEST_CNT=%s" , TEST_COUNT.toStdString().c_str() );

            envp[5] = Count_str ;
            envp[6] = NULL;

        }


    if( Command_test_enable == 1 )
      {

        qDebug() << "argv";
        for (int i = 0; i < 3; i++)
           qDebug() << argv[i];

        qDebug() << "envp";
        for (int i = 0 ; i < 7 ; i++)
           qDebug() << envp[i];

      }
     else
      {

         qDebug() << "argv";
         for (int i = 0; i != 2 + cnt; i++)
             qDebug() << argv[i];

         qDebug() << "envp";
         for (int i = 0; i != 3; i++)
             qDebug() << envp[i];

      }



        int status =  execvpe( path, argv, envp);

        return ;
    }