/* model.c
   ___________________________________________________

   Model File:  diazepam_v6.model

   Date:  Tue Oct 30 11:21:44 2018

   Created by:  "C:/Users/user/Desktop/DIAZEP~3/mcsim/mod/mod.exe v6.0.1"
    -- a model preprocessor by Don Maszle
   ___________________________________________________

   Copyright (c) 1993-2018 Free Software Foundation, Inc.

   Model calculations for compartmental model:

   14 States:
     C_mu -> 0.0;
     C_ad -> 0.0;
     C_te -> 0.0;
     C_sk -> 0.0;
     C_ht -> 0.0;
     C_br -> 0.0;
     C_ki -> 0.0;
     C_re -> 0.0;
     C_st -> 0.0;
     C_spl -> 0.0;
     C_li -> 0.0;
     C_lu -> 0.0;
     C_art -> 0.0;
     C_ven -> 0.0;

   1 Output:
     C_plasma -> 0.0;

   1 Input:
     Rate_in (is a function)

   76 Parameters:
     BM = 70;
     V_mu = 30;
     V_ad = 12.5;
     V_te = 0.035;
     V_sk = 2.6;
     V_ht = 0.33;
     V_br = 1.4;
     V_ki = 0.31;
     V_re = 16.8;
     V_st = 0.15;
     V_spl = 1.01;
     V_li = 1.8;
     V_lu = 0.47;
     V_art = 1.7;
     V_ven = 3.9;
     Ff_mu = 0.17;
     Ff_ad = 0.05;
     Ff_te = 0.0005;
     Ff_sk = 0.05;
     Ff_ht = 0.04;
     Ff_br = 0.12;
     Ff_ki = 0.19;
     Ff_st = 0.01;
     Ff_spl = 0.14;
     Ff_ha = 0.065;
     Ff_re = 0.1645;
     Kp_mu_base = 0.56;
     Kp_te_base = 0.76;
     Kp_sk_base = 0.46;
     Kp_ht_base = 0.86;
     Kp_br_base = 0.32;
     Kp_ki_base = 0.73;
     Kp_re_base = 0.50;
     Kp_st_base = 0.75;
     Kp_spl_base = 0.53;
     Kp_li_base = 1.35;
     Kp_lu_base = 0.71;
     log_Cl_int = 0;
     log_fudge = 0;
     log_Kp_ad = 0;
     Ratio_BP = 0.65;
     fu = 0.015;
     sigma = 0;
     Sigma_var = 0;
     Sigma_vve = 0;
     Sigma_vad = 0;
     Sigma_qad = 0;
     Sigma_cli = 0;
     Q_mu = 0;
     Q_ad = 0;
     Q_te = 0;
     Q_sk = 0;
     Q_ht = 0;
     Q_br = 0;
     Q_ki = 0;
     Q_re = 0;
     Q_st = 0;
     Q_spl = 0;
     Q_ha = 0;
     Q_ven = 0;
     Q_h = 0;
     fub = 0;
     Kp_mu = 0;
     Kp_te = 0;
     Kp_sk = 0;
     Kp_ht = 0;
     Kp_br = 0;
     Kp_ki = 0;
     Kp_re = 0;
     Kp_st = 0;
     Kp_spl = 0;
     Kp_li = 0;
     Kp_lu = 0;
     Kp_ad = 0;
     Cl_int = 0;
     fudge = 0;
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "modelu.h"
#include "random.h"
#include "yourcode.h"


/*----- Indices to Global Variables */

/* Model variables: States and other outputs */
#define ID_C_mu 0x00000
#define ID_C_ad 0x00001
#define ID_C_te 0x00002
#define ID_C_sk 0x00003
#define ID_C_ht 0x00004
#define ID_C_br 0x00005
#define ID_C_ki 0x00006
#define ID_C_re 0x00007
#define ID_C_st 0x00008
#define ID_C_spl 0x00009
#define ID_C_li 0x0000a
#define ID_C_lu 0x0000b
#define ID_C_art 0x0000c
#define ID_C_ven 0x0000d
#define ID_C_plasma 0x0000e

/* Inputs */
#define ID_Rate_in 0x00000

