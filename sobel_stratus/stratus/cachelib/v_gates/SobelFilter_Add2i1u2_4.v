`timescale 1ps / 1ps

// Generated by Cadence Genus(TM) Synthesis Solution 17.11-s014_1
// Generated on: Nov 17 2019 10:14:17 CST (Nov 17 2019 02:14:17 UTC)

module SobelFilter_Add2i1u2_4(in1, out1);
  input [1:0] in1;
  output [1:0] out1;
  wire [1:0] in1;
  wire [1:0] out1;
  INVX1 g4(.A (in1[0]), .Y (out1[0]));
  XOR2XL inc_add_33_2_g11(.A (in1[1]), .B (in1[0]), .Y (out1[1]));
endmodule


