 void renderSprites() {
     glUseProgram(spriteShaderProgramId);
     entityManagerRef->visitEntitiesWithTypeMask(componentMask, [&](Entity<EntityManagerTypes...> &entity){
         auto &aabbComponent = entity.template getComponent<AABBComponent>();
         auto &transformComponent = entity.template getComponent<TransformComponent>();
         
         Eigen::Translation<GLfloat, 3> translationMat((transformComponent.x - HALF_SCREEN_WIDTH) / HALF_SCREEN_WIDTH,
                                                       (transformComponent.y - HALF_SCREEN_HEIGHT) / HALF_SCREEN_HEIGHT,
                                                       0);
         Eigen::DiagonalMatrix<GLfloat, 3> scaleMat(aabbComponent.width / SCREEN_WIDTH,
                                                    aabbComponent.height / SCREEN_HEIGHT,
                                                    1);
         
         Eigen::Transform<GLfloat, 3, Eigen::Affine> transformMatrix = translationMat * scaleMat;
         
         boundsSprite.render(transformMatrix.matrix());
     });
 }