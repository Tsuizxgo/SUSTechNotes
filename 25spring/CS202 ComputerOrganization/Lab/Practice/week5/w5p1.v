module risv_v (
    input wire [31:0] instruction,
    output reg [31:0]imm,
    output reg [6:0] opcode
);
    assign opcode = instruction[6:0];

    always @(*) begin
        case(opcode)
        7'b0000011: begin //r
        imm = 32'b0;
        end
        7'b0000111: begin //i
        imm= {20{instruction[31]},instruction[31:20]}
        end
        7'b0001111:begin //s
        imm= {20{instruction[31]},instruction[31:25],instruction[11:7]}
        end
        7'b0001011:begin //b
        //b比较特殊，只取到倒数第二位，所以倒数第一位要补0
        imm={19{instruction[31]},instruction[31],instruction[7],instruction[30:25],instruction[11:8],1'b0}
        end
        7'b0011011:begin //u
        imm={instruction[31:12],12'b0}
        end
        7'b0011111:begin //j
        //j比较特殊，也是只取到倒数第二位，所以倒数第一位要补0
        imm={11{instruction[31]},instruction[31],instruction[30:21],instruction[20],instruction[19:12],1'b0}
        end
        endcase
    end
endmodule