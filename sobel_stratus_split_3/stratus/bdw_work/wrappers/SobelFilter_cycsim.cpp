/****************************************************************************
*
*  Copyright (c) 2015, Cadence Design Systems. All Rights Reserved.
*
*  This file contains confidential information that may not be
*  distributed under any circumstances without the written permision
*  of Cadence Design Systems.
*
****************************************************************************/

#ifdef NCSC
#include <string>
typedef std::string sc_string;
#define SYSTEMC_VERSION 20070314
#endif

#include "SobelFilter_cycsim.h"
#include "esc_catrace.h"
#include "verilated.h"
#include "VSobelFilter_rtl.h"


class VSobelFilter_rtl;

class SobelFilter_cycsimV : public SobelFilter_cycsim
{
    // Port declarations inherited from parent class

    // These signals are used to connect ports that need type conversion to the RTL ports
    sc_signal< uint32_t > i_rgb_data_I;
    sc_signal< uint32_t > o_newR_data_O;
    sc_signal< uint32_t > o_newG_data_O;
    sc_signal< uint32_t > o_newB_data_O;


    // The following threads are used to do the type conversion.
    inline void thread_i_rgb_data_I() {
        i_rgb_data_I = (sc_uint<24>)i_rgb_data.read();
    };
    inline void thread_o_newR_data_O() {
        o_newR_data = o_newR_data_O.read();
    };
    inline void thread_o_newG_data_O() {
        o_newG_data = o_newG_data_O.read();
    };
    inline void thread_o_newB_data_O() {
        o_newB_data = o_newB_data_O.read();
    };


    SC_HAS_PROCESS(SobelFilter_cycsimV);

public:

    SobelFilter_cycsimV( sc_module_name in_name=sc_module_name(sc_gen_unique_name(" SobelFilter") ) )
        : SobelFilter_cycsim(in_name)
    {
        // instantiate the verilated module
        SobelFilter_cyc0 = new VSobelFilter_rtl( "VSobelFilter" );
        // generate port connections
        SobelFilter_cyc0->i_clk(i_clk);
        SobelFilter_cyc0->i_rst(i_rst);
        SobelFilter_cyc0->i_rgb_busy(i_rgb_busy);
        SobelFilter_cyc0->i_rgb_vld(i_rgb_vld);
        SobelFilter_cyc0->i_rgb_data(i_rgb_data_I);
        SobelFilter_cyc0->o_newR_busy(o_newR_busy);
        SobelFilter_cyc0->o_newR_vld(o_newR_vld);
        SobelFilter_cyc0->o_newR_data(o_newR_data_O);
        SobelFilter_cyc0->o_newG_busy(o_newG_busy);
        SobelFilter_cyc0->o_newG_vld(o_newG_vld);
        SobelFilter_cyc0->o_newG_data(o_newG_data_O);
        SobelFilter_cyc0->o_newB_busy(o_newB_busy);
        SobelFilter_cyc0->o_newB_vld(o_newB_vld);
        SobelFilter_cyc0->o_newB_data(o_newB_data_O);


        // setup the type conversion threads
        SC_METHOD( thread_i_rgb_data_I);
            sensitive << i_rgb_data;
        SC_METHOD( thread_o_newR_data_O);
            sensitive << o_newR_data_O;
        SC_METHOD( thread_o_newG_data_O);
            sensitive << o_newG_data_O;
        SC_METHOD( thread_o_newB_data_O);
            sensitive << o_newB_data_O;


        TraceFileType* tfp = esc_get_ca_trace_file();
        if ( tfp )
        {
            SobelFilter_cyc0->trace(tfp,99);
        }
    };

    ~SobelFilter_cycsimV()
    {
        delete SobelFilter_cyc0;
    }

    void end_of_elaboration()
    {
        esc_open_ca_trace_file();
    }

    void end_of_simulation()
    {
        esc_close_ca_trace_file();
    }

protected:
    VSobelFilter_rtl* SobelFilter_cyc0;
};

SobelFilter_cycsim* SobelFilter_cycsim_factory()
{
    return new SobelFilter_cycsimV("SobelFilter");
}

class SobelFilter_linkup
{
public:
    SobelFilter_linkup() {
        extern SobelFilter_cycsim* (*SobelFilter_cycsim_factory_p)();
        SobelFilter_cycsim_factory_p = &SobelFilter_cycsim_factory;
    }
};

// Create the one instance of the factory for this verilated model.
SobelFilter_linkup SobelFilter_cycsimV_link;


