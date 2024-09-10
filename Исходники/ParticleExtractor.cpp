 void ParticleExtractor::exportParticlesFromListToImage(const std::vector<Vec2ui> *inputVector, GPUMapped<Image> *outputContainer)
 {
     Image *img = outputContainer->getObjectOnCPU();
     for( auto it = inputVector->begin(); it != inputVector->end(); ++it )
     {
         img->setPixel(it->x, it->y, 1.0f);
     }
     outputContainer->markAsChangedOnCPU();
     outputContainer->ensureIsUpToDateOnGPU();
 }