/* Parameters */
#define ID_BM 0x00010
#define ID_V_mu 0x00011
#define ID_V_ad 0x00012
#define ID_V_te 0x00013
#define ID_V_sk 0x00014
#define ID_V_ht 0x00015
#define ID_V_br 0x00016
#define ID_V_ki 0x00017
#define ID_V_re 0x00018
#define ID_V_st 0x00019
#define ID_V_spl 0x0001a
#define ID_V_li 0x0001b
#define ID_V_lu 0x0001c
#define ID_V_art 0x0001d
#define ID_V_ven 0x0001e
#define ID_Ff_mu 0x0001f
#define ID_Ff_ad 0x00020
#define ID_Ff_te 0x00021
#define ID_Ff_sk 0x00022
#define ID_Ff_ht 0x00023
#define ID_Ff_br 0x00024
#define ID_Ff_ki 0x00025
#define ID_Ff_st 0x00026
#define ID_Ff_spl 0x00027
#define ID_Ff_ha 0x00028
#define ID_Ff_re 0x00029
#define ID_Kp_mu_base 0x0002a
#define ID_Kp_te_base 0x0002b
#define ID_Kp_sk_base 0x0002c
#define ID_Kp_ht_base 0x0002d
#define ID_Kp_br_base 0x0002e
#define ID_Kp_ki_base 0x0002f
#define ID_Kp_re_base 0x00030
#define ID_Kp_st_base 0x00031
#define ID_Kp_spl_base 0x00032
#define ID_Kp_li_base 0x00033
#define ID_Kp_lu_base 0x00034
#define ID_log_Cl_int 0x00035
#define ID_log_fudge 0x00036
#define ID_log_Kp_ad 0x00037
#define ID_Ratio_BP 0x00038
#define ID_fu 0x00039
#define ID_sigma 0x0003a
#define ID_Sigma_var 0x0003b
#define ID_Sigma_vve 0x0003c
#define ID_Sigma_vad 0x0003d
#define ID_Sigma_qad 0x0003e
#define ID_Sigma_cli 0x0003f
#define ID_Q_mu 0x00040
#define ID_Q_ad 0x00041
#define ID_Q_te 0x00042
#define ID_Q_sk 0x00043
#define ID_Q_ht 0x00044
#define ID_Q_br 0x00045
#define ID_Q_ki 0x00046
#define ID_Q_re 0x00047
#define ID_Q_st 0x00048
#define ID_Q_spl 0x00049
#define ID_Q_ha 0x0004a
#define ID_Q_ven 0x0004b
#define ID_Q_h 0x0004c
#define ID_fub 0x0004d
#define ID_Kp_mu 0x0004e
#define ID_Kp_te 0x0004f
#define ID_Kp_sk 0x00050
#define ID_Kp_ht 0x00051
#define ID_Kp_br 0x00052
#define ID_Kp_ki 0x00053
#define ID_Kp_re 0x00054
#define ID_Kp_st 0x00055
#define ID_Kp_spl 0x00056
#define ID_Kp_li 0x00057
#define ID_Kp_lu 0x00058
#define ID_Kp_ad 0x00059
#define ID_Cl_int 0x0005a
#define ID_fudge 0x0005b


/*----- Global Variables */

/* For export. Keep track of who we are. */
char szModelDescFilename[] = "diazepam_v6.model";
char szModelSourceFilename[] = __FILE__;
char szModelGenAndVersion[] = "C:/Users/user/Desktop/DIAZEP~3/mcsim/mod/mod.exe v6.0.1";

/* Externs */
extern BOOL vbModelReinitd;

/* Model Dimensions */
int vnStates = 14;
int vnOutputs = 1;
int vnModelVars = 15;
int vnInputs = 1;
int vnParms = 76;

/* States and Outputs*/
double vrgModelVars[15];

/* Inputs */
IFN vrgInputs[1];

