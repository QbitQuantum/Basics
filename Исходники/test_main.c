int main() {

  UUID_HEAD * test_uuid;
  UUID_HEAD * test_uuid1;

  BYTE digest[DIGEST_SIZE];
  int ret;
//  static unsigned char alloc_buffer[4096*(1+1+4+1+16+1+256)];	

  void * hash_head;

//  alloc_init(alloc_buffer);

  test_uuid=Calloc(sizeof(UUID_HEAD));
  Memset(test_uuid->uuid,'A',DIGEST_SIZE);  

  hash_head=init_hash_list(8,0,0);
	
  ret=hashlist_add_elem(hash_head,test_uuid);	
  
  Memset(digest,'A',DIGEST_SIZE);
  test_uuid1=hashlist_find_elem(hash_head,digest);

  test_uuid=hashlist_get_first(hash_head);
  test_uuid1=hashlist_get_next(hash_head);

  test_uuid=hashlist_remove_elem(hash_head,digest);	
  test_uuid1=hashlist_find_elem(hash_head,digest);

//  void * list_queue;
//  list_queue=init_list_queue();
 
//  list_queue_put(list_queue,test_uuid);	  	
//  list_queue_put(list_queue,test_uuid1);
 
//  void * temp;
	
//  ret=list_queue_get(list_queue,&temp);
//  ret=list_queue_get(list_queue,&temp);
//  ret=list_queue_get(list_queue,&temp);

//  free_list_queue(list_queue);

    Free(test_uuid);
	

    return 0;
}