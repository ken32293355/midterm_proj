#include "System.h"
System::System( sc_module_name n, string input_bmp, string output_bmp ): sc_module( n ), 
	tb("tb"), sobel_filter("sobel_filter"), clk("clk", CLOCK_PERIOD, SC_NS), rst("rst"), _output_bmp(output_bmp)
{
	tb.i_clk(clk);
	tb.o_rst(rst);
	sobel_filter.i_clk(clk);
	sobel_filter.i_rst(rst);
	tb.o_rgb(rgb);
	tb.i_newR(newR);
	tb.i_newG(newG);
	tb.i_newB(newB);
	sobel_filter.i_rgb(rgb);
	sobel_filter.o_newR(newR);
	sobel_filter.o_newG(newG);
	sobel_filter.o_newB(newB);
	tb.read_bmp(input_bmp);
}

System::~System() {
  tb.write_bmp(_output_bmp);
}
