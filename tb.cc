#include "tb.h"

#include <systemc.h>

void tb::source() {
    rst.write(0);
    inp_vld.write(0);
    inp.write(1);
    wait();
    rst.write(0);
    wait();

    sc_int<16> tmp;

    for (int i = 0; i < 64; i++) {
        if (i > 23 && i < 29) {
            tmp = 256;
        } else {
            tmp = 0;
        }
        inp_vld.write(1);
        inp.write(tmp);
        do {
            wait();
        } while (inp_rdy.read() == 0);
        inp_vld.write(0);
    }
};

void tb::sink() {
    sc_int<16> indata;

    // Open simulation file
    char output_file[256];
    sprintf(output_file, "./output.dat");
    outfp = fopen(output_file, "w");
    if (outfp == NULL) {
        cout << "Error: Can't open output file " << output_file << endl;
        exit(0);
    }

    outp_rdy.write(0);

    for (int i = 0; i < 64; i++) {
        outp_rdy.write(1);
        do {
            wait();
        } while (outp_vld.read() == 0);
        indata = outp.read();
        outp_rdy.write(0);
        fprintf(outfp, "%d\n", indata.to_int());
        cout << i << ":\t" << indata.to_int() << endl;
    }

    fclose(outfp);

    sc_stop();
};