/****************************************************************************
*
*  Copyright (c) 2015, Cadence Design Systems. All Rights Reserved.
*
*  This file contains confidential information that may not be
*  distributed under any circumstances without the written permision
*  of Cadence Design Systems.
*
****************************************************************************/


#ifndef _SOBELFILTER_WRAP_INCLUDED_
#define _SOBELFILTER_WRAP_INCLUDED_


/* Save ioConfig define values for parent module and define those for this module's ioConfigs. */


#if defined(CYNTHVLG) 

#include <systemc.h>

#define SobelFilter_wrapper SobelFilter

/* This is the section that is seen during processing by cynthVLG of a module
 * that instantiates the module defined by this wrapper.
 */
SC_MODULE(SobelFilter)
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

	SC_CTOR(SobelFilter);
};

#elif defined(CYNTHHL) || defined(BDW_EXTRACT)

/* This is the section seen during processing by cynthHL or bdw_extract of a module 
 * that instantiates the module defined by this wrapper.
 */
#include <systemc.h>

#include "cynw_p2p.h"
#include "cyn_enums.h"


#define SobelFilter_wrapper SobelFilter

/* Only port declarations are required for nested modules.
 */
SC_MODULE(SobelFilter)
{
public:
	sc_in< bool > i_clk;
	sc_in< bool > i_rst;
	cynw::cynw_p2p_base_in <sc_dt::sc_uint <(int)24 >, CYN::cyn_enum <(int)1 > > i_rgb;
	cynw::cynw_p2p_base_out <sc_dt::sc_uint <(int)8 >, CYN::cyn_enum <(int)1 > > o_newR;
	cynw::cynw_p2p_base_out <sc_dt::sc_uint <(int)8 >, CYN::cyn_enum <(int)1 > > o_newG;
	cynw::cynw_p2p_base_out <sc_dt::sc_uint <(int)8 >, CYN::cyn_enum <(int)1 > > o_newB;


	SC_HAS_PROCESS(SobelFilter);
    	SobelFilter_wrapper( sc_module_name name = sc_module_name( sc_gen_unique_name("SobelFilter")) );
};

#else

#include <esc.h>


/* This is the section seen during processing by gcc either when the module
 * itself is compiled, or when a module that instantiates it is compiled.
 */

struct SobelFilter;
struct SobelFilter_cosim;
struct SobelFilter_cycsim;
struct SobelFilter_rtl;

#ifdef BDW_COWARE
#include	"SobelFilter_coware.h"
#endif

#include "cynw_p2p.h"
#include "cyn_enums.h"


// Declaration of wrapper with BEH level ports

SC_MODULE(SobelFilter_wrapper)
{
public:

	sc_in< bool > i_clk;
	sc_in< bool > i_rst;
	cynw::cynw_p2p_base_in <sc_dt::sc_uint <(int)24 >, CYN::cyn_enum <(int)1 > > i_rgb;
	cynw::cynw_p2p_base_out <sc_dt::sc_uint <(int)8 >, CYN::cyn_enum <(int)1 > > o_newR;
	cynw::cynw_p2p_base_out <sc_dt::sc_uint <(int)8 >, CYN::cyn_enum <(int)1 > > o_newG;
	cynw::cynw_p2p_base_out <sc_dt::sc_uint <(int)8 >, CYN::cyn_enum <(int)1 > > o_newB;

    
    // These signals are used to connect structured ports or ports that need
    // type conversion to the RTL ports.
    
    
	enum Representation { BDWRep_None, BDWRep_Behavioral, BDWRep_RTL_C, BDWRep_RTL_HDL, BDWRep_Gates, BDWRep_CYC_HDL };
	static const char * simConfigName();
	static Representation lookupRepresentation( const char* instName );
	// create the netlist
    void InitInstances( );
    void InitThreads();

    // delete the netlist
    void DeleteInstances();

	void CloseTrace();
	void start_of_simulation();
	void end_of_simulation();


    // The following threads are used to connect structured ports to the actual
    // RTL ports.
    

	SC_HAS_PROCESS(SobelFilter_wrapper);

    	SobelFilter_wrapper( sc_module_name name = sc_module_name( sc_gen_unique_name("SobelFilter")) )
		: sc_module(name)
		  ,i_clk("i_clk")
		  	,i_rst("i_rst")
		  	,i_rgb("i_rgb")
		  	,o_newR("o_newR")
		  	,o_newG("o_newG")
		  	,o_newB("o_newB")
		  	

		  ,SobelFilter0(0), SobelFilter_cosim0(0), SobelFilter_rtl0(0), SobelFilter_cycsim0(0)
		

    {
        InitInstances( );
		InitThreads();
    }


    // destructor
    ~SobelFilter_wrapper()
    {
        DeleteInstances();

		CloseTrace();
    }

    bool isBEH() { return ( SobelFilter_wrapper::lookupRepresentation( name() ) == BDWRep_Behavioral ); }
    bool isRTL_C() { return ( SobelFilter_wrapper::lookupRepresentation( name() ) == BDWRep_RTL_C ); }
    bool isRTL_V() { return ( SobelFilter_wrapper::lookupRepresentation( name() ) == BDWRep_RTL_HDL ); }
    bool isGATES_V() { return ( SobelFilter_wrapper::lookupRepresentation( name() ) == BDWRep_Gates ); }
	bool isCosim() { return ( isRTL_V() || isGATES_V() ); }
    bool isCycsim() { return ( SobelFilter_wrapper::lookupRepresentation( name() ) == BDWRep_CYC_HDL ); }

	SobelFilter* behModule() { return SobelFilter0; }
	SobelFilter_cosim* cosimModule() { return SobelFilter_cosim0; }
	SobelFilter_cycsim* cycsimModule() { return SobelFilter_cycsim0; }
	SobelFilter_rtl* rtlModule() { return SobelFilter_rtl0; }

	SobelFilter* SobelFilter0;
	SobelFilter_cosim* SobelFilter_cosim0;
	SobelFilter_rtl* SobelFilter_rtl0;
	SobelFilter_cycsim* SobelFilter_cycsim0;
};

