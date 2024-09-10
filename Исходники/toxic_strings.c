/* Deletes the line from beginning to pos and puts discarded portion in yank buffer.
   Return 0 on success, -1 if noting to discard. */
int discard_buf(ChatContext *ctx)
{
    if (ctx->pos <= 0)
        return -1;

    ctx->yank_len = ctx->pos;
    wmemcpy(ctx->yank, ctx->line, ctx->yank_len);
    ctx->yank[ctx->yank_len] = L'\0';

    wmemmove(ctx->line, &ctx->line[ctx->pos], ctx->len - ctx->pos);
    ctx->len -= ctx->pos;
    ctx->pos = 0;
    ctx->start = 0;
    ctx->line[ctx->len] = L'\0';

    return 0;
}