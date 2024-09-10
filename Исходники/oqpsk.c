/* ************************************************** */
double modulate(call_t *c, double snr) {
    if (snr == MAX_SNR) {
        return 0;
    } else {
        double bpsk_ber = 0.5 * erfc(sqrt(2*snr));
        return (1 - (1 - bpsk_ber) * (1- bpsk_ber));
    }
}