/* Parameters */
double BM;
double V_mu;
double V_ad;
double V_te;
double V_sk;
double V_ht;
double V_br;
double V_ki;
double V_re;
double V_st;
double V_spl;
double V_li;
double V_lu;
double V_art;
double V_ven;
double Ff_mu;
double Ff_ad;
double Ff_te;
double Ff_sk;
double Ff_ht;
double Ff_br;
double Ff_ki;
double Ff_st;
double Ff_spl;
double Ff_ha;
double Ff_re;
double Kp_mu_base;
double Kp_te_base;
double Kp_sk_base;
double Kp_ht_base;
double Kp_br_base;
double Kp_ki_base;
double Kp_re_base;
double Kp_st_base;
double Kp_spl_base;
double Kp_li_base;
double Kp_lu_base;
double log_Cl_int;
double log_fudge;
double log_Kp_ad;
double Ratio_BP;
double fu;
double sigma;
double Sigma_var;
double Sigma_vve;
double Sigma_vad;
double Sigma_qad;
double Sigma_cli;
double Q_mu;
double Q_ad;
double Q_te;
double Q_sk;
double Q_ht;
double Q_br;
double Q_ki;
double Q_re;
double Q_st;
double Q_spl;
double Q_ha;
double Q_ven;
double Q_h;
double fub;
double Kp_mu;
double Kp_te;
double Kp_sk;
double Kp_ht;
double Kp_br;
double Kp_ki;
double Kp_re;
double Kp_st;
double Kp_spl;
double Kp_li;
double Kp_lu;
double Kp_ad;
double Cl_int;
double fudge;

BOOL bDelays = 0;


/*----- Global Variable Map */

