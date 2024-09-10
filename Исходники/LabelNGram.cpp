//-------------------------------------------------------------------------
int labelNGram(Config& config)
{
  if (config.existsParam("debug"))debug=true; else debug=false;  
  if (config.existsParam("verbose"))verbose=true; else verbose=false;
  String extOutputLabel=".sym.lbl";                                               // the extension of the output files    
  if (config.existsParam("saveLabelFileExtension")) extOutputLabel=config.getParam("saveLabelFileExtension");   
  String pathOutput="./";                                                // the path of the output files    
  if (config.existsParam("labelOutputPath")) pathOutput=config.getParam("labelOutputPath");    
  String extSymbol=".sym";                                               // the extension of the symbol files   
  if (config.existsParam("symbolFileExtension")) extSymbol=config.getParam("symbolFileExtension");   
  String pathSymbol="./";   
  if (config.existsParam("symbolPath")) pathSymbol=config.getParam("symbolPath");   
  String formatSymbol="ascii";   
  if (config.existsParam("symbolFormat")) pathSymbol=config.getParam("symbolFormat");  
 
  String NGramFilename=config.getParam("NGramFilename");                                        
  unsigned long NGramOrder=3;
  if (config.existsParam("NGramOrder")) NGramOrder=config.getParam("NGramOrder").toLong();  
  unsigned long NGramSelected=16;
  if (config.existsParam("NGramSelected")) NGramSelected=config.getParam("NGramSelected").toLong();  
  NGram NGramTable(NGramOrder,NGramSelected);
  NGramTable.load(NGramFilename,config);                       // Load the NGRAM table, selecting the NGramSelected first
 
  String inputFilename=config.getParam("inputFilename");
  String labelSelectedFrames=config.getParam("labelSelectedFrames");
  XLine inputFileList;
  try{
    if (inputFilename.endsWith(".lst")){ // input is file containing a list of filenames
      XList tmp(inputFilename,config);
      inputFileList=tmp.getAllElements();
    }
    else inputFileList.addElement(inputFilename); // a single filename
    String *p;
    while ((p=inputFileList.getElement())){
      String& filename=*p;
      if (verbose)
	cout <<"labelNGram file["<<filename<<"] Table["<<NGramFilename<<"] Order["<<NGramOrder<<"] Selected["<<NGramSelected<<"]"<<endl;
      SegServer segServer;                
      LabelServer labelServer;
      loadClusterFile(filename,segServer,labelServer,config);
      long codeSelectedFrame=labelServer.getLabelIndexByString(labelSelectedFrames);       // Get the index of the selected cluster
      if (codeSelectedFrame==-1){                                                             // No data for this model !!!!!!!!!!!!!!
      cout << " WARNING - NO DATA with the label["<<labelSelectedFrames<<"] in file ["<<filename<<"]"<<endl;
      exit(0);
      }
      SegCluster& cluster=segServer.getCluster(codeSelectedFrame);                                   // Gives the cluster of the selected/used segments
      ULongVector tabS;
      unsigned long nbSym=loadSymbol(pathSymbol+filename+extSymbol,formatSymbol,tabS,config);        // Read the stream of symbols
      SegServer segServerOutput;
      SegCluster& clusterOut=segServerOutput.createCluster(0,labelSelectedFrames,cluster.sourceName());  
      //  
      computeLabelNGram(NGramTable,cluster,clusterOut,tabS,nbSym);
      //
    
      if (verbose){
	cout <<"File["<<filename<<"]" <<endl;
	cout << "Output the new label file in ["<<pathOutput+filename+extOutputLabel <<"]"<<endl;
      }
      outputLabelFile(clusterOut,pathOutput+filename+extOutputLabel,config);
    } // end file loop
  } // fin try
  
  
  catch (Exception& e)
    { 
      cout << e.toString().c_str() << endl;
    }
  return 0;
}