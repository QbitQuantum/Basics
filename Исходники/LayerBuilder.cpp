    bool intersects(const Rect& rect) const {
        if (!rect.intersects(mBounds)) return false;

        for (const BakedOpState* op : mOps) {
            if (rect.intersects(op->computedState.clippedBounds)) {
                return true;
            }
        }
        return false;
    }