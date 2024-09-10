void HelpDialog::setLocalizedTexts(const Translation* language)
{
    setWindowTitle(language->getTitle());
    if(windowTitle().isEmpty()) setWindowTitle(QStringLiteral("FTutor1D Help"));

    titleLabel->setText(language->getChildElementText("titleLabel"));
    if(titleLabel->text().isEmpty()) titleLabel->setText(QStringLiteral("FTutor1D Help"));

    openInPDFButton->setText(language->getChildElementText("openInPDFButton"));
    if(openInPDFButton->text().isEmpty()) openInPDFButton->setText(QStringLiteral("Open in PDF"));

    closeButton->setText(language->getChildElementText("closeButton"));
    if(closeButton->text().isEmpty()) closeButton->setText(QStringLiteral("Close"));


    closeButton->setText(language->getChildElementText("closeButton"));
    openInPDFButton->setText(language->getChildElementText("openInPDFButton"));

    Translation* tr = language->getTranslationForElement(QStringLiteral("text"));
    if(tr != nullptr)
    {
        QString firstParagraph = tr->getChildElementText(QStringLiteral("firstParagraph"));
        QString secondParagraph = tr->getChildElementText(QStringLiteral("secondParagraph"));
        QString thirdParagraph = tr->getChildElementText(QStringLiteral("thirdParagraph"));
        QString fourthParagraph = tr->getChildElementText(QStringLiteral("fourthParagraph"));
        QString fifthParagraph = tr->getChildElementText(QStringLiteral("fifthParagraph"));
        QString sixthParagraph = tr->getChildElementText(QStringLiteral("sixthParagraph"));
        QString seventhParagraph = tr->getChildElementText(QStringLiteral("seventhParagraph"));
        QString eightParagraph = tr->getChildElementText(QStringLiteral("eightParagraph"));
        QString ninthParagraph = tr->getChildElementText(QStringLiteral("ninthParagraph"));
        QString tenthParagraph = tr->getChildElementText(QStringLiteral("tenthParagraph"));

        text->setHtml(htmlTextHeader + "<p>" + firstParagraph +
                      "</p>\n<p></p>\n<p>" + secondParagraph +
                      "</p>\n<p></p>\n<p>" + thirdParagraph +
                      "</p>\n<p></p>\n<p>" + fourthParagraph +
                      "</p>\n<p></p>\n<p>" + fifthParagraph +
                      "</p>\n<p></p>\n<p>" + sixthParagraph +
                      "</p>\n<p></p>\n<p>" + seventhParagraph +
                      "</p>\n<p></p>\n<p>" + eightParagraph +
                      "</p>\n<p></p>\n<p>" + ninthParagraph +
                      "</p>\n<p></p>\n<p>" + tenthParagraph +
                      "</p>" + htmlTextFooter);

        delete tr;
    }
}