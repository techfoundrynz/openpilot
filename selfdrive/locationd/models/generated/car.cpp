#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3225337538683765968) {
   out_3225337538683765968[0] = delta_x[0] + nom_x[0];
   out_3225337538683765968[1] = delta_x[1] + nom_x[1];
   out_3225337538683765968[2] = delta_x[2] + nom_x[2];
   out_3225337538683765968[3] = delta_x[3] + nom_x[3];
   out_3225337538683765968[4] = delta_x[4] + nom_x[4];
   out_3225337538683765968[5] = delta_x[5] + nom_x[5];
   out_3225337538683765968[6] = delta_x[6] + nom_x[6];
   out_3225337538683765968[7] = delta_x[7] + nom_x[7];
   out_3225337538683765968[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3041048681105864260) {
   out_3041048681105864260[0] = -nom_x[0] + true_x[0];
   out_3041048681105864260[1] = -nom_x[1] + true_x[1];
   out_3041048681105864260[2] = -nom_x[2] + true_x[2];
   out_3041048681105864260[3] = -nom_x[3] + true_x[3];
   out_3041048681105864260[4] = -nom_x[4] + true_x[4];
   out_3041048681105864260[5] = -nom_x[5] + true_x[5];
   out_3041048681105864260[6] = -nom_x[6] + true_x[6];
   out_3041048681105864260[7] = -nom_x[7] + true_x[7];
   out_3041048681105864260[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_720286376718346434) {
   out_720286376718346434[0] = 1.0;
   out_720286376718346434[1] = 0.0;
   out_720286376718346434[2] = 0.0;
   out_720286376718346434[3] = 0.0;
   out_720286376718346434[4] = 0.0;
   out_720286376718346434[5] = 0.0;
   out_720286376718346434[6] = 0.0;
   out_720286376718346434[7] = 0.0;
   out_720286376718346434[8] = 0.0;
   out_720286376718346434[9] = 0.0;
   out_720286376718346434[10] = 1.0;
   out_720286376718346434[11] = 0.0;
   out_720286376718346434[12] = 0.0;
   out_720286376718346434[13] = 0.0;
   out_720286376718346434[14] = 0.0;
   out_720286376718346434[15] = 0.0;
   out_720286376718346434[16] = 0.0;
   out_720286376718346434[17] = 0.0;
   out_720286376718346434[18] = 0.0;
   out_720286376718346434[19] = 0.0;
   out_720286376718346434[20] = 1.0;
   out_720286376718346434[21] = 0.0;
   out_720286376718346434[22] = 0.0;
   out_720286376718346434[23] = 0.0;
   out_720286376718346434[24] = 0.0;
   out_720286376718346434[25] = 0.0;
   out_720286376718346434[26] = 0.0;
   out_720286376718346434[27] = 0.0;
   out_720286376718346434[28] = 0.0;
   out_720286376718346434[29] = 0.0;
   out_720286376718346434[30] = 1.0;
   out_720286376718346434[31] = 0.0;
   out_720286376718346434[32] = 0.0;
   out_720286376718346434[33] = 0.0;
   out_720286376718346434[34] = 0.0;
   out_720286376718346434[35] = 0.0;
   out_720286376718346434[36] = 0.0;
   out_720286376718346434[37] = 0.0;
   out_720286376718346434[38] = 0.0;
   out_720286376718346434[39] = 0.0;
   out_720286376718346434[40] = 1.0;
   out_720286376718346434[41] = 0.0;
   out_720286376718346434[42] = 0.0;
   out_720286376718346434[43] = 0.0;
   out_720286376718346434[44] = 0.0;
   out_720286376718346434[45] = 0.0;
   out_720286376718346434[46] = 0.0;
   out_720286376718346434[47] = 0.0;
   out_720286376718346434[48] = 0.0;
   out_720286376718346434[49] = 0.0;
   out_720286376718346434[50] = 1.0;
   out_720286376718346434[51] = 0.0;
   out_720286376718346434[52] = 0.0;
   out_720286376718346434[53] = 0.0;
   out_720286376718346434[54] = 0.0;
   out_720286376718346434[55] = 0.0;
   out_720286376718346434[56] = 0.0;
   out_720286376718346434[57] = 0.0;
   out_720286376718346434[58] = 0.0;
   out_720286376718346434[59] = 0.0;
   out_720286376718346434[60] = 1.0;
   out_720286376718346434[61] = 0.0;
   out_720286376718346434[62] = 0.0;
   out_720286376718346434[63] = 0.0;
   out_720286376718346434[64] = 0.0;
   out_720286376718346434[65] = 0.0;
   out_720286376718346434[66] = 0.0;
   out_720286376718346434[67] = 0.0;
   out_720286376718346434[68] = 0.0;
   out_720286376718346434[69] = 0.0;
   out_720286376718346434[70] = 1.0;
   out_720286376718346434[71] = 0.0;
   out_720286376718346434[72] = 0.0;
   out_720286376718346434[73] = 0.0;
   out_720286376718346434[74] = 0.0;
   out_720286376718346434[75] = 0.0;
   out_720286376718346434[76] = 0.0;
   out_720286376718346434[77] = 0.0;
   out_720286376718346434[78] = 0.0;
   out_720286376718346434[79] = 0.0;
   out_720286376718346434[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4784986273722259282) {
   out_4784986273722259282[0] = state[0];
   out_4784986273722259282[1] = state[1];
   out_4784986273722259282[2] = state[2];
   out_4784986273722259282[3] = state[3];
   out_4784986273722259282[4] = state[4];
   out_4784986273722259282[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4784986273722259282[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4784986273722259282[7] = state[7];
   out_4784986273722259282[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3360535700441986037) {
   out_3360535700441986037[0] = 1;
   out_3360535700441986037[1] = 0;
   out_3360535700441986037[2] = 0;
   out_3360535700441986037[3] = 0;
   out_3360535700441986037[4] = 0;
   out_3360535700441986037[5] = 0;
   out_3360535700441986037[6] = 0;
   out_3360535700441986037[7] = 0;
   out_3360535700441986037[8] = 0;
   out_3360535700441986037[9] = 0;
   out_3360535700441986037[10] = 1;
   out_3360535700441986037[11] = 0;
   out_3360535700441986037[12] = 0;
   out_3360535700441986037[13] = 0;
   out_3360535700441986037[14] = 0;
   out_3360535700441986037[15] = 0;
   out_3360535700441986037[16] = 0;
   out_3360535700441986037[17] = 0;
   out_3360535700441986037[18] = 0;
   out_3360535700441986037[19] = 0;
   out_3360535700441986037[20] = 1;
   out_3360535700441986037[21] = 0;
   out_3360535700441986037[22] = 0;
   out_3360535700441986037[23] = 0;
   out_3360535700441986037[24] = 0;
   out_3360535700441986037[25] = 0;
   out_3360535700441986037[26] = 0;
   out_3360535700441986037[27] = 0;
   out_3360535700441986037[28] = 0;
   out_3360535700441986037[29] = 0;
   out_3360535700441986037[30] = 1;
   out_3360535700441986037[31] = 0;
   out_3360535700441986037[32] = 0;
   out_3360535700441986037[33] = 0;
   out_3360535700441986037[34] = 0;
   out_3360535700441986037[35] = 0;
   out_3360535700441986037[36] = 0;
   out_3360535700441986037[37] = 0;
   out_3360535700441986037[38] = 0;
   out_3360535700441986037[39] = 0;
   out_3360535700441986037[40] = 1;
   out_3360535700441986037[41] = 0;
   out_3360535700441986037[42] = 0;
   out_3360535700441986037[43] = 0;
   out_3360535700441986037[44] = 0;
   out_3360535700441986037[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3360535700441986037[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3360535700441986037[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3360535700441986037[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3360535700441986037[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3360535700441986037[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3360535700441986037[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3360535700441986037[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3360535700441986037[53] = -9.8100000000000005*dt;
   out_3360535700441986037[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3360535700441986037[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3360535700441986037[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3360535700441986037[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3360535700441986037[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3360535700441986037[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3360535700441986037[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3360535700441986037[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3360535700441986037[62] = 0;
   out_3360535700441986037[63] = 0;
   out_3360535700441986037[64] = 0;
   out_3360535700441986037[65] = 0;
   out_3360535700441986037[66] = 0;
   out_3360535700441986037[67] = 0;
   out_3360535700441986037[68] = 0;
   out_3360535700441986037[69] = 0;
   out_3360535700441986037[70] = 1;
   out_3360535700441986037[71] = 0;
   out_3360535700441986037[72] = 0;
   out_3360535700441986037[73] = 0;
   out_3360535700441986037[74] = 0;
   out_3360535700441986037[75] = 0;
   out_3360535700441986037[76] = 0;
   out_3360535700441986037[77] = 0;
   out_3360535700441986037[78] = 0;
   out_3360535700441986037[79] = 0;
   out_3360535700441986037[80] = 1;
}
void h_25(double *state, double *unused, double *out_907941370619431812) {
   out_907941370619431812[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2802694273271145243) {
   out_2802694273271145243[0] = 0;
   out_2802694273271145243[1] = 0;
   out_2802694273271145243[2] = 0;
   out_2802694273271145243[3] = 0;
   out_2802694273271145243[4] = 0;
   out_2802694273271145243[5] = 0;
   out_2802694273271145243[6] = 1;
   out_2802694273271145243[7] = 0;
   out_2802694273271145243[8] = 0;
}
void h_24(double *state, double *unused, double *out_156579053550970250) {
   out_156579053550970250[0] = state[4];
   out_156579053550970250[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6360619872073468379) {
   out_6360619872073468379[0] = 0;
   out_6360619872073468379[1] = 0;
   out_6360619872073468379[2] = 0;
   out_6360619872073468379[3] = 0;
   out_6360619872073468379[4] = 1;
   out_6360619872073468379[5] = 0;
   out_6360619872073468379[6] = 0;
   out_6360619872073468379[7] = 0;
   out_6360619872073468379[8] = 0;
   out_6360619872073468379[9] = 0;
   out_6360619872073468379[10] = 0;
   out_6360619872073468379[11] = 0;
   out_6360619872073468379[12] = 0;
   out_6360619872073468379[13] = 0;
   out_6360619872073468379[14] = 1;
   out_6360619872073468379[15] = 0;
   out_6360619872073468379[16] = 0;
   out_6360619872073468379[17] = 0;
}
void h_30(double *state, double *unused, double *out_1183135432903937701) {
   out_1183135432903937701[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1725002056856462955) {
   out_1725002056856462955[0] = 0;
   out_1725002056856462955[1] = 0;
   out_1725002056856462955[2] = 0;
   out_1725002056856462955[3] = 0;
   out_1725002056856462955[4] = 1;
   out_1725002056856462955[5] = 0;
   out_1725002056856462955[6] = 0;
   out_1725002056856462955[7] = 0;
   out_1725002056856462955[8] = 0;
}
void h_26(double *state, double *unused, double *out_2126645285805600136) {
   out_2126645285805600136[0] = state[7];
}
void H_26(double *state, double *unused, double *out_938809045602910981) {
   out_938809045602910981[0] = 0;
   out_938809045602910981[1] = 0;
   out_938809045602910981[2] = 0;
   out_938809045602910981[3] = 0;
   out_938809045602910981[4] = 0;
   out_938809045602910981[5] = 0;
   out_938809045602910981[6] = 0;
   out_938809045602910981[7] = 1;
   out_938809045602910981[8] = 0;
}
void h_27(double *state, double *unused, double *out_1511257255295909329) {
   out_1511257255295909329[0] = state[3];
}
void H_27(double *state, double *unused, double *out_498592014327480262) {
   out_498592014327480262[0] = 0;
   out_498592014327480262[1] = 0;
   out_498592014327480262[2] = 0;
   out_498592014327480262[3] = 1;
   out_498592014327480262[4] = 0;
   out_498592014327480262[5] = 0;
   out_498592014327480262[6] = 0;
   out_498592014327480262[7] = 0;
   out_498592014327480262[8] = 0;
}
void h_29(double *state, double *unused, double *out_1786451317580415218) {
   out_1786451317580415218[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1214770712542070771) {
   out_1214770712542070771[0] = 0;
   out_1214770712542070771[1] = 1;
   out_1214770712542070771[2] = 0;
   out_1214770712542070771[3] = 0;
   out_1214770712542070771[4] = 0;
   out_1214770712542070771[5] = 0;
   out_1214770712542070771[6] = 0;
   out_1214770712542070771[7] = 0;
   out_1214770712542070771[8] = 0;
}
void h_28(double *state, double *unused, double *out_1093148065512788322) {
   out_1093148065512788322[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6297169729611601345) {
   out_6297169729611601345[0] = 1;
   out_6297169729611601345[1] = 0;
   out_6297169729611601345[2] = 0;
   out_6297169729611601345[3] = 0;
   out_6297169729611601345[4] = 0;
   out_6297169729611601345[5] = 0;
   out_6297169729611601345[6] = 0;
   out_6297169729611601345[7] = 0;
   out_6297169729611601345[8] = 0;
}
void h_31(double *state, double *unused, double *out_5006244668898803676) {
   out_5006244668898803676[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2833340235148105671) {
   out_2833340235148105671[0] = 0;
   out_2833340235148105671[1] = 0;
   out_2833340235148105671[2] = 0;
   out_2833340235148105671[3] = 0;
   out_2833340235148105671[4] = 0;
   out_2833340235148105671[5] = 0;
   out_2833340235148105671[6] = 0;
   out_2833340235148105671[7] = 0;
   out_2833340235148105671[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3225337538683765968) {
  err_fun(nom_x, delta_x, out_3225337538683765968);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3041048681105864260) {
  inv_err_fun(nom_x, true_x, out_3041048681105864260);
}
void car_H_mod_fun(double *state, double *out_720286376718346434) {
  H_mod_fun(state, out_720286376718346434);
}
void car_f_fun(double *state, double dt, double *out_4784986273722259282) {
  f_fun(state,  dt, out_4784986273722259282);
}
void car_F_fun(double *state, double dt, double *out_3360535700441986037) {
  F_fun(state,  dt, out_3360535700441986037);
}
void car_h_25(double *state, double *unused, double *out_907941370619431812) {
  h_25(state, unused, out_907941370619431812);
}
void car_H_25(double *state, double *unused, double *out_2802694273271145243) {
  H_25(state, unused, out_2802694273271145243);
}
void car_h_24(double *state, double *unused, double *out_156579053550970250) {
  h_24(state, unused, out_156579053550970250);
}
void car_H_24(double *state, double *unused, double *out_6360619872073468379) {
  H_24(state, unused, out_6360619872073468379);
}
void car_h_30(double *state, double *unused, double *out_1183135432903937701) {
  h_30(state, unused, out_1183135432903937701);
}
void car_H_30(double *state, double *unused, double *out_1725002056856462955) {
  H_30(state, unused, out_1725002056856462955);
}
void car_h_26(double *state, double *unused, double *out_2126645285805600136) {
  h_26(state, unused, out_2126645285805600136);
}
void car_H_26(double *state, double *unused, double *out_938809045602910981) {
  H_26(state, unused, out_938809045602910981);
}
void car_h_27(double *state, double *unused, double *out_1511257255295909329) {
  h_27(state, unused, out_1511257255295909329);
}
void car_H_27(double *state, double *unused, double *out_498592014327480262) {
  H_27(state, unused, out_498592014327480262);
}
void car_h_29(double *state, double *unused, double *out_1786451317580415218) {
  h_29(state, unused, out_1786451317580415218);
}
void car_H_29(double *state, double *unused, double *out_1214770712542070771) {
  H_29(state, unused, out_1214770712542070771);
}
void car_h_28(double *state, double *unused, double *out_1093148065512788322) {
  h_28(state, unused, out_1093148065512788322);
}
void car_H_28(double *state, double *unused, double *out_6297169729611601345) {
  H_28(state, unused, out_6297169729611601345);
}
void car_h_31(double *state, double *unused, double *out_5006244668898803676) {
  h_31(state, unused, out_5006244668898803676);
}
void car_H_31(double *state, double *unused, double *out_2833340235148105671) {
  H_31(state, unused, out_2833340235148105671);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
