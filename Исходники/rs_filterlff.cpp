/**
 * Implementation of the method used for RS_Import to communicate
 * with this filter.
 *
 * @param g The graphic in which the entities from the file
 * will be created or the graphics from which the entities are
 * taken to be stored in a file.
 */
bool RS_FilterLFF::fileImport(RS_Graphic& g, const QString& file, RS2::FormatType /*type*/) {
    RS_DEBUG->print("LFF Filter: importing file '%s'...", file.toLatin1().data());

    //this->graphic = &g;
    bool success = false;

    // Load font file as we normally do, but the font doesn't own the
    //  letters (we'll add them to the graphic instead. Hence 'false').
    RS_Font font(file, false);
    success = font.loadFont();

    if (success==false) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "Cannot open LFF file '%s'.", file.toLatin1().data());
		return false;
    }

    g.addVariable("Names",
                         font.getNames().join(","), 0);
    g.addVariable("LetterSpacing", font.getLetterSpacing(), 0);
    g.addVariable("WordSpacing", font.getWordSpacing(), 0);
    g.addVariable("LineSpacingFactor", font.getLineSpacingFactor(), 0);
    g.addVariable("Authors", font.getAuthors().join(","), 0);
    g.addVariable("License", font.getFileLicense(), 0);
    g.addVariable("Created", font.getFileCreate(), 0);
    if (!font.getEncoding().isEmpty()) {
        g.addVariable("Encoding", font.getEncoding(), 0);
    }

    font.generateAllFonts();
    RS_BlockList* letterList = font.getLetterList();
    for (uint i=0; i<font.countLetters(); ++i) {
        RS_Block* ch = font.letterAt(i);

        QString uCode;
        uCode.setNum(ch->getName().at(0).unicode(), 16);
        while (uCode.length()<4) {
//            uCode.rightJustified(4, '0');
            uCode="0"+uCode;
        }
        //ch->setName("[" + uCode + "] " + ch->getName());
        //letterList->rename(ch, QString("[%1]").arg(ch->getName()));
        letterList->rename(ch,
                           QString("[%1] %2").arg(uCode).arg(ch->getName().at(0)));

        g.addBlock(ch, false);
        ch->reparent(&g);
    }

    g.addBlockNotification();
	return true;
}