int main(int argc, char **argv)
{
    welcome();
    verbose = false;

    //defineverbose();

    CreateDirectory ("outFiles", NULL);




    InputFile start;// object reads from an input file and creates a new file
    start.run();

    vector<ProteinSequence> p1;

    ClustalWInitializers(); // this wont work without void ClustalWInitializers() above
    clustalw::ClustalWResources *resources = clustalw::ClustalWResources::Instance();
    resources->setPathToExecutable(string(argv[0]));
    userParameters->toggleOutputFasta();
    //userParameters->getOutputFasta();
    setUserParameters(); // this wont work without void setUserParameters()


    if ( checker == true )
    {
        string offendingSeq;
        Clustal* clustalObj;
        clustalObj = new clustalw::Clustal();
        clustalObj->sequenceInput(false, &offendingSeq);
        string phylipName;
        clustalObj->align(&phylipName);
        delete clustalObj;

        alignment_file = "outFiles//Alignment.aln";
        p1 = start.getProteinData();
    }
    else
    {
        // get p1 from the alignment file
        p1 = start.getAlignmentData();
        // do nothing
    }


    AminoAcidComposition Table;
    if ( Table.openFile(alignment_file) == true ) // open the specified alignment file
    {
    }
    Table.generateAminoAcidTables(p1); // from the alignment file
    /* Calls the following:
        vector<ProteinSequence> p2 = assembleSeq(p);
        p3 = processSeq(p2);
        createPropertyTable(p3);
        createAminoAcidComposition(p3);
    */

    p1.clear();
    p1 = Table.getFinalSeqs();
    /* cout << "size of p1 : " << p1.size() << endl;
    for ( size_t i = 0; i < p1.size(); i++ )
    {
        string s = p1[i].getPDB();
        cout << s << endl;
        s = p1[i].getSeq();
        cout << s << endl;
    } */


    DistanceAndSimilarity dm;
    dm.createDistanceTableCodes(p1);
    dm.createSimilarityMatrixCodes(p1);
    dm.createDistanceTableColours(p1);
    dm.createSimilarityMatrixColours(p1);

    VerticalColumn vp;
    vp.generateVerticalColumnComposition(p1);

    cout<< "\nPROCESS COMPLETED! \nThe following files were created:\n" << endl;
    for ( size_t i = 0; i < filenames.size(); i++ )
    {
        cout << "\t" << i+1 << ". " << filenames[i] << endl;
    }


    delete userParameters;
    delete utilityObject;
    delete subMatrix;

    if(logObject)
    {
        delete logObject;
    }



    //system("pause");
    return 0;
}