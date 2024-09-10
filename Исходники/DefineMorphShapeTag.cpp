void
DefineMorphShapeTag::read(SWFStream& in, TagType tag, movie_definition& md,
        const RunResources& r)
{
    assert(tag == DEFINEMORPHSHAPE
        || tag == DEFINEMORPHSHAPE2
        || tag == DEFINEMORPHSHAPE2_);

    const SWFRect bounds1 = readRect(in);
    const SWFRect bounds2 = readRect(in);

    if (tag == DEFINEMORPHSHAPE2 || tag == DEFINEMORPHSHAPE2_) {
        // TODO: Use these values.
        const SWFRect innerBound1 = readRect(in);
        const SWFRect innerBound2 = readRect(in);

        UNUSED(innerBound1);
        UNUSED(innerBound2);

        // This should be used -- first 6 bits reserved, then
        // 'non-scaling' stroke, then 'scaling' stroke -- these can be
        // used to optimize morphing.
        in.ensureBytes(1);
        static_cast<void>(in.read_u8());
    }

    in.ensureBytes(4);
    // Offset. What is this for?
    static_cast<void>(in.read_u32());

    // Next line will throw ParserException on malformed SWF
    const boost::uint16_t fillCount = in.read_variable_count();
    
    for (size_t i = 0; i < fillCount; ++i) {
        OptionalFillPair fp = readFills(in, tag, md, true);
        _shape1.addFillStyle(fp.first);
        _shape2.addFillStyle(*fp.second);
    }

    const boost::uint16_t lineCount = in.read_variable_count();
    LineStyle ls1, ls2;
    for (size_t i = 0; i < lineCount; ++i) {
        ls1.read_morph(in, tag, md, r, &ls2);
        _shape1.addLineStyle(ls1);
        _shape2.addLineStyle(ls2);
    }

    _shape1.read(in, tag, md, r);
    in.align();
    _shape2.read(in, tag, md, r);

    // Set bounds as read in *this* tags rather then
    // the one computed from ShapeRecord parser
    // (does it make sense ?)
    _shape1.setBounds(bounds1);
    _shape2.setBounds(bounds2);
    
    // Starting bounds are the same as shape1
    _bounds = bounds1;

    assert(_shape1.fillStyles().size() == _shape2.fillStyles().size());
    assert(_shape1.lineStyles().size() == _shape2.lineStyles().size());

}