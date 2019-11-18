/****************************************************************************
*
*  Copyright (c) 2015, Cadence Design Systems. All Rights Reserved.
*
*  This file contains confidential information that may not be
*  distributed under any circumstances without the written permision
*  of Cadence Design Systems.
*
****************************************************************************/
/****************************************************************************
*
* This file is used to wrap the three different versions of the DUT
* block called "SobelFilter". By default, it will include the behavioral
* model. Otherwise, it will include the RTL C++ or the RTL Verilog
* depending on the definition of either of "RTL" or "COSIM".
*
****************************************************************************/

#if defined(CYNTHVLG)


#ifndef BDW_PORTS_ONLY
#define BDW_PORTS_ONLY 1
#endif


#include	"SobelFilter_rtl.cpp"

#else 

#if defined(BDW_HUB)

#include "esc.h"

#if defined(BDW_RTL) || defined(COWARE_RTL_SobelFilter)

#define BDW_AUTO_KNOWN 1 


#ifndef BDW_PORTS_ONLY
#define BDW_PORTS_ONLY 1
#endif


#undef SobelFilter
#define SobelFilter SobelFilter_rtl
#	include	"SobelFilter_rtl.cpp"
#undef SobelFilter


#ifdef BDW_PORTS_ONLY
#undef BDW_PORTS_ONLY
#endif



#elif defined(BDW_HOIST) 
#else

#endif
#ifdef BDW_COWARE
#include	"SobelFilter_coware.h"
#else
#include	"SobelFilter_cosim.h"
#endif

// include for cycle-accurate verilator simulation
#include    "SobelFilter_cycsim.h"



// Include the source for the behavioral model so it will be compiled.
#include	"../SobelFilter.cpp"


#define		SobelFilter_INTERNAL


#include	"SobelFilter_wrap.h"

// this global pointer indicates whether or not the Verilator cycsim wrapper is present
SobelFilter_cycsim* (*SobelFilter_cycsim_factory_p)() = 0;

#define MAX_SIMCONFIG_LENGTH 128

#if BDW_WRITEFSDB == 1

#if defined(NC_SYSTEMC) && defined(BDW_NCSC_VER) && BDW_NCSC_VER > 102
#include "fsdb_nc_mix.h"
#else
#include "fsdb_trace_file.h"
#endif 
#if BDW_USE_SCV
#include "scv.h"
#include "scv_tr_fsdb.h"
#endif

#endif /* BDW_WRITEFSDB */

inline void esc_open_fsdb_trace( const char *file_name = "systemc" );
inline void esc_close_fsdb_trace();
inline void esc_close_fsdb_scv_trace();

// The following threads are used to connect structured ports to the actual
// RTL ports

const char * SobelFilter_wrapper::simConfigName()
{
	static char defineBuf[MAX_SIMCONFIG_LENGTH];
	const char *simConfig = NULL;
	if ( qbhGetDefine( "BDW_SIM_CONFIG", defineBuf, MAX_SIMCONFIG_LENGTH ) == qbhOK )
	{
		simConfig = defineBuf;
	}
	else
	{
		simConfig = getenv( "BDW_SIM_CONFIG" );
	}

	if ( simConfig == NULL )
	{
		esc_report_error( esc_fatal, "BDW_SIM_CONFIG needs to be set" );
	}

	return simConfig;
}

enum SobelFilter_wrapper::Representation SobelFilter_wrapper::lookupRepresentation( const char* instName )
{
	const char *simConfig = simConfigName();

	if ( simConfig == NULL )
		return BDWRep_None;

	Representation result;

	qbhProjectHandle hProj;
	qbhError err = qbhGetCurrentProject( &hProj );
	if ( err == qbhErrorNoProject )
	{
		err = qbhOpenProject( "project.tcl", &hProj );

		if ( err != qbhOK )
		{
			esc_report_error( esc_fatal, "could not open project file %s",
							  "project.tcl" );
			return BDWRep_None;
		}
	}

	int iresult = 0;
	err = qbhGetRepresentation(hProj, "SobelFilter", simConfig, instName, &iresult );
	result = (Representation)iresult;

