double metric_cmp(struct path_stats *ps1, struct path_stats *ps2)
{
    double diff = 0;

    if(ps1->delay != ps2->delay){
        diff += fdim(ps1->delay, ps2->delay) / fmax(ps1->delay, ps2->delay);
    }

    if(ps1->loss != ps2->loss){
        diff += fdim(ps1->loss, ps2->loss) / fmax(ps1->loss, ps2->loss);
    }

    if(ps1->jitter != ps2->jitter){
        diff += fdim(ps1->jitter, ps2->jitter) / fmax(ps1->jitter, ps2->jitter);
    }

    if(ps1->bandwidth != ps2->bandwidth){
        diff += fdim(ps1->bandwidth, ps2->bandwidth)
                / fmax(ps1->bandwidth, ps2->bandwidth);
    }

    return diff;
}