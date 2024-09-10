/*
 * Bareos is calling us to do the actual I/O
 */
static bRC pluginIO(bpContext *ctx, struct io_pkt *io)
{
   struct plugin_ctx *p_ctx = (struct plugin_ctx *)ctx->pContext;
   if (!p_ctx) {
      return bRC_Error;
   }

   io->status = 0;
   io->io_errno = 0;
   switch(io->func) {
   case IO_OPEN:
      Dmsg(ctx, dbglvl, "bpipe-fd: IO_OPEN\n");
      if (io->flags & (O_CREAT | O_WRONLY)) {
         char *writer_codes = apply_rp_codes(ctx);

         p_ctx->pfd = open_bpipe(writer_codes, 0, "w");
         Dmsg(ctx, dbglvl, "bpipe-fd: IO_OPEN fd=%p writer=%s\n", p_ctx->pfd, writer_codes);
         if (!p_ctx->pfd) {
            io->io_errno = errno;
            Jmsg(ctx, M_FATAL, "bpipe-fd: Open pipe writer=%s failed: ERR=%s\n", writer_codes, strerror(io->io_errno));
            Dmsg(ctx, dbglvl, "bpipe-fd: Open pipe writer=%s failed: ERR=%s\n", writer_codes, strerror(io->io_errno));
            if (writer_codes) {
               free(writer_codes);
            }
            return bRC_Error;
         }
         if (writer_codes) {
            free(writer_codes);
         }
      } else {
         p_ctx->pfd = open_bpipe(p_ctx->reader, 0, "r", false);
         Dmsg(ctx, dbglvl, "bpipe-fd: IO_OPEN fd=%p reader=%s\n", p_ctx->pfd, p_ctx->reader);
         if (!p_ctx->pfd) {
            io->io_errno = errno;
            Jmsg(ctx, M_FATAL, "bpipe-fd: Open pipe reader=%s failed: ERR=%s\n", p_ctx->reader, strerror(io->io_errno));
            Dmsg(ctx, dbglvl, "bpipe-fd: Open pipe reader=%s failed: ERR=%s\n", p_ctx->reader, strerror(io->io_errno));
            return bRC_Error;
         }
      }
      sleep(1);                 /* let pipe connect */
      break;
   case IO_READ:
      if (!p_ctx->pfd) {
         Jmsg(ctx, M_FATAL, "bpipe-fd: Logic error: NULL read FD\n");
         Dmsg(ctx, dbglvl, "bpipe-fd: Logic error: NULL read FD\n");
         return bRC_Error;
      }
      io->status = fread(io->buf, 1, io->count, p_ctx->pfd->rfd);
      if (io->status == 0 && ferror(p_ctx->pfd->rfd)) {
         io->io_errno = errno;
         Jmsg(ctx, M_FATAL, "bpipe-fd: Pipe read error: ERR=%s\n", strerror(io->io_errno));
         Dmsg(ctx, dbglvl, "bpipe-fd: Pipe read error: ERR=%s\n", strerror(io->io_errno));
         return bRC_Error;
      }
      break;
   case IO_WRITE:
      if (!p_ctx->pfd) {
         Jmsg(ctx, M_FATAL, "bpipe-fd: Logic error: NULL write FD\n");
         Dmsg(ctx, dbglvl, "bpipe-fd: Logic error: NULL write FD\n");
         return bRC_Error;
      }
      io->status = fwrite(io->buf, 1, io->count, p_ctx->pfd->wfd);
      if (io->status == 0 && ferror(p_ctx->pfd->wfd)) {
         io->io_errno = errno;
         Jmsg(ctx, M_FATAL, "bpipe-fd: Pipe write error: ERR=%s\n", strerror(io->io_errno));
         Dmsg(ctx, dbglvl, "bpipe-fd: Pipe write error: ERR=%s\n", strerror(io->io_errno));
         return bRC_Error;
      }
      break;
   case IO_CLOSE:
      if (!p_ctx->pfd) {
         Jmsg(ctx, M_FATAL, "bpipe-fd: Logic error: NULL FD on bpipe close\n");
         Dmsg(ctx, dbglvl, "bpipe-fd: Logic error: NULL FD on bpipe close\n");
         return bRC_Error;
      }
      io->status = close_bpipe(p_ctx->pfd);
      if (io->status) {
         Jmsg(ctx, M_FATAL, "bpipe-fd: Error closing stream for pseudo file %s: %d\n", p_ctx->fname, io->status);
         Dmsg(ctx, dbglvl, "bpipe-fd: Error closing stream for pseudo file %s: %d\n", p_ctx->fname, io->status);
      }
      break;
   case IO_SEEK:
      io->offset = p_ctx->offset;
      break;
   }

   return bRC_OK;
}