	if ( err == qbhOK )
		return result;

	// If this module isn't mentioned in the simConfig, assume it's behavioral.
	if ( err == qbhErrorNotFound ) {
		return BDWRep_Behavioral;
	} else if ( err == qbhErrorBadInstName ) {
		if (instName && *instName) {
			const char* leaf = strrchr( instName, '.' ) + 1;
			esc_report_error( esc_warning, "Instance names were specified for module '%s' in simConfig '%s', but they did not "
			                    "match the actal instance names in the RTL.  Try '%s' or '%s'. Simulating '%s' as BEH.\n",
								 "SobelFilter", simConfig, instName, leaf,  "SobelFilter" );
		}
		return BDWRep_Behavioral;
	}

    // If we couldn't get a license, then just exit.
    if ( err == qbhErrorNoLicense )
        exit(1);

	return BDWRep_None;
}

void SobelFilter_wrapper::InitInstances(  )
{
    enum SobelFilter_wrapper::Representation rep =
		SobelFilter_wrapper::lookupRepresentation( name() );

	esc_log_wrapper_inst( "SobelFilter" );
	esc_log_representation( "SobelFilter", name(), rep );

	

	switch ( rep )
	{
		case BDWRep_Gates:
		    SobelFilter_cosim0 = new SobelFilter_cosim( "SobelFilter" );

		    SobelFilter_cosim0->i_clk(i_clk);
		    SobelFilter_cosim0->i_rst(i_rst);
		    SobelFilter_cosim0->i_rgb_busy(i_rgb.busy);
		    SobelFilter_cosim0->i_rgb_vld(i_rgb.vld);
		    SobelFilter_cosim0->i_rgb_data(i_rgb.data);
		    SobelFilter_cosim0->o_newR_busy(o_newR.busy);
		    SobelFilter_cosim0->o_newR_vld(o_newR.vld);
		    SobelFilter_cosim0->o_newR_data(o_newR.data);
		    SobelFilter_cosim0->o_newG_busy(o_newG.busy);
		    SobelFilter_cosim0->o_newG_vld(o_newG.vld);
		    SobelFilter_cosim0->o_newG_data(o_newG.data);
		    SobelFilter_cosim0->o_newB_busy(o_newB.busy);
		    SobelFilter_cosim0->o_newB_vld(o_newB.vld);
		    SobelFilter_cosim0->o_newB_data(o_newB.data);

			break;
		case BDWRep_RTL_HDL:
		    SobelFilter_cosim0 = new SobelFilter_cosim( "SobelFilter" );

		    SobelFilter_cosim0->i_clk(i_clk);
		    SobelFilter_cosim0->i_rst(i_rst);
		    SobelFilter_cosim0->i_rgb_busy(i_rgb.busy);
		    SobelFilter_cosim0->i_rgb_vld(i_rgb.vld);
		    SobelFilter_cosim0->i_rgb_data(i_rgb.data);
		    SobelFilter_cosim0->o_newR_busy(o_newR.busy);
		    SobelFilter_cosim0->o_newR_vld(o_newR.vld);
		    SobelFilter_cosim0->o_newR_data(o_newR.data);
		    SobelFilter_cosim0->o_newG_busy(o_newG.busy);
		    SobelFilter_cosim0->o_newG_vld(o_newG.vld);
		    SobelFilter_cosim0->o_newG_data(o_newG.data);
		    SobelFilter_cosim0->o_newB_busy(o_newB.busy);
		    SobelFilter_cosim0->o_newB_vld(o_newB.vld);
		    SobelFilter_cosim0->o_newB_data(o_newB.data);

			break;
        case BDWRep_CYC_HDL:
            if ( SobelFilter_cycsim_factory_p )
                SobelFilter_cycsim0 = SobelFilter_cycsim_factory_p();
            else
            {
                esc_report_error( esc_fatal, "verilator_produced files not available for module SobelFilter");
                return;
            }

            esc_report_error( esc_note, " using verilator model for module \"SobelFilter\"");

		    SobelFilter_cycsim0->i_clk(i_clk);
		    SobelFilter_cycsim0->i_rst(i_rst);
		    SobelFilter_cycsim0->i_rgb_busy(i_rgb.busy);
		    SobelFilter_cycsim0->i_rgb_vld(i_rgb.vld);
		    SobelFilter_cycsim0->i_rgb_data(i_rgb.data);
		    SobelFilter_cycsim0->o_newR_busy(o_newR.busy);
		    SobelFilter_cycsim0->o_newR_vld(o_newR.vld);
		    SobelFilter_cycsim0->o_newR_data(o_newR.data);
		    SobelFilter_cycsim0->o_newG_busy(o_newG.busy);
		    SobelFilter_cycsim0->o_newG_vld(o_newG.vld);
		    SobelFilter_cycsim0->o_newG_data(o_newG.data);
		    SobelFilter_cycsim0->o_newB_busy(o_newB.busy);
		    SobelFilter_cycsim0->o_newB_vld(o_newB.vld);
		    SobelFilter_cycsim0->o_newB_data(o_newB.data);

			break;
#if defined(BDW_RTL) || defined(COWARE_RTL_SobelFilter)
		case BDWRep_RTL_C:
		    SobelFilter_rtl0 = new SobelFilter_rtl( "SobelFilter" );

		    SobelFilter_rtl0->i_clk(i_clk);
		    SobelFilter_rtl0->i_rst(i_rst);
		    SobelFilter_rtl0->i_rgb_busy(i_rgb.busy);
		    SobelFilter_rtl0->i_rgb_vld(i_rgb.vld);
		    SobelFilter_rtl0->i_rgb_data(i_rgb.data);
		    SobelFilter_rtl0->o_newR_busy(o_newR.busy);
		    SobelFilter_rtl0->o_newR_vld(o_newR.vld);
		    SobelFilter_rtl0->o_newR_data(o_newR.data);
		    SobelFilter_rtl0->o_newG_busy(o_newG.busy);
		    SobelFilter_rtl0->o_newG_vld(o_newG.vld);
		    SobelFilter_rtl0->o_newG_data(o_newG.data);
		    SobelFilter_rtl0->o_newB_busy(o_newB.busy);
		    SobelFilter_rtl0->o_newB_vld(o_newB.vld);
		    SobelFilter_rtl0->o_newB_data(o_newB.data);


			{
			const char *simConfig = SobelFilter_wrapper::simConfigName();
			
			if ( simConfig != NULL )
				{
				qbhProjectHandle hProj;
				qbhError err = qbhGetCurrentProject( &hProj );
				if ( err == qbhErrorNoProject )
				{
					err = qbhOpenProject( "project.tcl", &hProj );
			
					if ( err != qbhOK )
					{
						esc_report_error( esc_fatal, "could not open project file %s",
											  "project.tcl" );
							return;
					}
				}
			
				if ( esc_trace_is_enabled( esc_trace_vcd ) ) {
					esc_get_vcd_trace_file();
				}
				if ( esc_trace_is_enabled( esc_trace_fsdb ) ) {
					esc_get_fsdb_trace_file();
				}
				}
			}

			break;
#endif
		case BDWRep_Behavioral:
		    SobelFilter0 = new SobelFilter( "SobelFilter" );

		    SobelFilter0->i_clk(i_clk);
		    SobelFilter0->i_rst(i_rst);
		    SobelFilter0->i_rgb.busy(i_rgb.busy);
		    SobelFilter0->i_rgb.vld(i_rgb.vld);
		    SobelFilter0->i_rgb.data(i_rgb.data);
		    SobelFilter0->o_newR.busy(o_newR.busy);
		    SobelFilter0->o_newR.vld(o_newR.vld);
		    SobelFilter0->o_newR.data(o_newR.data);
		    SobelFilter0->o_newG.busy(o_newG.busy);
		    SobelFilter0->o_newG.vld(o_newG.vld);
		    SobelFilter0->o_newG.data(o_newG.data);
		    SobelFilter0->o_newB.busy(o_newB.busy);
		    SobelFilter0->o_newB.vld(o_newB.vld);
		    SobelFilter0->o_newB.data(o_newB.data);


			{
			const char *simConfig = SobelFilter_wrapper::simConfigName();
			
			if ( simConfig != NULL )
				{
				qbhProjectHandle hProj;
				qbhError err = qbhGetCurrentProject( &hProj );
				if ( err == qbhErrorNoProject )
				{
					err = qbhOpenProject( "project.tcl", &hProj );
			
					if ( err != qbhOK )
					{
						esc_report_error( esc_fatal, "could not open project file %s",
											  "project.tcl" );
							return;
					}
				}
			
				if ( esc_trace_is_enabled( esc_trace_vcd ) ) {
					esc_get_vcd_trace_file();
				}
				if ( esc_trace_is_enabled( esc_trace_fsdb ) ) {
					esc_get_fsdb_trace_file();
				}
				}
			}

			break;
		case BDWRep_None:
		default:
			esc_report_error( esc_error, "No representation could be determined for simulating instance %s. Please make sure that you used the right name string in the module constructor",
							  name() );
			break;
	}
}

