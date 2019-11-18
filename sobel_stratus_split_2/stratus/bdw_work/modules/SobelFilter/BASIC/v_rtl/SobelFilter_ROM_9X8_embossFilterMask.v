// Generated by stratus_hls 17.21-s100  (88813.070850)
// Sat Nov 16 23:15:37 2019
// from ../SobelFilter.cpp

`timescale 1ps / 1ps

      
module SobelFilter_ROM_9X8_embossFilterMask(in1, out1, clk);

      input [3:0] in1;
      input clk;
      output [7:0] out1;
      reg [7:0] out1;
      reg[7:0] embossFilterMask[8:0];

         initial begin
            $readmemh("bdw_work/modules/SobelFilter/BASIC/SobelFilter_ROM_9X8_embossFilterMask_0.memh", embossFilterMask);
         end

         always @(posedge clk)
          begin :SobelFilter_ROM_9X8_embossFilterMask_thread_1
            if (in1 < 4'd09) begin
               out1 <= embossFilterMask[in1];
            end
         end


endmodule

