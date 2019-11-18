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


#include	"SobelFilter_sc_wrap.h"
#include	"SobelFilter_sc_foreign.h"

// The following threads are used to connect structured ports to the actual
// RTL ports

void SobelFilter_wrapper::InitInstances(  )
{
	
            
    SobelFilter0 = new SobelFilter( "SobelFilter" );

    SobelFilter0->i_clk(i_clk);
    SobelFilter0->i_rst(i_rst);
    SobelFilter0->i_rgb_busy(i_rgb.busy);
    SobelFilter0->i_rgb_vld(i_rgb.vld);
    SobelFilter0->i_rgb_data(i_rgb.data);
    SobelFilter0->o_newR_busy(o_newR.busy);
    SobelFilter0->o_newR_vld(o_newR.vld);
    SobelFilter0->o_newR_data(o_newR.data);
    SobelFilter0->o_newG_busy(o_newG.busy);
    SobelFilter0->o_newG_vld(o_newG.vld);
    SobelFilter0->o_newG_data(o_newG.data);
    SobelFilter0->o_newB_busy(o_newB.busy);
    SobelFilter0->o_newB_vld(o_newB.vld);
    SobelFilter0->o_newB_data(o_newB.data);

}

void SobelFilter_wrapper::InitThreads()
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

