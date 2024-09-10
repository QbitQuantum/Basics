int Neuron::checkClick(ofVec2f mouse) {
    float dist = mouse.distance(loc);
    if (dist < r) return ID;
    else return -1;
}