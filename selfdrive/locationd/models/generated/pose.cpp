#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3875089391013904122) {
   out_3875089391013904122[0] = delta_x[0] + nom_x[0];
   out_3875089391013904122[1] = delta_x[1] + nom_x[1];
   out_3875089391013904122[2] = delta_x[2] + nom_x[2];
   out_3875089391013904122[3] = delta_x[3] + nom_x[3];
   out_3875089391013904122[4] = delta_x[4] + nom_x[4];
   out_3875089391013904122[5] = delta_x[5] + nom_x[5];
   out_3875089391013904122[6] = delta_x[6] + nom_x[6];
   out_3875089391013904122[7] = delta_x[7] + nom_x[7];
   out_3875089391013904122[8] = delta_x[8] + nom_x[8];
   out_3875089391013904122[9] = delta_x[9] + nom_x[9];
   out_3875089391013904122[10] = delta_x[10] + nom_x[10];
   out_3875089391013904122[11] = delta_x[11] + nom_x[11];
   out_3875089391013904122[12] = delta_x[12] + nom_x[12];
   out_3875089391013904122[13] = delta_x[13] + nom_x[13];
   out_3875089391013904122[14] = delta_x[14] + nom_x[14];
   out_3875089391013904122[15] = delta_x[15] + nom_x[15];
   out_3875089391013904122[16] = delta_x[16] + nom_x[16];
   out_3875089391013904122[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_528120661788585315) {
   out_528120661788585315[0] = -nom_x[0] + true_x[0];
   out_528120661788585315[1] = -nom_x[1] + true_x[1];
   out_528120661788585315[2] = -nom_x[2] + true_x[2];
   out_528120661788585315[3] = -nom_x[3] + true_x[3];
   out_528120661788585315[4] = -nom_x[4] + true_x[4];
   out_528120661788585315[5] = -nom_x[5] + true_x[5];
   out_528120661788585315[6] = -nom_x[6] + true_x[6];
   out_528120661788585315[7] = -nom_x[7] + true_x[7];
   out_528120661788585315[8] = -nom_x[8] + true_x[8];
   out_528120661788585315[9] = -nom_x[9] + true_x[9];
   out_528120661788585315[10] = -nom_x[10] + true_x[10];
   out_528120661788585315[11] = -nom_x[11] + true_x[11];
   out_528120661788585315[12] = -nom_x[12] + true_x[12];
   out_528120661788585315[13] = -nom_x[13] + true_x[13];
   out_528120661788585315[14] = -nom_x[14] + true_x[14];
   out_528120661788585315[15] = -nom_x[15] + true_x[15];
   out_528120661788585315[16] = -nom_x[16] + true_x[16];
   out_528120661788585315[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2615398431533649975) {
   out_2615398431533649975[0] = 1.0;
   out_2615398431533649975[1] = 0.0;
   out_2615398431533649975[2] = 0.0;
   out_2615398431533649975[3] = 0.0;
   out_2615398431533649975[4] = 0.0;
   out_2615398431533649975[5] = 0.0;
   out_2615398431533649975[6] = 0.0;
   out_2615398431533649975[7] = 0.0;
   out_2615398431533649975[8] = 0.0;
   out_2615398431533649975[9] = 0.0;
   out_2615398431533649975[10] = 0.0;
   out_2615398431533649975[11] = 0.0;
   out_2615398431533649975[12] = 0.0;
   out_2615398431533649975[13] = 0.0;
   out_2615398431533649975[14] = 0.0;
   out_2615398431533649975[15] = 0.0;
   out_2615398431533649975[16] = 0.0;
   out_2615398431533649975[17] = 0.0;
   out_2615398431533649975[18] = 0.0;
   out_2615398431533649975[19] = 1.0;
   out_2615398431533649975[20] = 0.0;
   out_2615398431533649975[21] = 0.0;
   out_2615398431533649975[22] = 0.0;
   out_2615398431533649975[23] = 0.0;
   out_2615398431533649975[24] = 0.0;
   out_2615398431533649975[25] = 0.0;
   out_2615398431533649975[26] = 0.0;
   out_2615398431533649975[27] = 0.0;
   out_2615398431533649975[28] = 0.0;
   out_2615398431533649975[29] = 0.0;
   out_2615398431533649975[30] = 0.0;
   out_2615398431533649975[31] = 0.0;
   out_2615398431533649975[32] = 0.0;
   out_2615398431533649975[33] = 0.0;
   out_2615398431533649975[34] = 0.0;
   out_2615398431533649975[35] = 0.0;
   out_2615398431533649975[36] = 0.0;
   out_2615398431533649975[37] = 0.0;
   out_2615398431533649975[38] = 1.0;
   out_2615398431533649975[39] = 0.0;
   out_2615398431533649975[40] = 0.0;
   out_2615398431533649975[41] = 0.0;
   out_2615398431533649975[42] = 0.0;
   out_2615398431533649975[43] = 0.0;
   out_2615398431533649975[44] = 0.0;
   out_2615398431533649975[45] = 0.0;
   out_2615398431533649975[46] = 0.0;
   out_2615398431533649975[47] = 0.0;
   out_2615398431533649975[48] = 0.0;
   out_2615398431533649975[49] = 0.0;
   out_2615398431533649975[50] = 0.0;
   out_2615398431533649975[51] = 0.0;
   out_2615398431533649975[52] = 0.0;
   out_2615398431533649975[53] = 0.0;
   out_2615398431533649975[54] = 0.0;
   out_2615398431533649975[55] = 0.0;
   out_2615398431533649975[56] = 0.0;
   out_2615398431533649975[57] = 1.0;
   out_2615398431533649975[58] = 0.0;
   out_2615398431533649975[59] = 0.0;
   out_2615398431533649975[60] = 0.0;
   out_2615398431533649975[61] = 0.0;
   out_2615398431533649975[62] = 0.0;
   out_2615398431533649975[63] = 0.0;
   out_2615398431533649975[64] = 0.0;
   out_2615398431533649975[65] = 0.0;
   out_2615398431533649975[66] = 0.0;
   out_2615398431533649975[67] = 0.0;
   out_2615398431533649975[68] = 0.0;
   out_2615398431533649975[69] = 0.0;
   out_2615398431533649975[70] = 0.0;
   out_2615398431533649975[71] = 0.0;
   out_2615398431533649975[72] = 0.0;
   out_2615398431533649975[73] = 0.0;
   out_2615398431533649975[74] = 0.0;
   out_2615398431533649975[75] = 0.0;
   out_2615398431533649975[76] = 1.0;
   out_2615398431533649975[77] = 0.0;
   out_2615398431533649975[78] = 0.0;
   out_2615398431533649975[79] = 0.0;
   out_2615398431533649975[80] = 0.0;
   out_2615398431533649975[81] = 0.0;
   out_2615398431533649975[82] = 0.0;
   out_2615398431533649975[83] = 0.0;
   out_2615398431533649975[84] = 0.0;
   out_2615398431533649975[85] = 0.0;
   out_2615398431533649975[86] = 0.0;
   out_2615398431533649975[87] = 0.0;
   out_2615398431533649975[88] = 0.0;
   out_2615398431533649975[89] = 0.0;
   out_2615398431533649975[90] = 0.0;
   out_2615398431533649975[91] = 0.0;
   out_2615398431533649975[92] = 0.0;
   out_2615398431533649975[93] = 0.0;
   out_2615398431533649975[94] = 0.0;
   out_2615398431533649975[95] = 1.0;
   out_2615398431533649975[96] = 0.0;
   out_2615398431533649975[97] = 0.0;
   out_2615398431533649975[98] = 0.0;
   out_2615398431533649975[99] = 0.0;
   out_2615398431533649975[100] = 0.0;
   out_2615398431533649975[101] = 0.0;
   out_2615398431533649975[102] = 0.0;
   out_2615398431533649975[103] = 0.0;
   out_2615398431533649975[104] = 0.0;
   out_2615398431533649975[105] = 0.0;
   out_2615398431533649975[106] = 0.0;
   out_2615398431533649975[107] = 0.0;
   out_2615398431533649975[108] = 0.0;
   out_2615398431533649975[109] = 0.0;
   out_2615398431533649975[110] = 0.0;
   out_2615398431533649975[111] = 0.0;
   out_2615398431533649975[112] = 0.0;
   out_2615398431533649975[113] = 0.0;
   out_2615398431533649975[114] = 1.0;
   out_2615398431533649975[115] = 0.0;
   out_2615398431533649975[116] = 0.0;
   out_2615398431533649975[117] = 0.0;
   out_2615398431533649975[118] = 0.0;
   out_2615398431533649975[119] = 0.0;
   out_2615398431533649975[120] = 0.0;
   out_2615398431533649975[121] = 0.0;
   out_2615398431533649975[122] = 0.0;
   out_2615398431533649975[123] = 0.0;
   out_2615398431533649975[124] = 0.0;
   out_2615398431533649975[125] = 0.0;
   out_2615398431533649975[126] = 0.0;
   out_2615398431533649975[127] = 0.0;
   out_2615398431533649975[128] = 0.0;
   out_2615398431533649975[129] = 0.0;
   out_2615398431533649975[130] = 0.0;
   out_2615398431533649975[131] = 0.0;
   out_2615398431533649975[132] = 0.0;
   out_2615398431533649975[133] = 1.0;
   out_2615398431533649975[134] = 0.0;
   out_2615398431533649975[135] = 0.0;
   out_2615398431533649975[136] = 0.0;
   out_2615398431533649975[137] = 0.0;
   out_2615398431533649975[138] = 0.0;
   out_2615398431533649975[139] = 0.0;
   out_2615398431533649975[140] = 0.0;
   out_2615398431533649975[141] = 0.0;
   out_2615398431533649975[142] = 0.0;
   out_2615398431533649975[143] = 0.0;
   out_2615398431533649975[144] = 0.0;
   out_2615398431533649975[145] = 0.0;
   out_2615398431533649975[146] = 0.0;
   out_2615398431533649975[147] = 0.0;
   out_2615398431533649975[148] = 0.0;
   out_2615398431533649975[149] = 0.0;
   out_2615398431533649975[150] = 0.0;
   out_2615398431533649975[151] = 0.0;
   out_2615398431533649975[152] = 1.0;
   out_2615398431533649975[153] = 0.0;
   out_2615398431533649975[154] = 0.0;
   out_2615398431533649975[155] = 0.0;
   out_2615398431533649975[156] = 0.0;
   out_2615398431533649975[157] = 0.0;
   out_2615398431533649975[158] = 0.0;
   out_2615398431533649975[159] = 0.0;
   out_2615398431533649975[160] = 0.0;
   out_2615398431533649975[161] = 0.0;
   out_2615398431533649975[162] = 0.0;
   out_2615398431533649975[163] = 0.0;
   out_2615398431533649975[164] = 0.0;
   out_2615398431533649975[165] = 0.0;
   out_2615398431533649975[166] = 0.0;
   out_2615398431533649975[167] = 0.0;
   out_2615398431533649975[168] = 0.0;
   out_2615398431533649975[169] = 0.0;
   out_2615398431533649975[170] = 0.0;
   out_2615398431533649975[171] = 1.0;
   out_2615398431533649975[172] = 0.0;
   out_2615398431533649975[173] = 0.0;
   out_2615398431533649975[174] = 0.0;
   out_2615398431533649975[175] = 0.0;
   out_2615398431533649975[176] = 0.0;
   out_2615398431533649975[177] = 0.0;
   out_2615398431533649975[178] = 0.0;
   out_2615398431533649975[179] = 0.0;
   out_2615398431533649975[180] = 0.0;
   out_2615398431533649975[181] = 0.0;
   out_2615398431533649975[182] = 0.0;
   out_2615398431533649975[183] = 0.0;
   out_2615398431533649975[184] = 0.0;
   out_2615398431533649975[185] = 0.0;
   out_2615398431533649975[186] = 0.0;
   out_2615398431533649975[187] = 0.0;
   out_2615398431533649975[188] = 0.0;
   out_2615398431533649975[189] = 0.0;
   out_2615398431533649975[190] = 1.0;
   out_2615398431533649975[191] = 0.0;
   out_2615398431533649975[192] = 0.0;
   out_2615398431533649975[193] = 0.0;
   out_2615398431533649975[194] = 0.0;
   out_2615398431533649975[195] = 0.0;
   out_2615398431533649975[196] = 0.0;
   out_2615398431533649975[197] = 0.0;
   out_2615398431533649975[198] = 0.0;
   out_2615398431533649975[199] = 0.0;
   out_2615398431533649975[200] = 0.0;
   out_2615398431533649975[201] = 0.0;
   out_2615398431533649975[202] = 0.0;
   out_2615398431533649975[203] = 0.0;
   out_2615398431533649975[204] = 0.0;
   out_2615398431533649975[205] = 0.0;
   out_2615398431533649975[206] = 0.0;
   out_2615398431533649975[207] = 0.0;
   out_2615398431533649975[208] = 0.0;
   out_2615398431533649975[209] = 1.0;
   out_2615398431533649975[210] = 0.0;
   out_2615398431533649975[211] = 0.0;
   out_2615398431533649975[212] = 0.0;
   out_2615398431533649975[213] = 0.0;
   out_2615398431533649975[214] = 0.0;
   out_2615398431533649975[215] = 0.0;
   out_2615398431533649975[216] = 0.0;
   out_2615398431533649975[217] = 0.0;
   out_2615398431533649975[218] = 0.0;
   out_2615398431533649975[219] = 0.0;
   out_2615398431533649975[220] = 0.0;
   out_2615398431533649975[221] = 0.0;
   out_2615398431533649975[222] = 0.0;
   out_2615398431533649975[223] = 0.0;
   out_2615398431533649975[224] = 0.0;
   out_2615398431533649975[225] = 0.0;
   out_2615398431533649975[226] = 0.0;
   out_2615398431533649975[227] = 0.0;
   out_2615398431533649975[228] = 1.0;
   out_2615398431533649975[229] = 0.0;
   out_2615398431533649975[230] = 0.0;
   out_2615398431533649975[231] = 0.0;
   out_2615398431533649975[232] = 0.0;
   out_2615398431533649975[233] = 0.0;
   out_2615398431533649975[234] = 0.0;
   out_2615398431533649975[235] = 0.0;
   out_2615398431533649975[236] = 0.0;
   out_2615398431533649975[237] = 0.0;
   out_2615398431533649975[238] = 0.0;
   out_2615398431533649975[239] = 0.0;
   out_2615398431533649975[240] = 0.0;
   out_2615398431533649975[241] = 0.0;
   out_2615398431533649975[242] = 0.0;
   out_2615398431533649975[243] = 0.0;
   out_2615398431533649975[244] = 0.0;
   out_2615398431533649975[245] = 0.0;
   out_2615398431533649975[246] = 0.0;
   out_2615398431533649975[247] = 1.0;
   out_2615398431533649975[248] = 0.0;
   out_2615398431533649975[249] = 0.0;
   out_2615398431533649975[250] = 0.0;
   out_2615398431533649975[251] = 0.0;
   out_2615398431533649975[252] = 0.0;
   out_2615398431533649975[253] = 0.0;
   out_2615398431533649975[254] = 0.0;
   out_2615398431533649975[255] = 0.0;
   out_2615398431533649975[256] = 0.0;
   out_2615398431533649975[257] = 0.0;
   out_2615398431533649975[258] = 0.0;
   out_2615398431533649975[259] = 0.0;
   out_2615398431533649975[260] = 0.0;
   out_2615398431533649975[261] = 0.0;
   out_2615398431533649975[262] = 0.0;
   out_2615398431533649975[263] = 0.0;
   out_2615398431533649975[264] = 0.0;
   out_2615398431533649975[265] = 0.0;
   out_2615398431533649975[266] = 1.0;
   out_2615398431533649975[267] = 0.0;
   out_2615398431533649975[268] = 0.0;
   out_2615398431533649975[269] = 0.0;
   out_2615398431533649975[270] = 0.0;
   out_2615398431533649975[271] = 0.0;
   out_2615398431533649975[272] = 0.0;
   out_2615398431533649975[273] = 0.0;
   out_2615398431533649975[274] = 0.0;
   out_2615398431533649975[275] = 0.0;
   out_2615398431533649975[276] = 0.0;
   out_2615398431533649975[277] = 0.0;
   out_2615398431533649975[278] = 0.0;
   out_2615398431533649975[279] = 0.0;
   out_2615398431533649975[280] = 0.0;
   out_2615398431533649975[281] = 0.0;
   out_2615398431533649975[282] = 0.0;
   out_2615398431533649975[283] = 0.0;
   out_2615398431533649975[284] = 0.0;
   out_2615398431533649975[285] = 1.0;
   out_2615398431533649975[286] = 0.0;
   out_2615398431533649975[287] = 0.0;
   out_2615398431533649975[288] = 0.0;
   out_2615398431533649975[289] = 0.0;
   out_2615398431533649975[290] = 0.0;
   out_2615398431533649975[291] = 0.0;
   out_2615398431533649975[292] = 0.0;
   out_2615398431533649975[293] = 0.0;
   out_2615398431533649975[294] = 0.0;
   out_2615398431533649975[295] = 0.0;
   out_2615398431533649975[296] = 0.0;
   out_2615398431533649975[297] = 0.0;
   out_2615398431533649975[298] = 0.0;
   out_2615398431533649975[299] = 0.0;
   out_2615398431533649975[300] = 0.0;
   out_2615398431533649975[301] = 0.0;
   out_2615398431533649975[302] = 0.0;
   out_2615398431533649975[303] = 0.0;
   out_2615398431533649975[304] = 1.0;
   out_2615398431533649975[305] = 0.0;
   out_2615398431533649975[306] = 0.0;
   out_2615398431533649975[307] = 0.0;
   out_2615398431533649975[308] = 0.0;
   out_2615398431533649975[309] = 0.0;
   out_2615398431533649975[310] = 0.0;
   out_2615398431533649975[311] = 0.0;
   out_2615398431533649975[312] = 0.0;
   out_2615398431533649975[313] = 0.0;
   out_2615398431533649975[314] = 0.0;
   out_2615398431533649975[315] = 0.0;
   out_2615398431533649975[316] = 0.0;
   out_2615398431533649975[317] = 0.0;
   out_2615398431533649975[318] = 0.0;
   out_2615398431533649975[319] = 0.0;
   out_2615398431533649975[320] = 0.0;
   out_2615398431533649975[321] = 0.0;
   out_2615398431533649975[322] = 0.0;
   out_2615398431533649975[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1089639957195522867) {
   out_1089639957195522867[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1089639957195522867[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1089639957195522867[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1089639957195522867[3] = dt*state[12] + state[3];
   out_1089639957195522867[4] = dt*state[13] + state[4];
   out_1089639957195522867[5] = dt*state[14] + state[5];
   out_1089639957195522867[6] = state[6];
   out_1089639957195522867[7] = state[7];
   out_1089639957195522867[8] = state[8];
   out_1089639957195522867[9] = state[9];
   out_1089639957195522867[10] = state[10];
   out_1089639957195522867[11] = state[11];
   out_1089639957195522867[12] = state[12];
   out_1089639957195522867[13] = state[13];
   out_1089639957195522867[14] = state[14];
   out_1089639957195522867[15] = state[15];
   out_1089639957195522867[16] = state[16];
   out_1089639957195522867[17] = state[17];
}
void F_fun(double *state, double dt, double *out_735303424521965914) {
   out_735303424521965914[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_735303424521965914[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_735303424521965914[2] = 0;
   out_735303424521965914[3] = 0;
   out_735303424521965914[4] = 0;
   out_735303424521965914[5] = 0;
   out_735303424521965914[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_735303424521965914[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_735303424521965914[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_735303424521965914[9] = 0;
   out_735303424521965914[10] = 0;
   out_735303424521965914[11] = 0;
   out_735303424521965914[12] = 0;
   out_735303424521965914[13] = 0;
   out_735303424521965914[14] = 0;
   out_735303424521965914[15] = 0;
   out_735303424521965914[16] = 0;
   out_735303424521965914[17] = 0;
   out_735303424521965914[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_735303424521965914[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_735303424521965914[20] = 0;
   out_735303424521965914[21] = 0;
   out_735303424521965914[22] = 0;
   out_735303424521965914[23] = 0;
   out_735303424521965914[24] = 0;
   out_735303424521965914[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_735303424521965914[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_735303424521965914[27] = 0;
   out_735303424521965914[28] = 0;
   out_735303424521965914[29] = 0;
   out_735303424521965914[30] = 0;
   out_735303424521965914[31] = 0;
   out_735303424521965914[32] = 0;
   out_735303424521965914[33] = 0;
   out_735303424521965914[34] = 0;
   out_735303424521965914[35] = 0;
   out_735303424521965914[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_735303424521965914[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_735303424521965914[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_735303424521965914[39] = 0;
   out_735303424521965914[40] = 0;
   out_735303424521965914[41] = 0;
   out_735303424521965914[42] = 0;
   out_735303424521965914[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_735303424521965914[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_735303424521965914[45] = 0;
   out_735303424521965914[46] = 0;
   out_735303424521965914[47] = 0;
   out_735303424521965914[48] = 0;
   out_735303424521965914[49] = 0;
   out_735303424521965914[50] = 0;
   out_735303424521965914[51] = 0;
   out_735303424521965914[52] = 0;
   out_735303424521965914[53] = 0;
   out_735303424521965914[54] = 0;
   out_735303424521965914[55] = 0;
   out_735303424521965914[56] = 0;
   out_735303424521965914[57] = 1;
   out_735303424521965914[58] = 0;
   out_735303424521965914[59] = 0;
   out_735303424521965914[60] = 0;
   out_735303424521965914[61] = 0;
   out_735303424521965914[62] = 0;
   out_735303424521965914[63] = 0;
   out_735303424521965914[64] = 0;
   out_735303424521965914[65] = 0;
   out_735303424521965914[66] = dt;
   out_735303424521965914[67] = 0;
   out_735303424521965914[68] = 0;
   out_735303424521965914[69] = 0;
   out_735303424521965914[70] = 0;
   out_735303424521965914[71] = 0;
   out_735303424521965914[72] = 0;
   out_735303424521965914[73] = 0;
   out_735303424521965914[74] = 0;
   out_735303424521965914[75] = 0;
   out_735303424521965914[76] = 1;
   out_735303424521965914[77] = 0;
   out_735303424521965914[78] = 0;
   out_735303424521965914[79] = 0;
   out_735303424521965914[80] = 0;
   out_735303424521965914[81] = 0;
   out_735303424521965914[82] = 0;
   out_735303424521965914[83] = 0;
   out_735303424521965914[84] = 0;
   out_735303424521965914[85] = dt;
   out_735303424521965914[86] = 0;
   out_735303424521965914[87] = 0;
   out_735303424521965914[88] = 0;
   out_735303424521965914[89] = 0;
   out_735303424521965914[90] = 0;
   out_735303424521965914[91] = 0;
   out_735303424521965914[92] = 0;
   out_735303424521965914[93] = 0;
   out_735303424521965914[94] = 0;
   out_735303424521965914[95] = 1;
   out_735303424521965914[96] = 0;
   out_735303424521965914[97] = 0;
   out_735303424521965914[98] = 0;
   out_735303424521965914[99] = 0;
   out_735303424521965914[100] = 0;
   out_735303424521965914[101] = 0;
   out_735303424521965914[102] = 0;
   out_735303424521965914[103] = 0;
   out_735303424521965914[104] = dt;
   out_735303424521965914[105] = 0;
   out_735303424521965914[106] = 0;
   out_735303424521965914[107] = 0;
   out_735303424521965914[108] = 0;
   out_735303424521965914[109] = 0;
   out_735303424521965914[110] = 0;
   out_735303424521965914[111] = 0;
   out_735303424521965914[112] = 0;
   out_735303424521965914[113] = 0;
   out_735303424521965914[114] = 1;
   out_735303424521965914[115] = 0;
   out_735303424521965914[116] = 0;
   out_735303424521965914[117] = 0;
   out_735303424521965914[118] = 0;
   out_735303424521965914[119] = 0;
   out_735303424521965914[120] = 0;
   out_735303424521965914[121] = 0;
   out_735303424521965914[122] = 0;
   out_735303424521965914[123] = 0;
   out_735303424521965914[124] = 0;
   out_735303424521965914[125] = 0;
   out_735303424521965914[126] = 0;
   out_735303424521965914[127] = 0;
   out_735303424521965914[128] = 0;
   out_735303424521965914[129] = 0;
   out_735303424521965914[130] = 0;
   out_735303424521965914[131] = 0;
   out_735303424521965914[132] = 0;
   out_735303424521965914[133] = 1;
   out_735303424521965914[134] = 0;
   out_735303424521965914[135] = 0;
   out_735303424521965914[136] = 0;
   out_735303424521965914[137] = 0;
   out_735303424521965914[138] = 0;
   out_735303424521965914[139] = 0;
   out_735303424521965914[140] = 0;
   out_735303424521965914[141] = 0;
   out_735303424521965914[142] = 0;
   out_735303424521965914[143] = 0;
   out_735303424521965914[144] = 0;
   out_735303424521965914[145] = 0;
   out_735303424521965914[146] = 0;
   out_735303424521965914[147] = 0;
   out_735303424521965914[148] = 0;
   out_735303424521965914[149] = 0;
   out_735303424521965914[150] = 0;
   out_735303424521965914[151] = 0;
   out_735303424521965914[152] = 1;
   out_735303424521965914[153] = 0;
   out_735303424521965914[154] = 0;
   out_735303424521965914[155] = 0;
   out_735303424521965914[156] = 0;
   out_735303424521965914[157] = 0;
   out_735303424521965914[158] = 0;
   out_735303424521965914[159] = 0;
   out_735303424521965914[160] = 0;
   out_735303424521965914[161] = 0;
   out_735303424521965914[162] = 0;
   out_735303424521965914[163] = 0;
   out_735303424521965914[164] = 0;
   out_735303424521965914[165] = 0;
   out_735303424521965914[166] = 0;
   out_735303424521965914[167] = 0;
   out_735303424521965914[168] = 0;
   out_735303424521965914[169] = 0;
   out_735303424521965914[170] = 0;
   out_735303424521965914[171] = 1;
   out_735303424521965914[172] = 0;
   out_735303424521965914[173] = 0;
   out_735303424521965914[174] = 0;
   out_735303424521965914[175] = 0;
   out_735303424521965914[176] = 0;
   out_735303424521965914[177] = 0;
   out_735303424521965914[178] = 0;
   out_735303424521965914[179] = 0;
   out_735303424521965914[180] = 0;
   out_735303424521965914[181] = 0;
   out_735303424521965914[182] = 0;
   out_735303424521965914[183] = 0;
   out_735303424521965914[184] = 0;
   out_735303424521965914[185] = 0;
   out_735303424521965914[186] = 0;
   out_735303424521965914[187] = 0;
   out_735303424521965914[188] = 0;
   out_735303424521965914[189] = 0;
   out_735303424521965914[190] = 1;
   out_735303424521965914[191] = 0;
   out_735303424521965914[192] = 0;
   out_735303424521965914[193] = 0;
   out_735303424521965914[194] = 0;
   out_735303424521965914[195] = 0;
   out_735303424521965914[196] = 0;
   out_735303424521965914[197] = 0;
   out_735303424521965914[198] = 0;
   out_735303424521965914[199] = 0;
   out_735303424521965914[200] = 0;
   out_735303424521965914[201] = 0;
   out_735303424521965914[202] = 0;
   out_735303424521965914[203] = 0;
   out_735303424521965914[204] = 0;
   out_735303424521965914[205] = 0;
   out_735303424521965914[206] = 0;
   out_735303424521965914[207] = 0;
   out_735303424521965914[208] = 0;
   out_735303424521965914[209] = 1;
   out_735303424521965914[210] = 0;
   out_735303424521965914[211] = 0;
   out_735303424521965914[212] = 0;
   out_735303424521965914[213] = 0;
   out_735303424521965914[214] = 0;
   out_735303424521965914[215] = 0;
   out_735303424521965914[216] = 0;
   out_735303424521965914[217] = 0;
   out_735303424521965914[218] = 0;
   out_735303424521965914[219] = 0;
   out_735303424521965914[220] = 0;
   out_735303424521965914[221] = 0;
   out_735303424521965914[222] = 0;
   out_735303424521965914[223] = 0;
   out_735303424521965914[224] = 0;
   out_735303424521965914[225] = 0;
   out_735303424521965914[226] = 0;
   out_735303424521965914[227] = 0;
   out_735303424521965914[228] = 1;
   out_735303424521965914[229] = 0;
   out_735303424521965914[230] = 0;
   out_735303424521965914[231] = 0;
   out_735303424521965914[232] = 0;
   out_735303424521965914[233] = 0;
   out_735303424521965914[234] = 0;
   out_735303424521965914[235] = 0;
   out_735303424521965914[236] = 0;
   out_735303424521965914[237] = 0;
   out_735303424521965914[238] = 0;
   out_735303424521965914[239] = 0;
   out_735303424521965914[240] = 0;
   out_735303424521965914[241] = 0;
   out_735303424521965914[242] = 0;
   out_735303424521965914[243] = 0;
   out_735303424521965914[244] = 0;
   out_735303424521965914[245] = 0;
   out_735303424521965914[246] = 0;
   out_735303424521965914[247] = 1;
   out_735303424521965914[248] = 0;
   out_735303424521965914[249] = 0;
   out_735303424521965914[250] = 0;
   out_735303424521965914[251] = 0;
   out_735303424521965914[252] = 0;
   out_735303424521965914[253] = 0;
   out_735303424521965914[254] = 0;
   out_735303424521965914[255] = 0;
   out_735303424521965914[256] = 0;
   out_735303424521965914[257] = 0;
   out_735303424521965914[258] = 0;
   out_735303424521965914[259] = 0;
   out_735303424521965914[260] = 0;
   out_735303424521965914[261] = 0;
   out_735303424521965914[262] = 0;
   out_735303424521965914[263] = 0;
   out_735303424521965914[264] = 0;
   out_735303424521965914[265] = 0;
   out_735303424521965914[266] = 1;
   out_735303424521965914[267] = 0;
   out_735303424521965914[268] = 0;
   out_735303424521965914[269] = 0;
   out_735303424521965914[270] = 0;
   out_735303424521965914[271] = 0;
   out_735303424521965914[272] = 0;
   out_735303424521965914[273] = 0;
   out_735303424521965914[274] = 0;
   out_735303424521965914[275] = 0;
   out_735303424521965914[276] = 0;
   out_735303424521965914[277] = 0;
   out_735303424521965914[278] = 0;
   out_735303424521965914[279] = 0;
   out_735303424521965914[280] = 0;
   out_735303424521965914[281] = 0;
   out_735303424521965914[282] = 0;
   out_735303424521965914[283] = 0;
   out_735303424521965914[284] = 0;
   out_735303424521965914[285] = 1;
   out_735303424521965914[286] = 0;
   out_735303424521965914[287] = 0;
   out_735303424521965914[288] = 0;
   out_735303424521965914[289] = 0;
   out_735303424521965914[290] = 0;
   out_735303424521965914[291] = 0;
   out_735303424521965914[292] = 0;
   out_735303424521965914[293] = 0;
   out_735303424521965914[294] = 0;
   out_735303424521965914[295] = 0;
   out_735303424521965914[296] = 0;
   out_735303424521965914[297] = 0;
   out_735303424521965914[298] = 0;
   out_735303424521965914[299] = 0;
   out_735303424521965914[300] = 0;
   out_735303424521965914[301] = 0;
   out_735303424521965914[302] = 0;
   out_735303424521965914[303] = 0;
   out_735303424521965914[304] = 1;
   out_735303424521965914[305] = 0;
   out_735303424521965914[306] = 0;
   out_735303424521965914[307] = 0;
   out_735303424521965914[308] = 0;
   out_735303424521965914[309] = 0;
   out_735303424521965914[310] = 0;
   out_735303424521965914[311] = 0;
   out_735303424521965914[312] = 0;
   out_735303424521965914[313] = 0;
   out_735303424521965914[314] = 0;
   out_735303424521965914[315] = 0;
   out_735303424521965914[316] = 0;
   out_735303424521965914[317] = 0;
   out_735303424521965914[318] = 0;
   out_735303424521965914[319] = 0;
   out_735303424521965914[320] = 0;
   out_735303424521965914[321] = 0;
   out_735303424521965914[322] = 0;
   out_735303424521965914[323] = 1;
}
void h_4(double *state, double *unused, double *out_4728717979023997278) {
   out_4728717979023997278[0] = state[6] + state[9];
   out_4728717979023997278[1] = state[7] + state[10];
   out_4728717979023997278[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5554766161294625725) {
   out_5554766161294625725[0] = 0;
   out_5554766161294625725[1] = 0;
   out_5554766161294625725[2] = 0;
   out_5554766161294625725[3] = 0;
   out_5554766161294625725[4] = 0;
   out_5554766161294625725[5] = 0;
   out_5554766161294625725[6] = 1;
   out_5554766161294625725[7] = 0;
   out_5554766161294625725[8] = 0;
   out_5554766161294625725[9] = 1;
   out_5554766161294625725[10] = 0;
   out_5554766161294625725[11] = 0;
   out_5554766161294625725[12] = 0;
   out_5554766161294625725[13] = 0;
   out_5554766161294625725[14] = 0;
   out_5554766161294625725[15] = 0;
   out_5554766161294625725[16] = 0;
   out_5554766161294625725[17] = 0;
   out_5554766161294625725[18] = 0;
   out_5554766161294625725[19] = 0;
   out_5554766161294625725[20] = 0;
   out_5554766161294625725[21] = 0;
   out_5554766161294625725[22] = 0;
   out_5554766161294625725[23] = 0;
   out_5554766161294625725[24] = 0;
   out_5554766161294625725[25] = 1;
   out_5554766161294625725[26] = 0;
   out_5554766161294625725[27] = 0;
   out_5554766161294625725[28] = 1;
   out_5554766161294625725[29] = 0;
   out_5554766161294625725[30] = 0;
   out_5554766161294625725[31] = 0;
   out_5554766161294625725[32] = 0;
   out_5554766161294625725[33] = 0;
   out_5554766161294625725[34] = 0;
   out_5554766161294625725[35] = 0;
   out_5554766161294625725[36] = 0;
   out_5554766161294625725[37] = 0;
   out_5554766161294625725[38] = 0;
   out_5554766161294625725[39] = 0;
   out_5554766161294625725[40] = 0;
   out_5554766161294625725[41] = 0;
   out_5554766161294625725[42] = 0;
   out_5554766161294625725[43] = 0;
   out_5554766161294625725[44] = 1;
   out_5554766161294625725[45] = 0;
   out_5554766161294625725[46] = 0;
   out_5554766161294625725[47] = 1;
   out_5554766161294625725[48] = 0;
   out_5554766161294625725[49] = 0;
   out_5554766161294625725[50] = 0;
   out_5554766161294625725[51] = 0;
   out_5554766161294625725[52] = 0;
   out_5554766161294625725[53] = 0;
}
void h_10(double *state, double *unused, double *out_114271878814552076) {
   out_114271878814552076[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_114271878814552076[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_114271878814552076[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6120139231157031441) {
   out_6120139231157031441[0] = 0;
   out_6120139231157031441[1] = 9.8100000000000005*cos(state[1]);
   out_6120139231157031441[2] = 0;
   out_6120139231157031441[3] = 0;
   out_6120139231157031441[4] = -state[8];
   out_6120139231157031441[5] = state[7];
   out_6120139231157031441[6] = 0;
   out_6120139231157031441[7] = state[5];
   out_6120139231157031441[8] = -state[4];
   out_6120139231157031441[9] = 0;
   out_6120139231157031441[10] = 0;
   out_6120139231157031441[11] = 0;
   out_6120139231157031441[12] = 1;
   out_6120139231157031441[13] = 0;
   out_6120139231157031441[14] = 0;
   out_6120139231157031441[15] = 1;
   out_6120139231157031441[16] = 0;
   out_6120139231157031441[17] = 0;
   out_6120139231157031441[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6120139231157031441[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6120139231157031441[20] = 0;
   out_6120139231157031441[21] = state[8];
   out_6120139231157031441[22] = 0;
   out_6120139231157031441[23] = -state[6];
   out_6120139231157031441[24] = -state[5];
   out_6120139231157031441[25] = 0;
   out_6120139231157031441[26] = state[3];
   out_6120139231157031441[27] = 0;
   out_6120139231157031441[28] = 0;
   out_6120139231157031441[29] = 0;
   out_6120139231157031441[30] = 0;
   out_6120139231157031441[31] = 1;
   out_6120139231157031441[32] = 0;
   out_6120139231157031441[33] = 0;
   out_6120139231157031441[34] = 1;
   out_6120139231157031441[35] = 0;
   out_6120139231157031441[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6120139231157031441[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6120139231157031441[38] = 0;
   out_6120139231157031441[39] = -state[7];
   out_6120139231157031441[40] = state[6];
   out_6120139231157031441[41] = 0;
   out_6120139231157031441[42] = state[4];
   out_6120139231157031441[43] = -state[3];
   out_6120139231157031441[44] = 0;
   out_6120139231157031441[45] = 0;
   out_6120139231157031441[46] = 0;
   out_6120139231157031441[47] = 0;
   out_6120139231157031441[48] = 0;
   out_6120139231157031441[49] = 0;
   out_6120139231157031441[50] = 1;
   out_6120139231157031441[51] = 0;
   out_6120139231157031441[52] = 0;
   out_6120139231157031441[53] = 1;
}
void h_13(double *state, double *unused, double *out_6600295503287438117) {
   out_6600295503287438117[0] = state[3];
   out_6600295503287438117[1] = state[4];
   out_6600295503287438117[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8767039986626958526) {
   out_8767039986626958526[0] = 0;
   out_8767039986626958526[1] = 0;
   out_8767039986626958526[2] = 0;
   out_8767039986626958526[3] = 1;
   out_8767039986626958526[4] = 0;
   out_8767039986626958526[5] = 0;
   out_8767039986626958526[6] = 0;
   out_8767039986626958526[7] = 0;
   out_8767039986626958526[8] = 0;
   out_8767039986626958526[9] = 0;
   out_8767039986626958526[10] = 0;
   out_8767039986626958526[11] = 0;
   out_8767039986626958526[12] = 0;
   out_8767039986626958526[13] = 0;
   out_8767039986626958526[14] = 0;
   out_8767039986626958526[15] = 0;
   out_8767039986626958526[16] = 0;
   out_8767039986626958526[17] = 0;
   out_8767039986626958526[18] = 0;
   out_8767039986626958526[19] = 0;
   out_8767039986626958526[20] = 0;
   out_8767039986626958526[21] = 0;
   out_8767039986626958526[22] = 1;
   out_8767039986626958526[23] = 0;
   out_8767039986626958526[24] = 0;
   out_8767039986626958526[25] = 0;
   out_8767039986626958526[26] = 0;
   out_8767039986626958526[27] = 0;
   out_8767039986626958526[28] = 0;
   out_8767039986626958526[29] = 0;
   out_8767039986626958526[30] = 0;
   out_8767039986626958526[31] = 0;
   out_8767039986626958526[32] = 0;
   out_8767039986626958526[33] = 0;
   out_8767039986626958526[34] = 0;
   out_8767039986626958526[35] = 0;
   out_8767039986626958526[36] = 0;
   out_8767039986626958526[37] = 0;
   out_8767039986626958526[38] = 0;
   out_8767039986626958526[39] = 0;
   out_8767039986626958526[40] = 0;
   out_8767039986626958526[41] = 1;
   out_8767039986626958526[42] = 0;
   out_8767039986626958526[43] = 0;
   out_8767039986626958526[44] = 0;
   out_8767039986626958526[45] = 0;
   out_8767039986626958526[46] = 0;
   out_8767039986626958526[47] = 0;
   out_8767039986626958526[48] = 0;
   out_8767039986626958526[49] = 0;
   out_8767039986626958526[50] = 0;
   out_8767039986626958526[51] = 0;
   out_8767039986626958526[52] = 0;
   out_8767039986626958526[53] = 0;
}
void h_14(double *state, double *unused, double *out_8940922193870001616) {
   out_8940922193870001616[0] = state[6];
   out_8940922193870001616[1] = state[7];
   out_8940922193870001616[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1926379653985114699) {
   out_1926379653985114699[0] = 0;
   out_1926379653985114699[1] = 0;
   out_1926379653985114699[2] = 0;
   out_1926379653985114699[3] = 0;
   out_1926379653985114699[4] = 0;
   out_1926379653985114699[5] = 0;
   out_1926379653985114699[6] = 1;
   out_1926379653985114699[7] = 0;
   out_1926379653985114699[8] = 0;
   out_1926379653985114699[9] = 0;
   out_1926379653985114699[10] = 0;
   out_1926379653985114699[11] = 0;
   out_1926379653985114699[12] = 0;
   out_1926379653985114699[13] = 0;
   out_1926379653985114699[14] = 0;
   out_1926379653985114699[15] = 0;
   out_1926379653985114699[16] = 0;
   out_1926379653985114699[17] = 0;
   out_1926379653985114699[18] = 0;
   out_1926379653985114699[19] = 0;
   out_1926379653985114699[20] = 0;
   out_1926379653985114699[21] = 0;
   out_1926379653985114699[22] = 0;
   out_1926379653985114699[23] = 0;
   out_1926379653985114699[24] = 0;
   out_1926379653985114699[25] = 1;
   out_1926379653985114699[26] = 0;
   out_1926379653985114699[27] = 0;
   out_1926379653985114699[28] = 0;
   out_1926379653985114699[29] = 0;
   out_1926379653985114699[30] = 0;
   out_1926379653985114699[31] = 0;
   out_1926379653985114699[32] = 0;
   out_1926379653985114699[33] = 0;
   out_1926379653985114699[34] = 0;
   out_1926379653985114699[35] = 0;
   out_1926379653985114699[36] = 0;
   out_1926379653985114699[37] = 0;
   out_1926379653985114699[38] = 0;
   out_1926379653985114699[39] = 0;
   out_1926379653985114699[40] = 0;
   out_1926379653985114699[41] = 0;
   out_1926379653985114699[42] = 0;
   out_1926379653985114699[43] = 0;
   out_1926379653985114699[44] = 1;
   out_1926379653985114699[45] = 0;
   out_1926379653985114699[46] = 0;
   out_1926379653985114699[47] = 0;
   out_1926379653985114699[48] = 0;
   out_1926379653985114699[49] = 0;
   out_1926379653985114699[50] = 0;
   out_1926379653985114699[51] = 0;
   out_1926379653985114699[52] = 0;
   out_1926379653985114699[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_3875089391013904122) {
  err_fun(nom_x, delta_x, out_3875089391013904122);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_528120661788585315) {
  inv_err_fun(nom_x, true_x, out_528120661788585315);
}
void pose_H_mod_fun(double *state, double *out_2615398431533649975) {
  H_mod_fun(state, out_2615398431533649975);
}
void pose_f_fun(double *state, double dt, double *out_1089639957195522867) {
  f_fun(state,  dt, out_1089639957195522867);
}
void pose_F_fun(double *state, double dt, double *out_735303424521965914) {
  F_fun(state,  dt, out_735303424521965914);
}
void pose_h_4(double *state, double *unused, double *out_4728717979023997278) {
  h_4(state, unused, out_4728717979023997278);
}
void pose_H_4(double *state, double *unused, double *out_5554766161294625725) {
  H_4(state, unused, out_5554766161294625725);
}
void pose_h_10(double *state, double *unused, double *out_114271878814552076) {
  h_10(state, unused, out_114271878814552076);
}
void pose_H_10(double *state, double *unused, double *out_6120139231157031441) {
  H_10(state, unused, out_6120139231157031441);
}
void pose_h_13(double *state, double *unused, double *out_6600295503287438117) {
  h_13(state, unused, out_6600295503287438117);
}
void pose_H_13(double *state, double *unused, double *out_8767039986626958526) {
  H_13(state, unused, out_8767039986626958526);
}
void pose_h_14(double *state, double *unused, double *out_8940922193870001616) {
  h_14(state, unused, out_8940922193870001616);
}
void pose_H_14(double *state, double *unused, double *out_1926379653985114699) {
  H_14(state, unused, out_1926379653985114699);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
