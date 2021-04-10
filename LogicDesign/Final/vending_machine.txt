`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/30 22:33:26
// Design Name: 
// Module Name: vending_machine
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module vending_machine(
    clk,
    rst,
    drink_type,
    coin_type,
    vend,
    change
    );

input           clk;
input           rst;
input           drink_type;
input   [1:0]   coin_type;

output          vend;
output  [1:0]   change;

/******** Define your registers here ********/
reg             vend;
reg     [1:0]   change;
reg     [2:0]   state;
reg     [2:0]   nextstate;

// coin_type, change, state parameters
parameter [2:0] NO_COIN = 3'b000;    // No coin inserted
parameter [2:0] WON_050 = 3'b001;    // 50 Won coin inserted
parameter [2:0] WON_100 = 3'b010;    // 100 Won coin inserted
// only for state
parameter [2:0] WON_150 = 3'b011;    // 150 Won coin inserted
parameter [2:0] WON_200 = 3'b100;    // 200 Won coin inserted
parameter [2:0] WON_250 = 3'b101;    // 250 Won coin inserted
parameter [2:0] WON_300 = 3'b110;    // 300 Won coin inserted
parameter [2:0] WON_350 = 3'b111;    // 300 Won coin inserted

// drink_type parameters
parameter       COKE    = 1'b0;     // Coke     = 300 Won
parameter       SPRITE  = 1'b1;     // Sprite   = 250 Won


/******** Design your implementation here ********/
always @ (posedge clk or negedge rst)
begin
    if (!rst)
    begin
        state <= NO_COIN;
        vend <= 1'b0;
        change <= 2'b00;
    end
    else
        
    begin
        case (state)
            NO_COIN:
            begin
            vend <= 'b0;
            change <= 2'b00;
                case (coin_type)
                2'b00 : state<=NO_COIN;
                2'b01 : state<=WON_050;
                2'b10 : state<=WON_100;
                endcase
                end
                
            WON_050 : 
            case (coin_type)
                2'b00 : state<=WON_050;
                2'b01 : state<=WON_100;
                2'b10 : state<=WON_150;
                endcase
                
            WON_100 :
                case (coin_type)
                            2'b00 : state<=WON_100;
                            2'b01 : state<=WON_150;
                            2'b10 : state<=WON_200;
                endcase
              
            WON_150 :
                case (coin_type)
                            2'b00 : state<=WON_150;
                            2'b01 : state<=WON_200;
                            2'b10 : state<=WON_250;
                endcase
              
            WON_200 : 
            case (coin_type)
                            2'b00 : state<=WON_200;
                            2'b01 : state<=WON_250;
                            2'b10 : state<=WON_300;
                            endcase
                            
            WON_250:
            if(drink_type == COKE)
                begin
                case (coin_type)
                            2'b00 : state<=WON_250;
                            2'b01 : state<=WON_300;
                            2'b10 : state<=WON_350;
                            endcase
                end
            else if(drink_type == SPRITE)
                begin
                    vend <= 'b1;
                    change <= 2'b00;
                    state <= NO_COIN;
                    end
                            
            WON_300 :
                begin
                if(drink_type == COKE)
                begin
                    vend <= 1'b1;
                    change <= 2'b00;
                    state <= NO_COIN;
                    end
                else if(drink_type == SPRITE)
                begin
                    vend <= 'b1;
                    change <= 2'b01;
                    state <= NO_COIN;
                    end
                end
                
            WON_350 :
                begin
                if(drink_type == COKE)
                    begin
                    vend <= 'b1;
                    change <= 2'b01;
                    state <= NO_COIN;
                    end
                end
        endcase
    end
    end
endmodule
