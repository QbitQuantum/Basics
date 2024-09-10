void main()
{
    vec3 EyePosition = vec3(gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0));
    vec3 VertexPosition = vec3(gl_ModelViewProjectionMatrix * gl_Vertex);

    // z = log(z / zn) / log(zf / zn)
    vec3 Extents = vec3(gl_ModelViewMatrix * vec4(BoxSize, BoxSize, BoxSize, 1.0));

    float maxd = length(Extents);
    float dist = length(EyePosition); // / maxd;
    float pscale = PointScale;

    vDistance = (pscale / dist / maxd);
    vPointSize = ParticleRadius * (pscale / dist);
    vIncident = normalize(-VertexPosition);
    vDensity = LinearRemap(Log10(ParticleDensity), Log10(DensityRange.x), Log10(DensityRange.y), 0.0, 1.0);
    vColor = ParticleColor;
    vEye = EyePosition;

    gl_PointSize = vPointSize;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz, 1.0);
    gl_FrontColor = gl_Color;
}