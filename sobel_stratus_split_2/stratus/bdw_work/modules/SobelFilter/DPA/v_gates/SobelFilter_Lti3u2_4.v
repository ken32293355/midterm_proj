`timescale 1ps / 1ps

// Generated by Cadence Genus(TM) Synthesis Solution 17.11-s014_1
// Generated on: Nov 17 2019 10:14:16 CST (Nov 17 2019 02:14:16 UTC)

module SobelFilter_Lti3u2_4(in1, out1);
  input [1:0] in1;
  output out1;
  wire [1:0] in1;
  wire out1;
  NAND2X1 gt_31_28_g22(.A (in1[1]), .B (in1[0]), .Y (out1));
endmodule

