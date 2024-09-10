int
main(int argc, char **argv)
{
    int rc = 0;
    int flag;
    int argerr = 0;
    static int command = '?';
    const char *validation = NULL;
    char *shadow = NULL;
    char *shadow_file = NULL;
    gboolean full_upload = FALSE;
    gboolean dangerous_cmd = FALSE;
    struct stat buf;
    int option_index = 0;

    crm_log_cli_init("crm_shadow");
    crm_set_options(NULL, "(query|command) [modifiers]", long_options,
                    "Perform configuration changes in a sandbox before updating the live cluster."
                    "\n\nSets up an environment in which configuration tools (cibadmin, crm_resource, etc) work"
                    " offline instead of against a live cluster, allowing changes to be previewed and tested"
                    " for side-effects.\n");

    if (argc < 2) {
        crm_help('?', EX_USAGE);
    }

    while (1) {
        flag = crm_get_option(argc, argv, &option_index);
        if (flag == -1 || flag == 0)
            break;

        switch (flag) {
            case 'a':
                full_upload = TRUE;
                break;
            case 'd':
            case 'E':
            case 'p':
            case 'w':
            case 'F':
                command = flag;
                free(shadow);
                shadow = NULL;
                {
                    const char *env = getenv("CIB_shadow");
                    if(env) {
                        shadow = strdup(env);
                    } else {
                        fprintf(stderr, "No active shadow configuration defined\n");
                        crm_exit(ENOENT);
                    }
                }
                break;
            case 'v':
                validation = optarg;
                break;
            case 'e':
            case 'c':
            case 's':
            case 'r':
                command = flag;
                free(shadow);
                shadow = strdup(optarg);
                break;
            case 'C':
            case 'D':
                command = flag;
                dangerous_cmd = TRUE;
                free(shadow);
                shadow = strdup(optarg);
                break;
            case 'V':
                command_options = command_options | cib_verbose;
                crm_bump_log_level(argc, argv);
                break;
            case '$':
            case '?':
                crm_help(flag, EX_OK);
                break;
            case 'f':
                command_options |= cib_quorum_override;
                force_flag = 1;
                break;
            case 'b':
                batch_flag = 1;
                break;
            default:
                printf("Argument code 0%o (%c)" " is not (?yet?) supported\n", flag, flag);
                ++argerr;
                break;
        }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
        crm_help('?', EX_USAGE);
    }

    if (optind > argc) {
        ++argerr;
    }

    if (argerr) {
        crm_help('?', EX_USAGE);
    }

    if (command == 'w') {
        /* which shadow instance is active? */
        const char *local = getenv("CIB_shadow");

        if (local == NULL) {
            fprintf(stderr, "No shadow instance provided\n");
            rc = -ENXIO;
            goto done;
        }
        fprintf(stdout, "%s\n", local);
        rc = 0;
        goto done;
    }

    if (shadow == NULL) {
        fprintf(stderr, "No shadow instance provided\n");
        fflush(stderr);
        rc = -EINVAL;
        goto done;

    } else if (command != 's' && command != 'c') {
        const char *local = getenv("CIB_shadow");

        if (local != NULL && safe_str_neq(local, shadow) && force_flag == FALSE) {
            fprintf(stderr,
                    "The supplied shadow instance (%s) is not the same as the active one (%s).\n"
                    "  To prevent accidental destruction of the cluster,"
                    " the --force flag is required in order to proceed.\n", shadow, local);
            fflush(stderr);
            rc = EX_USAGE;
            goto done;
        }
    }

    if (dangerous_cmd && force_flag == FALSE) {
        fprintf(stderr, "The supplied command is considered dangerous."
                "  To prevent accidental destruction of the cluster,"
                " the --force flag is required in order to proceed.\n");
        fflush(stderr);
        rc = EX_USAGE;
        goto done;
    }

    shadow_file = get_shadow_file(shadow);
    if (command == 'D') {
        /* delete the file */
        rc = stat(shadow_file, &buf);
        if (rc == 0) {
            rc = unlink(shadow_file);
            if (rc != 0) {
                fprintf(stderr, "Could not remove shadow instance '%s': %s\n", shadow,
                        strerror(errno));
                goto done;
            }
        }

        shadow_teardown(shadow);
        goto done;

    } else if (command == 'F') {
        printf("%s\n", shadow_file);
        rc = 0;
        goto done;
    }

    if (command == 'd' || command == 'r' || command == 'c' || command == 'C') {
        real_cib = cib_new_no_shadow();
        rc = real_cib->cmds->signon(real_cib, crm_system_name, cib_command);
        if (rc != pcmk_ok) {
            fprintf(stderr, "Signon to CIB failed: %s\n", pcmk_strerror(rc));
            goto done;
        }
    }

    rc = stat(shadow_file, &buf);

    if (command == 'e' || command == 'c') {
        if (rc == 0 && force_flag == FALSE) {
            fprintf(stderr, "A shadow instance '%s' already exists.\n"
                    "  To prevent accidental destruction of the cluster,"
                    " the --force flag is required in order to proceed.\n", shadow);
            rc = -ENOTUNIQ;
            goto done;
        }

    } else if (rc != 0) {
        fprintf(stderr, "Could not access shadow instance '%s': %s\n", shadow, strerror(errno));
        rc = -ENXIO;
        goto done;
    }

    rc = pcmk_ok;
    if (command == 'c' || command == 'e' || command == 'r') {
        xmlNode *output = NULL;

        /* create a shadow instance based on the current cluster config */
        if (command == 'c' || command == 'r') {
            rc = real_cib->cmds->query(real_cib, NULL, &output, command_options);
            if (rc != pcmk_ok) {
                fprintf(stderr, "Could not connect to the CIB: %s\n", pcmk_strerror(rc));
                goto done;
            }

        } else {
            output = createEmptyCib(0);
            if(validation) {
                crm_xml_add(output, XML_ATTR_VALIDATION, validation);
            }
            printf("Created new %s configuration\n",
                   crm_element_value(output, XML_ATTR_VALIDATION));
        }

        rc = write_xml_file(output, shadow_file, FALSE);
        free_xml(output);

        if (rc < 0) {
            fprintf(stderr, "Could not %s the shadow instance '%s': %s\n",
                    command == 'r' ? "reset" : "create",
                    shadow, strerror(errno));
            goto done;
        }
        shadow_setup(shadow, FALSE);
        rc = pcmk_ok;

    } else if (command == 'E') {
        const char *err = NULL;
        char *editor = getenv("EDITOR");

        if (editor == NULL) {
            fprintf(stderr, "No value for $EDITOR defined\n");
            rc = -EINVAL;
            goto done;
        }

        execlp(editor, "--", shadow_file, NULL);
        err = strerror(errno);
        fprintf(stderr, "Could not invoke $EDITOR (%s %s): %s\n", editor, shadow_file, err);
        rc = -EINVAL;
        goto done;

    } else if (command == 's') {
        shadow_setup(shadow, TRUE);
        rc = 0;
        goto done;

    } else if (command == 'P') {
        /* display the current contents */
        char *output_s = NULL;
        xmlNode *output = filename2xml(shadow_file);

        output_s = dump_xml_formatted(output);
        printf("%s", output_s);

        free(output_s);
        free_xml(output);

    } else if (command == 'd') {
        /* diff against cluster */
        xmlNode *diff = NULL;
        xmlNode *old_config = NULL;
        xmlNode *new_config = filename2xml(shadow_file);

        rc = real_cib->cmds->query(real_cib, NULL, &old_config, command_options);

        if (rc != pcmk_ok) {
            fprintf(stderr, "Could not query the CIB: %s\n", pcmk_strerror(rc));
            goto done;
        }

        xml_track_changes(new_config, NULL, new_config, FALSE);
        xml_calculate_changes(old_config, new_config);

        diff = xml_create_patchset(0, old_config, new_config, NULL, FALSE);

        xml_log_changes(LOG_INFO, __FUNCTION__, new_config);
        xml_accept_changes(new_config);

        if (diff != NULL) {
            xml_log_patchset(0, "  ", diff);
            rc = 1;
            goto done;
        }
        rc = 0;
        goto done;

    } else if (command == 'C') {
        /* commit to the cluster */
        xmlNode *input = filename2xml(shadow_file);

        if (full_upload) {
            rc = real_cib->cmds->replace(real_cib, NULL, input, command_options);
        } else {
            xmlNode *config = first_named_child(input, XML_CIB_TAG_CONFIGURATION);

            rc = real_cib->cmds->replace(real_cib, XML_CIB_TAG_CONFIGURATION, config,
                                         command_options);
        }

        if (rc != pcmk_ok) {
            fprintf(stderr, "Could not commit shadow instance '%s' to the CIB: %s\n",
                    shadow, pcmk_strerror(rc));
            goto done;
        }
        shadow_teardown(shadow);
        free_xml(input);
    }
  done:
    free(shadow_file);
    free(shadow);
    return crm_exit(rc);
}