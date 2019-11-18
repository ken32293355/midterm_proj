	if ( esc_trace_is_enabled( esc_trace_vcd ) ) {
		if ( SobelFilter0 != NULL ) {
			esc_trace_signal( &SobelFilter0->i_clk, ( std::string(name()) + std::string( ".SobelFilter.i_clk" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->i_rst, ( std::string(name()) + std::string( ".SobelFilter.i_rst" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->i_rgb.busy, ( std::string(name()) + std::string( ".SobelFilter.i_rgb.busy" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->i_rgb.vld, ( std::string(name()) + std::string( ".SobelFilter.i_rgb.vld" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->i_rgb.data, ( std::string(name()) + std::string( ".SobelFilter.i_rgb.data" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newR.busy, ( std::string(name()) + std::string( ".SobelFilter.o_newR.busy" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newR.vld, ( std::string(name()) + std::string( ".SobelFilter.o_newR.vld" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newR.data, ( std::string(name()) + std::string( ".SobelFilter.o_newR.data" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newG.busy, ( std::string(name()) + std::string( ".SobelFilter.o_newG.busy" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newG.vld, ( std::string(name()) + std::string( ".SobelFilter.o_newG.vld" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newG.data, ( std::string(name()) + std::string( ".SobelFilter.o_newG.data" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newB.busy, ( std::string(name()) + std::string( ".SobelFilter.o_newB.busy" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newB.vld, ( std::string(name()) + std::string( ".SobelFilter.o_newB.vld" ) ).c_str(), esc_trace_vcd );
			esc_trace_signal( &SobelFilter0->o_newB.data, ( std::string(name()) + std::string( ".SobelFilter.o_newB.data" ) ).c_str(), esc_trace_vcd );
		}
	}
	if ( esc_trace_is_enabled( esc_trace_fsdb ) ) {
		if ( SobelFilter0 != NULL ) {
			esc_trace_signal( &SobelFilter0->i_clk, ( std::string(name()) + std::string( ".SobelFilter.i_clk" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->i_rst, ( std::string(name()) + std::string( ".SobelFilter.i_rst" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->i_rgb.busy, ( std::string(name()) + std::string( ".SobelFilter.i_rgb.busy" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->i_rgb.vld, ( std::string(name()) + std::string( ".SobelFilter.i_rgb.vld" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->i_rgb.data, ( std::string(name()) + std::string( ".SobelFilter.i_rgb.data" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newR.busy, ( std::string(name()) + std::string( ".SobelFilter.o_newR.busy" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newR.vld, ( std::string(name()) + std::string( ".SobelFilter.o_newR.vld" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newR.data, ( std::string(name()) + std::string( ".SobelFilter.o_newR.data" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newG.busy, ( std::string(name()) + std::string( ".SobelFilter.o_newG.busy" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newG.vld, ( std::string(name()) + std::string( ".SobelFilter.o_newG.vld" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newG.data, ( std::string(name()) + std::string( ".SobelFilter.o_newG.data" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newB.busy, ( std::string(name()) + std::string( ".SobelFilter.o_newB.busy" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newB.vld, ( std::string(name()) + std::string( ".SobelFilter.o_newB.vld" ) ).c_str(), esc_trace_fsdb );
			esc_trace_signal( &SobelFilter0->o_newB.data, ( std::string(name()) + std::string( ".SobelFilter.o_newB.data" ) ).c_str(), esc_trace_fsdb );
		}
	}
