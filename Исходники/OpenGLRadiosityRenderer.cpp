void RadiosityRenderer::printTransformData(const MDagPath& dagPath)
{
    printf("got");
	
	
	//This method simply determines the transformation information on the DAG node and prints it out.
    MStatus status;
    MObject transformNode = dagPath.transform(&status);
    // This node has no transform - i.e., it’s the world node
    if (!status && status.statusCode () == MStatus::kInvalidParameter)
        return;
    MFnDagNode transform (transformNode, &status);
    if (!status) {
        status.perror("MFnDagNode constructor");
        return;
    }
    MTransformationMatrix matrix (transform.transformationMatrix());
	//cout << " translation: " << matrix.translation(MSpace::kWorld)
	//<< endl;
    double threeDoubles[3];
    MTransformationMatrix::RotationOrder rOrder;
    matrix.getRotation (threeDoubles, rOrder, MSpace::kWorld);
	
	cout << " rotation: ["
	<< threeDoubles[0] << ", "
	<< threeDoubles[1] << ", "
	<< threeDoubles[2] << "]\n";
    matrix.getScale (threeDoubles, MSpace::kWorld);
	
	cout << " scale: ["
	<< threeDoubles[0] << ", "
	<< threeDoubles[1] << ", "
	<< threeDoubles[2] << "]\n";
	
}