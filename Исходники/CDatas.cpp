//----------------------------------------------------------------------------
// Export Entreprise to XML file
//----------------------------------------------------------------------------
void Datas::exportEntreprise( QString filename, const CEntreprise &p )
{
    qDebug( "CDatas::exportPersonne" );

    // Fake to keep information about global which is used by gerant and employe save function
    CParser *parserEntses = g_ParserEntses;

    CParser *Parser = new CParser( filename );
    g_ParserEntses = Parser;
    Parser->initWrite( "Exportation" );
    p.saveToXML( Parser->getDocument() );
    Parser->writeFile();
    delete Parser;

    g_ParserEntses = parserEntses;
}