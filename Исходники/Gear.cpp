void Gear::createSinePartition() {
    // Use this to draw a sinus surface
    for (int i = 0; i < SEGMENT_COUNT; i++) {
        float position = (float) i / (float) SEGMENT_COUNT;
        float height = exp2f(sinf(position * 2.0f * M_PI));
        heightProfilePartition_.push_back(glm::vec2(position, height));
        //cout << position << ": " << height << std::endl;
    }
}