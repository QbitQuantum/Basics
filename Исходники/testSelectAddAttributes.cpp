MStatus testSelectAddAttribute::doIt( const MArgList& args )

{
    MDagPath node;
    MObject component;
    MSelectionList list;
    MFnDagNode nodeFn;
    MGlobal::getActiveSelectionList( list );
    for ( unsigned int index = 0; index < list.length(); index++ )
    {
        list.getDagPath( index, node, component );
        nodeFn.setObject( node );
        cout<<nodeFn.name().asChar( ) << "is selected" << endl;
    }
    return MS::kSuccess;
}