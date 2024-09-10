void	swab_dbrec (struct or_dbrec *rec,  SWABDIR direction)
{
#ifndef BYTE_SWAP
    return;
#else
    if (direction == NTOH) {
	NTOHL (rec->or_dbflags);
	NTOHL (rec->or_dbuflags);
	NTOHL (rec->or_reccount);
	NTOHL (rec->or_maxdba);
	NTOHL (rec->or_availd99);
	NTOHL (rec->or_unavaild99);
	NTOHL (rec->or_hufid);
	NTOHL (rec->or_dbsecmask);

	NTOHS (rec->or_dbotype);
	NTOHS (rec->or_compflags);
	NTOHS (rec->or_dbaccess);
	NTOHS (rec->or_minwordsz);
	NTOHS (rec->or_maxwordsz);
	NTOHS (rec->or_recslots);
	NTOHS (rec->or_fzkeysz);
	NTOHS (rec->or_abstrsz);
	NTOHS (rec->or_language);
    }

    else {	/* going the other direction */
	HTONL (rec->or_dbflags);
	HTONL (rec->or_dbuflags);
	HTONL (rec->or_reccount);
	HTONL (rec->or_maxdba);
	HTONL (rec->or_availd99);
	HTONL (rec->or_unavaild99);
	HTONL (rec->or_hufid);
	HTONL (rec->or_dbsecmask);

	HTONS (rec->or_dbotype);
	HTONS (rec->or_compflags);
	HTONS (rec->or_dbaccess);
	HTONS (rec->or_minwordsz);
	HTONS (rec->or_maxwordsz);
	HTONS (rec->or_recslots);
	HTONS (rec->or_fzkeysz);
	HTONS (rec->or_abstrsz);
	HTONS (rec->or_language);
    }
    return;
#endif /* BYTE_SWAP */
}  /* swab_dbrec() */