#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3875089391013904122);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_528120661788585315);
void pose_H_mod_fun(double *state, double *out_2615398431533649975);
void pose_f_fun(double *state, double dt, double *out_1089639957195522867);
void pose_F_fun(double *state, double dt, double *out_735303424521965914);
void pose_h_4(double *state, double *unused, double *out_4728717979023997278);
void pose_H_4(double *state, double *unused, double *out_5554766161294625725);
void pose_h_10(double *state, double *unused, double *out_114271878814552076);
void pose_H_10(double *state, double *unused, double *out_6120139231157031441);
void pose_h_13(double *state, double *unused, double *out_6600295503287438117);
void pose_H_13(double *state, double *unused, double *out_8767039986626958526);
void pose_h_14(double *state, double *unused, double *out_8940922193870001616);
void pose_H_14(double *state, double *unused, double *out_1926379653985114699);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}