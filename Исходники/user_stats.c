static sg_error
sg_get_user_stats_int(sg_vector **user_stats_vector_ptr) {
	size_t num_users = 0;
	sg_user_stats *user_ptr;
	time_t now = time(NULL);

#if defined (WIN32)
	LPWKSTA_USER_INFO_0 buf = NULL;
	LPWKSTA_USER_INFO_0 tmp_buf;
	unsigned long entries_read = 0;
	unsigned long entries_tot = 0;
	unsigned long resumehandle = 0;
	NET_API_STATUS nStatus;
	int i;
	char name[256];

#undef VECTOR_UPDATE_ERROR_CLEANUP
#define VECTOR_UPDATE_ERROR_CLEANUP if (buf != NULL) NetApiBufferFree(buf);

	do {
		nStatus = NetWkstaUserEnum(NULL, 0, (LPBYTE*)&buf,
				MAX_PREFERRED_LENGTH, &entries_read,
				&entries_tot, &resumehandle);
		if((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)) {
			if((tmp_buf = buf) == NULL)
				continue;

			for( i = 0; i < entries_read; ++i ) {
				/* assert(tmp_buf != NULL); */
				if( tmp_buf == NULL ) {
					sg_set_error(SG_ERROR_PERMISSION, "User list");
					ERROR_LOG("user", "Permission denied fetching user details");
					break; /* XXX break and not return? */
				}
				/* It's in unicode. We are not. Convert */
				WideCharToMultiByte(CP_ACP, 0, tmp_buf->wkui0_username, -1, name, sizeof(name), NULL, NULL);

				VECTOR_UPDATE(user_stats_vector_ptr, num_users + 1, user_ptr, sg_user_stats);
				if( SG_ERROR_NONE != sg_update_string( &user_ptr[num_users].login_name, name ) ) {
					VECTOR_UPDATE_ERROR_CLEANUP
					RETURN_FROM_PREVIOUS_ERROR( "user", sg_get_error() );
				}

				user_ptr[num_users].systime = now;

				++tmp_buf;
				++num_users;
			}
		}
		else {
			RETURN_WITH_SET_ERROR("user", SG_ERROR_PERMISSION, "User enum");
		}

		if (buf != NULL) {
			NetApiBufferFree(buf);
			buf=NULL;
		}
	} while (nStatus == ERROR_MORE_DATA);

	if (buf != NULL)
		NetApiBufferFree(buf);
#elif defined(CAN_USE_UTMPX) || defined(CAN_USE_UTMP)

#define SG_LUPDATE_IF(tgt,obj,memb) \
	(((void *)(&(obj->memb))) == ((void *)(&(obj->memb[0])))) \
	? sg_lupdate_string(tgt, obj->memb, sizeof(obj->memb))\
	: sg_update_string(tgt, obj->memb)

#define UTMP_MUTEX_NAME "utmp"

#undef VECTOR_UPDATE_ERROR_CLEANUP
# if defined(CAN_USE_UTMPX)
	struct utmpx *utx;
# endif
# if defined(CAN_USE_UTMP)
	struct utmp *ut;
# endif

	/* following block contains code for utmpx */
# if defined(CAN_USE_UTMPX)
#  ifdef ENABLE_THREADS
#   define VECTOR_UPDATE_ERROR_CLEANUP endutxent(); sg_unlock_mutex(UTMP_MUTEX_NAME);
	sg_lock_mutex(UTMP_MUTEX_NAME);
#  else
#   define VECTOR_UPDATE_ERROR_CLEANUP endutxent();
#  endif
	setutxent();
	while( NULL != (utx = getutxent()) ) {
		if( USER_PROCESS != utx->ut_type )
			continue;

		VECTOR_UPDATE(user_stats_vector_ptr, num_users + 1, user_ptr, sg_user_stats);

		if( ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].login_name, utx, ut_user ) ) ||
#  if defined(HAVE_UTMPX_HOST)
#   if defined(HAVE_UTMPX_SYSLEN)
		    ( SG_ERROR_NONE != sg_lupdate_string( &user_ptr[num_users].hostname, utx->ut_host, utx->ut_syslen + 1 ) ) ||
#   else
		    ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].hostname, utx, ut_host ) ) ||
#   endif
#  endif
		    ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].device, utx, ut_line ) ) ||
		    ( SG_ERROR_NONE != sg_update_mem( (void *)(&user_ptr[num_users].record_id), utx->ut_id, sizeof(utx->ut_id) ) ) ) {
			    VECTOR_UPDATE_ERROR_CLEANUP
			    RETURN_FROM_PREVIOUS_ERROR( "user", sg_get_error() );
		}

		user_ptr[num_users].record_id_size = sizeof(utx->ut_id);
		user_ptr[num_users].pid = utx->ut_pid;
		user_ptr[num_users].login_time = utx->ut_tv.tv_sec;
		user_ptr[num_users].systime = now;

		++num_users;
	}

	endutxent();

	if(!num_users) {
# endif

	/* following block contains code for utmp */
# if defined(CAN_USE_UTMP)

#  undef VECTOR_UPDATE_ERROR_CLEANUP
#  ifdef ENABLE_THREADS
#   define VECTOR_UPDATE_ERROR_CLEANUP endutent(); sg_unlock_mutex(UTMP_MUTEX_NAME);
#  else
#   define VECTOR_UPDATE_ERROR_CLEANUP endutent();
#  endif
	setutent();
	while( NULL != (ut = getutent()) ) {
#  ifdef HAVE_UTMP_TYPE
		if( USER_PROCESS != ut->ut_type )
			continue;
#  elif defined(HAVE_UTMP_NAME)
	    if (ut->ut_name[0] == '\0')
		    continue;
#  elif defined(HAVE_UTMP_USER)
	    if (ut->ut_user[0] == '\0')
		    continue;
#  endif

	    VECTOR_UPDATE(user_stats_vector_ptr, num_users + 1, user_ptr, sg_user_stats);

	    if( ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].device, ut, ut_line ) )
