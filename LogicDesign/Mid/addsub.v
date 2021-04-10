module addsub
(
    M,
    A,
    B,
    S,
    Co,
    V
);

input M;
input [3:0] A;
input [3:0] B;
output [3:0] S;
output Co;
output V;

wire [3:0] C;
wire [3:0] Bm;
assign Bm = {B[3]^M, B[2]^M, B[1]^M, B[0]^M};
full_adder FA0 (A[0], Bm[0], M, S[0], C[0]);
full_adder FA1 (A[1], Bm[1], C[0], S[1], C[1]);
full_adder FA2 (A[2], Bm[2], C[1], S[2], C[2]);
full_adder FA3 (A[3], Bm[3], C[2], S[3], C[3]);
assign Co = C[3];
assign V = C[3]^C[2];

endmodule