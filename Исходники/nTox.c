int main(int argc, char *argv[])
{
    if (argc < 4) {
        printf("[!] Usage: %s [IP] [port] [public_key] <nokey>\n", argv[0]);
        exit(0);
    }
    int c;
    int on = 0;
    initMessenger();
    //if keyfiles exist
    if(argc > 4){
        if(strncmp(argv[4], "nokey", 6) < 0){
        //load_key();
        }
    } else {
        load_key();
    }
    m_callback_friendrequest(print_request);
    m_callback_friendmessage(print_message);
    m_callback_namechange(print_nickchange);
    m_callback_userstatus(print_statuschange);
    char idstring0[200];
    char idstring1[32][5];
    char idstring2[32][5];
    uint32_t i;
    for(i = 0; i < 32; i++)
    {
        if(self_public_key[i] < 16)
            strcpy(idstring1[i],"0");
        else 
            strcpy(idstring1[i], "");
        sprintf(idstring2[i], "%hhX",self_public_key[i]);
    }
    strcpy(idstring0,"[i] your ID: ");
    for (i=0; i<32; i++) {
        strcat(idstring0,idstring1[i]);
        strcat(idstring0,idstring2[i]);
    }
    initscr();
    noecho();
    raw();
    getmaxyx(stdscr,y,x);
    new_lines(idstring0);
    new_lines("[i] commands: /f ID (to add friend), /m friendnumber message  (to send message), /s status (to change status), /n nick (to change nickname), /q (to quit)");
    strcpy(line, "");
    IP_Port bootstrap_ip_port;
    bootstrap_ip_port.port = htons(atoi(argv[2]));
    int resolved_address = resolve_addr(argv[1]);
    if (resolved_address != -1)
        bootstrap_ip_port.ip.i = resolved_address;
    else 
        exit(1);
    
    DHT_bootstrap(bootstrap_ip_port, hex_string_to_bin(argv[3]));
    nodelay(stdscr, TRUE);
    while(true) {
        if (on == 0 && DHT_isconnected()) {
            new_lines("[i] connected to DHT\n[i] define username with /n");
            on = 1;
        }

        doMessenger();
        c_sleep(1);
        do_refresh();

        c = getch();

        if (c == ERR || c == 27)
            continue;

        getmaxyx(stdscr, y, x);
        if (c == '\n') {
            line_eval(lines, line);
            strcpy(line, "");
        } else if (c == 127) {
            line[strlen(line) - 1] = '\0';
        } else if (isalnum(c) || ispunct(c) || c == ' ') {
            strcpy(line, appender(line, (char) c));
        }
    }
    endwin();
    return 0;
}