void SobelFilter_wrapper::InitThreads()
{
	if ( !isBEH() )
	{
		
	}
}

void SobelFilter_wrapper::start_of_simulation()
{

#include <SobelFilter_trace.h>

    esc_multiple_writers_warning();
}

void SobelFilter_wrapper::CloseTrace()
{
	if ( esc_trace_is_enabled( esc_trace_vcd ) ) {
	esc_close_vcd_trace();
	}
	if ( esc_trace_is_enabled( esc_trace_fsdb ) ) {
		esc_close_fsdb_trace();
		if ( esc_trace_is_enabled( esc_trace_scv ) ) {
			esc_close_fsdb_scv_trace();
		}
	}
}

void SobelFilter_wrapper::end_of_simulation()
{
	CloseTrace();
}



void SobelFilter_wrapper::DeleteInstances()
{
    if (SobelFilter0)
    {
        delete SobelFilter0;
        SobelFilter0 = 0;
    }
    if (SobelFilter_cosim0)
    {
        delete SobelFilter_cosim0;
        SobelFilter_cosim0 = 0;
    }
    if (SobelFilter_cycsim0)
    {
        delete SobelFilter_cycsim0;
        SobelFilter_cycsim0 = 0;
    }
#if defined(BDW_RTL) || defined(COWARE_RTL_SobelFilter)
    if (SobelFilter_rtl0)
    {
        delete SobelFilter_rtl0;
        SobelFilter_rtl0 = 0;
    }
#endif
}

