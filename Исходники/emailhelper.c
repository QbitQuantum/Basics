int main(int argc, char **argv)
{
    char server[STRING_SIZE];
    char port[STRING_SIZE];
    char opt_port[STRING_SIZE];
    char user[STRING_SIZE];
    char opt_user[STRING_SIZE];
    char password[STRING_SIZE];
    char opt_password[STRING_SIZE];
    char from[STRING_SIZE];
    char to[STRING_SIZE];
    char hostname[STRING_SIZE];
    char domainname[STRING_SIZE];
    char subject[STRING_SIZE];
    char subject_prefix[STRING_SIZE];
    char message[STRING_SIZE];
    char attachment[STRING_SIZE];
    char *opt_subject = NULL;
    char *opt_messagefile = NULL;
    char *opt_attachment = NULL;
    char date[STRING_SIZE];
    NODEKV *kv = NULL;
    NODEKV *main_kv = NULL;
    int rc;
    time_t curtime;
    struct tm *loctime;

    static struct option long_options[] = {
        { "subject", required_argument, 0, 's'},
        { "messagefile", required_argument, 0, 'm'},
        { "delete", no_argument, 0, 'd'},
        { "attachment", required_argument, 0, 'a'},
        { "verbose", no_argument, 0, 'v'},
        { "help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    int c;
    int option_index = 0;

    if (!(initsetuid()))
        exit(1);

    while ((c = getopt_long(argc, argv, "s:m:da:vh", long_options, &option_index)) != -1) {
        switch (c) {
        case 0:
            break;

        case 's':
            verbose_printf(3, "Option s ... \n");
            flag_subject = 1;

            /* check a valid subject */
            int len = 0;
            len = strlen(optarg);
            if (len > STRING_SIZE - 1) {
                fprintf(stdout, "Subject too long: %s\n", optarg);
                exit(EMAIL_ERR_SUBJECT);
            }
            if (strspn(optarg, LETTERS_NUMBERS "-_:.+, ") != len) {

                fprintf(stdout, "Invalid character in subject (%s)\n", optarg);
                exit(EMAIL_ERR_SUBJECT);
            }
            opt_subject = strdup(optarg);
            break;
        case 'm':
            verbose_printf(3, "Option m ... \n");
            flag_messagefile = 1;
            opt_messagefile = strdup(optarg);
            break;
        case 'd':
            verbose_printf(3, "Option d ... \n");
            flag_delete_messagefile = 1;
            break;
        case 'a':
            verbose_printf(3, "Option a ... \n");
            flag_attachment = 1;
            opt_attachment = strdup(optarg);
            break;
        case 'v':              /* verbose */
            flag_verbose++;
            break;
        case 'h':
            usage(argv[0], EMAIL_SUCCESS);
        default:
            fprintf(stdout, "unknown option\n");
            usage(argv[0], EMAIL_ERR_ANY);
        }
    }

    verbose_printf(1, "Reading email settings ... \n");
    if (read_kv_from_file(&kv, "/var/ipcop/email/settings") != SUCCESS) {
        fprintf(stdout, "Cannot read email settings\n");
        exit(EMAIL_ERR_ANY);
    }

    strcpy(server, "");
    verbose_printf(2, "Reading EMAIL_SERVER ... \n");
    if (find_kv_default(kv, "EMAIL_SERVER", server) != SUCCESS) {
        fprintf(stdout, "Cannot read EMAIL_SERVER\n");
        exit(EMAIL_ERR_SERVER);
    }

    verbose_printf(2, "Validate EMAIL_SERVER ... \n");
    if (!(strlen(server))) {
        fprintf(stdout, "Email server cannot be empty\n");
        exit(EMAIL_ERR_SERVER);
    }
    else if (strchr(server, ' ')) {
        fprintf(stdout, "Email server cannot contain spaces\n");
        exit(EMAIL_ERR_SERVER);
    }
    else if (strlen(server) != strspn(server, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-.")) {
        fprintf(stdout, "Email server contains non valid chars\n");
        exit(EMAIL_ERR_SERVER);
    }


    strcpy(opt_port, "");
    verbose_printf(2, "Reading EMAIL_SERVER_PORT ... \n");
    if (find_kv_default(kv, "EMAIL_SERVER_PORT", opt_port) != SUCCESS) {
        fprintf(stdout, "Cannot read EMAIL_SERVER_PORT\n");
        exit(EMAIL_ERR_PORT);
    }

    verbose_printf(2, "Validate EMAIL_SERVER_PORT ... \n");
    if (strchr(opt_port, ' ')) {
        fprintf(stdout, "Email server port cannot contain spaces\n");
        exit(EMAIL_ERR_PORT);
    }
    else if (strlen(opt_port) != strspn(opt_port, NUMBERS)) {
        fprintf(stdout, "Email server port contains non valid chars\n");
        exit(EMAIL_ERR_PORT);
    }
    else if (strlen(opt_port)) {
        verbose_printf(2, "Use EMAIL_SERVER_PORT from settings... \n");
        snprintf(port, STRING_SIZE, ":%s", opt_port);
    }
    else {
        verbose_printf(2, "No EMAIL_SERVER_PORT in settings... \n");
        strcpy(port, "");
    }


    strcpy(opt_user, "");
    verbose_printf(2, "Reading EMAIL_USR ... \n");
    if (find_kv_default(kv, "EMAIL_USR", opt_user) != SUCCESS) {
        fprintf(stdout, "Cannot read EMAIL_USR\n");
        exit(EMAIL_ERR_USR);
    }

    verbose_printf(2, "Validate EMAIL_USR ... \n");
    if (strchr(opt_user, ' ')) {
        fprintf(stdout, "Username cannot contain spaces\n");
        exit(EMAIL_ERR_USR);
    }
    else if (strlen(opt_user) != strspn(opt_user, LETTERS_NUMBERS "-_.@")) {
        fprintf(stdout, "Username contains non valid chars\n");
        exit(EMAIL_ERR_USR);
    }
    else if (strlen(opt_user)) {
        verbose_printf(2, "Use EMAIL_USR from settings... \n");
        snprintf(user, STRING_SIZE, "-xu %s", opt_user);
    }
    else {
        verbose_printf(2, "No EMAIL_USR in settings... \n");
        strcpy(user, "");
    }


    strcpy(opt_password, "");
    verbose_printf(2, "Reading EMAIL_PW ... \n");
    if (find_kv_default(kv, "EMAIL_PW", opt_password) != SUCCESS) {
        fprintf(stdout, "Cannot read EMAIL_PW\n");
        exit(EMAIL_ERR_PW);
    }

    verbose_printf(2, "Validate EMAIL_PW ... \n");
    if (strchr(opt_password, ' ')) {
        fprintf(stdout, "Password cannot contain spaces\n");
        exit(EMAIL_ERR_PW);
    }
    else if (strchr(opt_password, '"') || strstr(opt_password, "'")) {
        fprintf(stdout, "Password cannot contain single or double quotes\n");
        exit(EMAIL_ERR_PW);
    }
    else if (strlen(opt_password)) {
        verbose_printf(2, "Use EMAIL_PW from settings... \n");
        snprintf(password, STRING_SIZE, "-xp %s", opt_password);
    }
    else {
        verbose_printf(2, "No EMAIL_PW in settings... \n");
        strcpy(password, "");
    }


    strcpy(from, "");
    verbose_printf(2, "Reading EMAIL_FROM ... \n");
    if (find_kv_default(kv, "EMAIL_FROM", from) != SUCCESS) {
        fprintf(stdout, "Cannot read EMAIL_FROM\n");
        exit(EMAIL_ERR_FROM);
    }

    verbose_printf(2, "Validate EMAIL_FROM ... \n");
    if (!(strlen(from))) {
        fprintf(stdout, "From email cannot be empty\n");
        exit(EMAIL_ERR_FROM);
    }
    else if (strchr(from, ' ')) {
        fprintf(stdout, "From email cannot contain spaces\n");
        exit(EMAIL_ERR_FROM);
    }
    else if (strlen(from) != strspn(from,  LETTERS_NUMBERS "-_.@=+#")) {
        fprintf(stdout, "From email contains non valid chars\n");
        exit(EMAIL_ERR_FROM);
    }


    strcpy(to, "");
    verbose_printf(2, "Reading EMAIL_TO ... \n");
    if (find_kv_default(kv, "EMAIL_TO", to) != SUCCESS) {
        fprintf(stdout, "Cannot read EMAIL_TO\n");
        exit(EMAIL_ERR_TO);
    }

    verbose_printf(2, "Validate EMAIL_TO ... \n");
    if (!(strlen(to))) {
        fprintf(stdout, "To email cannot be empty\n");
        exit(EMAIL_ERR_TO);
    }
    else if (strlen(to) != strspn(to,  LETTERS_NUMBERS "-_.@=+# ")) {
        fprintf(stdout, "To email contains non valid chars\n");
        exit(EMAIL_ERR_TO);
    }


    verbose_printf(1, "Reading main settings ... \n");
    if (read_kv_from_file(&main_kv, "/var/ipcop/main/settings") != SUCCESS) {
        fprintf(stdout, "Cannot read main settings\n");
        exit(EMAIL_ERR_ANY);
    }


    strcpy(hostname, "");
    verbose_printf(2, "Reading HOSTNAME ... \n");
    if (find_kv_default(main_kv, "HOSTNAME", hostname) != SUCCESS) {
        fprintf(stdout, "Cannot read HOSTNAME\n");
        exit(EMAIL_ERR_HOSTNAME);
    }


    strcpy(domainname, "");
    verbose_printf(2, "Reading DOMAINNAME ... \n");
    if (find_kv_default(main_kv, "DOMAINNAME", domainname) != SUCCESS) {
        fprintf(stdout, "Cannot read DOMAINNAME\n");
        exit(EMAIL_ERR_DOMAINNAME);
    }


    snprintf(subject_prefix, STRING_SIZE, "[IPCop] %s.%s:", hostname, domainname);


    if (flag_subject) {
        verbose_printf(1, "Have subject: %s \n", opt_subject);
        snprintf(subject, STRING_SIZE, "-u \"%s %s\"", subject_prefix, opt_subject);
    }
    else {
        verbose_printf(2, "No subject... \n");
        snprintf(subject, STRING_SIZE, "-u \"%s\"", subject_prefix);
    }

    if (flag_messagefile) {
        if (access(opt_messagefile, 0) == -1) {
            verbose_printf(2, "Messagefile is not available \n");
            exit(EMAIL_ERR_MESSAGE);
        }
        else {
            verbose_printf(1, "Use messagefile: %s \n", opt_messagefile);
            snprintf(message, STRING_SIZE, "-o message-file=%s", tmpEmailFile);

            verbose_printf(2, "Replace placeholders in messagefile\n");

           curtime = time (NULL);
           loctime = localtime (&curtime);
           strftime (date, STRING_SIZE, "%Y-%m-%d, %H:%M", loctime);

            snprintf(sed, STRING_SIZE_LARGE, "/bin/sed -e 's/__HOSTNAME__/%s.%s/;s/__CURRENT_DATE__/%s/;'  %s > %s", hostname, domainname, date, opt_messagefile, tmpEmailFile);

            verbose_printf(2, "sed: %s\n", sed);
            rc = safe_system(sed);
            if (rc) {
                fprintf(stdout, "Couldn't replace placeholders in messagefile: %d\n", rc);
                exit(EMAIL_ERR_SED);
            }
        }
    }
    else {
        verbose_printf(2, "No message... \n");
        strcpy(message, "-m \" \"");
    }

    if (flag_attachment) {
        if (access(opt_attachment, 0) == -1) {
            verbose_printf(2, "Attachment is not available \n");
            exit(EMAIL_ERR_ATTACH);
        }
        else {
            verbose_printf(1, "Use attachment: %s \n", opt_attachment);
            snprintf(attachment, STRING_SIZE, "-a %s", opt_attachment);
        }
    }
    else {
        verbose_printf(2, "No attachment... \n");
        strcpy(attachment, "");
    }


    snprintf(command, STRING_SIZE_LARGE,
            "/usr/bin/sendEmail -s %s%s %s %s -f %s -t %s %s %s %s -o message-charset=utf-8", server, port, user, password, from, to, subject, message, attachment);

    verbose_printf(2, "Command: %s\n", command);
    rc = safe_system(command);
    if (rc) {
        fprintf(stdout, "Couldn't send Email, sendEmail exitcode: %d\n", rc);
        exit(EMAIL_ERR_SENDEMAIL);
    }

    unlink(tmpEmailFile);

    if (flag_messagefile && flag_delete_messagefile) {
        verbose_printf(1, "Delete messagefile: %s \n", opt_messagefile);
        unlink(opt_messagefile);
    }

    return EMAIL_SUCCESS;
}