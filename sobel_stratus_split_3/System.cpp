#include "System.h"
System::System( sc_module_name n, string input_bmp, string output_bmp ): sc_module( n ), 
	tb("tb"), sobel_filter("sobel_filter"), clk("clk", CLOCK_PERIOD, SC_NS), rst("rst"), _output_bmp(output_bmp)
{
	tb.i_clk(clk);
	tb.o_rst(rst);
	sobel_filter.i_clk(clk);
	sobel_filter.i_rst(rst);
	tb.o_rgb0(rgb0);
	tb.i_newR0(newR0);
	tb.i_newG0(newG0);
	tb.i_newB0(newB0);
	sobel_filter.i_rgb0(rgb0);
	sobel_filter.o_newR0(newR0);
	sobel_filter.o_newG0(newG0);
	sobel_filter.o_newB0(newB0);
	tb.o_rgb1(rgb1);
	tb.i_newR1(newR1);
	tb.i_newG1(newG1);
	tb.i_newB1(newB1);
	sobel_filter.i_rgb1(rgb1);
	sobel_filter.o_newR1(newR1);
	sobel_filter.o_newG1(newG1);
	sobel_filter.o_newB1(newB1);
	tb.o_rgb2(rgb2);
	tb.i_newR2(newR2);
	tb.i_newG2(newG2);
	tb.i_newB2(newB2);
	sobel_filter.i_rgb2(rgb2);
	sobel_filter.o_newR2(newR2);
	sobel_filter.o_newG2(newG2);
	sobel_filter.o_newB2(newB2);


	tb.read_bmp(input_bmp);
}

System::~System() {
  tb.write_bmp(_output_bmp);
}
