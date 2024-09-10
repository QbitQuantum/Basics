/**
 * Call this method to generate d code for a UMLClassifier.
 * @param c   the class to generate code for
 */
void DWriter::writeClass(UMLClassifier *c)
{
    if (!c) {
        uDebug() << "Cannot write class of NULL concept!";
        return;
    }

    isInterface = c->isInterface();

    QString fileName = cleanName(c->name().toLower());

    //find an appropriate name for our file
    fileName = findFileName(c, QLatin1String(".d"));
    if (fileName.isEmpty()) {
        emit codeGenerated(c, false);
        return;
    }

    // check that we may open that file for writing
    QFile file;
    if (!openFile(file, fileName)) {
        emit codeGenerated(c, false);
        return;
    }

    // open text stream to file
    QTextStream d(&file);

    //try to find a heading file (license, coments, etc)
    QString str;
    str = getHeadingFile(QLatin1String(".d"));
    if (!str.isEmpty()) {
        str.replace(QRegExp(QLatin1String("%filename%")), fileName);
        str.replace(QRegExp(QLatin1String("%filepath%")), file.fileName());
        d<<str<<m_endl;
    }

    // source file begins with the module declaration
    writeModuleDecl(c, d);

    // imports
    writeModuleImports(c, d);

    // write the opening declaration for the class incl any documentation,
    // interfaces and/or inheritence issues we have
    writeClassDecl(c, d);

    // start body of class
    d << " {" << m_endl;

    // Preparations
    //

    // sort attributes by Scope
    UMLAttributeList  atl;
    UMLAttributeList  atpub, atprot, atpriv, atpkg, atexport;
    UMLAttributeList  final_atpub, final_atprot, final_atpriv, final_atpkg, final_atexport;

    if (!isInterface) {
        UMLAttributeList atl = c->getAttributeList();
        foreach (UMLAttribute* at, atl) {
            switch(at->visibility())
            {
                case Uml::Visibility::Public:
                    if (at->isStatic())
                        final_atpub.append(at);
                    else
                        atpub.append(at);
                    break;
                case Uml::Visibility::Protected:
                    if (at->isStatic())
                        final_atprot.append(at);
                    else
                        atprot.append(at);
                    break;
                case Uml::Visibility::Private:
                    if (at->isStatic())
                        final_atpriv.append(at);
                    else
                        atpriv.append(at);
                    break;/* TODO: requires support from the gui & other structures
                case Uml::Visibility::Package:
                    if (at->getStatic())
                    final_atpkg.append(at);
                    else
                    atpkg.append(at);
                    break;
                case Uml::Visibility::Export:
                    if (at->getStatic())
                    final_atexport.append(at);
                    else
                    atexport.append(at);
                    break;*/
                default:
                    break;
            }
        }
    }