VMMAPSTRCT vrgvmGlo[] = {
  {"C_mu", (PVOID) &vrgModelVars[ID_C_mu], ID_STATE | ID_C_mu},
  {"C_ad", (PVOID) &vrgModelVars[ID_C_ad], ID_STATE | ID_C_ad},
  {"C_te", (PVOID) &vrgModelVars[ID_C_te], ID_STATE | ID_C_te},
  {"C_sk", (PVOID) &vrgModelVars[ID_C_sk], ID_STATE | ID_C_sk},
  {"C_ht", (PVOID) &vrgModelVars[ID_C_ht], ID_STATE | ID_C_ht},
  {"C_br", (PVOID) &vrgModelVars[ID_C_br], ID_STATE | ID_C_br},
  {"C_ki", (PVOID) &vrgModelVars[ID_C_ki], ID_STATE | ID_C_ki},
  {"C_re", (PVOID) &vrgModelVars[ID_C_re], ID_STATE | ID_C_re},
  {"C_st", (PVOID) &vrgModelVars[ID_C_st], ID_STATE | ID_C_st},
  {"C_spl", (PVOID) &vrgModelVars[ID_C_spl], ID_STATE | ID_C_spl},
  {"C_li", (PVOID) &vrgModelVars[ID_C_li], ID_STATE | ID_C_li},
  {"C_lu", (PVOID) &vrgModelVars[ID_C_lu], ID_STATE | ID_C_lu},
  {"C_art", (PVOID) &vrgModelVars[ID_C_art], ID_STATE | ID_C_art},
  {"C_ven", (PVOID) &vrgModelVars[ID_C_ven], ID_STATE | ID_C_ven},
  {"C_plasma", (PVOID) &vrgModelVars[ID_C_plasma], ID_OUTPUT | ID_C_plasma},
  {"Rate_in", (PVOID) &vrgInputs[ID_Rate_in], ID_INPUT | ID_Rate_in},
  {"BM", (PVOID) &BM, ID_PARM | ID_BM},
  {"V_mu", (PVOID) &V_mu, ID_PARM | ID_V_mu},
  {"V_ad", (PVOID) &V_ad, ID_PARM | ID_V_ad},
  {"V_te", (PVOID) &V_te, ID_PARM | ID_V_te},
  {"V_sk", (PVOID) &V_sk, ID_PARM | ID_V_sk},
  {"V_ht", (PVOID) &V_ht, ID_PARM | ID_V_ht},
  {"V_br", (PVOID) &V_br, ID_PARM | ID_V_br},
  {"V_ki", (PVOID) &V_ki, ID_PARM | ID_V_ki},
  {"V_re", (PVOID) &V_re, ID_PARM | ID_V_re},
  {"V_st", (PVOID) &V_st, ID_PARM | ID_V_st},
  {"V_spl", (PVOID) &V_spl, ID_PARM | ID_V_spl},
  {"V_li", (PVOID) &V_li, ID_PARM | ID_V_li},
  {"V_lu", (PVOID) &V_lu, ID_PARM | ID_V_lu},
  {"V_art", (PVOID) &V_art, ID_PARM | ID_V_art},
  {"V_ven", (PVOID) &V_ven, ID_PARM | ID_V_ven},
  {"Ff_mu", (PVOID) &Ff_mu, ID_PARM | ID_Ff_mu},
  {"Ff_ad", (PVOID) &Ff_ad, ID_PARM | ID_Ff_ad},
  {"Ff_te", (PVOID) &Ff_te, ID_PARM | ID_Ff_te},
  {"Ff_sk", (PVOID) &Ff_sk, ID_PARM | ID_Ff_sk},
  {"Ff_ht", (PVOID) &Ff_ht, ID_PARM | ID_Ff_ht},
  {"Ff_br", (PVOID) &Ff_br, ID_PARM | ID_Ff_br},
  {"Ff_ki", (PVOID) &Ff_ki, ID_PARM | ID_Ff_ki},
  {"Ff_st", (PVOID) &Ff_st, ID_PARM | ID_Ff_st},
  {"Ff_spl", (PVOID) &Ff_spl, ID_PARM | ID_Ff_spl},
  {"Ff_ha", (PVOID) &Ff_ha, ID_PARM | ID_Ff_ha},
  {"Ff_re", (PVOID) &Ff_re, ID_PARM | ID_Ff_re},
  {"Kp_mu_base", (PVOID) &Kp_mu_base, ID_PARM | ID_Kp_mu_base},
  {"Kp_te_base", (PVOID) &Kp_te_base, ID_PARM | ID_Kp_te_base},
  {"Kp_sk_base", (PVOID) &Kp_sk_base, ID_PARM | ID_Kp_sk_base},
  {"Kp_ht_base", (PVOID) &Kp_ht_base, ID_PARM | ID_Kp_ht_base},
  {"Kp_br_base", (PVOID) &Kp_br_base, ID_PARM | ID_Kp_br_base},
  {"Kp_ki_base", (PVOID) &Kp_ki_base, ID_PARM | ID_Kp_ki_base},
  {"Kp_re_base", (PVOID) &Kp_re_base, ID_PARM | ID_Kp_re_base},
  {"Kp_st_base", (PVOID) &Kp_st_base, ID_PARM | ID_Kp_st_base},
  {"Kp_spl_base", (PVOID) &Kp_spl_base, ID_PARM | ID_Kp_spl_base},
  {"Kp_li_base", (PVOID) &Kp_li_base, ID_PARM | ID_Kp_li_base},
  {"Kp_lu_base", (PVOID) &Kp_lu_base, ID_PARM | ID_Kp_lu_base},
  {"log_Cl_int", (PVOID) &log_Cl_int, ID_PARM | ID_log_Cl_int},
  {"log_fudge", (PVOID) &log_fudge, ID_PARM | ID_log_fudge},
  {"log_Kp_ad", (PVOID) &log_Kp_ad, ID_PARM | ID_log_Kp_ad},
  {"Ratio_BP", (PVOID) &Ratio_BP, ID_PARM | ID_Ratio_BP},
  {"fu", (PVOID) &fu, ID_PARM | ID_fu},
  {"sigma", (PVOID) &sigma, ID_PARM | ID_sigma},
  {"Sigma_var", (PVOID) &Sigma_var, ID_PARM | ID_Sigma_var},
  {"Sigma_vve", (PVOID) &Sigma_vve, ID_PARM | ID_Sigma_vve},
  {"Sigma_vad", (PVOID) &Sigma_vad, ID_PARM | ID_Sigma_vad},
  {"Sigma_qad", (PVOID) &Sigma_qad, ID_PARM | ID_Sigma_qad},
  {"Sigma_cli", (PVOID) &Sigma_cli, ID_PARM | ID_Sigma_cli},
  {"Q_mu", (PVOID) &Q_mu, ID_PARM | ID_Q_mu},
  {"Q_ad", (PVOID) &Q_ad, ID_PARM | ID_Q_ad},
  {"Q_te", (PVOID) &Q_te, ID_PARM | ID_Q_te},
  {"Q_sk", (PVOID) &Q_sk, ID_PARM | ID_Q_sk},
  {"Q_ht", (PVOID) &Q_ht, ID_PARM | ID_Q_ht},
  {"Q_br", (PVOID) &Q_br, ID_PARM | ID_Q_br},
  {"Q_ki", (PVOID) &Q_ki, ID_PARM | ID_Q_ki},
  {"Q_re", (PVOID) &Q_re, ID_PARM | ID_Q_re},
  {"Q_st", (PVOID) &Q_st, ID_PARM | ID_Q_st},
  {"Q_spl", (PVOID) &Q_spl, ID_PARM | ID_Q_spl},
  {"Q_ha", (PVOID) &Q_ha, ID_PARM | ID_Q_ha},
  {"Q_ven", (PVOID) &Q_ven, ID_PARM | ID_Q_ven},
  {"Q_h", (PVOID) &Q_h, ID_PARM | ID_Q_h},
  {"fub", (PVOID) &fub, ID_PARM | ID_fub},
  {"Kp_mu", (PVOID) &Kp_mu, ID_PARM | ID_Kp_mu},
  {"Kp_te", (PVOID) &Kp_te, ID_PARM | ID_Kp_te},
  {"Kp_sk", (PVOID) &Kp_sk, ID_PARM | ID_Kp_sk},
  {"Kp_ht", (PVOID) &Kp_ht, ID_PARM | ID_Kp_ht},
  {"Kp_br", (PVOID) &Kp_br, ID_PARM | ID_Kp_br},
  {"Kp_ki", (PVOID) &Kp_ki, ID_PARM | ID_Kp_ki},
  {"Kp_re", (PVOID) &Kp_re, ID_PARM | ID_Kp_re},
  {"Kp_st", (PVOID) &Kp_st, ID_PARM | ID_Kp_st},
  {"Kp_spl", (PVOID) &Kp_spl, ID_PARM | ID_Kp_spl},
  {"Kp_li", (PVOID) &Kp_li, ID_PARM | ID_Kp_li},
  {"Kp_lu", (PVOID) &Kp_lu, ID_PARM | ID_Kp_lu},
  {"Kp_ad", (PVOID) &Kp_ad, ID_PARM | ID_Kp_ad},
  {"Cl_int", (PVOID) &Cl_int, ID_PARM | ID_Cl_int},
  {"fudge", (PVOID) &fudge, ID_PARM | ID_fudge},
  {"", NULL, 0} /* End flag */
};  /* vrgpvmGlo[] */


