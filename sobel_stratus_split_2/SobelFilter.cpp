#include <cmath>
#ifndef NATIVE_SYSTEMC
#include "stratus_hls.h"
#endif

#include "SobelFilter.h"
using namespace std;
SobelFilter::SobelFilter(sc_module_name n) : sc_module(n)
{
#ifndef NATIVE_SYSTEMC
	HLS_FLATTEN_ARRAY(val);
#endif
	SC_THREAD(do_filter0);
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);
	SC_THREAD(do_filter1);
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);

#ifndef NATIVE_SYSTEMC
	i_rgb0.clk_rst(i_clk, i_rst);
	o_newR0.clk_rst(i_clk, i_rst);
	o_newG0.clk_rst(i_clk, i_rst);
	o_newB0.clk_rst(i_clk, i_rst);
	i_rgb1.clk_rst(i_clk, i_rst);
	o_newR1.clk_rst(i_clk, i_rst);
	o_newG1.clk_rst(i_clk, i_rst);
	o_newB1.clk_rst(i_clk, i_rst);
#endif
}

SobelFilter::~SobelFilter() {}

// sobel mask
const int mask[MASK_N][MASK_X][MASK_Y] = {{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}},

										  {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}};

const sc_int<8> embossFilterMask[MASK_X][MASK_Y] =
	{
		-1, -1, 0,
		-1, 0, 1,
		0, 1, 1};

const sc_int<8> sharpenFilterMask[MASK_X][MASK_Y] =
{
		1, 1, 1,
		1, -7, 1,
		1, 1, 1
};

void SobelFilter::do_filter0()
{
	int newR, newG, newB;
	int bias = 0;
	sc_uint<8> batch_r[3][256];
	sc_uint<8> batch_g[3][256];
	sc_uint<8> batch_b[3][256];
	sc_dt::sc_uint<24> rgb;
	int cnt = 0;
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_rgb0.reset();
		o_newR0.reset();
		o_newG0.reset();
		o_newB0.reset();
#endif
		wait();
	}
// read first two rows
	for (int y = 0; y < 2; y = y + 1)
	{
		// printf("read %d row", cnt++);
		for (int x = 0; x < 256; x++)
		{

#ifndef NATIVE_SYSTEMC
			{
				rgb = i_rgb0.get();
				wait();
			}
#else
			rgb = i_rgb.read();
#endif
			batch_r[y][x] = rgb.range(7, 0);
			batch_g[y][x] = rgb.range(15, 8);
			batch_b[y][x] = rgb.range(23, 16);
		}
	}

	const int adjustX = (MASK_X % 2) ? 1 : 0;
	const int adjustY = (MASK_Y % 2) ? 1 : 0;
	const int xBound = MASK_X / 2;
	const int yBound = MASK_Y / 2;

	while (true)
	{
		// read new rows
		for (int x = 0; x < 256; x++)
		{

#ifndef NATIVE_SYSTEMC
			{
				rgb = i_rgb0.get();
				wait();
			}
#else
			rgb = i_rgb0.read();
#endif
			batch_r[2][x] = rgb.range(7, 0);
			batch_g[2][x] = rgb.range(15, 8);
			batch_b[2][x] = rgb.range(23, 16);
		}
		// printf("read %d row\n", cnt++);

		for (int x = 0; x < 256; x++)
		{
			newR = newG = newB = 0; // reset color
			int y = MASK_Y / 2;		// do filter on center row
			for (int v = -yBound; v != yBound + adjustY; ++v)
			{
				for (int u = -xBound; u != xBound + adjustX; ++u)
				{
					if (x + u >= 0 && x + u < 256 && y + v >= 0 && y + v < 3)
					{
						newR += batch_r[v + y][x + u] * sharpenFilterMask[v + yBound][u + xBound];
						newB += batch_g[v + y][x + u] * sharpenFilterMask[v + yBound][u + xBound];
						newB += batch_b[v + y][x + u] * sharpenFilterMask[v + yBound][u + xBound];
					}
				}

			}

				newR = int(min(max(int(newR + bias), 0), 255));
				newG = int(min(max(int(newG + bias), 0), 255));
				newB = int(min(max(int(newB + bias), 0), 255));
#ifndef NATIVE_SYSTEMC
				{
					HLS_DEFINE_PROTOCOL("output");
					o_newR0.put(newR);
					o_newG0.put(newG);
					o_newB0.put(newB);
					wait();
				}
#else
				o_newR0.write(newR);
				o_newG0.write(newG);
				o_newB0.write(newB);
#endif

		}
		for (int y = 1; y < 3; y++)
		{
			for (int x = 0; x < 256; x++)
			{
				batch_r[y - 1][x] = batch_r[y][x];
				batch_g[y - 1][x] = batch_g[y][x];
				batch_b[y - 1][x] = batch_b[y][x];
			}
		}
	}
}