#  if defined(HAVE_UTMP_USER)
	     || ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].login_name, ut, ut_user ) )
#  elif defined(HAVE_UTMP_NAME)
	     || ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].login_name, ut, ut_name ) )
#  endif
#  if defined(HAVE_UTMP_HOST)
	     || ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].hostname, ut, ut_host ) )
#  endif
#  if defined(HAVE_UTMP_ID)
	     || ( SG_ERROR_NONE != sg_update_mem( (void **)(&user_ptr[num_users].record_id), ut->ut_id, sizeof(ut->ut_id) ) )
#  endif
	    ) {
			VECTOR_UPDATE_ERROR_CLEANUP
			RETURN_FROM_PREVIOUS_ERROR( "user", sg_get_error() );
	    }

#  if defined(HAVE_UTMP_ID)
	    user_ptr[num_users].record_id_size = sizeof(ut->ut_id);
#  endif
#  if defined(HAVE_UTMP_PID)
	    user_ptr[num_users].pid = ut->ut_pid;
#  endif
#if defined(HAVE_UTMP_TIME)
	    user_ptr[num_users].login_time = ut->ut_time;
#endif
	    user_ptr[num_users].systime = now;

	    ++num_users;
    }

    endutent();
# endif

# if defined(CAN_USE_UTMPX)
    }
#endif

# ifdef ENABLE_THREADS
    sg_unlock_mutex(UTMP_MUTEX_NAME);
# endif
#elif defined(HAVE_STRUCT_UTMP) && defined(_PATH_UTMP)
    struct utmp entry;
    FILE *f;

    if ((f=fopen(_PATH_UTMP, "r")) == NULL) {
	    RETURN_WITH_SET_ERROR_WITH_ERRNO("user", SG_ERROR_OPEN, _PATH_UTMP);
    }

#ifdef SG_LUPDATE_IF
#undef SG_LUPDATE_IF
#endif

#define SG_LUPDATE_IF(tgt,obj,memb) \
	(((void *)(&(obj.memb))) == ((void *)(&(obj.memb[0])))) \
	? sg_lupdate_string(tgt, obj.memb, sizeof(obj.memb))\
	: sg_update_string(tgt, obj.memb)

#undef VECTOR_UPDATE_ERROR_CLEANUP
#define VECTOR_UPDATE_ERROR_CLEANUP fclose(f);

    while((fread(&entry, sizeof(entry),1,f)) != 0){
#ifdef HAVE_UTMP_TYPE
	    if( USER_PROCESS != ut->ut_type )
		    continue;
#elif defined(HAVE_UTMP_NAME)
	    if (entry.ut_name[0] == '\0')
		    continue;
#elif defined(HAVE_UTMP_USER)
	    if (entry.ut_user[0] == '\0')
		    continue;
#endif

	    VECTOR_UPDATE(user_stats_vector_ptr, num_users + 1, user_ptr, sg_user_stats);

	    if( ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].device, entry, ut_line ) )
#if defined(HAVE_UTMP_USER)
	     || ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].login_name, entry, ut_user ) )
#elif defined(HAVE_UTMP_NAME)
	     || ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].login_name, entry, ut_name ) )
#endif
#if defined(HAVE_UTMP_HOST)
	     || ( SG_ERROR_NONE != SG_LUPDATE_IF( &user_ptr[num_users].hostname, entry, ut_host ) )
#endif
#if defined(HAVE_UTMP_ID)
	     || ( SG_ERROR_NONE != sg_update_mem( &user_ptr[num_users].record_id, entry.ut_id, sizeof(entry.ut_id) ) )
#endif
	    ) {
			VECTOR_UPDATE_ERROR_CLEANUP
			RETURN_FROM_PREVIOUS_ERROR( "user", sg_get_error() );
	    }

#if defined(HAVE_UTMP_ID)
	    user_ptr[num_users].record_id_size = sizeof(entry.ut_id);
#endif
#if defined(HAVE_UTMP_PID)
	    user_ptr[num_users].pid = entry.ut_pid;
#endif
#if defined(HAVE_UTMP_TIME)
	    user_ptr[num_users].login_time = entry.ut_time;
#endif
		user_ptr[num_users].systime = now;

		++num_users;
	}

	fclose(f);
#else
	RETURN_WITH_SET_ERROR("user", SG_ERROR_UNSUPPORTED, OS_TYPE);
#endif

	return SG_ERROR_NONE;
}