/* Get the set of key mappings for a single modifier combination.
   Mappings are appended to "head". Returns 0 on success and -1 on failure. */
static int getkeys(name_mapping_t *keys, int max, int mod) {
  sequence_t *current, *new_seq;
  int i;

  for (i = 0; i < max; i++) {
    /* Check if the key is blocked from the command line. */
    if (blocked_keys != NULL) {
      name_mapping_t key_mod[2] = {keys[i], modifiers[mod]};
      if (lfind(&key_mod, blocked_keys, &blocked_keys_fill, sizeof(char *),
                (int (*)(const void *, const void *))check_key) != NULL) {
        printf("Skipping blocked key %s%s\n", modifiers[mod].name, keys[i].name);
        continue;
      }
    }

    printf("%s%s ", modifiers[mod].name, keys[i].name);
    fflush(stdout);

#ifndef NO_AUTOLEARN
    /* When auto learning, just send the appropriate events to the terminal. */
    if (option_auto_learn) {
      send_event(keys[i].keysym, modifiers[mod].keysym);
    }
#endif

    /* Retrieve key sequence. */
    new_seq = get_sequence();
    if (new_seq == NULL) {
      printf("\n");
      continue;
    } else if (new_seq == (void *)-1) {
      return -1;
    }
    printf("%s ", new_seq->seq);
    current = head;
    /* Check for duplicate sequences, and set the duplicate field if one is found. */
    while (current != NULL) {
      if (strcmp(current->seq, new_seq->seq) == 0 && current->duplicate == NULL) {
        printf("(duplicate for %s%s)", current->modifiers->name, current->keynames->name);
        new_seq->duplicate = current;
        break;
      } else {
        current = current->next;
      }
    }

    new_seq->modifiers = modifiers + mod;
    new_seq->keynames = keys + i;
    new_seq->next = head;
    head = new_seq;
    printf("\n");
  }
  return 0;
}