/*----- InitModel
   Should be called to initialize model variables at
   the beginning of experiment before reading
   variants from the simulation spec file.
*/

void InitModel(void)
{
  /* Initialize things in the order that they appear in
     model definition file so that dependencies are
     handled correctly. */

  vrgModelVars[ID_C_mu] = 0.0;
  vrgModelVars[ID_C_ad] = 0.0;
  vrgModelVars[ID_C_te] = 0.0;
  vrgModelVars[ID_C_sk] = 0.0;
  vrgModelVars[ID_C_ht] = 0.0;
  vrgModelVars[ID_C_br] = 0.0;
  vrgModelVars[ID_C_ki] = 0.0;
  vrgModelVars[ID_C_re] = 0.0;
  vrgModelVars[ID_C_st] = 0.0;
  vrgModelVars[ID_C_spl] = 0.0;
  vrgModelVars[ID_C_li] = 0.0;
  vrgModelVars[ID_C_lu] = 0.0;
  vrgModelVars[ID_C_art] = 0.0;
  vrgModelVars[ID_C_ven] = 0.0;
  vrgInputs[ID_Rate_in].iType = IFN_CONSTANT;
  vrgInputs[ID_Rate_in].dTStartPeriod = 0;
  vrgInputs[ID_Rate_in].bOn = FALSE;
  vrgInputs[ID_Rate_in].dMag = 0.000000;
  vrgInputs[ID_Rate_in].dT0 = 0.000000;
  vrgInputs[ID_Rate_in].dTexp = 0.000000;
  vrgInputs[ID_Rate_in].dDecay = 0.000000;
  vrgInputs[ID_Rate_in].dTper = 0.000000;
  vrgInputs[ID_Rate_in].hMag = 0;
  vrgInputs[ID_Rate_in].hT0 = 0;
  vrgInputs[ID_Rate_in].hTexp = 0;
  vrgInputs[ID_Rate_in].hDecay = 0;
  vrgInputs[ID_Rate_in].hTper = 0;
  vrgInputs[ID_Rate_in].dVal = 0.0;
  vrgInputs[ID_Rate_in].nDoses = 0;
  vrgModelVars[ID_C_plasma] = 0.0;
  BM = 70;
  V_mu = 30;
  V_ad = 12.5;
  V_te = 0.035;
  V_sk = 2.6;
  V_ht = 0.33;
  V_br = 1.4;
  V_ki = 0.31;
  V_re = 16.8;
  V_st = 0.15;
  V_spl = 1.01;
  V_li = 1.8;
  V_lu = 0.47;
  V_art = 1.7;
  V_ven = 3.9;
  Ff_mu = 0.17;
  Ff_ad = 0.05;
  Ff_te = 0.0005;
  Ff_sk = 0.05;
  Ff_ht = 0.04;
  Ff_br = 0.12;
  Ff_ki = 0.19;
  Ff_st = 0.01;
  Ff_spl = 0.14;
  Ff_ha = 0.065;
  Ff_re = 0.1645;
  Kp_mu_base = 0.56;
  Kp_te_base = 0.76;
  Kp_sk_base = 0.46;
  Kp_ht_base = 0.86;
  Kp_br_base = 0.32;
  Kp_ki_base = 0.73;
  Kp_re_base = 0.50;
  Kp_st_base = 0.75;
  Kp_spl_base = 0.53;
  Kp_li_base = 1.35;
  Kp_lu_base = 0.71;
  log_Cl_int = 0;
  log_fudge = 0;
  log_Kp_ad = 0;
  Ratio_BP = 0.65;
  fu = 0.015;
  sigma = 0;
  Sigma_var = 0;
  Sigma_vve = 0;
  Sigma_vad = 0;
  Sigma_qad = 0;
  Sigma_cli = 0;
  Q_mu = 0;
  Q_ad = 0;
  Q_te = 0;
  Q_sk = 0;
  Q_ht = 0;
  Q_br = 0;
  Q_ki = 0;
  Q_re = 0;
  Q_st = 0;
  Q_spl = 0;
  Q_ha = 0;
  Q_ven = 0;
  Q_h = 0;
  fub = 0;
  Kp_mu = 0;
  Kp_te = 0;
  Kp_sk = 0;
  Kp_ht = 0;
  Kp_br = 0;
  Kp_ki = 0;
  Kp_re = 0;
  Kp_st = 0;
  Kp_spl = 0;
  Kp_li = 0;
  Kp_lu = 0;
  Kp_ad = 0;
  Cl_int = 0;
  fudge = 0;

  vbModelReinitd = TRUE;

} /* InitModel */


