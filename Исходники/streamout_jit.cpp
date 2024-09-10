    //////////////////////////////////////////////////////////////////////////
    // @brief processes a single decl from the streamout stream. Reads 4 components from the input
    //        stream and writes N components to the output buffer given the componentMask or if
    //        a hole, just increments the buffer pointer
    // @param pStream - pointer to current attribute
    // @param pOutBuffers - pointers to the current location of each output buffer
    // @param decl - input decl
    void buildDecl(Value* pStream, Value* pOutBuffers[4], const STREAMOUT_DECL& decl)
    {
        // @todo add this to x86 macros
        Function* maskStore = Intrinsic::getDeclaration(JM()->mpCurrentModule, Intrinsic::x86_avx_maskstore_ps);

        uint32_t numComponents = _mm_popcnt_u32(decl.componentMask);
        uint32_t packedMask = (1 << numComponents) - 1;
        if (!decl.hole)
        {
            // increment stream pointer to correct slot
            Value* pAttrib = GEP(pStream, C(4 * decl.attribSlot));

            // load 4 components from stream
            Type* simd4Ty = VectorType::get(IRB()->getFloatTy(), 4);
            Type* simd4PtrTy = PointerType::get(simd4Ty, 0);
            pAttrib = BITCAST(pAttrib, simd4PtrTy);
            Value *vattrib = LOAD(pAttrib);

            // shuffle/pack enabled components
            Value* vpackedAttrib = VSHUFFLE(vattrib, vattrib, PackMask(decl.componentMask));

            // store to output buffer
            // cast SO buffer to i8*, needed by maskstore
            Value* pOut = BITCAST(pOutBuffers[decl.bufferIndex], PointerType::get(mInt8Ty, 0));

            // cast input to <4xfloat>
            Value* src = BITCAST(vpackedAttrib, simd4Ty);
            CALL(maskStore, {pOut, ToMask(packedMask), src});
        }

        // increment SO buffer
        pOutBuffers[decl.bufferIndex] = GEP(pOutBuffers[decl.bufferIndex], C(numComponents));
    }