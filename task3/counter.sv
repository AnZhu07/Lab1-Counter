module counter #(
  parameter WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock 
  input  logic             rst,      // reset 
  input  logic             en,       // load counter from data
  input  logic [WIDTH-1:0] v,        // value to preload
  output logic [WIDTH-1:0] count     // count output
);

always_ff @ (posedge clk)
    if (rst) count<= {WIDTH{1'b0}};
    //else     count <= en ? v : count + {{WIDTH-1{1'b0}},1'b1}; //part1
    else     count <= count + {{WIDTH-1{1'b0}},en};//en ? v : count + {{WIDTH-1{1'b0}},en}; //part2 of task3
    /*else
      if (en) count <= v;
      else    count <= count + {{WIDTH-1{1'b0}},en}; //part2 of task3
    */

endmodule

