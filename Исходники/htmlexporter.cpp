void HTMLExporter::exportBasket(Basket *basket, bool isSubBasket)
{
    if (!basket->isLoaded()) {
        basket->load();
    }

    // Compute the absolute & relative paths for this basket:
    filesFolderPath   = i18nc("HTML export folder (files)", "%1_files", filePath) + "/";
    if (isSubBasket) {
        basketFilePath    = basketsFolderPath + basket->folderName().left(basket->folderName().length() - 1) + ".html";
        filesFolderName   = "../";
        dataFolderName    = basket->folderName().left(basket->folderName().length() - 1) + "-" + i18nc("HTML export folder (data)", "data") + "/";
        dataFolderPath    = basketsFolderPath + dataFolderName;
        basketsFolderName = "";
    } else {
        basketFilePath    = filePath;
        filesFolderName   = i18nc("HTML export folder (files)", "%1_files", KUrl(filePath).fileName()) + "/";
        dataFolderName    = filesFolderName + i18nc("HTML export folder (data)",    "data")  + "/";
        dataFolderPath    = filesFolderPath + i18nc("HTML export folder (data)",    "data")  + "/";
        basketsFolderName = filesFolderName + i18nc("HTML export folder (baskets)", "baskets")  + "/";
    }
    iconsFolderName   = (isSubBasket ? "../" : filesFolderName) + i18nc("HTML export folder (icons)",   "icons")   + "/"; // eg.: "foo.html_files/icons/"   or "../icons/"
    imagesFolderName  = (isSubBasket ? "../" : filesFolderName) + i18nc("HTML export folder (images)",  "images")  + "/"; // eg.: "foo.html_files/images/"  or "../images/"

    kDebug() << "Exporting ================================================";
    kDebug() << "  filePath:" << filePath;
    kDebug() << "  basketFilePath:" << basketFilePath;
    kDebug() << "  filesFolderPath:" << filesFolderPath;
    kDebug() << "  filesFolderName:" << filesFolderName;
    kDebug() << "  iconsFolderPath:" << iconsFolderPath;
    kDebug() << "  iconsFolderName:" << iconsFolderName;
    kDebug() << "  imagesFolderPath:" << imagesFolderPath;
    kDebug() << "  imagesFolderName:" << imagesFolderName;
    kDebug() << "  dataFolderPath:" << dataFolderPath;
    kDebug() << "  dataFolderName:" << dataFolderName;
    kDebug() << "  basketsFolderPath:" << basketsFolderPath;
    kDebug() << "  basketsFolderName:" << basketsFolderName;

    // Create the data folder for this basket:
    QDir dir;
    dir.mkdir(dataFolderPath);

    backgroundColorName = basket->backgroundColor().name().toLower().mid(1);

    // Generate basket icons:
    QString basketIcon16 = iconsFolderName + copyIcon(basket->icon(), 16);
    QString basketIcon32 = iconsFolderName + copyIcon(basket->icon(), 32);

    // Generate the [+] image for groups:
    QPixmap expandGroup(Note::EXPANDER_WIDTH, Note::EXPANDER_HEIGHT);
    expandGroup.fill(basket->backgroundColor());
    QPainter painter(&expandGroup);
    Note::drawExpander(&painter, 0, 0, basket->backgroundColor(), /*expand=*/true, basket);
    painter.end();
    expandGroup.save(imagesFolderPath + "expand_group_" + backgroundColorName + ".png", "PNG");

    // Generate the [-] image for groups:
    QPixmap foldGroup(Note::EXPANDER_WIDTH, Note::EXPANDER_HEIGHT);
    foldGroup.fill(basket->backgroundColor());
    painter.begin(&foldGroup);
    Note::drawExpander(&painter, 0, 0, basket->backgroundColor(), /*expand=*/false, basket);
    painter.end();
    foldGroup.save(imagesFolderPath + "fold_group_" + backgroundColorName + ".png", "PNG");

    // Open the file to write:
    QFile file(basketFilePath);
    if (!file.open(QIODevice::WriteOnly))
        return;
    stream.setDevice(&file);
    stream.setCodec("UTF-8");

    // Compute the colors to draw dragient for notes:
    QColor topBgColor;
    QColor bottomBgColor;
    Note::getGradientColors(basket->backgroundColor(), &topBgColor, &bottomBgColor);
    // Compute the gradient image for notes:
    QString gradientImageFileName = Basket::saveGradientBackground(basket->backgroundColor(), basket->Q3ScrollView::font(), imagesFolderPath);

    // Output the header:
    QString borderColor = Tools::mixColor(basket->backgroundColor(), basket->textColor()).name();
    stream <<
           "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n"
           "<html>\n"
           " <head>\n"
           "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n"
           "  <meta name=\"Generator\" content=\"" << KGlobal::mainComponent().aboutData()->programName() << " " << VERSION << " http://basket.kde.org/\">\n"
           "  <style type=\"text/css\">\n"
//		"   @media print {\n"
//		"    span.printable { display: inline; }\n"
//		"   }\n"
           "   body { margin: 10px; font: 11px sans-serif; }\n" // TODO: Use user font
           "   h1 { text-align: center; }\n"
           "   img { border: none; vertical-align: middle; }\n";
    if (withBasketTree) {
        stream <<
               "   .tree { margin: 0; padding: 1px 0 1px 1px; width: 150px; _width: 149px; overflow: hidden; float: left; }\n"
               "   .tree ul { margin: 0 0 0 10px; padding: 0; }\n"
               "   .tree li { padding: 0; margin: 0; list-style: none; }\n"
               "   .tree a { display: block; padding: 1px; height: 16px; text-decoration: none;\n"
               "             white-space: nowrap; word-wrap: normal; text-wrap: suppress; color: black; }\n"
               "   .tree span { -moz-border-radius: 6px; display: block; float: left;\n"
               "                line-height: 16px; height: 16px; vertical-align: middle; padding: 0 1px; }\n"
               "   .tree img { vertical-align: top; padding-right: 1px; }\n"
               "   .tree .current { background-color: " << kapp->palette().color(QPalette::Highlight).name() << "; "
               "-moz-border-radius: 3px 0 0 3px; border-radius: 3px 0 0 3px; color: " << kapp->palette().color(QPalette::Highlight).name() << "; }\n"
               "   .basketSurrounder { margin-left: 152px; _margin: 0; _float: right; }\n";
    }
    stream <<
           "   .basket { background-color: " << basket->backgroundColor().name() << "; border: solid " << borderColor << " 1px; "
           "font: " << Tools::cssFontDefinition(basket->Q3ScrollView::font()) << "; color: " << basket->textColor().name() << "; padding: 1px; width: 100%; }\n"
           "   table.basket { border-collapse: collapse; }\n"
           "   .basket * { padding: 0; margin: 0; }\n"
           "   .basket table { width: 100%; border-spacing: 0; _border-collapse: collapse; }\n"
           "   .column { vertical-align: top; }\n"
           "   .columnHandle { width: " << Note::RESIZER_WIDTH << "px; background: transparent url('" << imagesFolderName << "column_handle_" << backgroundColorName << ".png') repeat-y; }\n"
           "   .group { margin: 0; padding: 0; border-collapse: collapse; width: 100% }\n"
           "   .groupHandle { margin: 0; width: " << Note::GROUP_WIDTH << "px; text-align: center; }\n"
           "   .note { padding: 1px 2px; background: " << bottomBgColor.name() << " url('" << imagesFolderName << gradientImageFileName << "')"
           " repeat-x; border-top: solid " << topBgColor.name() <<
           " 1px; border-bottom: solid " << Tools::mixColor(topBgColor, bottomBgColor).name() <<
           " 1px; width: 100%; }\n"
           "   .tags { width: 1px; white-space: nowrap; }\n"
           "   .tags img { padding-right: 2px; }\n"
           << LinkLook::soundLook->toCSS("sound", basket->textColor())
           << LinkLook::fileLook->toCSS("file", basket->textColor())
           << LinkLook::localLinkLook->toCSS("local", basket->textColor())
           << LinkLook::networkLinkLook->toCSS("network", basket->textColor())
           << LinkLook::launcherLook->toCSS("launcher", basket->textColor())
           <<
           "   .unknown { margin: 1px 2px; border: 1px solid " << borderColor << "; -moz-border-radius: 4px; }\n";
    QList<State*> states = basket->usedStates();
    QString statesCss;
    for (State::List::Iterator it = states.begin(); it != states.end(); ++it)
        statesCss += (*it)->toCSS(imagesFolderPath, imagesFolderName, basket->Q3ScrollView::font());
    stream <<
           statesCss <<
           "   .credits { text-align: right; margin: 3px 0 0 0; _margin-top: -17px; font-size: 80%; color: " << borderColor << "; }\n"
           "  </style>\n"
           "  <title>" << Tools::textToHTMLWithoutP(basket->basketName()) << "</title>\n"
           "  <link rel=\"shortcut icon\" type=\"image/png\" href=\"" << basketIcon16 << "\">\n";
    // Create the column handle image:
    QPixmap columnHandle(Note::RESIZER_WIDTH, 50);
    painter.begin(&columnHandle);
    Note::drawInactiveResizer(&painter, 0, 0, columnHandle.height(), basket->backgroundColor(), /*column=*/true);
    painter.end();
    columnHandle.save(imagesFolderPath + "column_handle_" + backgroundColorName + ".png", "PNG");

    stream <<
           " </head>\n"
           " <body>\n"
           "  <h1><img src=\"" << basketIcon32 << "\" width=\"32\" height=\"32\" alt=\"\"> " << Tools::textToHTMLWithoutP(basket->basketName()) << "</h1>\n";

    if (withBasketTree)
        writeBasketTree(basket);

    // If filtering, only export filtered notes, inform to the user:
    // TODO: Filtering tags too!!
    // TODO: Make sure only filtered notes are exported!
//	if (decoration()->filterData().isFiltering)
//		stream <<
//			"  <p>" << i18n("Notes matching the filter &quot;%1&quot;:").arg(Tools::textToHTMLWithoutP(decoration()->filterData().string)) << "</p>\n";

    stream <<
           "  <div class=\"basketSurrounder\">\n";

    if (basket->isColumnsLayout())
        stream <<
               "   <table class=\"basket\">\n"
               "    <tr>\n";
    else
        stream <<
               "   <div class=\"basket\" style=\"position: relative; height: " << basket->contentsHeight() << "px; width: " << basket->contentsWidth() << "px; min-width: 100%;\">\n";

    for (Note *note = basket->firstNote(); note; note = note->next())
        exportNote(note, /*indent=*/(basket->isFreeLayout() ? 4 : 5));

    // Output the footer:
    if (basket->isColumnsLayout())
        stream <<
               "    </tr>\n"
               "   </table>\n";
    else
        stream <<
               "   </div>\n";
    stream << QString(
               "  </div>\n"
               "  <p class=\"credits\">%1</p>\n").arg(
               i18n("Made with <a href=\"http://basket.kde.org/\">%1</a> %2, a KDE tool to take notes and keep information at hand.",
                    KGlobal::mainComponent().aboutData()->programName(), VERSION));

    // Copy a transparent GIF image in the folder, needed for the JavaScript hack:
    QString gifFileName = "spacer.gif";
    QFile transGIF(imagesFolderPath + gifFileName);
    if (!transGIF.exists() && transGIF.open(QIODevice::WriteOnly)) {
        QDataStream streamGIF(&transGIF);
        // This is a 1px*1px transparent GIF image:
        const char blankGIF[] = {
            0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x0a, 0x00, 0x0a, 0x00,
            0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x21,
            0xfe, 0x15, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x20,
            0x77, 0x69, 0x74, 0x68, 0x20, 0x54, 0x68, 0x65, 0x20, 0x47,
            0x49, 0x4d, 0x50, 0x00, 0x21, 0xf9, 0x04, 0x01, 0x0a, 0x00,
            0x01, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x0a,
            0x00, 0x00, 0x02, 0x08, 0x8c, 0x8f, 0xa9, 0xcb, 0xed, 0x0f,
            0x63, 0x2b, 0x00, 0x3b
        };
        streamGIF.writeRawData(blankGIF, 74);
        transGIF.close();
    }
    stream <<
           "  <!--[if lt IE 7]>\n"
           "   <script>\n"
           "    function fixPng(img) {\n"
           "     if (!img.style.filter) {\n"
           "      img.style.filter = \"progid:DXImageTransform.Microsoft.AlphaImageLoader(src='\" + img.src + \"')\";\n"
           "      img.src = \"" << imagesFolderName << gifFileName << "\";\n"
           "     }\n"
           "    }\n"
           "    for (i = document.images.length - 1; i >= 0; i -= 1) {\n"
           "     var img = document.images[i];\n"
           "     if (img.src.substr(img.src.length - 4) == \".png\")\n"
           "      if (img.complete)\n"
           "       fixPng(img);\n"
           "      else\n"
           "       img.attachEvent(\"onload\", function() { fixPng(window.event.srcElement); });\n"
           "    }\n"
           "   </script>\n"
           "  <![endif]-->\n"
           " </body>\n"
           "</html>\n";

    file.close();
    stream.setDevice(0);
    progress->setValue(progress->value()+1); // Basket exportation finished

    // Recursively export child baskets:
    BasketListViewItem *item = Global::bnpView->listViewItemForBasket(basket);
    if (item->childCount() >=0) {
        for (int i=0; i < item->childCount(); i++) {
            exportBasket(((BasketListViewItem *)item->child(i))->basket(), /*isSubBasket=*/true);
        }
    }
}