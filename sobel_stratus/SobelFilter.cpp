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
	SC_THREAD(do_filter);
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);

#ifndef NATIVE_SYSTEMC
	i_rgb.clk_rst(i_clk, i_rst);
	o_newR.clk_rst(i_clk, i_rst);
	o_newG.clk_rst(i_clk, i_rst);
	o_newB.clk_rst(i_clk, i_rst);
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
		-1, -1, 0,
		-1, 0, 1,
		0, 1, 1};

void SobelFilter::do_filter()
{
	int newR, newG, newB;
	int bias = 128;
	sc_uint<8> batch_r[3][256];
	sc_uint<8> batch_g[3][256];
	sc_uint<8> batch_b[3][256];
	sc_dt::sc_uint<24> rgb;
	// int cnt = 0;
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_rgb.reset();
		o_newR.reset();
		o_newG.reset();
		o_newB.reset();
#endif
		wait();
	}
	// buffer necessary rows
	for (int y = 0; y < MASK_Y - 1; y++)
	{
		for (int x = 0; x < 256; x++)
		{
#ifndef NATIVE_SYSTEMC
			{
				rgb = i_rgb.get();
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
	// boundary condition
	const int adjustX = (MASK_X % 2) ? 1 : 0;
	const int adjustY = (MASK_Y % 2) ? 1 : 0;
	const int xBound = MASK_X / 2;
	const int yBound = MASK_Y / 2;

	while (true)
	{
		{
			HLS_CONSTRAIN_LATENCY(0, 1, "lat00");
			newR = 0;
			newG = 0;
			newB = 0;
		}

		// read new rows
		for (int x = 0; x < 256; x++)
		{

#ifndef NATIVE_SYSTEMC
			{
				rgb = i_rgb.get();
				wait();
			}
#else
			rgb = i_rgb.read();
#endif
			batch_r[2][x] = rgb.range(7, 0);
			batch_g[2][x] = rgb.range(15, 8);
			batch_b[2][x] = rgb.range(23, 16);
		}

		// calculate a batch of new row
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
						newR += batch_r[v + y][x + u] * embossFilterMask[v + yBound][u + xBound];
						newB += batch_g[v + y][x + u] * embossFilterMask[v + yBound][u + xBound];
						newB += batch_b[v + y][x + u] * embossFilterMask[v + yBound][u + xBound];
					}
				}
			}
			newR = int(min(max(int(newR + bias), 0), 255));
			newG = int(min(max(int(newG + bias), 0), 255));
			newB = int(min(max(int(newB + bias), 0), 255));

#ifndef NATIVE_SYSTEMC
			{
				HLS_DEFINE_PROTOCOL("output");
				o_newR.put(newR);
				o_newG.put(newG);
				o_newB.put(newB);
				wait();
			}
#else
			o_newR.write(newR);
			o_newG.write(newG);
			o_newB.write(newB);
#endif
		}
		for (unsigned int v = 0; v < MASK_Y; ++v)
		{
			for (unsigned int u = 0; u < MASK_X; ++u)
			{
				sc_dt::sc_uint<24> rgb;
#ifndef NATIVE_SYSTEMC
				{
					// HLS_DEFINE_PROTOCOL("input");
					rgb = i_rgb.get();
					wait();
				}
#else
				rgb = i_rgb.read();
#endif
				{
					HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
					newR += rgb.range(7, 0) * sharpenFilterMask[u][v];
					newG += rgb.range(15, 8) * sharpenFilterMask[u][v];
					newB += rgb.range(23, 16) * sharpenFilterMask[u][v];
				}
			}
		}
		{
			HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
			newR = int(min(max(int(newR + bias), 0), 255));
			newG = int(min(max(int(newG + bias), 0), 255));
			newB = int(min(max(int(newB + bias), 0), 255));
		}
#ifndef NATIVE_SYSTEMC
		{
			HLS_DEFINE_PROTOCOL("output");
			o_newR.put(newR);
			o_newG.put(newG);
			o_newB.put(newB);
			wait();
		}
#else
		o_newR.write(newR);
		o_newG.write(newG);
		o_newB.write(newB);
#endif
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