// The following threads are used to connect RTL ports to the actual
// structured ports

const char * SobelFilter_wrapper_r::simConfigName()
{
	static char defineBuf[MAX_SIMCONFIG_LENGTH];
	const char *simConfig = NULL;
	if ( qbhGetDefine( "BDW_SIM_CONFIG", defineBuf, MAX_SIMCONFIG_LENGTH ) == qbhOK )
	{
		simConfig = defineBuf;
	}
	else
	{
		simConfig = getenv( "BDW_SIM_CONFIG" );
	}

	if ( simConfig == NULL )
	{
		esc_report_error( esc_fatal, "BDW_SIM_CONFIG needs to be set" );
	}

	return simConfig;
}

enum SobelFilter_wrapper_r::Representation SobelFilter_wrapper_r::lookupRepresentation( const char* instName )
{
	const char *simConfig = simConfigName();

	if ( simConfig == NULL )
		return BDWRep_None;

	Representation result;

	qbhProjectHandle hProj;
	qbhError err = qbhGetCurrentProject( &hProj );
	if ( err == qbhErrorNoProject )
	{
		err = qbhOpenProject( "project.tcl", &hProj );

		if ( err != qbhOK )
		{
			esc_report_error( esc_fatal, "could not open project file %s",
							  "project.tcl" );
			return BDWRep_None;
		}
	}

	int iresult = 0;
	err = qbhGetRepresentation(hProj, "SobelFilter", simConfig, instName, &iresult );
	result = (Representation)iresult;

	if ( err == qbhOK )
		return result;

