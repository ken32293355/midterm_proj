#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
using namespace sc_core;

#ifndef NATIVE_SYSTEMC
#include <cynw_p2p.h>
#endif

#include "filter_def.h"

class SobelFilter: public sc_module
{
public:
	sc_in_clk i_clk;
	sc_in < bool >  i_rst;
#ifndef NATIVE_SYSTEMC
	cynw_p2p< sc_dt::sc_uint<24> >::in i_rgb0;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newR0;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newG0;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newB0;
	cynw_p2p< sc_dt::sc_uint<24> >::in i_rgb1;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newR1;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newG1;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newB1;
	cynw_p2p< sc_dt::sc_uint<24> >::in i_rgb2;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newR2;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newG2;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_newB2;
#else
	sc_fifo_in< sc_dt::sc_uint<24> > i_rgb0;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newR0;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newG0;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newB0;
	sc_fifo_in< sc_dt::sc_uint<24> > i_rgb1;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newR1;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newG1;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newB1;
	sc_fifo_in< sc_dt::sc_uint<24> > i_rgb2;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newR2;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newG2;
	sc_fifo_out< sc_dt::sc_uint<8> > o_newB2;
#endif
	SC_HAS_PROCESS( SobelFilter );
	SobelFilter( sc_module_name n );
	~SobelFilter();
private:
	void do_filter0();
	void do_filter1();
	void do_filter2();
  int val[MASK_N];
};
#endif
