void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    #define facesInput prhs[0]
    #define verticesInput prhs[1]

    #define edgesOutput plhs[0]
    #define edgeLengthsOutput plhs[1]
    #define edgeUnitsOutput plhs[2]
    #define edgeCentersOutput plhs[3]
    #define edgeNormalsOutput plhs[4]
    #define faceNormalsOutput plhs[5]
    #define faceAreasOutput plhs[6]
    #define volumeOutput plhs[7]

    mxArray *faceCell, *edgesCell, *edgeCentersCell, *edgeLengthsCell, 
            *edgeUnitsCell, *faceNormalCell, *edgeNormalsCell;
    double *face, *vertices, *edges, *edgeCenters, *edgeLengths,
           *edgeUnits, *faceNormal, *edgeNormals, *faceAreas, *volume;
    double tmp;
    mwIndex f, e, i;
    mwIndex currentVertexIdx, nextVertexIdx, edgeIdx;
    mwSize faceNumber, edgeNumber, vertexNumber;
    mwSize edgesOutputSize[EDGES_OUTPUT_DIM];

    if (nrhs != 2)
        mexErrMsgTxt("There should be exactly two inputs, faces and vertices.");
    if (nlhs != 8)
        mexErrMsgTxt("There should be exactly 8 outputs. "
            "edges, edgeLengths, edgeCenters, edgeUnits, edgeCenters, "
            "edgeNormals, faceNormals.");
    if (!mxIsCell(facesInput))
        mexErrMsgTxt("Input faces should be a cell array!");
    if (!mxIsDouble(verticesInput))
        mexErrMsgTxt("Input vertices should be a double matrix!");
                
    faceNumber = mxGetNumberOfElements(facesInput);
    vertices = mxGetPr(verticesInput);
    vertexNumber = mxGetN(verticesInput);

    edgesOutputSize[0] = faceNumber;
    edgesOutputSize[1] = 1;

    edgesOutput = mxCreateCellArray(EDGES_OUTPUT_DIM, edgesOutputSize);
    edgeLengthsOutput = mxCreateCellArray(EDGES_OUTPUT_DIM, edgesOutputSize);
    edgeUnitsOutput = mxCreateCellArray(EDGES_OUTPUT_DIM, edgesOutputSize);
    edgeCentersOutput = mxCreateCellArray(EDGES_OUTPUT_DIM, edgesOutputSize);
    edgeNormalsOutput = mxCreateCellArray(EDGES_OUTPUT_DIM, edgesOutputSize);
    faceNormalsOutput = mxCreateCellArray(EDGES_OUTPUT_DIM, edgesOutputSize);
    faceAreasOutput = mxCreateDoubleMatrix(faceNumber, 1, mxREAL); 
    faceAreas = mxGetPr(faceAreasOutput);
    volumeOutput = mxCreateDoubleMatrix(1, 1, mxREAL); 
    volume = mxGetPr(volumeOutput);

    for (f = 0; f < faceNumber; f++)
    {
        faceCell = mxGetCell(facesInput, f);
        face = mxGetPr(faceCell);

        edgeNumber = (mwIndex)(mxGetN(faceCell)) - 1; 
            // face is 1 by e + 1 array, the last entry is duplication of
            // the first one

        edgesCell = mxCreateDoubleMatrix(dim, edgeNumber, mxREAL);
        edges = mxGetPr(edgesCell);

        edgeCentersCell = mxCreateDoubleMatrix(dim, edgeNumber, mxREAL);
        edgeCenters = mxGetPr(edgeCentersCell);

        edgeLengthsCell = mxCreateDoubleMatrix(1, edgeNumber, mxREAL);
        edgeLengths = mxGetPr(edgeLengthsCell);

        edgeUnitsCell = mxCreateDoubleMatrix(dim, edgeNumber, mxREAL);
        edgeUnits = mxGetPr(edgeUnitsCell);

        edgeNormalsCell = mxCreateDoubleMatrix(dim, edgeNumber, mxREAL);
        edgeNormals = mxGetPr(edgeNormalsCell);

        faceNormalCell = mxCreateDoubleMatrix(dim, 1, mxREAL);
        faceNormal = mxGetPr(faceNormalCell);

        for (e = 0; e < edgeNumber; e++)
        {
            for (i = 0; i < dim; i++)
            {
                nextVertexIdx = (mwIndex)face[e+1] * dim + i;
                currentVertexIdx = (mwIndex)face[e] * dim + i;

                edgeIdx = dim * e + i;

                edgeCenters[edgeIdx] = (vertices[nextVertexIdx] 
                    + vertices[currentVertexIdx]) / 2;
                edges[edgeIdx] = vertices[nextVertexIdx] 
                    - vertices[currentVertexIdx];
            }
            edgeLengths[e] = twoNorm(edges + e * dim, dim);

            for (i = 0; i < dim; i++)
            {
                edgeIdx = dim * e + i;
                edgeUnits[edgeIdx] = edges[edgeIdx] / edgeLengths[e];
            }
        }
        cross(edgeUnits, edgeUnits + dim, faceNormal); 
        mexPrint1dArray(faceNormal, dim);
        tmp = twoNorm(faceNormal, dim);
        divideScaler(faceNormal, dim, tmp);

        faceAreas[f] = calcFaceArea(vertices, vertexNumber, face,
            edgeNumber, faceNormal);

        for (e = 0; e < edgeNumber; e++){
            cross(edgeUnits + e * dim, faceNormal, edgeNormals + e * dim);
            for (i = 0; i < dim; i++){
                edgeNormals[e * dim + i] *= edgeLengths[e];
            }
        }
        mxSetCell(edgesOutput, f, edgesCell);
        mxSetCell(edgeCentersOutput, f, edgeCentersCell);
        mxSetCell(edgeLengthsOutput, f, edgeLengthsCell);
        mxSetCell(edgeUnitsOutput, f, edgeUnitsCell);
        mxSetCell(faceNormalsOutput, f, faceNormalCell);
        mxSetCell(edgeNormalsOutput, f, edgeNormalsCell);
    }
    *volume = calcPolyVolumeCellFaces(faceAreas, vertices, facesInput, 
        faceNormalsOutput);
}