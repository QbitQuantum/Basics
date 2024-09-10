GodRaysResult GodRaysSampler::getResult(const SpaceSegment &segment) {
    Vector3 step = segment.getEnd().sub(segment.getStart());
    double max_length = step.getNorm();
    step = step.normalize().scale(walk_step);
    Vector3 walker = segment.getStart();
    double travelled = 0.0;
    double inside = 0.0;

    if (max_length > this->max_length) {
        max_length = this->max_length;
    }

    while (travelled < max_length) {
        double light = getCachedLight(walker);

        inside += light * walk_step;

        walker = walker.add(step);
        travelled += walk_step;
    }

    return GodRaysResult(inside, travelled);
}