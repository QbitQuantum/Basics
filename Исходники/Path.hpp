    /**
     * This method evaluates the path at a given time and returns the target
     * position and velocity of the robot.
     *
     * @param t Time (in seconds) since the robot started the path. Throws an
     *     exception if t<0
     * @return A MotionInstant containing the position and velocity at the given
     *     time if @t is within the range of the path.  If @t is not within the
     *     time range of this path, this method returns boost::none.
     */
    virtual boost::optional<RobotInstant> evaluate(
        RJ::Seconds t) const override {
        if (!path) {
            return boost::none;
        }

        boost::optional<RobotInstant> instant = path->evaluate(t);
        if (!angleFunction) {
            return instant;
        } else {
            if (instant) {
                instant->angle = angleFunction->operator()(instant->motion);
                return instant;
            } else {
                return boost::none;
            }
        }
    }