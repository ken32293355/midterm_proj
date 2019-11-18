#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <systemc>
using namespace sc_core;

#include "Testbench.h"
#ifndef NATIVE_SYSTEMC
#include "SobelFilter_wrap.h"
#else
#include "SobelFilter.h"
#endif

class System: public sc_module
{
public:
	SC_HAS_PROCESS( System );
	System( sc_module_name n, std::string input_bmp, std::string output_bmp );
	~System();
private:
  Testbench tb;
#ifndef NATIVE_SYSTEMC
	SobelFilter_wrapper sobel_filter;
#else
	SobelFilter sobel_filter;
#endif
	sc_clock clk;
	sc_signal<bool> rst;
#ifndef NATIVE_SYSTEMC
	cynw_p2p< sc_dt::sc_uint<24> > rgb1;
	cynw_p2p< sc_dt::sc_uint<8> > newR1;
	cynw_p2p< sc_dt::sc_uint<8> > newG1;
	cynw_p2p< sc_dt::sc_uint<8> > newB1;
	cynw_p2p< sc_dt::sc_uint<24> > rgb0;
	cynw_p2p< sc_dt::sc_uint<8> > newR0;
	cynw_p2p< sc_dt::sc_uint<8> > newG0;
	cynw_p2p< sc_dt::sc_uint<8> > newB0;
#else
	sc_fifo< sc_dt::sc_uint<24> > rgb0;
	sc_fifo< sc_dt::sc_uint<8> > newR0;
	sc_fifo< sc_dt::sc_uint<8> > newG0;
	sc_fifo< sc_dt::sc_uint<8> > newB0;
	sc_fifo< sc_dt::sc_uint<24> > rgb1;
	sc_fifo< sc_dt::sc_uint<8> > newR1;
	sc_fifo< sc_dt::sc_uint<8> > newG1;
	sc_fifo< sc_dt::sc_uint<8> > newB1;
#endif

	std::string _output_bmp;
};
#endif
