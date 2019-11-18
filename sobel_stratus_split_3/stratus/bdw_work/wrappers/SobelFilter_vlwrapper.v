/****************************************************************************
*
*  Copyright (c) 2015, Cadence Design Systems. All Rights Reserved.
*
*  This file contains confidential information that may not be
*  distributed under any circumstances without the written permision
*  of Cadence Design Systems.
*
****************************************************************************/
/****************************************************************************
*
* Verilog Verification wrapper module for the SobelFilter module.
*
* This module contains the followng items:
*	- A foreign module definition for use in instantiatin the type_wrapper module
*      which contains the BEH module instance.
*	- An instance of the type_wrapper foreign module.
*   - alwyas blocks each type_wrapper output.
*
****************************************************************************/

`timescale 1 ps / 1 ps

module SobelFilter_vlwrapper(
      i_clk,
       i_rst,
       i_rgb_busy,
       i_rgb_vld,
       i_rgb_data,
       o_newR_busy,
       o_newR_vld,
       o_newR_data,
       o_newG_busy,
       o_newG_vld,
       o_newG_data,
       o_newB_busy,
       o_newB_vld,
       o_newB_data

    );

	input i_clk;
	input i_rst;
	output i_rgb_busy;
	reg i_rgb_busy;
	wire m_i_rgb_busy;
	input i_rgb_vld;
	input [23:0] i_rgb_data;
	input o_newR_busy;
	output o_newR_vld;
	reg o_newR_vld;
	wire m_o_newR_vld;
	output [7:0] o_newR_data;
	reg[7:0] o_newR_data;
	wire [7:0] m_o_newR_data;
	input o_newG_busy;
	output o_newG_vld;
	reg o_newG_vld;
	wire m_o_newG_vld;
	output [7:0] o_newG_data;
	reg[7:0] o_newG_data;
	wire [7:0] m_o_newG_data;
	input o_newB_busy;
	output o_newB_vld;
	reg o_newB_vld;
	wire m_o_newB_vld;
	output [7:0] o_newB_data;
	reg[7:0] o_newB_data;
	wire [7:0] m_o_newB_data;


    // Instantiate the Verilog module that instantiates the SystemC module
    SobelFilter_type_wrapper SobelFilter_sc(
        .i_clk(i_clk),
         .i_rst(i_rst),
         .i_rgb_busy(m_i_rgb_busy),
         .i_rgb_vld(i_rgb_vld),
         .i_rgb_data(i_rgb_data),
         .o_newR_busy(o_newR_busy),
         .o_newR_vld(m_o_newR_vld),
         .o_newR_data(m_o_newR_data),
         .o_newG_busy(o_newG_busy),
         .o_newG_vld(m_o_newG_vld),
         .o_newG_data(m_o_newG_data),
         .o_newB_busy(o_newB_busy),
         .o_newB_vld(m_o_newB_vld),
         .o_newB_data(m_o_newB_data)

    );

    // Always blocks for non-blocking assignments of type_wrapper outputs to
    // Verilog Verificatoin wrapper outputs.

    always @(m_i_rgb_busy)
     begin
      i_rgb_busy <= m_i_rgb_busy;
     end
    always @(m_o_newR_vld)
     begin
      o_newR_vld <= m_o_newR_vld;
     end
    always @(m_o_newR_data)
     begin
      o_newR_data <= m_o_newR_data;
     end
    always @(m_o_newG_vld)
     begin
      o_newG_vld <= m_o_newG_vld;
     end
    always @(m_o_newG_data)
     begin
      o_newG_data <= m_o_newG_data;
     end
    always @(m_o_newB_vld)
     begin
      o_newB_vld <= m_o_newB_vld;
     end
    always @(m_o_newB_data)
     begin
      o_newB_data <= m_o_newB_data;
     end


endmodule

// This is an internal module that instantiates the user's SystemC input module
// using the Incisive foreign module instantiation feature.
// The name of the module and the names of the inputs and outputs must match
// with those defined in the SystemC type_wrapper module
module SobelFilter_type_wrapper(
      i_clk,
       i_rst,
       i_rgb_busy,
       i_rgb_vld,
       i_rgb_data,
       o_newR_busy,
       o_newR_vld,
       o_newR_data,
       o_newG_busy,
       o_newG_vld,
       o_newG_data,
       o_newB_busy,
       o_newB_vld,
       o_newB_data

    ) (* integer foreign = "SystemC";
    *);

	input i_clk;
	input i_rst;
	output i_rgb_busy;
	input i_rgb_vld;
	input [23:0] i_rgb_data;
	input o_newR_busy;
	output o_newR_vld;
	output [7:0] o_newR_data;
	input o_newG_busy;
	output o_newG_vld;
	output [7:0] o_newG_data;
	input o_newB_busy;
	output o_newB_vld;
	output [7:0] o_newB_data;


endmodule
