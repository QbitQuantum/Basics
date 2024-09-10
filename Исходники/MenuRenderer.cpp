	void MenuRenderer::render(UIComponent *component) {
		if(component->isHidden) return;
		UIAnimator *animator = component->getActiveAnimator();
		UIManager *uiManager = context->uiManager;
		if (animator) {
			animator->drawPreComponent(context);
		}
		// if virtual size bigger than drawable area, scissor to drawable
		if (component->isVirtualLargerThanDrawable()) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(component->left, context->gConfig->viewportHeight - component->bottom, component->right - component->left, component->bottom - component->top);
		}
		if (!component->isEnabled) {
			context->renderContext->colorFilter = Vector4f(0.5f,0.5f,0.5f,1.0f);
		} else {
			context->renderContext->colorFilter = Vector4f(1,1,1,1);
		}
		// draw this component first then recurse children
		S32 menuResourceId = component->backgroundMenuResourceId;
		if (component->isPressed) {
			if (component->pressedBackgroundMenuResourceId != NO_RESOURCE) {
				menuResourceId = component->pressedBackgroundMenuResourceId;
			}
		} else {
			if (uiManager->selectedComponent == component) {
				if (component->selectedBackgroundMenuResourceId != NO_RESOURCE) {
					menuResourceId = component->selectedBackgroundMenuResourceId;
				}
			}
		}
		if (menuResourceId != NO_RESOURCE) {
			Texture *texture = context->glResourceManager->getTexture(getAssetNameForResource(menuResourceId));
			if (menuResourceId != activeResourceId) {
				if (texture) {
					texture->bind();
				}
				activeResourceId = menuResourceId;
			}
			context->quadRenderer->render(texture, component->virtualTop, component->virtualRight, component->virtualBottom, component->virtualLeft);
		}
		if (component->text) {
			if (component->isEnabled) {
				context->renderContext->colorFilter = Vector4f(component->textR,component->textB,component->textG,component->textA);
			} else {
				context->renderContext->colorFilter = Vector4f(component->textR*0.5f,component->textB*0.5f,component->textG*0.5f,component->textA);
			}
			// starting a text render means we're switching textures
			activeResourceId = -1;
			// TODO - optimize for 1 pass text
			F32 componentWidth = component->virtualRight - component->virtualLeft;
			F32 componentHeight = component->virtualBottom - component->virtualTop;
			F32 textWidth = textRenderer->measureWidth(component->text);
			F32 textLineHeight = textRenderer->getHeight();
			F32 totalTextHeight = textLineHeight;
			if (component->isTextMultiline) {
				// take padding into account
				totalTextHeight = textRenderer->measureMultilineHeight(component->text, componentWidth - (component->paddingLeftDips + component->paddingRightDips) * context->gConfig->uiScale);
			}
			F32 textBottomOffset = totalTextHeight - textLineHeight;
			F32 textLeft = component->virtualLeft;
			// confusing - textBottom refers to the bottom of the _first_ row of text, which is the top row in multiline.
			F32 textBottom = component->virtualBottom;
			if (component->textHorizontalAlignment == UIComponent::LEFT) {
				textLeft += component->paddingLeftDips * context->gConfig->uiScale;
			} else if (component->textHorizontalAlignment == UIComponent::HORIZONTAL_CENTER) {
				textLeft += (componentWidth / 2 - textWidth / 2);
			} else if (component->textHorizontalAlignment == UIComponent::RIGHT) {
				textLeft += (componentWidth - textWidth) - component->paddingRightDips * context->gConfig->uiScale;
			}
			if (component->textVerticalAlignment == UIComponent::BOTTOM) {
				textBottom -= textBottomOffset;
				textBottom -= component->paddingBottomDips * context->gConfig->uiScale;
			} else if (component->textVerticalAlignment == UIComponent::VERTICAL_CENTER) {
				textBottom -= (componentHeight / 2 + totalTextHeight / 2) - textLineHeight;
			} else if (component->textVerticalAlignment == UIComponent::TOP) {
				textBottom -= (componentHeight - textLineHeight) - component->paddingTopDips * context->gConfig->uiScale;
			}
			if (textLeft < component->virtualLeft + component->paddingLeftDips * context->gConfig->uiScale) {
				textLeft = component->virtualLeft + component->paddingLeftDips * context->gConfig->uiScale;
			}
			if (textBottom > component->virtualBottom - component->paddingBottomDips * context->gConfig->uiScale) {
				textBottom = component->virtualBottom - component->paddingBottomDips * context->gConfig->uiScale;
			}
			textRenderer->startText();
			if (component->isTextMultiline) {
				textRenderer->renderMultiline(component->text, textLeft, textBottom, component->virtualRight - component->paddingRightDips * context->gConfig->uiScale, component->virtualBottom - component->paddingBottomDips * context->gConfig->uiScale);
			} else {
				textRenderer->render(component->text, textLeft, textBottom);
			}
			textRenderer->finishText();
		}
		if (component->components->getSize() > 0) {
			// recurse through layout's components
			UIComponent **components = component->components->array;
			int i;
			for (i = 0; i < component->components->getSize(); i++) {
				render(components[i]);
			}
		}
		context->renderContext->colorFilter = Vector4f(1,1,1,1);
		if (component->isVirtualLargerThanDrawable()) {
			glDisable(GL_SCISSOR_TEST);
		}
		if (animator) {
			animator->drawPostComponent(context);
		}
	}