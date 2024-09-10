void setTextureMatrix(mat4 currentModelMatrix){
    mat4 scaleBiasMatrix;

    IdentityMatrix(textureMatrix);

// Scale and bias transform, moving from unit cube [-1,1] to [0,1]
    scaleBiasMatrix = Mult(T(0.5, 0.5, 0.0), S(0.5, 0.5, 1.0));
    textureMatrix = Mult(Mult(scaleBiasMatrix, projectionMatrix), Mult(lightViewMatrix,currentModelMatrix));


    //  textureMatrix = Mult(Mult(scaleBiasMatrix, projectionMatrix), modelViewMatrix);
    // Multiply modelview and transformation matrices
}