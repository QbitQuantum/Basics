static zip_int64_t
read_file(void *state, void *data, zip_uint64_t len, zip_source_cmd_t cmd)
{
    struct read_file *ctx;
    char *buf;
    zip_uint64_t n;
    size_t i;

    ctx = (struct read_file *)state;
    buf = (char *)data;

    switch (cmd) {
        case ZIP_SOURCE_BEGIN_WRITE:
            if (ctx->fname == NULL) {
                zip_error_set(&ctx->error, ZIP_ER_OPNOTSUPP, 0);
                return -1;
            }
            return create_temp_output(ctx);
            
        case ZIP_SOURCE_COMMIT_WRITE: {
	    mode_t mask;

            if (fclose(ctx->fout) < 0) {
                ctx->fout = NULL;
                zip_error_set(&ctx->error, ZIP_ER_WRITE, errno);
            }
            ctx->fout = NULL;
            if (rename(ctx->tmpname, ctx->fname) < 0) {
                zip_error_set(&ctx->error, ZIP_ER_RENAME, errno);
                return -1;
            }
	    mask = umask(022);
	    umask(mask);
	    /* not much we can do if chmod fails except make the whole commit fail */
	    (void)chmod(ctx->fname, 0666&~mask);
	    free(ctx->tmpname);
	    ctx->tmpname = NULL;
            return 0;
	}
            
        case ZIP_SOURCE_CLOSE:
            if (ctx->fname) {
                fclose(ctx->f);
                ctx->f = NULL;
            }
            return 0;
            
        case ZIP_SOURCE_ERROR:
            return zip_error_to_data(&ctx->error, data, len);
            
        case ZIP_SOURCE_FREE:
            free(ctx->fname);
	    free(ctx->tmpname);
            if (ctx->f)
                fclose(ctx->f);
            free(ctx);
            return 0;
            
        case ZIP_SOURCE_OPEN:
            if (ctx->fname) {
                if ((ctx->f=fopen(ctx->fname, "rb")) == NULL) {
                    zip_error_set(&ctx->error, ZIP_ER_OPEN, errno);
                    return -1;
                }
            }
            
            if (ctx->start > 0) {
                if (_zip_fseek_u(ctx->f, ctx->start, SEEK_SET, &ctx->error) < 0) {
                    return -1;
                }
            }
            ctx->current = ctx->start;
            return 0;
            
        case ZIP_SOURCE_READ:
            if (ctx->end > 0) {
                n = ctx->end-ctx->current;
                if (n > len) {
                    n = len;
                }
            }
            else {
                n = len;
            }
            
            if (n > SIZE_MAX)
                n = SIZE_MAX;

            if ((i=fread(buf, 1, (size_t)n, ctx->f)) == 0) {
                if (ferror(ctx->f)) {
                    zip_error_set(&ctx->error, ZIP_ER_READ, errno);
                    return -1;
                }
            }
            ctx->current += i;

            return (zip_int64_t)i;
            
        case ZIP_SOURCE_REMOVE:
            if (remove(ctx->fname) < 0) {
                zip_error_set(&ctx->error, ZIP_ER_REMOVE, errno);
                return -1;
            }
            return 0;
            
        case ZIP_SOURCE_ROLLBACK_WRITE:
            if (ctx->fout) {
                fclose(ctx->fout);
                ctx->fout = NULL;
            }
            (void)remove(ctx->tmpname);
	    free(ctx->tmpname);
            ctx->tmpname = NULL;
            return 0;
	
        case ZIP_SOURCE_SEEK: {
            zip_int64_t new_current;
            int need_seek;
	    zip_source_args_seek_t *args = ZIP_SOURCE_GET_ARGS(zip_source_args_seek_t, data, len, &ctx->error);

	    if (args == NULL)
		return -1;
            
            need_seek = 1;
            
            switch (args->whence) {
                case SEEK_SET:
                    new_current = args->offset;
                    break;
                    
                case SEEK_END:
                    if (ctx->end == 0) {
                        if (_zip_fseek(ctx->f, args->offset, SEEK_END, &ctx->error) < 0) {
                            return -1;
                        }
                        if ((new_current = ftello(ctx->f)) < 0) {
                            zip_error_set(&ctx->error, ZIP_ER_SEEK, errno);
                            return -1;
                        }
                        need_seek = 0;
                    }
                    else {
                        new_current = (zip_int64_t)ctx->end + args->offset;
                    }
                    break;
                case SEEK_CUR:
                    new_current = (zip_int64_t)ctx->current + args->offset;
                    break;

                default:
                    zip_error_set(&ctx->error, ZIP_ER_INVAL, 0);
                    return -1;
            }

            if (new_current < 0 || (zip_uint64_t)new_current < ctx->start || (ctx->end != 0 && (zip_uint64_t)new_current > ctx->end)) {
                zip_error_set(&ctx->error, ZIP_ER_INVAL, 0);
                return -1;
            }
            
            ctx->current = (zip_uint64_t)new_current;

            if (need_seek) {
                if (_zip_fseek_u(ctx->f, ctx->current, SEEK_SET, &ctx->error) < 0) {
                    return -1;
                }
            }
            return 0;
        }
            
        case ZIP_SOURCE_SEEK_WRITE: {
            zip_source_args_seek_t *args;
            
            args = ZIP_SOURCE_GET_ARGS(zip_source_args_seek_t, data, len, &ctx->error);
            if (args == NULL) {
                return -1;
            }
            
            if (_zip_fseek(ctx->fout, args->offset, args->whence, &ctx->error) < 0) {
                return -1;
            }
            return 0;
        }

        case ZIP_SOURCE_STAT: {
	    if (len < sizeof(ctx->st))
		return -1;

	    if (ctx->st.valid != 0)
		memcpy(data, &ctx->st, sizeof(ctx->st));
	    else {
		zip_stat_t *st;
		struct stat fst;
		int err;
	    
		if (ctx->f)
		    err = fstat(fileno(ctx->f), &fst);
		else
		    err = stat(ctx->fname, &fst);

		if (err != 0) {
                    zip_error_set(&ctx->error, ZIP_ER_READ, errno);
		    return -1;
		}

		st = (zip_stat_t *)data;
		
		zip_stat_init(st);
		st->mtime = fst.st_mtime;
		st->valid |= ZIP_STAT_MTIME;
		if (ctx->end != 0) {
                    st->size = ctx->end - ctx->start;
		    st->valid |= ZIP_STAT_SIZE;
		}
		else if ((fst.st_mode&S_IFMT) == S_IFREG) {
		    st->size = (zip_uint64_t)fst.st_size;
		    st->valid |= ZIP_STAT_SIZE;
		}
	    }
	    return sizeof(ctx->st);
	}

        case ZIP_SOURCE_SUPPORTS:
	    return ctx->supports;
            
        case ZIP_SOURCE_TELL:
            return (zip_int64_t)ctx->current;
            
        case ZIP_SOURCE_TELL_WRITE:
        {
            off_t ret = ftello(ctx->fout);
            
            if (ret < 0) {
                zip_error_set(&ctx->error, ZIP_ER_TELL, errno);
                return -1;
            }
            return ret;
        }
            
        case ZIP_SOURCE_WRITE:
        {
            size_t ret;
            
	    clearerr(ctx->fout);
            ret = fwrite(data, 1, len, ctx->fout);
            if (ret != len || ferror(ctx->fout)) {
                zip_error_set(&ctx->error, ZIP_ER_WRITE, errno);
                return -1;
            }
            
            return (zip_int64_t)ret;
        }

        default:
            zip_error_set(&ctx->error, ZIP_ER_OPNOTSUPP, 0);
            return -1;
    }
}