	// If this module isn't mentioned in the simConfig, assume it's behavioral.
	if ( err == qbhErrorNotFound )
		return BDWRep_Behavioral;

    // If we couldn't get a license, then just exit.
    if ( err == qbhErrorNoLicense )
        exit(1);

	return BDWRep_None;
}

void SobelFilter_wrapper_r::InitInstances()
{
    enum SobelFilter_wrapper_r::Representation rep =
		SobelFilter_wrapper_r::lookupRepresentation( name() );

	esc_log_wrapper_inst( "SobelFilter" );
	esc_log_representation( "SobelFilter", name(), rep );

	switch ( rep )
	{
		case BDWRep_Gates:
		    SobelFilter_cosim0 = new SobelFilter_cosim( "SobelFilter" );

		    SobelFilter_cosim0->i_clk(i_clk);
		    SobelFilter_cosim0->i_rst(i_rst);
		    SobelFilter_cosim0->i_rgb_busy(i_rgb_busy);
		    SobelFilter_cosim0->i_rgb_vld(i_rgb_vld);
		    SobelFilter_cosim0->i_rgb_data(i_rgb_data);
		    SobelFilter_cosim0->o_newR_busy(o_newR_busy);
		    SobelFilter_cosim0->o_newR_vld(o_newR_vld);
		    SobelFilter_cosim0->o_newR_data(o_newR_data);
		    SobelFilter_cosim0->o_newG_busy(o_newG_busy);
		    SobelFilter_cosim0->o_newG_vld(o_newG_vld);
		    SobelFilter_cosim0->o_newG_data(o_newG_data);
		    SobelFilter_cosim0->o_newB_busy(o_newB_busy);
		    SobelFilter_cosim0->o_newB_vld(o_newB_vld);
		    SobelFilter_cosim0->o_newB_data(o_newB_data);

			break;
		case BDWRep_RTL_HDL:
		    SobelFilter_cosim0 = new SobelFilter_cosim( "SobelFilter" );

		    SobelFilter_cosim0->i_clk(i_clk);
		    SobelFilter_cosim0->i_rst(i_rst);
		    SobelFilter_cosim0->i_rgb_busy(i_rgb_busy);
		    SobelFilter_cosim0->i_rgb_vld(i_rgb_vld);
		    SobelFilter_cosim0->i_rgb_data(i_rgb_data);
		    SobelFilter_cosim0->o_newR_busy(o_newR_busy);
		    SobelFilter_cosim0->o_newR_vld(o_newR_vld);
		    SobelFilter_cosim0->o_newR_data(o_newR_data);
		    SobelFilter_cosim0->o_newG_busy(o_newG_busy);
		    SobelFilter_cosim0->o_newG_vld(o_newG_vld);
		    SobelFilter_cosim0->o_newG_data(o_newG_data);
		    SobelFilter_cosim0->o_newB_busy(o_newB_busy);
		    SobelFilter_cosim0->o_newB_vld(o_newB_vld);
		    SobelFilter_cosim0->o_newB_data(o_newB_data);

			break;
        case BDWRep_CYC_HDL:
            if ( SobelFilter_cycsim_factory_p )
                SobelFilter_cycsim0 = SobelFilter_cycsim_factory_p();
            else
            {
                esc_report_error( esc_fatal, "verilator_produced files not available for module SobelFilter");
                return;
            }

            esc_report_error( esc_note, " using verilator model for module \"SobelFilter\"");

		    SobelFilter_cycsim0->i_clk(i_clk);
		    SobelFilter_cycsim0->i_rst(i_rst);
		    SobelFilter_cycsim0->i_rgb_busy(i_rgb_busy);
		    SobelFilter_cycsim0->i_rgb_vld(i_rgb_vld);
		    SobelFilter_cycsim0->i_rgb_data(i_rgb_data);
		    SobelFilter_cycsim0->o_newR_busy(o_newR_busy);
		    SobelFilter_cycsim0->o_newR_vld(o_newR_vld);
		    SobelFilter_cycsim0->o_newR_data(o_newR_data);
		    SobelFilter_cycsim0->o_newG_busy(o_newG_busy);
		    SobelFilter_cycsim0->o_newG_vld(o_newG_vld);
		    SobelFilter_cycsim0->o_newG_data(o_newG_data);
		    SobelFilter_cycsim0->o_newB_busy(o_newB_busy);
		    SobelFilter_cycsim0->o_newB_vld(o_newB_vld);
		    SobelFilter_cycsim0->o_newB_data(o_newB_data);

			break;
#if defined(BDW_RTL) || defined(COWARE_RTL_SobelFilter)
		case BDWRep_RTL_C:
		    SobelFilter_rtl0 = new SobelFilter_rtl( "SobelFilter" );

		    SobelFilter_rtl0->i_clk(i_clk);
		    SobelFilter_rtl0->i_rst(i_rst);
		    SobelFilter_rtl0->i_rgb_busy(i_rgb_busy);
		    SobelFilter_rtl0->i_rgb_vld(i_rgb_vld);
		    SobelFilter_rtl0->i_rgb_data(i_rgb_data);
		    SobelFilter_rtl0->o_newR_busy(o_newR_busy);
		    SobelFilter_rtl0->o_newR_vld(o_newR_vld);
		    SobelFilter_rtl0->o_newR_data(o_newR_data);
		    SobelFilter_rtl0->o_newG_busy(o_newG_busy);
		    SobelFilter_rtl0->o_newG_vld(o_newG_vld);
		    SobelFilter_rtl0->o_newG_data(o_newG_data);
		    SobelFilter_rtl0->o_newB_busy(o_newB_busy);
		    SobelFilter_rtl0->o_newB_vld(o_newB_vld);
		    SobelFilter_rtl0->o_newB_data(o_newB_data);


			{
			const char *simConfig = SobelFilter_wrapper::simConfigName();
			
			if ( simConfig != NULL )
				{
				qbhProjectHandle hProj;
				qbhError err = qbhGetCurrentProject( &hProj );
				if ( err == qbhErrorNoProject )
				{
					err = qbhOpenProject( "project.tcl", &hProj );
			
					if ( err != qbhOK )
					{
						esc_report_error( esc_fatal, "could not open project file %s",
											  "project.tcl" );
							return;
					}
				}
			
				if ( esc_trace_is_enabled( esc_trace_vcd ) ) {
					esc_get_vcd_trace_file();
				}
				if ( esc_trace_is_enabled( esc_trace_fsdb ) ) {
					esc_get_fsdb_trace_file();
				}
				}
			}

			break;
#endif
		case BDWRep_Behavioral:
		    SobelFilter0 = new SobelFilter( "SobelFilter" );

		    SobelFilter0->i_clk(i_clk);
		    SobelFilter0->i_rst(i_rst);
		    SobelFilter0->i_rgb.busy(i_rgb_busy);
		    SobelFilter0->i_rgb.vld(i_rgb_vld);
		    SobelFilter0->i_rgb.data(i_rgb_data);
		    SobelFilter0->o_newR.busy(o_newR_busy);
		    SobelFilter0->o_newR.vld(o_newR_vld);
		    SobelFilter0->o_newR.data(o_newR_data);
		    SobelFilter0->o_newG.busy(o_newG_busy);
		    SobelFilter0->o_newG.vld(o_newG_vld);
		    SobelFilter0->o_newG.data(o_newG_data);
		    SobelFilter0->o_newB.busy(o_newB_busy);
		    SobelFilter0->o_newB.vld(o_newB_vld);
		    SobelFilter0->o_newB.data(o_newB_data);


			{
			const char *simConfig = SobelFilter_wrapper::simConfigName();
			
			if ( simConfig != NULL )
				{
				qbhProjectHandle hProj;
				qbhError err = qbhGetCurrentProject( &hProj );
				if ( err == qbhErrorNoProject )
				{
					err = qbhOpenProject( "project.tcl", &hProj );
			
					if ( err != qbhOK )
					{
						esc_report_error( esc_fatal, "could not open project file %s",
											  "project.tcl" );
							return;
					}
				}
			
				if ( esc_trace_is_enabled( esc_trace_vcd ) ) {
					esc_get_vcd_trace_file();
				}
				if ( esc_trace_is_enabled( esc_trace_fsdb ) ) {
					esc_get_fsdb_trace_file();
				}
				}
			}

			break;
		case BDWRep_None:
		default:
			esc_report_error( esc_error, "No representation could be determined for simulating instance %s. Please make sure that you used the right name string in the module constructor",
							  name() );
			break;
	}
}

