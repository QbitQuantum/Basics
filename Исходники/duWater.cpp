btScalar duWater::getWaterLevel(btScalar pos_x,
                                btScalar pos_z,
                                int wrapperNum)
{

    // get water wrapper by index
    duWater::WaterWrapper *wWrapper = wrapperByInd(wrapperNum);
    if (!wWrapper)
        return btScalar(0.0);

    if (!wWrapper->wavesHeight)
        return wWrapper->waterLevel;

    float time = m_time;

    ////////// DISTANT WAVES //////////
    // first component
    float noise_coords[2];

    duWaterDynInfo* dynInfo = wWrapper->dynamicsInfo;

    noise_coords[0] = dynInfo->dst_noise_scale0 *
                          (pos_x + dynInfo->dst_noise_freq0 * time);
    noise_coords[1] = dynInfo->dst_noise_scale0 * 
                          (pos_z + dynInfo->dst_noise_freq0 * time);
    float noise1 = snoise(noise_coords);

    // second component
    noise_coords[0] = dynInfo->dst_noise_scale1 *
                          (pos_z - dynInfo->dst_noise_freq1 * time);
    noise_coords[1] = dynInfo->dst_noise_scale1 * 
                          (pos_x - dynInfo->dst_noise_freq1 * time);
    float noise2 = snoise(noise_coords);

    float dist_waves = wWrapper->wavesHeight * noise1 * noise2;

    float wave_height;

    if (wWrapper->wDistArray) {
        ////////// SHORE WAVES //////////
        // get coordinates in texture pixels
        double x = (pos_x - wWrapper->shoreMapCenterX) / wWrapper->shoreMapSizeX;
        double z = (wWrapper->shoreMapCenterZ + pos_z) / wWrapper->shoreMapSizeZ;
        x += 0.5f;
        z += 0.5f;

        // if position is out of boundings, consider that shore dist = 1
        if (x > 1.f || x < 0.f || z > 1.f || z < 0.f)
            wave_height = dist_waves;
        else {
            // get coordinates in pixels
            int array_width = wWrapper->shoreMapTexSize;
            x *= array_width - .5f;
            z *= array_width - .5f;

            double floor_px;
            double floor_py;
            float fract_px = modf(x, &floor_px);
            float fract_py = modf(z, &floor_py);

            int px = static_cast<int>(floor_px);
            int py = static_cast<int>(floor_py);

            btScalar *distArray = wWrapper->wDistArray;

            int up_lim = array_width - 1;

            float dist00 = distArray[py * array_width + px];
            float dist10 = distArray[py * array_width + btMin(px + 1, up_lim)];
            float dist01 = distArray[btMin(py + 1, up_lim) * array_width + px];
            float dist11 = distArray[btMin(py + 1, up_lim) * array_width + btMin(px + 1, up_lim)];

            // distance on bottom, top edge
            float dist0010 = dist00 * (1.f - fract_px) + dist10 * fract_px;
            float dist0111 = dist01 * (1.f - fract_px) + dist11 * fract_px;

            float shore_dist = dist0010 * (1.f - fract_py) + dist0111 * fract_py;

            float shore_waves_length = wWrapper->wavesLength / float(wWrapper->maxShoreDist) / M_PI;

            float waves_coords[2] = {dynInfo->dir_noise_scale *
                                 (pos_x + dynInfo->dir_noise_freq * time),
                                     dynInfo->dir_noise_scale *
                                 (pos_z + dynInfo->dir_noise_freq * time)};

            float dist_fact = sqrt(shore_dist);

            float shore_dir_waves = wWrapper->wavesHeight
                * fmax(shore_dist, dynInfo->dir_min_shore_fac)
                * sinf((dist_fact / shore_waves_length + dynInfo->dir_freq * time))
                * fmax(snoise(waves_coords), dynInfo->dir_min_noise_fac);
            // mix two types of waves basing on distance to the shore
            float mix_rate = btMax(dist_fact, dynInfo->dst_min_fac);
            wave_height = shore_dir_waves * (1 - mix_rate) + dist_waves * mix_rate;
        }
    } else
        wave_height = dist_waves;

    btScalar cur_water_level = wWrapper->waterLevel + wave_height;
    return cur_water_level;
}