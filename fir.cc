#include "fir.h"

sc_uint<8> coef[5] = {18, 77, 107, 77, 18};

void fir::fir_main(void) {
    sc_int<16> taps[5];

    // Reset
    for (int i = 0; i < 5; i++) {
        taps[i] = 0;
    }
    outp.write(0);
    outp_vld.write(0);
    inp_rdy.write(0);
    wait();

    while (true) {
        sc_int<16> val = 0;
        sc_int<16> in_val;

        inp_rdy.write(1);
        do {
            wait();
        } while (inp_vld.read() == 0);
        in_val = inp.read();
        inp_rdy.write(0);

        for (int i = 5 - 1; i > 0; i--) {
            taps[i] = taps[i - 1];
        }
        taps[0] = in_val;

        for (int i = 0; i < 5; i++) {
            val += coef[i] * taps[i];
        }
        outp_vld.write(1);
        outp.write(val);
        do {
            wait();
        } while (outp_rdy.read() == 0);
        outp_vld.write(0);
    }
}