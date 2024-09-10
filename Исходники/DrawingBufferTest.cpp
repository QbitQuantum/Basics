 static PassRefPtr<DrawingBufferForTests> create(PassOwnPtr<WebGraphicsContext3D> context,
     const IntSize& size, PreserveDrawingBuffer preserve)
 {
     OwnPtr<Extensions3DUtil> extensionsUtil = Extensions3DUtil::create(context.get());
     RefPtr<DrawingBufferForTests> drawingBuffer =
         adoptRef(new DrawingBufferForTests(context, extensionsUtil.release(), preserve));
     if (!drawingBuffer->initialize(size)) {
         drawingBuffer->beginDestruction();
         return PassRefPtr<DrawingBufferForTests>();
     }
     return drawingBuffer.release();
 }