void MultiDirectionalEar::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        Vector2D windowPos = environment->getWindowPos(object->getPosition());        
        for (int i = 0; i < nearestObjects.size(); i++) {
            Object *nearestObject = nearestObjects[i];
            if (nearestObject->getVoice() && nearestObject->getVoiceInterval() <= 0.0) {
                nearestObject->resetVoiceInterval();
                Vector2D objectWindowPos = environment->getWindowPos(nearestObject->getPosition());
                Vector2D relativePos = objectWindowPos.add(windowPos.mult(-1.0));
                relativePos = relativePos.normalize();
                double pan = relativePos.getX();
                
                double nearestObjectDistance = windowPos.distanceTo(objectWindowPos);
                double gain = 1.0 - (nearestObjectDistance / 1000.0);
                if (gain < 0.0) {
                    gain = 0.0;
                }
                
                al_play_sample(nearestObject->getVoice(), gain, pan, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }                    
    }
}