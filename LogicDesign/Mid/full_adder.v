module full_adder
(
    A,
    B,
    Ci,
    S,
    Co
    );
    
input A;
input B;
input Ci;
output S;
output Co;

wire C0, C1, S0;

half_adder UO (A, B, S0, C0);
half_adder U1 (S0, Ci, S, C1);

assign Co = C0 | C1;

endmodule