// Declaration of wrapper with RTL level ports

SC_MODULE(SobelFilter_wrapper_r)
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

    
    // These signals are used to connect structured ports or ports that need
    // type conversion to the RTL ports.
    
    
	enum Representation { BDWRep_None, BDWRep_Behavioral, BDWRep_RTL_C, BDWRep_RTL_HDL, BDWRep_Gates, BDWRep_CYC_HDL };

	static const char * simConfigName();
	static Representation lookupRepresentation( const char* instName );
	// create the netlist
    void InitInstances();
    void InitThreads();

    // delete the netlist
    void DeleteInstances();

	void CloseTrace();
	void start_of_simulation();
	void end_of_simulation();


    // The following threads are used to connect structured ports to the actual
    // RTL ports.
    

	SC_HAS_PROCESS(SobelFilter_wrapper_r);

	SobelFilter_wrapper_r( sc_module_name name = sc_module_name( sc_gen_unique_name("SobelFilter")) )
		: sc_module(name)
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
		  	

		  ,SobelFilter0(0), SobelFilter_cosim0(0), SobelFilter_rtl0(0), SobelFilter_cycsim0(0)
		

    {
        InitInstances();
        InitThreads();
		end_module();
    }


    // destructor
    ~SobelFilter_wrapper_r()
    {
        DeleteInstances();

		CloseTrace();
    }

    bool isBEH() { return ( SobelFilter_wrapper_r::lookupRepresentation( name() ) == BDWRep_Behavioral ); }
    bool isRTL_C() { return ( SobelFilter_wrapper_r::lookupRepresentation( name() ) == BDWRep_RTL_C ); }
    bool isRTL_V() { return ( SobelFilter_wrapper_r::lookupRepresentation( name() ) == BDWRep_RTL_HDL ); }
    bool isGATES_V() { return ( SobelFilter_wrapper_r::lookupRepresentation( name() ) == BDWRep_Gates ); }
	bool isCosim() { return ( isRTL_V() || isGATES_V() ); }
    bool isCycsim() { return ( SobelFilter_wrapper_r::lookupRepresentation( name() ) == BDWRep_CYC_HDL ); }

	SobelFilter* behModule() { return SobelFilter0; }
	SobelFilter_cosim* cosimModule() { return SobelFilter_cosim0; }
	SobelFilter_cycsim* cycsimModule() { return SobelFilter_cycsim0; }
	SobelFilter_rtl* rtlModule() { return SobelFilter_rtl0; }

protected:
	SobelFilter* SobelFilter0;
	SobelFilter_cosim* SobelFilter_cosim0;
	SobelFilter_rtl* SobelFilter_rtl0;
	SobelFilter_cycsim* SobelFilter_cycsim0;
};

#endif

/* Restore ioConfig define values for parent module. */

#endif /*  */
