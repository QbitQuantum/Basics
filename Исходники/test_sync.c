void test_peer_does_not_have (void *context, void *peer_context, void *key_context, const sync_key_t *key){
  struct test_peer *state = (struct test_peer *)context;
  struct test_peer *peer = (struct test_peer *)peer_context;
  struct test_key *test_key = (struct test_key *)key_context;
  
  LOGF("%s - %s does not have %s that we need to send", 
    state->name, peer->name, alloca_sync_key(key));
  
  assert(sync_key_exists(state->state, key)==1);
  assert(sync_key_exists(peer->state, key)==0);
  assert(test_key->initial_peer);
  
  struct test_transfer *transfer = allocate(sizeof(struct test_transfer));
  transfer->src = state;
  transfer->dest = peer;
  transfer->key = test_key;
  transfer->delay_till = packets_sent + 10;
  if (transfer_tail){
    transfer_tail->next = transfer;
  }else{
    transfer_head = transfer;
  }
  transfer_tail = transfer;
}