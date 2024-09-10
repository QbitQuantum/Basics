void main()
{
    mat4 matModelViewProjection = matrixCameraToClip * matrixModelToCamera;

    // how large (in meters) is one cell?
    vec3 cellSize = vec3(
      (boundingBoxMax.x - boundingBoxMin.x) / gridCellCount.x,
      (boundingBoxMax.y - boundingBoxMin.y) / gridCellCount.y,
      (boundingBoxMax.z - boundingBoxMin.z) / gridCellCount.z
    );

    // Given the cell hash (=gl_PrimitiveIDIn), whats the 3d-grid-coordinate of the cell's center?
    // This is the reverse of particleskernel.cu -> calcGridHash(int3 gridCell).
    ivec3 gridCellCoordinate = ivec3(
      floor(mod(gl_PrimitiveIDIn, gridCellCount.x)),
      floor(mod(gl_PrimitiveIDIn, gridCellCount.x * gridCellCount.y) / gridCellCount.x),
      floor(mod(gl_PrimitiveIDIn, gridCellCount.x * gridCellCount.y * gridCellCount.z) / (gridCellCount.x * gridCellCount.y))
    );

    vec3 posCenterOfCell = vec3(
      boundingBoxMin.x + (cellSize.x * gridCellCoordinate.x) + (cellSize.x / 2.0),
      boundingBoxMin.y + (cellSize.y * gridCellCoordinate.y) + (cellSize.y / 2.0),
      boundingBoxMin.z + (cellSize.z * gridCellCoordinate.z) + (cellSize.z / 2.0)
    );

    vec4 cameraPosition = inverse(matrixModelToCamera) * vec4(0,0,0,1);

    vec3 toCamera = normalize(cameraPosition.xyz - posCenterOfCell);

    float quadSize = min(min(cellSize.x/2, cellSize.y/2),cellSize.z/2) * quadSizeFactor;

    vec3 upWorld = vec3(0.0, 1.0, 0.0);

    vec3 right = normalize(-cross(toCamera, upWorld)) * quadSize;
    vec3 up = normalize(cross(toCamera, normalize(-right))) * quadSize;

    // Don't draw completely transparent boxes. For some reason, this also fixes the problem of the quads disappearing at certain viewing-angles.
    if(cellvalue[0] == 0.0) return;
    
    float alpha = cellvalue[0];
    if(alphaExponentiation != 1.0) alpha = pow(alpha, alphaExponentiation);
    if(alpha < 1.0 && alpha > 0.993) alpha = 0.4; // show dilated cells with obvious difference.
    if(alpha > 1.0) alpha = 1.0;
    alpha *= alphaMultiplication;
    //if(cellvalue[0] > 0) alpha = 1.0;

    vec4 outColor = fixedColor;
    outColor.a = alpha;

    // bottom left
    posCenterOfCell -= right;
    posCenterOfCell -= up;
    gl_Position = matModelViewProjection * vec4(posCenterOfCell, 1.0);
    //texureCoordinate = vec2(-1.0, -1.0);
    colorGS_to_FS = outColor;
    EmitVertex();

    // top left
    posCenterOfCell += up*2;
    gl_Position = matModelViewProjection * vec4(posCenterOfCell, 1.0);
    //texureCoordinate = vec2(-1.0, 1.0);
    colorGS_to_FS = outColor;
    EmitVertex();

    // bottom right
    posCenterOfCell -= up*2;
    posCenterOfCell += right * 2;
    gl_Position = matModelViewProjection * vec4(posCenterOfCell, 1.0);
    //texureCoordinate = vec2(1.0, -1.0);
    colorGS_to_FS = outColor;
    EmitVertex();

    // top right
    posCenterOfCell += up*2;
    gl_Position = matModelViewProjection * vec4(posCenterOfCell, 1.0);
    //texureCoordinate = vec2(1.0, 1.0);
    colorGS_to_FS = outColor;
    EmitVertex();

    EndPrimitive();
}