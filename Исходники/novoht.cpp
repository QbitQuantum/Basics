void NoVoHT::merge(){
   char buf[300];
   char sec[300];
	sem_wait(&map_lock);
   sem_wait(&write_lock);
   fflush(dbfile);
   rewind(dbfile);
   while (readTabString(dbfile,buf) != NULL){
      if(buf[0] == '~'){
         readTabString(dbfile, sec);
         char * pos;
         pos = strtok(sec, ",");
         while (pos != NULL) {
            fseek(swapFile, (off_t) atoi(pos), SEEK_SET);
            char test[300];
            readTabString(swapFile,test);
            if (strcmp(test,(buf+1)) == 0){
               fseek(swapFile, (off_t) atoi(pos), SEEK_SET);
               fputc('~',swapFile);
            }
            pos = strtok(NULL, ",");
         }
      }
      else{
         //while (map_lock) {}
         //map_lock = true;
         //sem_wait(&map_lock);
         fseek(swapFile, 0, SEEK_END);
         string s(buf);
         readTabString(dbfile,sec);
         kvpair* p = kvpairs[hash(s)%size];
         while (p != NULL){
            if (p->key.compare(s) == 0){
               destroyFposList(p->positions);
               p->positions = new fpos_list;
               p->positions->next = NULL;
               fgetpos(swapFile, &(p->positions->pos));
               fprintf(swapFile, "%s\t%s\t", p->key.c_str(), p->val.c_str());
               printf("%s\t%s\t", p->key.c_str(), p->val.c_str());
               p->diff = false;
               break;
            }
            else
               p = p->next;
         }
         //map_lock = false;
         //sem_post(&map_lock);
      }
   }
	fclose(dbfile);
   fclose(swapFile);
   rename(".novoht.swp", filename.c_str());
   dbfile = fopen(filename.c_str(), "r+");
   //remove(".novoht.mrg");
	int rmrc = unlink(".novoht.mrg");
   if (rmrc) {
      perror("Error deleting merge file");
   }
   rewriting = false;
	sem_post(&map_lock);
   sem_post(&write_lock);
}