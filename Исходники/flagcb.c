void debugCB_fromU(const void *context,
                   UConverterFromUnicodeArgs *fromUArgs,
                   const UChar* codeUnits,
                   int32_t length,
                   UChar32 codePoint,
                   UConverterCallbackReason reason,
                   UErrorCode * err)
{
    debugCBContext *ctx = (debugCBContext*)context;
    /*UConverterFromUCallback junkFrom;*/
    
#if DEBUG_TMI
    printf("debugCB_fromU: Context %p:%d called, reason %d on cnv %p [err=%s]\n", ctx, ctx->serial, reason, fromUArgs->converter, u_errorName(*err));
#endif

    if(ctx->magic != 0xC0FFEE) {
        fprintf(stderr, "debugCB_fromU: Context %p:%d magic is 0x%x should be 0xC0FFEE.\n", ctx,ctx->serial, ctx->magic);
        return;
    }

    if(reason == UCNV_CLONE) {
        /* see comments in above flagCB clone code */

        UConverterFromUCallback   saveCallback;
        const void *saveContext;
        debugCBContext *cloned;
        UErrorCode subErr = U_ZERO_ERROR;

        /* "recreate" it */
#if DEBUG_TMI
        printf("debugCB_fromU: cloning..\n");
#endif
        cloned = debugCB_clone(ctx);

        if(cloned == NULL) {
            fprintf(stderr, "debugCB_fromU: internal clone failed on %p\n", ctx);
            *err = U_MEMORY_ALLOCATION_ERROR;
            return;
        }

        ucnv_setFromUCallBack(fromUArgs->converter,
                              cloned->subCallback,
                              cloned->subContext,
                              &saveCallback,
                              &saveContext,
                              &subErr);
        
        if( cloned->subCallback != NULL) {
#if DEBUG_TMI
            printf("debugCB_fromU:%p calling subCB %p\n", ctx, cloned->subCallback);
#endif
            /* call subCB if present */
            cloned->subCallback(cloned->subContext, fromUArgs, codeUnits,
                                length, codePoint, reason, err);
        } else {
            printf("debugCB_fromU:%p, NOT calling subCB, it's NULL\n", ctx);
        }

        /* set back callback */
        ucnv_setFromUCallBack(fromUArgs->converter,
                              saveCallback,  /* Us */
                              cloned,        /* new context */
                              &cloned->subCallback,  /* IMPORTANT! Accept any change in CB or context */
                              &cloned->subContext,
                              &subErr);
        
        if(U_FAILURE(subErr)) {
            *err = subErr;
        }
    }
    
    /* process other reasons here */

    /* always call subcb if present */
    if(ctx->subCallback != NULL && reason != UCNV_CLONE) {
        ctx->subCallback(ctx->subContext,
                         fromUArgs,
                         codeUnits,
                         length,
                         codePoint,
                         reason,
                         err);
    }

    if(reason == UCNV_CLOSE) {
#if DEBUG_TMI
        printf("debugCB_fromU: Context %p:%d closing\n", ctx, ctx->serial);
#endif
        free(ctx);
    }

#if DEBUG_TMI
    printf("debugCB_fromU: leaving cnv %p, ctx %p: err %s\n", fromUArgs->converter, ctx, u_errorName(*err));
#endif
}