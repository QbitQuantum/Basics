JNIEXPORT void JNICALL
Java_java_awt_MWGraphics_pFillRect (JNIEnv * env, jclass cls, jint _graphicsEngine, jint x, jint y, jint w, jint h)
{
	GraphicsEngine *graphicsEngine = (GraphicsEngine *)_graphicsEngine;

	graphicsEngine->FillRect(graphicsEngine, x, y, w, h);
}