void SobelFilter_wrapper_r::InitThreads()
{
	if ( isBEH() ) 
	{
		
	}
}

void SobelFilter_wrapper_r::start_of_simulation()
{

#include <SobelFilter_trace.h>

    esc_multiple_writers_warning();
}

void SobelFilter_wrapper_r::CloseTrace()
{
	if ( esc_trace_is_enabled( esc_trace_vcd ) ) {
	esc_close_vcd_trace();
	}
	if ( esc_trace_is_enabled( esc_trace_fsdb ) ) {
		esc_close_fsdb_trace();
		if ( esc_trace_is_enabled( esc_trace_scv ) ) {
			esc_close_fsdb_scv_trace();
		}
	}
}

void SobelFilter_wrapper_r::end_of_simulation()
{
	CloseTrace();
}



void SobelFilter_wrapper_r::DeleteInstances()
{
    if (SobelFilter0)
    {
        delete SobelFilter0;
        SobelFilter0 = 0;
    }
    if (SobelFilter_cosim0)
    {
        delete SobelFilter_cosim0;
        SobelFilter_cosim0 = 0;
    }
    if (SobelFilter_cycsim0)
    {
        delete SobelFilter_cycsim0;
        SobelFilter_cycsim0 = 0;
    }
#if defined(BDW_RTL) || defined(COWARE_RTL_SobelFilter)
    if (SobelFilter_rtl0)
    {
        delete SobelFilter_rtl0;
        SobelFilter_rtl0 = 0;
    }
#endif
}

