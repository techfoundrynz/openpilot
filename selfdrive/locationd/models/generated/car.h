#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_3225337538683765968);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3041048681105864260);
void car_H_mod_fun(double *state, double *out_720286376718346434);
void car_f_fun(double *state, double dt, double *out_4784986273722259282);
void car_F_fun(double *state, double dt, double *out_3360535700441986037);
void car_h_25(double *state, double *unused, double *out_907941370619431812);
void car_H_25(double *state, double *unused, double *out_2802694273271145243);
void car_h_24(double *state, double *unused, double *out_156579053550970250);
void car_H_24(double *state, double *unused, double *out_6360619872073468379);
void car_h_30(double *state, double *unused, double *out_1183135432903937701);
void car_H_30(double *state, double *unused, double *out_1725002056856462955);
void car_h_26(double *state, double *unused, double *out_2126645285805600136);
void car_H_26(double *state, double *unused, double *out_938809045602910981);
void car_h_27(double *state, double *unused, double *out_1511257255295909329);
void car_H_27(double *state, double *unused, double *out_498592014327480262);
void car_h_29(double *state, double *unused, double *out_1786451317580415218);
void car_H_29(double *state, double *unused, double *out_1214770712542070771);
void car_h_28(double *state, double *unused, double *out_1093148065512788322);
void car_H_28(double *state, double *unused, double *out_6297169729611601345);
void car_h_31(double *state, double *unused, double *out_5006244668898803676);
void car_H_31(double *state, double *unused, double *out_2833340235148105671);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}