/*----- Dynamics section */

void CalcDeriv (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

  CalcInputs (pdTime); /* Get new input vals */


  rgDerivs[ID_C_mu] = Q_mu * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_mu] / Kp_mu ) / V_mu ;

  rgDerivs[ID_C_ad] = Q_ad * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_ad] / Kp_ad ) / V_ad ;

  rgDerivs[ID_C_te] = Q_te * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_te] / Kp_te ) / V_te ;

  rgDerivs[ID_C_sk] = Q_sk * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_sk] / Kp_sk ) / V_sk ;

  rgDerivs[ID_C_ht] = Q_ht * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_ht] / Kp_ht ) / V_ht ;

  rgDerivs[ID_C_br] = Q_br * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_br] / Kp_br ) / V_br ;

  rgDerivs[ID_C_ki] = Q_ki * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_ki] / Kp_ki ) / V_ki ;

  rgDerivs[ID_C_re] = Q_re * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_re] / Kp_re ) / V_re ;

  rgDerivs[ID_C_st] = Q_st * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_st] / Kp_st ) / V_st ;

  rgDerivs[ID_C_spl] = Q_spl * ( rgModelVars[ID_C_art] - rgModelVars[ID_C_spl] / Kp_spl ) / V_spl ;

  rgDerivs[ID_C_li] = ( Q_ha * rgModelVars[ID_C_art] + Q_st * rgModelVars[ID_C_st] / Kp_st + Q_spl * rgModelVars[ID_C_spl] / Kp_spl - ( Q_h + Cl_int * fub ) * rgModelVars[ID_C_li] / Kp_li ) / V_li ;

  rgDerivs[ID_C_lu] = Q_ven * ( rgModelVars[ID_C_ven] - rgModelVars[ID_C_lu] / Kp_lu ) / V_lu ;

  rgDerivs[ID_C_art] = Q_ven * ( rgModelVars[ID_C_lu] / Kp_lu - rgModelVars[ID_C_art] ) / V_art ;

  rgDerivs[ID_C_ven] = ( Q_mu * rgModelVars[ID_C_mu] / Kp_mu + Q_ad * rgModelVars[ID_C_ad] / Kp_ad + Q_te * rgModelVars[ID_C_te] / Kp_te + Q_sk * rgModelVars[ID_C_sk] / Kp_sk + Q_ht * rgModelVars[ID_C_ht] / Kp_ht + Q_br * rgModelVars[ID_C_br] / Kp_br + Q_ki * rgModelVars[ID_C_ki] / Kp_ki + Q_re * rgModelVars[ID_C_re] / Kp_re + Q_h * rgModelVars[ID_C_li] / Kp_li - Q_ven * rgModelVars[ID_C_ven] + vrgInputs[ID_Rate_in].dVal ) / V_ven ;

} /* CalcDeriv */