#if BDW_WRITEFSDB == 1

inline void esc_open_fsdb_trace( const char *file_name  )
{
#if defined(NC_SYSTEMC) && defined(BDW_NCSC_VER) && BDW_NCSC_VER > 102
    fsdbDumpfile(file_name);
# else
	sc_trace_file *fsdb_file;

	// SystemC suffixes .fsdb to filenames automatically. Make sure
	// that doesn't get tacked onto a filename that already has the suffix.
	if ( strrchr( file_name, '.' ) != NULL )
	{
		char *trunc_file_name = new char[strlen(file_name)+1];
		strcpy( trunc_file_name, file_name );

		fsdb_file = new fsdb_trace_file( trunc_file_name );
		esc_set_trace_file( fsdb_file, esc_trace_fsdb );

		delete trunc_file_name;
	}
	else
	{
		fsdb_file = new fsdb_trace_file( file_name );
		esc_set_trace_file( fsdb_file, esc_trace_fsdb );
	}
#endif

//
// Novas's SystemC wrapper doesn't have a way to set the time unit as of SystemC 2.1v1.
//
//		((fsdb_trace_file*)fsdb_file)->sc_set_fsdb_time_unit( -12 );
}

inline void esc_close_fsdb_trace()
{
#if ! defined(NC_SYSTEMC) | ! defined(BDW_NCSC_VER) | BDW_NCSC_VER <= 102
	fsdb_trace_file * fsdb_file =
		(fsdb_trace_file *)esc_trace_file( esc_trace_fsdb );

	if ( fsdb_file != NULL )
	{
		fsdb_file->CloseFile();
		delete fsdb_file;
		esc_set_trace_file( NULL, esc_trace_fsdb );
	}
#endif
}

#else

inline void esc_open_fsdb_trace( const char *file_name )
{
}

inline void esc_close_fsdb_trace()
{
}

#endif

#if BDW_USE_SCV && BDW_WRITEFSDB == 1
static scv_tr_db* local_fsdb_scv_db = 0;

