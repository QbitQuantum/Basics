static void paintOp_rp(SkCanvas*, SkReader32* reader, uint32_t op32,
                       SkGPipeState* state) {
    size_t offset = reader->offset();
    size_t stop = offset + PaintOp_unpackData(op32);
    SkPaint* p = state->editPaint();

    do {
        uint32_t p32 = reader->readU32();
        unsigned op = PaintOp_unpackOp(p32);
        unsigned data = PaintOp_unpackData(p32);

//        SkDebugf(" read %08X op=%d flags=%d data=%d\n", p32, op, done, data);

        switch (op) {
            case kReset_PaintOp: p->reset(); break;
            case kFlags_PaintOp: p->setFlags(data); break;
            case kColor_PaintOp: p->setColor(reader->readU32()); break;
            case kFilterLevel_PaintOp: p->setFilterQuality((SkFilterQuality)data); break;
            case kStyle_PaintOp: p->setStyle((SkPaint::Style)data); break;
            case kJoin_PaintOp: p->setStrokeJoin((SkPaint::Join)data); break;
            case kCap_PaintOp: p->setStrokeCap((SkPaint::Cap)data); break;
            case kWidth_PaintOp: p->setStrokeWidth(reader->readScalar()); break;
            case kMiter_PaintOp: p->setStrokeMiter(reader->readScalar()); break;
            case kEncoding_PaintOp:
                p->setTextEncoding((SkPaint::TextEncoding)data);
                break;
            case kHinting_PaintOp: p->setHinting((SkPaint::Hinting)data); break;
            case kAlign_PaintOp: p->setTextAlign((SkPaint::Align)data); break;
            case kTextSize_PaintOp: p->setTextSize(reader->readScalar()); break;
            case kTextScaleX_PaintOp: p->setTextScaleX(reader->readScalar()); break;
            case kTextSkewX_PaintOp: p->setTextSkewX(reader->readScalar()); break;

            case kFlatIndex_PaintOp: {
                PaintFlats pf = (PaintFlats)PaintOp_unpackFlags(p32);
                unsigned index = data;
                set_paintflat(p, state->getFlat(index), pf);
                break;
            }

            case kTypeface_PaintOp:
                SkASSERT(SkToBool(state->getFlags() &
                                  SkGPipeWriter::kCrossProcess_Flag));
                p->setTypeface(state->getTypeface(data));
                break;
            default: SkDEBUGFAIL("bad paintop"); return;
        }
        SkASSERT(reader->offset() <= stop);
    } while (reader->offset() < stop);
}