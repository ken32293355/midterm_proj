#ifndef TESTBENCH_H_
#define TESTBENCH_H_

#include <string>
using namespace std;

#include <systemc>
using namespace sc_core;

#ifndef NATIVE_SYSTEMC
#include <cynw_p2p.h>
#endif

#include "filter_def.h"

#define WHITE 255
#define BLACK 0
#define THRESHOLD 90

class Testbench : public sc_module
{
public:
	sc_in_clk i_clk;
	sc_out<bool> o_rst;
#ifndef NATIVE_SYSTEMC
	cynw_p2p<sc_dt::sc_uint<24> >::base_out o_rgb0;
	cynw_p2p<sc_dt::sc_uint<24> >::base_out o_rgb1;
	cynw_p2p<sc_dt::sc_uint<8> >::base_in i_newR0;
	cynw_p2p<sc_dt::sc_uint<8> >::base_in i_newG0;
	cynw_p2p<sc_dt::sc_uint<8> >::base_in i_newB0;
	cynw_p2p<sc_dt::sc_uint<8> >::base_in i_newR1;
	cynw_p2p<sc_dt::sc_uint<8> >::base_in i_newG1;
	cynw_p2p<sc_dt::sc_uint<8> >::base_in i_newB1;
#else
	sc_fifo_out<sc_dt::sc_uint<24> > o_rgb0;
	sc_fifo_out<sc_dt::sc_uint<24> > o_rgb1;
	sc_fifo_in<sc_dt::sc_uint<32> >::base_in i_newR0;
	sc_fifo_in<sc_dt::sc_uint<32> >::base_in i_newG0;
	sc_fifo_in<sc_dt::sc_uint<32> >::base_in i_newB0;
	sc_fifo_in<sc_dt::sc_uint<32> >::base_in i_newR1;
	sc_fifo_in<sc_dt::sc_uint<32> >::base_in i_newG1;
	sc_fifo_in<sc_dt::sc_uint<32> >::base_in i_newB1;
#endif

	SC_HAS_PROCESS(Testbench);

	Testbench(sc_module_name n);
	~Testbench();

	int read_bmp(string infile_name);
	int write_bmp(string outfile_name);

	unsigned int get_width() { return width; }

	unsigned int get_height() { return height; }

	unsigned int get_width_bytes() { return width_bytes; }

	unsigned int get_bytes_per_pixel() { return bytes_per_pixel; }

	unsigned char *get_source_image() { return source_bitmap; }
	unsigned char *get_target_image() { return target_bitmap; }

private:
	unsigned int input_rgb_raw_data_offset;
	const unsigned int output_rgb_raw_data_offset;
	unsigned int width;
	unsigned int height;
	unsigned int width_bytes;
	unsigned char bits_per_pixel;
	unsigned short bytes_per_pixel;
	unsigned char *source_bitmap;
	unsigned char *target_bitmap;

	unsigned int n_txn;
	sc_time max_txn_time;
	sc_time min_txn_time;
	sc_time total_txn_time;
	sc_time total_start_time;
	sc_time total_run_time;

	void feed_rgb0();
	void fetch_result0();
	void feed_rgb1();
	void fetch_result1();
	bool fetch_result0_finish;
};
#endif
