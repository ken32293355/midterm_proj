`timescale 1ps / 1ps

// Generated by Cadence Genus(TM) Synthesis Solution 17.11-s014_1
// Generated on: Nov 17 2019 10:14:08 CST (Nov 17 2019 02:14:08 UTC)

module SobelFilter_Add2i128s32_4(in1, out1);
  input [31:0] in1;
  output [31:0] out1;
  wire [31:0] in1;
  wire [31:0] out1;
  wire add_33_2_n_1, add_33_2_n_3, add_33_2_n_4, add_33_2_n_7,
       add_33_2_n_9, add_33_2_n_11, add_33_2_n_13, add_33_2_n_15;
  wire add_33_2_n_17, add_33_2_n_18, add_33_2_n_20, add_33_2_n_23,
       add_33_2_n_25, add_33_2_n_27, add_33_2_n_29, add_33_2_n_31;
  wire add_33_2_n_33, add_33_2_n_35, add_33_2_n_37, add_33_2_n_39,
       add_33_2_n_41, add_33_2_n_43, add_33_2_n_45;
  assign out1[0] = in1[0];
  assign out1[1] = in1[1];
  assign out1[2] = in1[2];
  assign out1[3] = in1[3];
  assign out1[4] = in1[4];
  assign out1[5] = in1[5];
  assign out1[6] = in1[6];
  INVX1 g7(.A (in1[7]), .Y (out1[7]));
  XNOR2X1 add_33_2_g699(.A (in1[31]), .B (add_33_2_n_45), .Y
       (out1[31]));
  XNOR2X1 add_33_2_g700(.A (in1[30]), .B (add_33_2_n_43), .Y
       (out1[30]));
  NAND2BX1 add_33_2_g701(.AN (add_33_2_n_43), .B (in1[30]), .Y
       (add_33_2_n_45));
  XNOR2X1 add_33_2_g702(.A (in1[29]), .B (add_33_2_n_41), .Y
       (out1[29]));
  NAND2BX1 add_33_2_g703(.AN (add_33_2_n_41), .B (in1[29]), .Y
       (add_33_2_n_43));
  XNOR2X1 add_33_2_g704(.A (in1[28]), .B (add_33_2_n_39), .Y
       (out1[28]));
  NAND2BX1 add_33_2_g705(.AN (add_33_2_n_39), .B (in1[28]), .Y
       (add_33_2_n_41));
  XNOR2X1 add_33_2_g706(.A (in1[27]), .B (add_33_2_n_37), .Y
       (out1[27]));
  NAND2BX1 add_33_2_g707(.AN (add_33_2_n_37), .B (in1[27]), .Y
       (add_33_2_n_39));
  XNOR2X1 add_33_2_g708(.A (in1[26]), .B (add_33_2_n_35), .Y
       (out1[26]));
  NAND2BX1 add_33_2_g709(.AN (add_33_2_n_35), .B (in1[26]), .Y
       (add_33_2_n_37));
  XNOR2X1 add_33_2_g710(.A (in1[25]), .B (add_33_2_n_33), .Y
       (out1[25]));
  NAND2BX1 add_33_2_g711(.AN (add_33_2_n_33), .B (in1[25]), .Y
       (add_33_2_n_35));
  XNOR2X1 add_33_2_g712(.A (in1[24]), .B (add_33_2_n_31), .Y
       (out1[24]));
  NAND2BX1 add_33_2_g713(.AN (add_33_2_n_31), .B (in1[24]), .Y
       (add_33_2_n_33));
  XNOR2X1 add_33_2_g714(.A (in1[23]), .B (add_33_2_n_29), .Y
       (out1[23]));
  NAND2BX1 add_33_2_g715(.AN (add_33_2_n_29), .B (in1[23]), .Y
       (add_33_2_n_31));
  XNOR2X1 add_33_2_g716(.A (in1[22]), .B (add_33_2_n_27), .Y
       (out1[22]));
  NAND2BX1 add_33_2_g717(.AN (add_33_2_n_27), .B (in1[22]), .Y
       (add_33_2_n_29));
  XNOR2X1 add_33_2_g718(.A (in1[21]), .B (add_33_2_n_25), .Y
       (out1[21]));
  NAND2BX1 add_33_2_g719(.AN (add_33_2_n_25), .B (in1[21]), .Y
       (add_33_2_n_27));
  XNOR2X1 add_33_2_g720(.A (in1[20]), .B (add_33_2_n_23), .Y
       (out1[20]));
  NAND2BX1 add_33_2_g721(.AN (add_33_2_n_23), .B (in1[20]), .Y
       (add_33_2_n_25));
  XNOR2X1 add_33_2_g722(.A (in1[19]), .B (add_33_2_n_20), .Y
       (out1[19]));
  NAND2BX1 add_33_2_g723(.AN (add_33_2_n_20), .B (in1[19]), .Y
       (add_33_2_n_23));
  XNOR2X1 add_33_2_g724(.A (in1[17]), .B (add_33_2_n_18), .Y
       (out1[17]));
  XNOR2X1 add_33_2_g725(.A (in1[18]), .B (add_33_2_n_17), .Y
       (out1[18]));
  NAND2BX1 add_33_2_g726(.AN (add_33_2_n_17), .B (in1[18]), .Y
       (add_33_2_n_20));
  XNOR2X1 add_33_2_g727(.A (in1[16]), .B (add_33_2_n_15), .Y
       (out1[16]));
  NAND2BX1 add_33_2_g728(.AN (add_33_2_n_15), .B (in1[16]), .Y
       (add_33_2_n_18));
  NAND3BXL add_33_2_g729(.AN (add_33_2_n_15), .B (in1[17]), .C
       (in1[16]), .Y (add_33_2_n_17));
  XNOR2X1 add_33_2_g730(.A (in1[15]), .B (add_33_2_n_13), .Y
       (out1[15]));
  NAND2BX1 add_33_2_g731(.AN (add_33_2_n_13), .B (in1[15]), .Y
       (add_33_2_n_15));
  XNOR2X1 add_33_2_g732(.A (in1[14]), .B (add_33_2_n_11), .Y
       (out1[14]));
  NAND2BX1 add_33_2_g733(.AN (add_33_2_n_11), .B (in1[14]), .Y
       (add_33_2_n_13));
  XNOR2X1 add_33_2_g734(.A (in1[13]), .B (add_33_2_n_9), .Y (out1[13]));
  NAND2BX1 add_33_2_g735(.AN (add_33_2_n_9), .B (in1[13]), .Y
       (add_33_2_n_11));
  XNOR2X1 add_33_2_g736(.A (in1[12]), .B (add_33_2_n_7), .Y (out1[12]));
  NAND2BX1 add_33_2_g737(.AN (add_33_2_n_7), .B (in1[12]), .Y
       (add_33_2_n_9));
  XNOR2X1 add_33_2_g738(.A (in1[11]), .B (add_33_2_n_4), .Y (out1[11]));
  NAND2BX1 add_33_2_g739(.AN (add_33_2_n_4), .B (in1[11]), .Y
       (add_33_2_n_7));
  XNOR2X1 add_33_2_g740(.A (in1[9]), .B (add_33_2_n_1), .Y (out1[9]));
  XNOR2X1 add_33_2_g741(.A (in1[10]), .B (add_33_2_n_3), .Y (out1[10]));
  NAND2BX1 add_33_2_g742(.AN (add_33_2_n_3), .B (in1[10]), .Y
       (add_33_2_n_4));
  NAND3X1 add_33_2_g743(.A (in1[7]), .B (in1[9]), .C (in1[8]), .Y
       (add_33_2_n_3));
  XOR2XL add_33_2_g744(.A (in1[8]), .B (in1[7]), .Y (out1[8]));
  NAND2X1 add_33_2_g745(.A (in1[8]), .B (in1[7]), .Y (add_33_2_n_1));
endmodule

