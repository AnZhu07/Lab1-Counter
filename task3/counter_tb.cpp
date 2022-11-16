#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");
    

    //init Vbuddy
    if (vbdOpen()!=1) return (-1);
    vbdHeader("Lab1: Counter");
      //one-shot behaviour, reflects input stimuli change. 

    // initialize simulation inputs
    top->clk = 1;
    top->rst =0;
    //top->en=0;
    top->en = 0;
    top->v=0;
    vbdSetMode(1);
    
    // run simulation for many clock cycles
    for (i=0; i<800; i++){

        //dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump (2*i+clk);  // unit is in ps
            top->clk = !top->clk;
            top->eval ();
        }

        top->en = vbdFlag();
        top->v = vbdValue();
    

        // ++++ Send count value to Vbuddy
        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, int(top->count) & 0xF);
        vbdCycle(i+1);      
        //vbdPlot(int(top->count), 0, 255);
        //-----end of Vbuddy output section

        //change input stimuli
        
        if (Verilated::gotFinish())  exit(0);
    }

    vbdClose();  //++++
    tfp->close();
    exit(0);

}