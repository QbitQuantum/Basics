int main(void)
{
    volatile SAMPLE values[NR_CHANNELS];
    volatile uint16_t seqno = 0;
    volatile uint16_t count = 0;
    int idle, channel;

    ocp_init();
    shm_init();

    WR_MAGIC( 0x0ADCDA8A );

    WR_SEQNO( seqno );
    while (1)
    {
        // Read ADC data into values
        values[0] = adc_read( 0, 0, 0 );
        values[1] = adc_read1( 0, 0, 0 );
        values[2] = adc_read2( 0, 0, 0 );
        values[3] = adc_read3( 0, 0, 0 );

        // Write into shared memory
        for ( channel = 0; channel < NR_CHANNELS; ++channel ) {
            WR_DATA( seqno, channel, count, values[channel] );
        }

        // Increment and update sample counts
        count++;
        WR_COUNT( count );

        if ( count >= SAMPLES_PER_MSG ) {
            count = 0;
            WR_COUNT( count );

            seqno++;
            WR_SEQNO( seqno );

            // Signal to host that data is ready for reading
            for ( idle=0; idle < 2; ++idle ) {
                seqno = seqno;
            }
            generate_host_interrupt( PRU0_ARM_DONE_INTERRUPT + 16 );
        }

        // Idle some until time for the next sample
        //
        // We want a delay of abuot 100us (10kHz) between samples. Since
        // the PRU runs at 200MHz (5ns per op), we want 20000 ops for
        // an approximate delay of 100us. Since one iteration is
        // approximately 10 assembly instructions, counting up to 2000
        // for now.
        for ( idle=0; idle < 2000; ++idle ) {
            seqno = seqno;
        }
    }

    __halt();

    return 0;
}