inline void esc_open_fsdb_scv_trace( const char *file_name  )
{
	// Start SCV logging to FSDB if there is not already a database setup.
    if (!esc_get_scv_tr_db() && esc_trace_is_enabled(esc_trace_scv) )
	{
		scv_startup();
		scv_tr_fsdb_init();

		char* scv_file_name = new char[strlen(file_name) + 1];
		strcpy( scv_file_name, file_name );
		char* fsdb_suffix = strstr( scv_file_name, ".fsdb" );
		if (fsdb_suffix)
			*fsdb_suffix = 0;
		local_fsdb_scv_db = new scv_tr_db(scv_file_name);

		delete [] scv_file_name;
		esc_set_scv_tr_db(local_fsdb_scv_db);
		scv_tr_db::set_default_db(local_fsdb_scv_db);
		local_fsdb_scv_db->set_recording(true);
	}
}

inline void esc_close_fsdb_scv_trace()
{
    if ( local_fsdb_scv_db && (local_fsdb_scv_db == esc_get_scv_tr_db() ) ) 
	{
		delete local_fsdb_scv_db;
		local_fsdb_scv_db = 0;
		esc_set_scv_tr_db(0);
	}
}
#else 
inline void esc_open_fsdb_scv_trace( const char *file_name  )
{
}

inline void esc_close_fsdb_scv_trace()
{
}

#endif

class SobelFilter_wrapper_fsdb_opener {
public:
	SobelFilter_wrapper_fsdb_opener() {
		esc_set_open_fsdb_trace( esc_open_fsdb_trace );
		esc_set_open_fsdb_scv_trace( esc_open_fsdb_scv_trace );
	}
};

static SobelFilter_wrapper_fsdb_opener
  SobelFilter_wrapper_fsdb_opener_inst;

#else

// Visible to uses of the wrapper outside of the BDW environment.
// Only behavioral SystemC simulation is supported.


// Include the source for the behavioral model so it will be compiled.
#include	"../SobelFilter.cpp"

#define		SobelFilter_INTERNAL


#include	"SobelFilter_wrap.h"

const char * SobelFilter_wrapper::simConfigName()
{
  return "";
}

enum SobelFilter_wrapper::Representation SobelFilter_wrapper::lookupRepresentation( const char* instName )
{
  return BDWRep_Behavioral;
}

void SobelFilter_wrapper::InitInstances( sc_core::sc_module_name n )
{
	SobelFilter0 = new SobelFilter( "SobelFilter" );

	SobelFilter0->i_clk(i_clk);
	SobelFilter0->i_rst(i_rst);
	SobelFilter0->i_rgb.busy(i_rgb.busy);
	SobelFilter0->i_rgb.vld(i_rgb.vld);
	SobelFilter0->i_rgb.data(i_rgb.data);
	SobelFilter0->o_newR.busy(o_newR.busy);
	SobelFilter0->o_newR.vld(o_newR.vld);
	SobelFilter0->o_newR.data(o_newR.data);
	SobelFilter0->o_newG.busy(o_newG.busy);
	SobelFilter0->o_newG.vld(o_newG.vld);
	SobelFilter0->o_newG.data(o_newG.data);
	SobelFilter0->o_newB.busy(o_newB.busy);
	SobelFilter0->o_newB.vld(o_newB.vld);
	SobelFilter0->o_newB.data(o_newB.data);

}

void SobelFilter_wrapper::InitThreads()
{
}

void SobelFilter_wrapper::CloseTrace()
{
}

void SobelFilter_wrapper::DeleteInstances()
{
    if (SobelFilter0)
    {
        delete SobelFilter0;
        SobelFilter0 = 0;
    }
}

void SobelFilter_wrapper::start_of_simulation()
{
}

void SobelFilter_wrapper::end_of_simulation()
{
}



inline void esc_open_fsdb_trace( const char *file_name )
{
}

inline void esc_close_fsdb_trace()
{
}


inline void esc_open_fsdb_scv_trace( const char *file_name  )
{
}

inline void esc_close_fsdb_scv_trace()
{
}

class SobelFilter_wrapper_fsdb_opener {
public:
	SobelFilter_wrapper_fsdb_opener() {
	}
};

static SobelFilter_wrapper_fsdb_opener
  SobelFilter_wrapper_fsdb_opener_inst;

#endif

#endif
