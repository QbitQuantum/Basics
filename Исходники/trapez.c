//Based on trapez_motion_2.m
//Assumes 0 initial speed
long long trapez_gen_motion_1(long long pos_i, long long pos_f, long long spd_max, long long a)
{
	long long abs_d_pos = 0, abs_acc_pos = 0, dual_abs_acc_pos = 0;

    //spd_max & a have to be positive
    spd_max = llabs(spd_max);
    a = llabs(a);

    //Compute parameters (in global variables)
    trapez_compute_params(pos_i, pos_f, spd_max, a);

    //Absolute values
    abs_d_pos = llabs(d_pos);
    abs_acc_pos = llabs(acc_pos);
    dual_abs_acc_pos = 2*abs_acc_pos;

    #ifdef DEBUGGING_OUTPUT
    printf("d_pos = %lld, abs_d_pos = %lld.\n", d_pos, abs_d_pos);
    printf("1) acc_pos = %lld, abs_acc_pos = %lld.\n", acc_pos, abs_acc_pos);
    #endif

    //It's possible to overshoot position if the acceleration is too low.
    //In that case we should sacrifice the top speed
    if(dual_abs_acc_pos > abs_d_pos)
    {
        #ifdef DEBUGGING_OUTPUT
        printf("Position overshoot.\n");
        #endif

        //New top speed:
        spd_max = sqrt(a*abs_d_pos);
        #ifdef DEBUGGING_OUTPUT
        printf("New spd_max: %lld.\n", spd_max);
        #endif

        //Redo the initial math:
        //Compute parameters (in global variables)
        trapez_compute_params(pos_i, pos_f, spd_max, a);

        //Absolute values (they probably changed)
        abs_d_pos = abs(d_pos);
        abs_acc_pos = abs(acc_pos);
        dual_abs_acc_pos = 2*abs_acc_pos;
    }

    //Plateau - constant speed
    #ifdef DEBUGGING_OUTPUT
    printf("d_pos = %lld, abs_d_pos = %lld.\n", d_pos, abs_d_pos);
    printf("2) acc_pos = %lld, abs_acc_pos = %lld.\n", acc_pos, abs_acc_pos);
    #endif

    cte_spd_pos = abs_d_pos - (2*abs_acc_pos);
    if(spd_max == 0)
        spd_max = 1;    //Prevents div/0
    cte_spd_pos_discrete = (SPD_FACTOR*cte_spd_pos/spd_max)*TRAPEZ_ONE_OVER_DT;
    cte_spd_pos_discrete = cte_spd_pos_discrete / SPD_FACTOR;
    #ifdef DEBUGGING_OUTPUT
    printf("cte_spd_pos = %lld, cte_spd_pos_discrete = %lld.\n", cte_spd_pos, cte_spd_pos_discrete);
    #endif
    if(cte_spd_pos_discrete < 0)
    {
        cte_spd_pos_discrete = 0;
        #ifdef DEBUGGING_OUTPUT
        printf("No steady speed!\n");
        #endif
    }

    //Transitions:
    trapez_transitions[0] = a_t_discrete;
    trapez_transitions[1] = a_t_discrete + cte_spd_pos_discrete;
    trapez_transitions[2] = 2*a_t_discrete + cte_spd_pos_discrete;
    #ifdef DEBUGGING_OUTPUT
    printf("tr[0] = %lld, tr[1] = %lld, tr[2] = %lld.\n", trapez_transitions[0], trapez_transitions[1], trapez_transitions[2]);
    #endif
    pos_step = 0;   //Variable used to output the current position command

    return (2*a_t_discrete + cte_spd_pos_discrete); //Returns the number of steps
}