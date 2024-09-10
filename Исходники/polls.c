/* 
 * Read and process poll commands
 * Return:  -1 for quit command
 *          0 otherwise
 */
int process_args(int cmd_argc, char **cmd_argv, Poll **poll_list_ptr) {

    // some commands need the poll_list head and others
    // require the address of that head
    Poll *poll_list = *poll_list_ptr; 

    if (cmd_argc <= 0) {
        return 0;
    } else if (strcmp(cmd_argv[0], "quit") == 0 && cmd_argc == 1) {
        return -1;
        
    } else if (strcmp(cmd_argv[0], "add_poll") == 0 && cmd_argc == 3) {
        if (insert_new_poll(cmd_argv[1], strtol(cmd_argv[2], NULL, 10), 
            poll_list_ptr) == 1) {
            error("Poll by this name already exists");
        }
        
    } else if (strcmp(cmd_argv[0], "list_polls") == 0 && cmd_argc == 1) {
        print_polls(poll_list);
        
    } else if (strcmp(cmd_argv[0], "configure_poll") == 0 && cmd_argc >= 3) {
        int label_count = cmd_argc - 2; 
        int result = configure_poll(cmd_argv[1], &cmd_argv[2], label_count, 
                     poll_list);
        if (result == 1) {
           error("Poll by this name does not exist");
        } else if (result == 2) {
           error("Wrong number of slot labels provided for this poll\n");
        }

    } else if (strcmp(cmd_argv[0], "add_participant") == 0 && cmd_argc == 4) {
        int return_code = add_participant(cmd_argv[1], cmd_argv[2], poll_list, 
                                          cmd_argv[3]);
        if (return_code == 1) {
           error("Poll by this name does not exist");
        } else if (return_code == 2) {
           error("This Poll already has a participant by this name");
        } else if (return_code == 3) {
           error("Availability string is wrong size for this poll");
        }
      
    } else if (strcmp(cmd_argv[0], "add_comment") == 0 && cmd_argc >= 4) {
        // first determine how long a string we need
        int space_needed = 0;
        int i;
        for (i=3; i<cmd_argc; i++) {
            space_needed += strlen(cmd_argv[i]) + 1;
        }
        // allocate the space
        char *comment = malloc(space_needed);
        if (comment == NULL) {
            perror("malloc");
            exit(1);
        }
        // copy in the bits to make a single string
        strcpy(comment, cmd_argv[3]);
        for (i=4; i<cmd_argc; i++) {
            strcat(comment, " ");
            strcat(comment, cmd_argv[i]);
        }
        
        int return_code = add_comment(cmd_argv[1], cmd_argv[2], comment, 
                                      poll_list);
        // comment was only used as parameter so we are finished with it now
        free(comment);

        if (return_code == 1) {
           error("There is no poll with this name");
        } else if (return_code == 2) {
           error("There is no participant by this name in this poll");
        }

    } else if (strcmp(cmd_argv[0], "update_availability") == 0 && cmd_argc == 4) {
        int return_code = update_availability(cmd_argv[1], cmd_argv[2], 
                                           cmd_argv[3], poll_list);
        if (return_code == 1) {
           error("There is no poll with this name");
        } else if (return_code == 2) {
           error("There is no participant by this name in this poll");
        } else if (return_code == 3) {
           error("The length of the provided availability does not match" 
                  "number of slots in this poll");
        }

    } else if (strcmp(cmd_argv[0], "delete_poll") == 0 && cmd_argc == 2) {
        if (delete_poll(cmd_argv[1], poll_list_ptr) == 1) {
            error("No poll by this name exists");
        }

    } else if (strcmp(cmd_argv[0], "print_poll_info") == 0 && cmd_argc == 2) {
        if (print_poll_info(cmd_argv[1], poll_list) == 1) {
            error("No poll by this name exists");
        }

    } else {
        error("Incorrect syntax");
    }
    return 0;
}