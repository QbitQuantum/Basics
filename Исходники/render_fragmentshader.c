void main (void) {
	gl_FragColor = clamp(effectColorAdd + texture2D(diffuseTextureUnit, gl_PointCoord) * fragColor * effectColorMul, 0.0, 1.0);
}