void SobelFilter::do_filter1()
{
	int newR, newG, newB;
	int bias = 0;
	sc_uint<8> batch_r[3][256];
	sc_uint<8> batch_g[3][256];
	sc_uint<8> batch_b[3][256];
	sc_dt::sc_uint<24> rgb;
	int cnt = 0;
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_rgb1.reset();
		o_newR1.reset();
		o_newG1.reset();
		o_newB1.reset();
#endif
		wait();
	}
// read first two rows
	for (int y = 0; y < 2; y = y + 1)
	{
		// printf("read %d row", cnt++);
		for (int x = 0; x < 256; x++)
		{

#ifndef NATIVE_SYSTEMC
			{
				rgb = i_rgb1.get();
				wait();
			}
#else
			rgb = i_rgb.read();
#endif
			batch_r[y][x] = rgb.range(7, 0);
			batch_g[y][x] = rgb.range(15, 8);
			batch_b[y][x] = rgb.range(23, 16);
		}
	}

	const int adjustX = (MASK_X % 2) ? 1 : 0;
	const int adjustY = (MASK_Y % 2) ? 1 : 0;
	const int xBound = MASK_X / 2;
	const int yBound = MASK_Y / 2;

	while (true)
	{
		// read new rows
		for (int x = 0; x < 256; x++)
		{

#ifndef NATIVE_SYSTEMC
			{
				rgb = i_rgb1.get();
				wait();
			}
#else
			rgb = i_rgb0.read();
#endif
			batch_r[2][x] = rgb.range(7, 0);
			batch_g[2][x] = rgb.range(15, 8);
			batch_b[2][x] = rgb.range(23, 16);
		}
		// printf("read %d row\n", cnt++);

		for (int x = 0; x < 256; x++)
		{
			newR = newG = newB = 0; // reset color
			int y = MASK_Y / 2;		// do filter on center row
			for (int v = -yBound; v != yBound + adjustY; ++v)
			{
				for (int u = -xBound; u != xBound + adjustX; ++u)
				{
					if (x + u >= 0 && x + u < 256 && y + v >= 0 && y + v < 3)
					{
						newR += batch_r[v + y][x + u] * sharpenFilterMask[v + yBound][u + xBound];
						newB += batch_g[v + y][x + u] * sharpenFilterMask[v + yBound][u + xBound];
						newB += batch_b[v + y][x + u] * sharpenFilterMask[v + yBound][u + xBound];
					}
				}

			}

				newR = int(min(max(int(newR + bias), 0), 255));
				newG = int(min(max(int(newG + bias), 0), 255));
				newB = int(min(max(int(newB + bias), 0), 255));
#ifndef NATIVE_SYSTEMC
				{
					HLS_DEFINE_PROTOCOL("output");
					o_newR1.put(newR);
					o_newG1.put(newG);
					o_newB1.put(newB);
					wait();
				}
#else
				o_newR1.write(newR);
				o_newG1.write(newG);
				o_newB1.write(newB);
#endif

		}
		for (int y = 1; y < 3; y++)
		{
			for (int x = 0; x < 256; x++)
			{
				batch_r[y - 1][x] = batch_r[y][x];
				batch_g[y - 1][x] = batch_g[y][x];
				batch_b[y - 1][x] = batch_b[y][x];
			}
		}
	}
}

