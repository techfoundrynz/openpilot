#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_2951365999577599155);
void live_err_fun(double *nom_x, double *delta_x, double *out_7066363659211833050);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_4380014424488228125);
void live_H_mod_fun(double *state, double *out_8893148822357461988);
void live_f_fun(double *state, double dt, double *out_7505269279520480075);
void live_F_fun(double *state, double dt, double *out_7230553242490462120);
void live_h_4(double *state, double *unused, double *out_8215354461143228689);
void live_H_4(double *state, double *unused, double *out_3253325367486502543);
void live_h_9(double *state, double *unused, double *out_1628005971826214775);
void live_H_9(double *state, double *unused, double *out_3494515014116093188);
void live_h_10(double *state, double *unused, double *out_1220761447463208291);
void live_H_10(double *state, double *unused, double *out_913689467467544656);
void live_h_12(double *state, double *unused, double *out_6258791675236666620);
void live_H_12(double *state, double *unused, double *out_8272781775518464338);
void live_h_35(double *state, double *unused, double *out_8070263911561674260);
void live_H_35(double *state, double *unused, double *out_7428399265866073569);
void live_h_32(double *state, double *unused, double *out_244329575480877556);
void live_H_32(double *state, double *unused, double *out_1627094893658461011);
void live_h_13(double *state, double *unused, double *out_2522573963901855308);
void live_H_13(double *state, double *unused, double *out_3564973201228481534);
void live_h_14(double *state, double *unused, double *out_1628005971826214775);
void live_H_14(double *state, double *unused, double *out_3494515014116093188);
void live_h_33(double *state, double *unused, double *out_3220944777897939004);
void live_H_33(double *state, double *unused, double *out_4277842261227215965);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}