/*
 * The prime routine for the BAT layer is to create a new hash index.
 * Its argument is the element type and the maximum number of BUNs be
 * stored under the hash function.
 */
gdk_return
BAThash(BAT *b, BUN masksize)
{
	BAT *o = NULL;
	lng t0 = 0, t1 = 0;

	if (BATcheckhash(b)) {
		if (o != NULL) {
			o->T->hash = b->T->hash;
			BBPunfix(b->batCacheid);
		}
		return GDK_SUCCEED;
	}
	MT_lock_set(&GDKhashLock(abs(b->batCacheid)), "BAThash");
	if (b->T->hash == NULL) {
		unsigned int tpe = ATOMbasetype(b->ttype);
		BUN cnt = BATcount(b);
		BUN mask, maxmask = 0;
		BUN p = BUNfirst(b), q = BUNlast(b), r;
		Hash *h = NULL;
		Heap *hp;
		const char *nme = BBP_physical(b->batCacheid);
		const char *ext = b->batCacheid > 0 ? "thash" : "hhash";
		BATiter bi = bat_iterator(b);
#ifdef PERSISTENTHASH
		int fd;
#endif

		ALGODEBUG fprintf(stderr, "#BAThash: create hash(" BUNFMT ");\n", BATcount(b));
		if ((hp = GDKzalloc(sizeof(*hp))) == NULL ||
		    (hp->farmid = BBPselectfarm(b->batRole, b->ttype, hashheap)) < 0 ||
		    (hp->filename = GDKmalloc(strlen(nme) + 12)) == NULL) {
			MT_lock_unset(&GDKhashLock(abs(b->batCacheid)), "BAThash");
			GDKfree(hp);
			return GDK_FAIL;
		}
		sprintf(hp->filename, "%s.%s", nme, ext);

		/* cnt = 0, hopefully there is a proper capacity from
		 * which we can derive enough information */
		if (!cnt)
			cnt = BATcapacity(b);

		if (b->ttype == TYPE_void) {
			if (b->tseqbase == oid_nil) {
				MT_lock_unset(&GDKhashLock(abs(b->batCacheid)), "BAThash");
				ALGODEBUG fprintf(stderr, "#BAThash: cannot create hash-table on void-NIL column.\n");
				GDKfree(hp->filename);
				GDKfree(hp);
				return GDK_FAIL;
			}
			ALGODEBUG fprintf(stderr, "#BAThash: creating hash-table on void column..\n");

			tpe = TYPE_void;
		}
		/* determine hash mask size p = first; then no dynamic
		 * scheme */
		if (masksize > 0) {
			mask = HASHmask(masksize);
		} else if (ATOMsize(tpe) == 1) {
			mask = (1 << 8);
		} else if (ATOMsize(tpe) == 2) {
			mask = (1 << 16);
		} else if (b->tkey) {
			mask = HASHmask(cnt);
		} else {
			/* dynamic hash: we start with
			 * HASHmask(cnt)/64; if there are too many
			 * collisions we try HASHmask(cnt)/16, then
			 * HASHmask(cnt)/4, and finally
			 * HASHmask(cnt).  */
			maxmask = HASHmask(cnt);
			mask = maxmask >> 6;
			p += (cnt >> 2);	/* try out on first 25% of b */
			if (p > q)
				p = q;
		}

		t0 = GDKusec();

		do {
			BUN nslots = mask >> 3;	/* 1/8 full is too full */

			r = BUNfirst(b);
			if (h) {
				char *fnme;
				bte farmid;

				ALGODEBUG fprintf(stderr, "#BAThash: retry hash construction\n");
				fnme = GDKstrdup(hp->filename);
				farmid = hp->farmid;
				HEAPfree(hp, 1);
				memset(hp, 0, sizeof(*hp));
				hp->filename = fnme;
				hp->farmid = farmid;
				GDKfree(h);
				h = NULL;
			}
			/* create the hash structures */
			if ((h = HASHnew(hp, ATOMtype(b->ttype), BATcapacity(b), mask, BATcount(b))) == NULL) {

				MT_lock_unset(&GDKhashLock(abs(b->batCacheid)), "BAThash");
				GDKfree(hp->filename);
				GDKfree(hp);
				return GDK_FAIL;
			}

			switch (tpe) {
			case TYPE_bte:
				starthash(bte);
				break;
			case TYPE_sht:
				starthash(sht);
				break;
			case TYPE_int:
			case TYPE_flt:
#if SIZEOF_OID == SIZEOF_INT
			case TYPE_oid:
#endif
#if SIZEOF_WRD == SIZEOF_INT
			case TYPE_wrd:
#endif
				starthash(int);
				break;
			case TYPE_dbl:
			case TYPE_lng:
#if SIZEOF_OID == SIZEOF_LNG
			case TYPE_oid:
#endif
#if SIZEOF_WRD == SIZEOF_LNG
			case TYPE_wrd:
#endif
				starthash(lng);
				break;
#ifdef HAVE_HGE
			case TYPE_hge:
				starthash(hge);
				break;
#endif
			default:
				for (; r < p; r++) {
					ptr v = BUNtail(bi, r);
					BUN c = (BUN) heap_hash_any(b->T->vheap, h, v);

					if (HASHget(h, c) == HASHnil(h) &&
					    nslots-- == 0)
						break;	/* mask too full */
					HASHputlink(h, r, HASHget(h, c));
					HASHput(h, c, r);
				}
				break;
			}
		} while (r < p && mask < maxmask && (mask <<= 2));

		/* finish the hashtable with the current mask */
		p = r;
		switch (tpe) {
		case TYPE_bte:
			finishhash(bte);
			break;
		case TYPE_sht:
			finishhash(sht);
			break;
		case TYPE_int:
		case TYPE_flt:
#if SIZEOF_OID == SIZEOF_INT
		case TYPE_oid:
#endif
#if SIZEOF_WRD == SIZEOF_INT
		case TYPE_wrd:
#endif
			finishhash(int);
			break;
		case TYPE_dbl:
		case TYPE_lng:
#if SIZEOF_OID == SIZEOF_LNG
		case TYPE_oid:
#endif
#if SIZEOF_WRD == SIZEOF_LNG
		case TYPE_wrd:
#endif
			finishhash(lng);
			break;
#ifdef HAVE_HGE
		case TYPE_hge:
			finishhash(hge);
			break;
#endif
		default:
			for (; p < q; p++) {
				ptr v = BUNtail(bi, p);
				BUN c = (BUN) heap_hash_any(b->T->vheap, h, v);

				HASHputlink(h, p, HASHget(h, c));
				HASHput(h, c, p);
			}
			break;
		}
#ifdef PERSISTENTHASH
		if ((BBP_status(b->batCacheid) & BBPEXISTING) &&
		    b->batInserted == b->batCount &&
		    HEAPsave(hp, nme, ext) == GDK_SUCCEED &&
		    (fd = GDKfdlocate(hp->farmid, nme, "rb+", ext)) >= 0) {
			ALGODEBUG fprintf(stderr, "#BAThash: persisting hash %d\n", b->batCacheid);
			((size_t *) hp->base)[0] |= 1 << 24;
			if (write(fd, hp->base, SIZEOF_SIZE_T) < 0)
				perror("write hash");
			if (!(GDKdebug & FORCEMITOMASK)) {
#if defined(NATIVE_WIN32)
				_commit(fd);
#elif defined(HAVE_FDATASYNC)
				fdatasync(fd);
#elif defined(HAVE_FSYNC)
				fsync(fd);
#endif
			}
			close(fd);
		} else
			ALGODEBUG fprintf(stderr, "#BAThash: NOT persisting hash %d\n", b->batCacheid);
#endif
		b->T->hash = h;
		t1 = GDKusec();
		ALGODEBUG fprintf(stderr, "#BAThash: hash construction " LLFMT " usec\n", t1 - t0);
		ALGODEBUG HASHcollisions(b, b->T->hash);
	}