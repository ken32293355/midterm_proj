/****************************************************************************
*
*  Copyright (c) 2017, Cadence Design Systems. All Rights Reserved.
*
*  This file contains confidential information that may not be
*  distributed under any circumstances without the written permision
*  of Cadence Design Systems.
*
****************************************************************************/


#ifndef _SOBELFILTER_SC_FOREIGN_INCLUDED_
#define _SOBELFILTER_SC_FOREIGN_INCLUDED_

#include <systemc.h>


// Declaration of wrapper with RTL level ports

struct SobelFilter : public ncsc_foreign_module
{
public:

	sc_in< bool > i_clk;
	sc_in< bool > i_rst;
	sc_out< bool > i_rgb_busy;
	sc_in< bool > i_rgb_vld;
	sc_in< sc_uint< 24 > > i_rgb_data;
	sc_in< bool > o_newR_busy;
	sc_out< bool > o_newR_vld;
	sc_out< sc_uint< 8 > > o_newR_data;
	sc_in< bool > o_newG_busy;
	sc_out< bool > o_newG_vld;
	sc_out< sc_uint< 8 > > o_newG_data;
	sc_in< bool > o_newB_busy;
	sc_out< bool > o_newB_vld;
	sc_out< sc_uint< 8 > > o_newB_data;


    const char* hdl_name() const { return "SobelFilter"; }
    
	SobelFilter( sc_module_name name )
		: ncsc_foreign_module(name)
		  ,i_clk("i_clk")
		  	,i_rst("i_rst")
		  	,i_rgb_busy("i_rgb_busy")
		  	,i_rgb_vld("i_rgb_vld")
		  	,i_rgb_data("i_rgb_data")
		  	,o_newR_busy("o_newR_busy")
		  	,o_newR_vld("o_newR_vld")
		  	,o_newR_data("o_newR_data")
		  	,o_newG_busy("o_newG_busy")
		  	,o_newG_vld("o_newG_vld")
		  	,o_newG_data("o_newG_data")
		  	,o_newB_busy("o_newB_busy")
		  	,o_newB_vld("o_newB_vld")
		  	,o_newB_data("o_newB_data")
		  	

		
    {
    }

};

#endif /* _SOBELFILTER_SC_FOREIGN_INCLUDED_ */
