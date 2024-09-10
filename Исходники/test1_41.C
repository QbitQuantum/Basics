// static int mutatorTest(char *pathname, BPatch *bpatch)
test_results_t test1_41_Mutator::executeTest() {
   unsigned int n=0;
   const char *child_argv[5];
   child_argv[n++] = pathname;
   if (debugPrint) child_argv[n++] = const_cast<char*>("-verbose");
   child_argv[n++] = const_cast<char*>("-run");
   child_argv[n++] = const_cast<char*>("test1_41"); // run test41 in mutatee
   child_argv[n++] = NULL;

   int counts[iterations];

   // Run the mutatee twice, querying line info each time & store the info
   for (n = 0; n < iterations; n++) {
      dprintf("Starting \"%s\"\n", pathname);
      BPatch_process *proc = bpatch->processCreate(pathname, child_argv,
                                                    NULL);
      if (!proc) {
         logerror("*ERROR*: unable to create handle for executable\n", n);
         logerror("**Failed** test #41 (repeated line information)\n");
         return FAILED;
      }
      dprintf("Mutatee started, pid=%d\n", n, proc->getPid());

      BPatch_image *image = proc->getImage();
      if (!image) {
         logerror("*ERROR*: unable to get image from thread\n");
         logerror("**Failed** test #41 (repeated line information)\n");
         return FAILED;
      }
      if (isMutateeFortran(image)) {
         // This shouldn't happen..
         proc->terminateExecution();
         logerror("Skipped test #41 (repeated line information)\n");
         return SKIPPED;
      }

      BPatch_module *module = image->findModule("test1_41_mutatee.c", true);
      if (!module) {
         module = image->findModule("solo_mutatee_boilerplate.c", true);
         if (true) {
            logerror("*ERROR*: unable to get module from image\n");
            logerror("Looking for \"test1_41_solo_me.c\" or \"solo_mutatee_boilerplate.c\". Available modules:\n");
            BPatch_Vector<BPatch_module *> *mods = image->getModules();
            char buffer[512];
            for (unsigned i = 0; i < mods->size(); i++) {
               BPatch_module *mod = (*mods)[i];
               char name[512];
               mod->getName(name, 512);
               sprintf(buffer, "\t%s\n",
                       name);
               logerror(buffer);
            }
		 }
      }

      if (!module) {
		  fprintf(stderr, "%s[%d]:  could not find module solo_mutatee_boilerplate.c\n", FILE__, __LINE__);
         // First try again for 'test1_41_solo_me.c'
         module = image->findModule("test1_41_solo_me.c", true);
         if (!module) {
            logerror("*ERROR*: unable to get module from image\n");
            logerror("Looking for \"test1_41_solo_me.c\" or \"solo_mutatee_boilerplate.c\". Available modules:\n");
            BPatch_Vector<BPatch_module *> *mods = image->getModules();
            char buffer[512];
            for (unsigned i = 0; i < mods->size(); i++) {
               BPatch_module *mod = (*mods)[i];
               char name[512];
               mod->getName(name, 512);
               sprintf(buffer, "\t%s\n",
                       name);
               logerror(buffer);
            }

            logerror("**Failed** test #41 (repeated line information)\n");

            return FAILED;
         }
      }

      char buffer[16384]; // FIXME ugly magic number; No module name should be that long..
      module->getName(buffer, sizeof(buffer));

      BPatch_Vector<BPatch_statement> statements;
      bool res = module->getStatements(statements);
      if (!res) {
         fprintf(stderr, "%s[%d]:  getStatements()\n", __FILE__, __LINE__);
         return FAILED;
      }

      counts[n] = statements.size();
      dprintf("Trial %d: found %d statements\n", n, statements.size());

      proc->terminateExecution();
   }

   // Make sure we got the same info each time we ran the mutatee
   int last_count = -1;
   for (int i = 0; i < iterations; i++) {
      if ((last_count >= 0) && (last_count != counts[i])) {
         logerror("*ERROR*: statement counts didn't match: %d vs. %d\n", last_count, counts[i]);
         logerror("**Failed** test #41 (repeated line information)\n");
         return FAILED;
      }
      last_count = counts[i];
   }

   logerror("Passed test #41 (repeated line information)\n");
   return PASSED;
}