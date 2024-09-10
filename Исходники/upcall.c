static struct izo_upcall_hdr *upc_pack(__u32 opcode, int pathlen, char *path,
                                       char *fsetname, int reclen, char *rec,
                                       int *size)
{
        struct izo_upcall_hdr *hdr;
        char *ptr;
        ENTRY;

        *size = sizeof(struct izo_upcall_hdr);
        if ( fsetname ) {
                *size += round_strlen(fsetname);
        }
        if ( path ) { 
                *size += round_strlen(path);
        }
        if ( rec ) { 
                *size += size_round(reclen);
        }
        PRESTO_ALLOC(hdr, *size);
        if (!hdr) { 
                CERROR("intermezzo upcall: out of memory (opc %d)\n", opcode);
                EXIT;
                return NULL;
        }
        memset(hdr, 0, *size);

        ptr = (char *)hdr + sizeof(*hdr);

        /* XXX do we need fsuid ? */
        hdr->u_len = *size;
        hdr->u_version = IZO_UPC_VERSION;
        hdr->u_opc = opcode;
        hdr->u_pid = current->pid;
        hdr->u_uid = current->fsuid;

        if (path) { 
                /*XXX Robert: please review what len to pass in for 
                  NUL terminated strings */
                hdr->u_pathlen = strlen(path);
                LOGL0(path, hdr->u_pathlen, ptr);
        }
        if (fsetname) { 
                hdr->u_fsetlen = strlen(fsetname);
                LOGL0(fsetname, strlen(fsetname), ptr);
        }
        if (rec) { 
                hdr->u_reclen = reclen;
                LOGL(rec, reclen, ptr);
        }
        
        EXIT;
        return hdr;
}