/*----- Model scaling */

void ScaleModel (PDOUBLE pdTime)
{

  Q_ven = 11.22 * pow ( BM , 0.81 ) ;

  Q_mu = Ff_mu * Q_ven ;
  Q_ad = Ff_ad * Q_ven ;
  Q_te = Ff_te * Q_ven ;
  Q_sk = Ff_sk * Q_ven ;
  Q_ht = Ff_ht * Q_ven ;
  Q_br = Ff_br * Q_ven ;
  Q_ki = Ff_ki * Q_ven ;
  Q_st = Ff_st * Q_ven ;
  Q_spl = Ff_spl * Q_ven ;
  Q_ha = Ff_ha * Q_ven ;
  Q_re = Ff_re * Q_ven ;

  Q_h = Q_ha + Q_st + Q_spl ;

  fub = fu / Ratio_BP ;

  Kp_ad = exp ( log_Kp_ad ) ;
  Cl_int = exp ( log_Cl_int ) ;
  fudge = exp ( log_fudge ) ;

  Kp_mu = Kp_mu_base * fudge ;
  Kp_te = Kp_te_base * fudge ;
  Kp_sk = Kp_sk_base * fudge ;
  Kp_ht = Kp_ht_base * fudge ;
  Kp_br = Kp_br_base * fudge ;
  Kp_ki = Kp_ki_base * fudge ;
  Kp_re = Kp_re_base * fudge ;
  Kp_st = Kp_st_base * fudge ;
  Kp_spl = Kp_spl_base * fudge ;
  Kp_li = Kp_li_base * fudge ;
  Kp_lu = Kp_lu_base * fudge ;

} /* ScaleModel */


/*----- Jacobian calculations */

void CalcJacob (PDOUBLE pdTime, double rgModelVars[],
                long column, double rgdJac[])
{

} /* CalcJacob */


/*----- Outputs calculations */

void CalcOutputs (double  rgModelVars[], double  rgDerivs[], PDOUBLE pdTime)
{

  rgModelVars[ID_C_plasma] = rgModelVars[ID_C_ven] / Ratio_BP ;
  rgModelVars[ID_C_plasma] = ( rgModelVars[ID_C_plasma] > 0 ? rgModelVars[ID_C_plasma] : 1E-30 ) ;

}  /* CalcOutputs */


