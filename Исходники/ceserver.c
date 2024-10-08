int DispatchCommand(int currentsocket, unsigned char command)
{
  int r;

  switch (command)
  {
    case CMD_GETVERSION:
    {
      PCeVersion v;
      int versionsize=strlen(versionstring);
      v=(PCeVersion)malloc(sizeof(CeVersion)+versionsize);
      v->stringsize=versionsize;
      v->version=1;

      memcpy((char *)v+sizeof(CeVersion), versionstring, versionsize);

      //version request
      sendall(currentsocket, v, sizeof(CeVersion)+versionsize, 0);

      free(v);

      break;
    }

    case CMD_GETARCHITECTURE:
    {
#ifdef __i386__
      unsigned char arch=0;
#endif
#ifdef __x86_64__
      unsigned char arch=1;
#endif
#ifdef __arm__
      unsigned char arch=2;
#endif
#ifdef __aarch64__
      unsigned char arch=3;
#endif
      sendall(currentsocket, &arch, sizeof(arch), 0);
      break;
    }

    case CMD_CLOSECONNECTION:
    {
      printf("Connection %d closed properly\n", currentsocket);
      fflush(stdout);
      close(currentsocket);

      return NULL;
    }

    case CMD_TERMINATESERVER:
    {
      printf("Command to terminate the server received\n");
      fflush(stdout);
      close(currentsocket);
      exit(0);
    }

    case CMD_STARTDEBUG:
    {
      HANDLE h;
      if (recvall(currentsocket, &h, sizeof(h), MSG_WAITALL)>0)
      {
        int r;
        printf("Calling StartDebug(%d)\n", h);
        r=StartDebug(h);
        sendall(currentsocket, &r, sizeof(r), 0);

        if (r)
        {
          isDebuggerThread=1;
          debugfd=GetDebugPort(h);
        }
      }
      break;
    }

    case CMD_WAITFORDEBUGEVENT:
    {
      struct
      {
        HANDLE pHandle;
        int timeout;
      } wfd;

      if (recvall(currentsocket, &wfd, sizeof(wfd), MSG_WAITALL)>0)
      {
        int r;
        DebugEvent event;
        memset(&event, 0, sizeof(event));

        r=WaitForDebugEvent(wfd.pHandle, &event, wfd.timeout);
        sendall(currentsocket, &r, sizeof(r), r?MSG_MORE:0);

        if (r)
        {
          if (event.debugevent==SIGTRAP)
          {
            printf("!!!SIGTRAP!!!\n");
            printf("event.address=%llx\n", event.address);
          }

          sendall(currentsocket, &event, sizeof(event),0);
        }
      }
      break;
    }

    case CMD_CONTINUEFROMDEBUGEVENT:
    {
      struct
      {
        HANDLE pHandle;
        int tid;
        int ignore;
      } cfd;

      if (recvall(currentsocket, &cfd, sizeof(cfd), MSG_WAITALL)>0)
      {
        int r;
        // Calling ContinueFromDebugEvent
        r=ContinueFromDebugEvent(cfd.pHandle, cfd.tid, cfd.ignore);
        // Returned from ContinueFromDebugEvent
        sendall(currentsocket, &r, sizeof(r), 0);
      }
      break;
    }

    case CMD_SETBREAKPOINT:
    {
      CeSetBreapointInput sb;

      printf("CMD_SETBREAKPOINT. sizeof(sb)=%d\n", sizeof(sb));

      if (recvall(currentsocket, &sb, sizeof(sb), MSG_WAITALL)>0)
      {
        int r;

        printf("Calling SetBreakpoint\n");
        r=SetBreakpoint(sb.hProcess, sb.tid, sb.debugreg, (void *)sb.Address, sb.bptype, sb.bpsize);
        printf("SetBreakpoint returned %d\n",r);
        sendall(currentsocket, &r, sizeof(r), 0);
      }
      break;
    }

    case CMD_REMOVEBREAKPOINT:
    {
      CeRemoveBreapointInput rb;

      if (recvall(currentsocket, &rb, sizeof(rb), MSG_WAITALL)>0)
      {
        int r;

        printf("Calling RemoveBreakpoint\n");
        r=RemoveBreakpoint(rb.hProcess, rb.tid, rb.debugreg, rb.wasWatchpoint);
        printf("RemoveBreakpoint returned: %d\n", r);
        sendall(currentsocket, &r, sizeof(r), 0);
      }
      break;
    }

    case CMD_GETTHREADCONTEXT:
    {
#pragma pack(1)
      struct
      {
        HANDLE hProcess;
        int tid;
        int type;
      } gtc;
#pragma pack()

      CONTEXT Context;
      int result;

      printf("CMD_GETTHREADCONTEXT:\n");

      recvall(currentsocket, &gtc, sizeof(gtc), MSG_WAITALL);

      printf("Going to call GetThreadContext(%d, %d, %p, %d)\n", gtc.hProcess, gtc.tid, &Context, gtc.type);
      memset(&Context, 0, sizeof(Context));

      result=GetThreadContext(gtc.hProcess, gtc.tid, &Context, gtc.type);

      printf("result=%d\n", result);

      if (result)
      {
        uint32_t structsize=sizeof(Context);
        sendall(currentsocket, &result, sizeof(result), MSG_MORE);
        sendall(currentsocket, &structsize, sizeof(structsize), MSG_MORE);
        sendall(currentsocket, &Context, structsize, 0); //and context
      }
      else
        sendall(currentsocket, &result, sizeof(result), 0);

      break;

    }

    case CMD_SUSPENDTHREAD:
    {
      CeSuspendThreadInput st;

      if (recvall(currentsocket, &st, sizeof(st), MSG_WAITALL)>0)
      {
        int r;

        printf("Calling SuspendThread\n");
        r=SuspendThread(st.hProcess, st.tid);
        printf("SuspendThread returned\n");
        sendall(currentsocket, &r, sizeof(r), 0);
      }
      break;
    }

    case CMD_RESUMETHREAD:
    {
      CeResumeThreadInput rt;

      if (recvall(currentsocket, &rt, sizeof(rt), MSG_WAITALL)>0)
      {
        int r;

        printf("Calling ResumeThread\n");
        r=ResumeThread(rt.hProcess, rt.tid);
        printf("ResumeThread returned\n");
        sendall(currentsocket, &r, sizeof(r), 0);
      }
      break;
    }

    case CMD_CLOSEHANDLE:
    {
      HANDLE h;

      if (recvall(currentsocket, &h, sizeof(h), MSG_WAITALL)>0)
      {
        CloseHandle(h);
        int r=1;
        sendall(currentsocket, &r, sizeof(r), 0); //stupid naggle

      }
      else
      {
        printf("Error during read for CMD_CLOSEHANDLE\n");
        close(currentsocket);
        fflush(stdout);
        return 0;
      }
      break;
    }

    case CMD_CREATETOOLHELP32SNAPSHOT:
    {
      CeCreateToolhelp32Snapshot params;
      HANDLE result;

      printf("CMD_CREATETOOLHELP32SNAPSHOT\n");

      if (recvall(currentsocket, &params, sizeof(CeCreateToolhelp32Snapshot), MSG_WAITALL) > 0)
      {
        printf("Calling CreateToolhelp32Snapshot\n");
        result=CreateToolhelp32Snapshot(params.dwFlags, params.th32ProcessID);
        printf("result of CreateToolhelp32Snapshot=%d\n", result);

        fflush(stdout);

        sendall(currentsocket, &result, sizeof(HANDLE), 0);

      }
      else
      {
        printf("Error during read for CMD_CREATETOOLHELP32SNAPSHOT\n");
        fflush(stdout);
        close(currentsocket);
        return 0;
      }

      break;
    }

    case CMD_MODULE32FIRST: //slightly obsolete now
    case CMD_MODULE32NEXT:
    {
      HANDLE toolhelpsnapshot;
      if (recvall(currentsocket, &toolhelpsnapshot, sizeof(toolhelpsnapshot), MSG_WAITALL) >0)
      {
        BOOL result;
        ModuleListEntry me;
        CeModuleEntry *r;
        int size;

        if (command==CMD_MODULE32FIRST)
          result=Module32First(toolhelpsnapshot, &me);
        else
          result=Module32Next(toolhelpsnapshot, &me);

        if (result)
        {
          size=sizeof(CeModuleEntry)+ strlen(me.moduleName);
          r=(PCeModuleEntry)malloc(size);
          r->modulebase=me.baseAddress;
          r->modulesize=me.moduleSize;
          r->modulenamesize=strlen(me.moduleName);

          // Sending %s size %x\n, me.moduleName, r->modulesize
          memcpy((char *)r+sizeof(CeModuleEntry), me.moduleName, r->modulenamesize);
        }
        else
        {
          size=sizeof(CeModuleEntry);
          r=(PCeModuleEntry)malloc(size);
          r->modulebase=0;
          r->modulesize=0;
          r->modulenamesize=0;
        }

        r->result=result;

        sendall(currentsocket, r, size, 0);

        free(r);
      }
      break;
    }

    case CMD_PROCESS32FIRST: //obsolete
    case CMD_PROCESS32NEXT:
    {
      HANDLE toolhelpsnapshot;
      if (recvall(currentsocket, &toolhelpsnapshot, sizeof(toolhelpsnapshot), MSG_WAITALL) >0)
      {
        ProcessListEntry pe;
        BOOL result;
        CeProcessEntry *r;
        int size;

        if (command==CMD_PROCESS32FIRST)
          result=Process32First(toolhelpsnapshot, &pe);
        else
          result=Process32Next(toolhelpsnapshot, &pe);

        //  printf("result=%d\n", result);

        if (result)
        {
          size=sizeof(CeProcessEntry)+ strlen(pe.ProcessName);
          r=(PCeProcessEntry)malloc(size);
          r->processnamesize=strlen(pe.ProcessName);
          r->pid=pe.PID;
          memcpy((char *)r+sizeof(CeProcessEntry), pe.ProcessName, r->processnamesize);
        }
        else
        {
          size=sizeof(CeProcessEntry);
          r=(PCeProcessEntry)malloc(size);
          r->processnamesize=0;
          r->pid=0;
        }

        r->result=result;

        sendall(currentsocket, r, size, 0);

        free(r);

      }
      break;
    }

    case CMD_READPROCESSMEMORY:
    {
      CeReadProcessMemoryInput c;

      r=recvall(currentsocket, &c, sizeof(c), MSG_WAITALL);
      if (r>0)
      {
        PCeReadProcessMemoryOutput o=NULL;
        o=(PCeReadProcessMemoryOutput)malloc(sizeof(CeReadProcessMemoryOutput)+c.size);

        o->read=ReadProcessMemory(c.handle, (void *)(uintptr_t)c.address, &o[1], c.size);

        if (c.compress)
        {
          //compress the output
#define COMPRESS_BLOCKSIZE (64*1024)
          int i;
          unsigned char *uncompressed=&o[1];
          uint32_t uncompressedSize=o->read;
          uint32_t compressedSize=0;
          int maxBlocks=1+(c.size / COMPRESS_BLOCKSIZE);

          unsigned char **compressedBlocks=malloc(maxBlocks*sizeof(unsigned char *) ); //send in blocks of 64kb and reallocate the pointerblock if there's not enough space
          int currentBlock=0;

          z_stream strm;
          strm.zalloc = Z_NULL;
          strm.zfree = Z_NULL;
          strm.opaque = Z_NULL;
          deflateInit(&strm, c.compress);

          compressedBlocks[currentBlock]=malloc(COMPRESS_BLOCKSIZE);
          strm.avail_out=COMPRESS_BLOCKSIZE;
          strm.next_out=compressedBlocks[currentBlock];

          strm.next_in=uncompressed;
          strm.avail_in=uncompressedSize;

          while (strm.avail_in)
          {
            r=deflate(&strm, Z_NO_FLUSH);
            if (r!=Z_OK)
            {
              if (r==Z_STREAM_END)
                break;
              else
              {
                printf("Error while compressing\n");
                break;
              }
            }

            if (strm.avail_out==0)
            {
              //new output block
              currentBlock++;
              if (currentBlock>=maxBlocks)
              {
                //list was too short, reallocate
                printf("Need to realloc the pointerlist (p1)\n");

                maxBlocks*=2;
                compressedBlocks=realloc(compressedBlocks, maxBlocks*sizeof(unsigned char*));
              }
              compressedBlocks[currentBlock]=malloc(COMPRESS_BLOCKSIZE);
              strm.avail_out=COMPRESS_BLOCKSIZE;
              strm.next_out=compressedBlocks[currentBlock];
            }
          }
          // finishing compressiong
          while (1)
          {

            r=deflate(&strm, Z_FINISH);

            if (r==Z_STREAM_END)
              break; //done

            if (r!=Z_OK)
            {
              printf("Failure while finishing compression:%d\n", r);
              break;
            }

            if (strm.avail_out==0)
            {
              //new output block
              currentBlock++;
              if (currentBlock>=maxBlocks)
              {
                //list was too short, reallocate
                printf("Need to realloc the pointerlist (p2)\n");
                maxBlocks*=2;
                compressedBlocks=realloc(compressedBlocks, maxBlocks*sizeof(unsigned char*));
              }
              compressedBlocks[currentBlock]=malloc(COMPRESS_BLOCKSIZE);
              strm.avail_out=COMPRESS_BLOCKSIZE;
              strm.next_out=compressedBlocks[currentBlock];
            }
          }
          deflateEnd(&strm);

          compressedSize=strm.total_out;
          // Sending compressed data
          sendall(currentsocket, &uncompressedSize, sizeof(uncompressedSize), MSG_MORE); //followed by the compressed size
          sendall(currentsocket, &compressedSize, sizeof(compressedSize), MSG_MORE); //the compressed data follows
          for (i=0; i<=currentBlock; i++)
          {
            if (i!=currentBlock)
              sendall(currentsocket, compressedBlocks[i], COMPRESS_BLOCKSIZE, MSG_MORE);
            else
              sendall(currentsocket, compressedBlocks[i], COMPRESS_BLOCKSIZE-strm.avail_out, 0); //last one, flush

            free(compressedBlocks[i]);
          }
          free(compressedBlocks);
        }
        else
          sendall(currentsocket, o, sizeof(CeReadProcessMemoryOutput)+o->read, 0);

        if (o)
          free(o);
      }
      break;
    }

    case CMD_WRITEPROCESSMEMORY:
    {
      CeWriteProcessMemoryInput c;

      printf("CMD_WRITEPROCESSMEMORY:\n");

      r=recvall(currentsocket, &c, sizeof(c), MSG_WAITALL);
      if (r>0)
      {
        CeWriteProcessMemoryOutput o;
        unsigned char *buf;

        printf("recv returned %d bytes\n", r);
        printf("c.size=%d\n", c.size);

        if (c.size)
        {
          buf=(unsigned char *)malloc(c.size);

          r=recvall(currentsocket, buf, c.size, MSG_WAITALL);
          if (r>0)
          {
            printf("received %d bytes for the buffer. Wanted %d\n", r, c.size);
            o.written=WriteProcessMemory(c.handle, (void *)(uintptr_t)c.address, buf, c.size);

            r=sendall(currentsocket, &o, sizeof(CeWriteProcessMemoryOutput), 0);
            printf("wpm: returned %d bytes to caller\n", r);

          }
          else
            printf("wpm recv error while reading the data\n");

          free(buf);
        }
        else
        {
          printf("wpm with a size of 0 bytes");
          o.written=0;
          r=sendall(currentsocket, &o, sizeof(CeWriteProcessMemoryOutput), 0);
          printf("wpm: returned %d bytes to caller\n", r);
        }
      }
      else
      {
        printf("RPM: recv failed\n");
      }
      break;
    }

    case CMD_VIRTUALQUERYEXFULL:
    {
      CeVirtualQueryExFullInput c;
      CeVirtualQueryExFullOutput o;

      r=recvall(currentsocket, &c, sizeof(c), MSG_WAITALL);
      if (r>0)
      {
        RegionInfo *rinfo=NULL;
        uint32_t count=0;
        if (VirtualQueryExFull(c.handle, c.flags, &rinfo, &count))
        {
          int i;

          sendall(currentsocket, &count, sizeof(count),0);

          for (i=0; i<count; i++)
            sendall(currentsocket, &rinfo[i], sizeof(RegionInfo),0);

          if (rinfo)
            free(rinfo);
        }
      }
      break;
    }
    case CMD_GETREGIONINFO:
    case CMD_VIRTUALQUERYEX:
    {
      CeVirtualQueryExInput c;
      r=recvall(currentsocket, &c, sizeof(c), MSG_WAITALL);
      if (r>0)
      {
        RegionInfo rinfo;
        CeVirtualQueryExOutput o;

        if (sizeof(uintptr_t)==4)
        {
          if (c.baseaddress>0xFFFFFFFF)
          {
            o.result=0;
            sendall(currentsocket, &o, sizeof(o), 0);
            break;
          }
        }

        char mapsline[200];

        if (command==CMD_VIRTUALQUERYEX)
          o.result=VirtualQueryEx(c.handle, (void *)(uintptr_t)c.baseaddress, &rinfo, NULL);
        else
        if (command==CMD_GETREGIONINFO)
          o.result=VirtualQueryEx(c.handle, (void *)(uintptr_t)c.baseaddress, &rinfo, mapsline);

        o.protection=rinfo.protection;
        o.baseaddress=rinfo.baseaddress;
        o.type=rinfo.type;
        o.size=rinfo.size;

        if (command==CMD_VIRTUALQUERYEX)
          sendall(currentsocket, &o, sizeof(o), 0);
        else
        if (command==CMD_GETREGIONINFO)
        {
          sendall(currentsocket, &o, sizeof(o), MSG_MORE);
          {
            uint8_t size=strlen(mapsline);
            sendall(currentsocket, &size, sizeof(size), MSG_MORE);
            sendall(currentsocket, mapsline, size, 0);
          }
        }
      }
      break;
    }
    case CMD_OPENPROCESS:
    {
      int pid=0;

      r=recvall(currentsocket, &pid, sizeof(int), MSG_WAITALL);
      if (r>0)
      {
        int processhandle;

        printf("OpenProcess(%d)\n", pid);
        processhandle=OpenProcess(pid);

        printf("processhandle=%d\n", processhandle);
        sendall(currentsocket, &processhandle, sizeof(int), 0);
      }
      else
      {
        printf("Error\n");
        fflush(stdout);
        close(currentsocket);
        return NULL;
      }
      break;
    }

    case CMD_GETSYMBOLLISTFROMFILE:
    {
      //get the list and send it to the client
      //zip it first
      uint32_t symbolpathsize;

      printf("CMD_GETSYMBOLLISTFROMFILE\n");

      if (recvall(currentsocket, &symbolpathsize, sizeof(symbolpathsize), MSG_WAITALL)>0)
      {
        char *symbolpath=(char *)malloc(symbolpathsize+1);
        symbolpath[symbolpathsize]='\0';

        if (recvall(currentsocket, symbolpath, symbolpathsize, MSG_WAITALL)>0)
        {
          unsigned char *output=NULL;

          printf("symbolpath=%s\n", symbolpath);

          if (memcmp("/dev/", symbolpath, 5)!=0) //don't even bother if it's a /dev/ file
            GetSymbolListFromFile(symbolpath, &output);

          if (output)
          {
            printf("output is not NULL (%p)\n", output);

            fflush(stdout);

            printf("Sending %d bytes\n", *(uint32_t *)&output[4]);
            sendall(currentsocket, output, *(uint32_t *)&output[4], 0); //the output buffer contains the size itself
            free(output);
          }
          else
          {
            printf("Sending 8 bytes (fail)\n");
            uint64_t fail=0;
            sendall(currentsocket, &fail, sizeof(fail), 0); //just write 0
          }
        }
        else
        {
          printf("Failure getting symbol path\n");
          close(currentsocket);
        }
        free(symbolpath);
      }
      break;
    }

    case CMD_LOADEXTENSION:
    {
      //Load the extension if it isn't loaded yet
      //LOADEXTENSION(handle)
      uint32_t handle;
      if (recvall(currentsocket, &handle, sizeof(handle),0)>0)
      {
        int result=loadCEServerExtension(handle);

        sendall(currentsocket, &result, sizeof(result),0);
      }

      break;
    }

    case CMD_ALLOC:
    {
      //ALLOC(processhandle, preferedbase, size)
      CeAllocInput c;
      printf("CESERVER: CMD_ALLOC\n");
      if (recvall(currentsocket, &c, sizeof(c),0)>0)
      {
        printf("c.hProcess=%d\n", c.hProcess);
        printf("c.preferedBase=%llx\n", c.preferedBase);
        printf("c.size=%d\n", c.size);

        uint64_t address=ext_alloc(c.hProcess, c.preferedBase, c.size);

        sendall(currentsocket, &address, sizeof(address),0);
      }

      break;
    }

    case CMD_FREE:
    {
      CeFreeInput c;
      printf("CESERVER: CMD_FREE\n");
      if (recvall(currentsocket, &c, sizeof(c),0)>0)
      {
        uint32_t r;
        r=ext_free(c.hProcess, c.address, c.size);

        sendall(currentsocket, &r, sizeof(r),0);
      }

      break;
    }

    case CMD_CREATETHREAD:
    {
      CeCreateThreadInput c;
      printf("CESERVER: CMD_CREATETHREAD\n");
      if (recvall(currentsocket, &c, sizeof(c),0)>0)
      {
        uint64_t th;
        HANDLE h;
        th=ext_createThread(c.hProcess, c.startaddress, c.startaddress);

        printf("returned from ext_createthread\n");

        if (th) //create a handle for this object
        {
          uint64_t *threadobject=(uint64_t *)malloc(sizeof(uint64_t));

          *threadobject=th;
          h=CreateHandleFromPointer(threadobject, htNativeThreadHandle);
        }
        else
          h=0;

        sendall(currentsocket, &h, sizeof(h),0);
      }
      break;
    }

    case CMD_LOADMODULE:
    {
      CeLoadModuleInput c;

      printf("CESERVER: CMD_LOADMODULE\n");
      if (recvall(currentsocket, &c, sizeof(c),0)>0)
      {
        char modulepath[c.modulepathlength+1];

        if (recvall(currentsocket, &modulepath, sizeof(c.modulepathlength),0)>0)
        {
          uint32_t result;
          modulepath[c.modulepathlength]=0;

          result=ext_loadModule(c.hProcess, modulepath);

          sendall(currentsocket, &result, sizeof(result),0);
        }
      }
      break;
    }

    case CMD_SPEEDHACK_SETSPEED:
    {
      CeSpeedhackSetSpeedInput c;
      printf("CESERVER: CMD_SPEEDHACK_SETSPEED\n");
      if (recvall(currentsocket, &c, sizeof(c),0)>0)
      {
        uint32_t r;
        r=ext_speedhack_setSpeed(c.hProcess, c.speed);

        sendall(currentsocket, &r, sizeof(r),0);
      }

      break;
    }

  }
}