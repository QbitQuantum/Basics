void ScrollingSystem::DoUpdate(float dt) {
    FOR_EACH_ENTITY_COMPONENT(Scrolling, a, sc)
        EltIt iter = elements.find(a);
        if (iter == elements.end()) {
            if ( glm::abs(glm::length(sc->direction) - 1) <= 0.001) {
                initScrolling(a, sc);
                iter = elements.find(a);
            }
            continue;
        }
        if (!sc->show) {
            ScrollingElement& se = iter->second;
            for (int i=0; i<2; i++) {
                RENDERING(se.e[i])->show = false;
            }
            continue;
        }

        LOGF_IF(sc->speed < 0, "Scrolling component '" << sc << "' has a speed < 0");

        ScrollingElement& se = iter->second;
        for (int i=0; i<2; i++) {
            RENDERING(se.e[i])->show = true;

            AnchorComponent* tc = ANCHOR(se.e[i]);
            tc->position += sc->direction * (sc->speed * dt);

            bool isVisible = theRenderingSystem.isVisible(se.e[i]);
            if (!se.hasBeenVisible[i] && isVisible) {
                se.hasBeenVisible[i] = true;
            } else if (se.hasBeenVisible[i] && !isVisible) {
                se.imageIndex[i] = (se.imageIndex[i] + 2) % sc->images.size();
                RENDERING(se.e[i])->texture = sc->images[se.imageIndex[i]];
                const auto* ptc = TRANSFORM(a);
                tc->position =
                    ANCHOR(se.e[(i+1)%2])->position -
                    glm::vec2(sc->direction.x * ptc->size.x, sc->direction.y * ptc->size.y);
                se.hasBeenVisible[i] = false;
            }
        }
    END_FOR_EACH()
}