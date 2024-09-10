/*
  this offset nulling algorithm is inspired by this paper from Bill Premerlani

  http://gentlenav.googlecode.com/files/MagnetometerOffsetNullingRevisited.pdf

  The base algorithm works well, but is quite sensitive to
  noise. After long discussions with Bill, the following changes were
  made:

    1) we keep a history buffer that effectively divides the mag
       vectors into a set of N streams. The algorithm is run on the
       streams separately

    2) within each stream we only calculate a change when the mag
       vector has changed by a significant amount.

  This gives us the property that we learn quickly if there is no
  noise, but still learn correctly (and slowly) in the face of lots of
  noise.
 */
void
Compass::null_offsets(void)
{
    if (_null_enable == false || _learn == 0) {
        // auto-calibration is disabled
        return;
    }

    // this gain is set so we converge on the offsets in about 5
    // minutes with a 10Hz compass
    const float gain = 0.01;
    const float max_change = 10.0;
    const float min_diff = 50.0;
    Vector3f ofs;

    ofs = _offset.get();

    if (!_null_init_done) {
        // first time through
        _null_init_done = true;
        for (uint8_t i=0; i<_mag_history_size; i++) {
            // fill the history buffer with the current mag vector,
            // with the offset removed
            _mag_history[i] = Vector3i((mag_x+0.5) - ofs.x, (mag_y+0.5) - ofs.y, (mag_z+0.5) - ofs.z);
        }
        _mag_history_index = 0;
        return;
    }

    Vector3f b1, b2, diff;
    float length;

    // get a past element
    b1 = Vector3f(_mag_history[_mag_history_index].x,
                  _mag_history[_mag_history_index].y,
                  _mag_history[_mag_history_index].z);
    // the history buffer doesn't have the offsets
    b1 += ofs;

    // get the current vector
    b2 = Vector3f(mag_x, mag_y, mag_z);

    // calculate the delta for this sample
    diff = b2 - b1;
    length = diff.length();
    if (length < min_diff) {
        // the mag vector hasn't changed enough - we don't get
        // enough information from this vector to use it.
        // Note that we don't put the current vector into the mag
        // history here. We want to wait for a larger rotation to
        // build up before calculating an offset change, as accuracy
        // of the offset change is highly dependent on the size of the
        // rotation.
        _mag_history_index = (_mag_history_index + 1) % _mag_history_size;
        return;
    }

    // put the vector in the history
    _mag_history[_mag_history_index] = Vector3i((mag_x+0.5) - ofs.x, (mag_y+0.5) - ofs.y, (mag_z+0.5) - ofs.z);
    _mag_history_index = (_mag_history_index + 1) % _mag_history_size;

    // equation 6 of Bills paper
    diff = diff * (gain * (b2.length() - b1.length()) / length);

    // limit the change from any one reading. This is to prevent
    // single crazy readings from throwing off the offsets for a long
    // time
    length = diff.length();
    if (length > max_change) {
        diff *= max_change / length;
    }

    // set the new offsets
    _offset.set(_offset.get() - diff);
}