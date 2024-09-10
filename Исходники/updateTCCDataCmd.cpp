MStatus updateTCCData::getTCCNode( MSelectionList &selList )
{
    MStatus status; 
    MItSelectionList selListIter( selList );
    selListIter.setFilter( MFn::kMesh );
    
    for( ; !selListIter.isDone(); selListIter.next() )
    {
        MDagPath dagPath;
        MObject component;
        selListIter.getDagPath( dagPath, component );
        status = dagPath.extendToShape();
    
        if (status == MS::kSuccess)
        {
            MFnDependencyNode meshShapeFn(dagPath.node());
            
            MObject outMeshAttr = meshShapeFn.attribute( "outMesh" );
            MPlug outMeshPlug(dagPath.node(), outMeshAttr );
//            worldMeshPlug = worldMeshPlug.elementByLogicalIndex( 0 );
            cout<<"inMesh-connected dagnode name: "<<endl<<" > "<<outMeshPlug.info().asChar()<<endl;
            
            MPlugArray plugArray;
            outMeshPlug.connectedTo(plugArray, true, true);
            cout<<"connected attrs: "<<plugArray.length()<<endl;
            
            for (size_t k=0; k<plugArray.length(); k++)
            {
                MObject TCCnode(plugArray[k].node());
                MFnDependencyNode TCCDepNode( TCCnode );
                
                cout<<"Dependency node type: "<<TCCDepNode.typeName().asChar()<<endl;
                if (TCCDepNode.typeName() == "TCC")
                {
                    fSrcDagPath = dagPath;
                    fTCCnode = TCCnode;
                    fComponent = component;
                    return MS::kSuccess;
                }
            }
        }
    }    
    
    return MS::kFailure;
}