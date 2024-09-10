void BaseReverseMode<Base>::reverse_local_computation(size_t ind_num, size_t dep_num) {
    using std::sin;
    using std::cos;
    using std::acos;
    using std::sqrt;
    using std::pow;
    using std::log;
    using std::exp;

    DerivativeInfo<locint, Base> info;
    if (!trace) {
        warning_NoTraceSet();
    }
    if (ind_num != trace->get_num_ind()) {
        warning_NumberInconsistent("independent", ind_num, trace->get_num_ind());
    }
    if (dep_num != trace->get_num_dep()) {
        warning_NumberInconsistent("dependent", dep_num, trace->get_num_dep());
    }
    size_t ind_count = trace->get_num_ind();
    size_t dep_count = trace->get_num_dep();

    locint res;
    double coval;
    trace->init_reverse();
    opbyte op = trace->get_next_op_r();

    while (op != start_of_tape) {
        info.clear();
        info.opcode = op;
        switch (op) {
        case start_of_tape:
        case end_of_tape:
            break;
        case assign_ind:
            res = trace->get_next_loc_r();;
            trace->get_next_val_r();
            if (ind_count == 0) {
                // TODO(warning)
            }
            ind_count--;
            indep_index_map[res] = ind_count;
            break;
        case assign_dep:
            res = trace->get_next_loc_r();
            dep_value[res] = trace->get_next_val_r();
            init_dep_deriv(res);
            if (dep_count == 0) {
                // TODO(warning)
            }
            dep_count--;
            dep_index_map[res] = dep_count;
            break;
        case assign_param:
            info.r = trace->get_next_loc_r();
            trace->get_next_param_r();
            break;
        case assign_d:
            info.r = trace->get_next_loc_r();
            trace->get_next_coval_r();
            break;
        case assign_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.dx = 1.0;
            break;
        case comp_eq:
        case comp_lt:
            trace->get_next_loc_r();
            trace->get_next_loc_r();
            trace->get_next_coval_r();
            break;
        case eq_plus_a:
        case plus_a_a:
            info.r = trace->get_next_loc_r();
            info.y = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.dx = 1.0;
            info.dy = 1.0;
            PSEUDO_BINARY
            break;
        case eq_plus_d:
        case plus_d_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            trace->get_next_coval_r();
            info.dx = 1.0;
            break;
        case eq_minus_a:
        case minus_a_a:
            info.r = trace->get_next_loc_r();
            info.y = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.dx = 1.0;
            info.dy = -1.0;
            PSEUDO_BINARY
            break;
        case minus_d_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            trace->get_next_coval_r();
            info.dx = -1.0;
            break;
        case eq_mult_a:
        case mult_a_a:
            info.r = trace->get_next_loc_r();
            info.y = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vy = trace->get_next_val_r();
            info.vx = trace->get_next_val_r();
            info.dx = info.vy;
            info.dy = info.vx;
            info.pxy = 1.0;
            PSEUDO_BINARY
            break;
        case eq_mult_d:
        case mult_d_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.dx = trace->get_next_coval_r();
            break;
        case eq_div_a:
        case div_a_a:
            info.r = trace->get_next_loc_r();
            info.y = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vy = trace->get_next_val_r();
            info.vx = trace->get_next_val_r();
            info.dx = 1.0 / info.vy;
            info.dy = -info.vx / (info.vy*info.vy);
            info.pxy = -1.0 / (info.vy*info.vy);
            info.pyy = 2.0 * info.vx / (info.vy*info.vy*info.vy);
            info.pxyy = 2.0 / (info.vy * info.vy * info.vy);
            info.pyyy = -6.0 * info.vx / (info.vy*info.vy*info.vy*info.vy);
            PSEUDO_BINARY
            break;
        case div_d_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            coval = trace->get_next_coval_r();
            info.dx = -coval / (info.vx*info.vx);
            info.pxx = 2.0 * coval / (info.vx*info.vx*info.vx);
            info.pxxx = -6.0 * coval / (info.vx*info.vx*info.vx*info.vx);
            break;
        case sin_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            info.dx = cos(info.vx);
            info.pxx = -sin(info.vx);
            info.pxxx = -cos(info.vx);
            break;
        case cos_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            info.dx = -sin(info.vx);
            info.pxx = -cos(info.vx);
            info.pxxx = sin(info.vx);
            break;
        case asin_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            {
                Base t = sqrt(1.0 - info.vx * info.vx);
                info.dx = 1.0 / t;
                info.pxx = info.vx / (t * t * t);
                info.pxxx = (2.0*info.vx*info.vx+1.0) / (t*t*t*t*t);
            }
            break;
        case acos_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            {
                Base t = -sqrt(1.0 - info.vx * info.vx);
                info.dx = 1.0 / t;
                info.pxx = info.vx / (t * t * t);
                info.pxxx = (2.0*info.vx*info.vx+1.0) / (t*t*t*t*t);
            }
            break;
        case atan_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            {
                Base t = 1.0 + info.vx * info.vx;
                info.dx = 1.0 / t;
                info.pxx = -2.0 * info.vx / (t * t);
                info.pxxx = (6.0*info.vx*info.vx-2.0)/(t*t*t);
            }
            break;
        case sqrt_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            if (info.vx != 0.0) {
                info.dx = 0.5/sqrt(info.vx);
                info.pxx = -0.5 * info.dx / info.vx;
                info.pxxx = -1.5 * info.pxx / info.vx;
            }
            break;
        case exp_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            info.dx = exp(info.vx);
            info.pxx = info.dx;
            info.pxxx = info.dx;
            break;
        case log_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            info.dx = 1.0 / info.vx;
            info.pxx = - info.dx * info.dx;
            info.pxxx = -2.0 * info.pxx / info.vx;
            break;
        case pow_a_a:
            info.r = trace->get_next_loc_r();
            info.y = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vy = trace->get_next_val_r();
            info.vx = trace->get_next_val_r();
            {
                Base t = pow(info.vx, info.vy);
                info.dx = info.vy * t / info.vx;
                info.pxx = (info.vy - 1) * info.dx / info.vx;
                info.dy = log(info.vx) * t;
                info.pyy = log(info.vx) * info.dy;
                info.pxy = (info.vy * log(info.vx) + 1) * t / info.vx;
                info.pxxx = (info.vy - 2) * info.pxx / info.vx;
                info.pxxy = (info.vy-1)*info.pxy/info.vx + info.vy*t/(info.vx*info.vx);
                info.pxyy = info.dx*log(info.vx)*log(info.vx) + 2*log(info.vx)*t/info.vx;
                info.pyyy = log(info.vx) * info.pyy;
            }
            PSEUDO_BINARY
            break;
        case pow_a_d:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            coval = trace->get_next_coval_r();
            info.coval = coval;
            {
                Base t = pow(info.vx, coval);
                info.dx = coval * t / info.vx;
                info.pxx = (coval - 1) * info.dx / info.vx;
                info.pxxx = (coval - 2) * info.pxx / info.vx;
            }
            break;
        case pow_d_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            coval = trace->get_next_coval_r();
            info.coval = coval;
            {
                Base t = pow(coval, info.vx);
                info.dx = log(coval) * t;
                info.pxx = log(coval) * info.dx;
                info.pxxx = log(coval) * info.pxx;
            }
            break;
        case erf_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            info.dx = 2.0/sqrt(PI)*exp(-info.vx*info.vx);
            info.pxx = info.dx * (-2.0 * info.vx);
            info.pxxx = info.dx * (4.0 * info.vx * info.vx - 2);
            break;
        case fabs_a:
            info.r = trace->get_next_loc_r();
            info.x = trace->get_next_loc_r();
            info.vx = trace->get_next_val_r();
            if (info.vx > 0) {
                info.dx = 1.0;
            } else if (info.vx < 0) {
                info.dx = -1.0;
            } else {
                // TODO(muwang) : warning message
            }
            break;
        case rmpi_send:
        case rmpi_recv:
            break;
        default:
            warning_UnrecognizedOpcode((int)op);
        }
        // call to inherited virtual functions
        process_sac(info);

        op = trace->get_next_op_r();
    }
    // this is only for preaccumulation
    info.clear();
    info.opcode = op;
    process_sac(info);
    trace->end_reverse();
    return;
}