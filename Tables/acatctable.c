 /*********************************************************************************************************************
 *
 *  File:                acatctable.c
 *
 *  Last modification:   2012-11-15
 *
 *  Author:              P. R. Shah, M. C. VanDyke
 *
 *  COPYRIGHT (C):       2020. Northrop Grumman Corporation.  Unless otherwise marked, all files
 *                       contained herein are Northrop Grumman Proprietary Level <I>
 *
 *  COPYRIGHT NOTICE:    All information contained herein is, and remains the property of the
 *                       Northrop Grumman Corporation. The intellectual and technical concepts
 *                       contained herein are proprietary to Northrop Grumman Systems Corporation
 *                       and may be covered by U.S. and Foreign Patents, patents in process, and
 *                       are protected by trade secret or copyright law. Dissemination of this
 *                       information or reproduction of this material is strictly forbidden unless
 *                       prior written permission is obtained from Northrop Grumman.
 *
 *  WARNING:             The export of technical data without approval from the U.S. Department
 *                       of State is prohibited under the U.S. Arms Export Control Act, Title 22,
 *                       U.S.C., Sec. 2751, et. seq. and the International Traffic in Arms
 *                       Regulations (ITAR), 22 C.F.R. Sec. 120 et seq.   Violations of these laws
 *                       and regulations carry severe criminal penalties.
 *
 *  DESTRUCTION NOTICE:  Destroy by any method that will prevent disclosure of contents or
 *                       reconstruction.
 *
 *********************************************************************************************************************/


/*
** Spacecraft Attitude Control Parameter Table ...
*/

#include "u_proto.h"
#include "acsdefines.h"
#include "acatctable.h"

ac_atc_table_type  AcAtcTable =
{
  { 700.0, 1100.0}, /* Inertia11Lim */
  { -40.0,   40.0}, /* Inertia12Lim */
  { -40.0,   40.0}, /* Inertia13Lim */
  { 700.0, 1100.0}, /* Inertia22Lim */
  { -40.0,   40.0}, /* Inertia23Lim */
  { 200.0,  400.0}, /* Inertia33Lim */

  {{{  916.925,   -23.449,   -10.286 },    /* IscInit, kg-m^2, Mass Props Rev E BOL */
    {  -23.449,   883.866,     1.574 },    /* payloadAz = 90 / payloadEl = 0 */
    {  -10.286,     1.574,   340.438 }}},

  /* Standby RateNull CoarseSunAcq SunPoint DeltaV   Normal   Target   Mission */   /* --- Torque Enable Flags, NA */
  {  FALSE,    TRUE,     TRUE,     TRUE,     TRUE,    TRUE,    TRUE,    TRUE },     /* EnableCtlTorque */
  {  FALSE,    TRUE,     TRUE,     TRUE,     TRUE,    TRUE,    TRUE,    TRUE },     /* EnableGyrTorque */
  {  FALSE,    TRUE,     TRUE,     TRUE,     TRUE,    TRUE,    TRUE,    TRUE },     /* EnableCmdTorque */

  {                                 /* PassiveModeEnabled */
    FALSE                         , /* [True/False      ] PD_FAULT       */
    FALSE                         , /* [True/False      ] PD_IDLE        */
    FALSE                         , /* [True/False      ] PD_HOLD        */
    TRUE                          , /* [True/False      ] PD_SLEWING     */
    FALSE                         , /* [True/False      ] PD_TRACKING    */
    TRUE                          , /* [True/False      ] PD_DECELERATE  */
    FALSE                         , /* [True/False      ] PD_TRACK_TABLE */
    TRUE                            /* [True/False      ] PD_COMM_ANGLE  */
  },

  /* Stowed  Deploying  Deployed */                           /* --- EnableLPF, NA ... */
  {{ FALSE,    TRUE,      TRUE  },                            /* Standby        */
   { FALSE,    TRUE,      TRUE  },                            /* RateNull       */
   { FALSE,    TRUE,      TRUE  },                            /* CoarseSunAcq   */
   { FALSE,    TRUE,      TRUE  },                            /* CoarseSunPoint */
   { FALSE,    TRUE,      TRUE  },                            /* DeltaV         */
   { FALSE,    TRUE,      TRUE  },                            /* Normal         */
   { FALSE,    TRUE,      TRUE  },                            /* TargetPoint    */
   { FALSE,    TRUE,      TRUE  }},                           /* Mission        */

                                                              /* --- X-Axis Torque Filter ... */
  { 3,                                                        /* CascadeOrder */
    0, 0, 0,                                                  /* Pad structure */
       1.216355483255598E-1,                                  /* A0 */
   {{  1.437848788711524E+0,   9.999999999999927E-1 },        /* A1 A2 - 1st Filter */
    { -7.795636228047393E-1,   9.999999999999841E-1 },        /* A1 A2 - 2nd Filter */
    { -1.986179155592837E-1,   1.000000000000023E+0 }},       /* A1 A2 - 3rd Filter */
   {{ -9.106593886195251E-1,   7.978000333789819E-1 },        /* B1 B2 - 1st Filter */
    { -4.696648399744229E-1,   4.127456171133396E-1 },        /* B1 B2 - 2nd Filter */
    {  3.350109308789905E-2,   6.531978171884680E-2 }},       /* B1 B2 - 3rd Filter */
  },
                                                              /* --- Y-Axis Torque Filter ... */
  { 3,                                                        /* CascadeOrder */
    0, 0, 0,                                                  /* Pad structure */
       1.216355483255598E-1,                                  /* A0 */
   {{  1.437848788711524E+0,   9.999999999999927E-1 },        /* A1 A2 - 1st Filter */
    { -7.795636228047393E-1,   9.999999999999841E-1 },        /* A1 A2 - 2nd Filter */
    { -1.986179155592837E-1,   1.000000000000023E+0 }},       /* A1 A2 - 3rd Filter */
   {{ -9.106593886195251E-1,   7.978000333789819E-1 },        /* B1 B2 - 1st Filter */
    { -4.696648399744229E-1,   4.127456171133396E-1 },        /* B1 B2 - 2nd Filter */
    {  3.350109308789905E-2,   6.531978171884680E-2 }},       /* B1 B2 - 3rd Filter */
  },
                                                              /* --- Z-Axis Torque Filter ... */
  { 3,                                                        /* CascadeOrder */
    0, 0, 0,                                                  /* Pad structure */
       1.216355483255598E-1,                                  /* A0 */
   {{  1.437848788711524E+0,   9.999999999999927E-1 },        /* A1 A2 - 1st Filter */
    { -7.795636228047393E-1,   9.999999999999841E-1 },        /* A1 A2 - 2nd Filter */
    { -1.986179155592837E-1,   1.000000000000023E+0 }},       /* A1 A2 - 3rd Filter */
   {{ -9.106593886195251E-1,   7.978000333789819E-1 },        /* B1 B2 - 1st Filter */
    { -4.696648399744229E-1,   4.127456171133396E-1 },        /* B1 B2 - 2nd Filter */
    {  3.350109308789905E-2,   6.531978171884680E-2 }},       /* B1 B2 - 3rd Filter */
  },
  (180 * NUM_AC_CYCLES), /* MaxPassiveDurationCnt */
  { 0, 0, 0 },          /* Spare */
  {
                                                                       /* --- Attitude Error Limits ...    */
    {{ 0.0,               0.0,               0.0               }},     /* RateNullThetaErrBdyLmt, rad      */
    {{ 2.00E+0*DEG_2_RAD, 2.00E+0*DEG_2_RAD, 2.00E+0*DEG_2_RAD }},     /* CSAThetaErrBdyLmt, rad           */
    {{ 2.00E+0*DEG_2_RAD, 2.00E+0*DEG_2_RAD, 2.00E+0*DEG_2_RAD }},     /* CSPThetaErrBdyLmt, rad           */
    {{ 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD }},     /* TgtPntThetaErrBdyLmt, rad        */
    {{ 2.50E-1*DEG_2_RAD, 2.50E-1*DEG_2_RAD, 2.50E-1*DEG_2_RAD }},     /* NormalThetaErrBdyLmt, rad        */
    {{ 2.50E-1*DEG_2_RAD, 2.50E-1*DEG_2_RAD, 2.50E-1*DEG_2_RAD }},     /* MissionThetaErrBdyLmt, rad       */
    {{ 2.50E+0*DEG_2_RAD, 2.50E+0*DEG_2_RAD, 2.50E+0*DEG_2_RAD }},     /* DeltaVThetaErrBdyLmtBRE, rad     */
    {{ 2.50E+0*DEG_2_RAD, 2.50E+0*DEG_2_RAD, 2.50E+0*DEG_2_RAD }},     /* DeltaVThetaErrBdyLmtREA, rad     */
                                                                       /* --- Rate Error Limits ...        */
    {{ 2.50E-1*DEG_2_RAD, 2.50E-1*DEG_2_RAD, 2.50E-1*DEG_2_RAD }},     /* RateNullOmegaErrBdyLmt, rad/sec  */
    {{ 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD }},     /* CSAOmegaErrBdyLmt, rad/sec       */
    {{ 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD }},     /* CSPOmegaErrBdyLmt, rad/sec       */
    {{ 6.00E-1*DEG_2_RAD, 6.00E-1*DEG_2_RAD, 6.00E-1*DEG_2_RAD }},     /* TgtPntOmegaErrBdyLmt, rad/sec    */
    {{ 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD }},     /* NormalOmegaErrBdyLmt, rad/sec    */
    {{ 2.00E-2*DEG_2_RAD, 2.00E-2*DEG_2_RAD, 2.00E-2*DEG_2_RAD }},     /* MissionOmegaErrBdyLmt, rad/sec   */
    {{ 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD }},     /* DeltaVOmegaErrBdyLmtBRE, rad/sec */
    {{ 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD }},     /* DeltaVOmegaErrBdyLmtREA, rad/sec */
                                                                       /* --- Integral Error Limits ...    */
    {{ 0.0,               0.0,               0.0 }},                   /* RateNullIntegralErrBdyLmt, sec   */
    {{ 0.0,               0.0,               0.0 }},                   /* CSAIntegralErrBdyLmt, sec        */
    {{ 0.0,               0.0,               0.0 }},                   /* CSPIntegralErrBdyLmt, sec        */
    {{ 0.0,               0.0,               0.0 }},                   /* TgtPntIntegralErrBdyLmt, sec     */
    {{ 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD, 1.50E+0*DEG_2_RAD }},     /* NormalIntegralErrBdyLmt, sec     */
    {{ 5.00E+0*DEG_2_RAD, 5.00E+0*DEG_2_RAD, 5.00E+0*DEG_2_RAD }},     /* MissionIntegralErrBdyLmt, sec    */
    {{ 1.20E+1*DEG_2_RAD, 1.20E+1*DEG_2_RAD, 1.20E+1*DEG_2_RAD }},     /* DeltaVIntegralErrBdyLmtBRE, sec  */
    {{ 1.20E+1*DEG_2_RAD, 1.20E+1*DEG_2_RAD, 1.20E+1*DEG_2_RAD }},     /* DeltaVIntegralErrBdyLmtREA, sec  */
  },
                                                              /* --- Attitude Control Gains, 1/sec^2 ... */
  {{{{ 0.0,       0.0,       0.0       }},                    /* Standby ... Stowed */
    {{ 0.0,       0.0,       0.0       }},                    /* Standby ... Deploying */
    {{ 0.0,       0.0,       0.0       }}},                   /* Standby ... Deployed */
   {{{ 0.0,       0.0,       0.0       }},                    /* RateNull .... Stowed */
    {{ 0.0,       0.0,       0.0       }},                    /* RateNull .... Deploying */
    {{ 0.0,       0.0,       0.0       }}},                   /* RateNull .... Deployed */
   {{{ 6.1685E-3, 6.1685E-3, 6.1685E-3 }},                    /* CSA .... Stowed */
    {{ 6.1685E-3, 6.1685E-3, 6.1685E-3 }},                    /* CSA .... Deploying */
    {{ 6.1685E-3, 6.1685E-3, 6.1685E-3 }}},                   /* CSA .... Deployed */
   {{{ 6.1685E-3, 6.1685E-3, 6.1685E-3 }},                    /* CSP .... Stowed */
    {{ 6.1685E-3, 6.1685E-3, 6.1685E-3 }},                    /* CSP .... Deploying */
    {{ 6.1685E-3, 6.1685E-3, 6.1685E-3 }}},                   /* CSP .... Deployed */
   {{{ 5.5630E-2, 5.5630E-2, 5.5630E-2 }},                    /* DeltaV .... Stowed */
    {{ 5.5630E-2, 5.5630E-2, 5.5630E-2 }},                    /* DeltaV .... Deploying */
    {{ 5.5630E-2, 5.5630E-2, 5.5630E-2 }}},                   /* DeltaV .... Deployed */
   {{{ 1.3907E-2, 1.3907E-2, 1.3907E-2 }},                    /* Normal .... Stowed */
    {{ 1.3907E-2, 1.3907E-2, 1.3907E-2 }},                    /* Normal .... Deploying */
    {{ 1.3907E-2, 1.3907E-2, 1.3907E-2 }}},                   /* Normal .... Deployed */
   {{{ 5.9522E-2, 5.9522E-2, 5.9522E-2 }},                    /* TgtPnt .... Stowed */
    {{ 5.9522E-2, 5.9522E-2, 5.9522E-2 }},                    /* TgtPnt .... Deploying */
    {{ 5.9522E-2, 5.9522E-2, 5.9522E-2 }}},                   /* TgtPnt .... Deployed */
   {{{ 1.4522e-3, 1.4522e-3, 1.4522e-3 }},                    /* Mission .... Stowed */
    {{ 1.4522e-3, 1.4522e-3, 1.4522e-3 }},                    /* Mission .... Deploying */
    {{ 1.4522e-3, 1.4522e-3, 1.4522e-3 }}}},                  /* Mission .... Deployed */

                                                              /* --- Rate Control Gains, 1/sec ... */
  {{{{ 0.0,       0.0,       0.0       }},                    /* Standby ... Stowed */
    {{ 0.0,       0.0,       0.0       }},                    /* Standby ... Deploying */
    {{ 0.0,       0.0,       0.0       }}},                   /* Standby ... Deployed */
   {{{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }},                    /* RateNull .... Stowed */
    {{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }},                    /* RateNull .... Deploying */
    {{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }}},                   /* RateNull .... Deployed */
   {{{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }},                    /* CSA .... Stowed */
    {{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }},                    /* CSA .... Deploying */
    {{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }}},                   /* CSA .... Deployed */
   {{{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }},                    /* CSP .... Stowed */
    {{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }},                    /* CSP .... Deploying */
    {{ 1.1107E-1, 1.1107E-1, 1.1107E-1 }}},                   /* CSP .... Deployed */
   {{{ 3.4197E-1, 3.4197E-1, 3.4197E-1 }},                    /* DeltaV .... Stowed */
    {{ 3.4197E-1, 3.4197E-1, 3.4197E-1 }},                    /* DeltaV .... Deploying */
    {{ 3.4197E-1, 3.4197E-1, 3.4197E-1 }}},                   /* DeltaV .... Deployed */
   {{{ 1.7099E-1, 1.7099E-1, 1.7099E-1 }},                    /* Normal .... Stowed */
    {{ 1.7099E-1, 1.7099E-1, 1.7099E-1 }},                    /* Normal .... Deploying */
    {{ 1.7099E-1, 1.7099E-1, 1.7099E-1 }}},                   /* Normal .... Deployed */
   {{{ 3.5657E-1, 3.5657E-1, 3.5657E-1 }},                    /* TgtPnt .... Stowed */
    {{ 3.5657E-1, 3.5657E-1, 3.5657E-1 }},                    /* TgtPnt .... Deploying */
    {{ 3.5657E-1, 3.5657E-1, 3.5657E-1 }}},                   /* TgtPnt .... Deployed */
   {{{ 5.4901e-2, 5.4901e-2, 5.4901e-2 }},                    /* Mission .... Stowed */
    {{ 5.4901e-2, 5.4901e-2, 5.4901e-2 }},                    /* Mission .... Deploying */
    {{ 5.4901e-2, 5.4901e-2, 5.4901e-2 }}}},                  /* Mission .... Deployed */

                                                              /* --- Integral Control Gains, 1/sec^3 ... */
  {{{{ 0.0,       0.0,       0.0       }},                    /* Standby ... Stowed */
    {{ 0.0,       0.0,       0.0       }},                    /* Standby ... Deploying */
    {{ 0.0,       0.0,       0.0       }}},                   /* Standby ... Deployed */
   {{{ 0.0,       0.0,       0.0       }},                    /* RateNull .. Stowed */
    {{ 0.0,       0.0,       0.0       }},                    /* RateNull .. Deploying */
    {{ 0.0,       0.0,       0.0       }}},                   /* RateNull .. Deployed */
   {{{ 0.0,       0.0,       0.0       }},                    /* CSA ....... Stowed */
    {{ 0.0,       0.0,       0.0       }},                    /* CSA ....... Deploying */
    {{ 0.0,       0.0,       0.0       }}},                   /* CSA ....... Deployed */
   {{{ 0.0,       0.0,       0.0       }},                    /* CSP ....... Stowed */
    {{ 0.0,       0.0,       0.0       }},                    /* CSP ....... Deploying */
    {{ 0.0,       0.0,       0.0       }}},                   /* CSP ....... Deployed */
   {{{ 2.6789E-3, 2.6789E-3, 2.6789E-3 }},                    /* DeltaV .... Stowed */
    {{ 2.6789E-3, 2.6789E-3, 2.6789E-3 }},                    /* DeltaV .... Deploying */
    {{ 2.6789E-3, 2.6789E-3, 2.6789E-3 }}},                   /* DeltaV .... Deployed */
   {{{ 3.3487E-4, 3.3487E-4, 3.3487E-4 }},                    /* Normal .... Stowed */
    {{ 3.3487E-4, 3.3487E-4, 3.3487E-4 }},                    /* Normal .... Deploying */
    {{ 3.3487E-4, 3.3487E-4, 3.3487E-4 }}},                   /* Normal .... Deployed */
   {{{ 0.0,       0.0,       0.0       }},                    /* TgtPnt .... Stowed */
    {{ 0.0,       0.0,       0.0       }},                    /* TgtPnt .... Deploying */
    {{ 0.0,       0.0,       0.0       }}},                   /* TgtPnt .... Deployed */
   {{{ 1.0335e-5, 1.0335e-5, 1.0335e-5 }},                    /* Mission .... Stowed */
    {{ 1.0335e-5, 1.0335e-5, 1.0335e-5 }},                    /* Mission .... Deploying */
    {{ 1.0335e-5, 1.0335e-5, 1.0335e-5 }}}},                  /* Mission .... Deployed */

  {                                                           /* --- FDC ... */
    {                                                         /* --- SunAcq ... */
      {{ 5.00*DEG_2_RAD, 5.00*DEG_2_RAD, 5.00*DEG_2_RAD }},   /* ThetaErrHardThr, rad */
      {{ 4.09*DEG_2_RAD, 4.09*DEG_2_RAD, 4.09*DEG_2_RAD }},   /* ThetaErrSoftThr, rad     (VMAG=7.1) */
      {{ 0.86*DEG_2_RAD, 0.86*DEG_2_RAD, 0.86*DEG_2_RAD }},   /* OmegaErrHardThr, rad/sec (VMAG=1.5) */
      {{ 0.57*DEG_2_RAD, 0.57*DEG_2_RAD, 0.57*DEG_2_RAD }},   /* OmegaErrSoftThr, rad/sec (VMAG=1.0) */

      60*NUM_AC_CYCLES,                                       /* ThetaErrHardCnt, cnt */
      60*NUM_AC_CYCLES,                                       /* ThetaErrSoftCnt, cnt */
      60*NUM_AC_CYCLES,                                       /* OmegaErrHardCnt, cnt */
      60*NUM_AC_CYCLES,                                       /* OmegaErrSoftCnt, cnt */

      0.40*DEG_2_RAD,                                         /* StaXResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaYResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaZResidualThr, rad */
      1.5,                                                    /* DeltaSysMomThr, N-m-s */

      300*NUM_AC_CYCLES,                                      /* ResidualTestCnt, cnt */
      1,                                                      /* DeltaSysMomCnt, cnt */
      { 0, 0 }                                                /* SpareWord */
    },
    {                                                         /* --- TgtPnt ... */
      {{ 1.00*DEG_2_RAD, 1.00*DEG_2_RAD, 1.00*DEG_2_RAD }},   /* ThetaErrHardThr, rad */
      {{ 0.50*DEG_2_RAD, 0.50*DEG_2_RAD, 0.50*DEG_2_RAD }},   /* ThetaErrSoftThr, rad */
      {{ 0.18*DEG_2_RAD, 0.18*DEG_2_RAD, 0.18*DEG_2_RAD }},   /* OmegaErrHardThr, rad/sec */
      {{ 0.09*DEG_2_RAD, 0.09*DEG_2_RAD, 0.09*DEG_2_RAD }},   /* OmegaErrSoftThr, rad/sec */

      10*NUM_AC_CYCLES,                                       /* ThetaErrHardCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* ThetaErrSoftCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* OmegaErrHardCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* OmegaErrSoftCnt, cnt */

      0.40*DEG_2_RAD,                                         /* StaXResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaYResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaZResidualThr, rad */
      1.5,                                                    /* DeltaSysMomThr, N-m-s */

      300*NUM_AC_CYCLES,                                      /* ResidualTestCnt, cnt */
      1,                                                      /* DeltaSysMomCnt, cnt */
      { 0, 0 }                                                /* SpareWord */
    },
    {                                                         /* --- Normal ... */
      {{ 1.00*DEG_2_RAD, 1.00*DEG_2_RAD, 1.00*DEG_2_RAD }},   /* ThetaErrHardThr, rad */
      {{ 0.50*DEG_2_RAD, 0.50*DEG_2_RAD, 0.50*DEG_2_RAD }},   /* ThetaErrSoftThr, rad */
      {{ 0.18*DEG_2_RAD, 0.18*DEG_2_RAD, 0.18*DEG_2_RAD }},   /* OmegaErrHardThr, rad/sec */
      {{ 0.09*DEG_2_RAD, 0.09*DEG_2_RAD, 0.09*DEG_2_RAD }},   /* OmegaErrSoftThr, rad/sec */

      10*NUM_AC_CYCLES,                                       /* ThetaErrHardCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* ThetaErrSoftCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* OmegaErrHardCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* OmegaErrSoftCnt, cnt */

      0.40*DEG_2_RAD,                                         /* StaXResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaYResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaZResidualThr, rad */
      1.5,                                                    /* DeltaSysMomThr, N-m-s */

      300*NUM_AC_CYCLES,                                      /* ResidualTestCnt, cnt */
      1,                                                      /* DeltaSysMomCnt, cnt */
      { 0, 0 }                                                /* SpareWord */
    },
    {                                                         /* --- Mission ... */
      {{ 15.00*DEG_2_RAD, 15.00*DEG_2_RAD, 45.00*DEG_2_RAD }},/* ThetaErrHardThr, rad */
      {{ 10.00*DEG_2_RAD, 10.00*DEG_2_RAD, 30.00*DEG_2_RAD }},/* ThetaErrSoftThr, rad */
      {{ 0.15*DEG_2_RAD, 0.15*DEG_2_RAD, 0.15*DEG_2_RAD }},   /* OmegaErrHardThrStationary, rad/sec */
      {{ 0.10*DEG_2_RAD, 0.10*DEG_2_RAD, 0.10*DEG_2_RAD }},   /* OmegaErrSoftThrStationary, rad/sec */
      {{ 0.45*DEG_2_RAD, 0.45*DEG_2_RAD, 1.50*DEG_2_RAD }},   /* OmegaErrHardThrMoving, rad/sec */
      {{ 0.30*DEG_2_RAD, 0.30*DEG_2_RAD, 1.00*DEG_2_RAD }},   /* OmegaErrSoftThrMoving, rad/sec */

      10*NUM_AC_CYCLES,                                       /* ThetaErrHardCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* ThetaErrSoftCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* OmegaErrHardCnt, cnt */
      10*NUM_AC_CYCLES,                                       /* OmegaErrSoftCnt, cnt */

      0.40*DEG_2_RAD,                                         /* StaXResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaYResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaZResidualThr, rad */
      1.5,                                                    /* DeltaSysMomThr, N-m-s */

      300*NUM_AC_CYCLES,                                      /* ResidualTestCnt, cnt */
      1,                                                      /* DeltaSysMomCnt, cnt */
      {                                                       /* MplSlewingState      */
        FALSE,                                                /* [True/False      ] PD_FAULT       */
        FALSE,                                                /* [True/False      ] PD_IDLE        */
        FALSE,                                                /* [True/False      ] PD_HOLD        */
        TRUE ,                                                /* [True/False      ] PD_SLEWING     */
        FALSE,                                                /* [True/False      ] PD_TRACKING    */
        TRUE ,                                                /* [True/False      ] PD_DECELERATE  */
        TRUE ,                                                /* [True/False      ] PD_TRACK_TABLE */
        TRUE                                                  /* [True/False      ] PD_COMM_ANGLE  */
      },
      { 0, 0 }                                                /* SpareWord */
    },
    {                                                         /* --- DeltaV ... */
      {{ 4.00*DEG_2_RAD, 4.00*DEG_2_RAD, 4.00*DEG_2_RAD }},   /* ThetaErrHardThrBRE, rad */
      {{ 2.00*DEG_2_RAD, 2.00*DEG_2_RAD, 2.00*DEG_2_RAD }},   /* ThetaErrSoftThrBRE, rad */
      {{ 0.50*DEG_2_RAD, 0.50*DEG_2_RAD, 0.50*DEG_2_RAD }},   /* OmegaErrHardThrBRE, rad/sec */
      {{ 0.20*DEG_2_RAD, 0.20*DEG_2_RAD, 0.20*DEG_2_RAD }},   /* OmegaErrSoftThrBRE, rad/sec */

      10*NUM_AC_CYCLES,                                       /* ThetaErrHardCntBRE, cnt */
      10*NUM_AC_CYCLES,                                       /* ThetaErrSoftCntBRE, cnt */
      10*NUM_AC_CYCLES,                                       /* OmegaErrHardCntBRE, cnt */
      10*NUM_AC_CYCLES,                                       /* OmegaErrSoftCntBRE, cnt */

      {{ 5.00*DEG_2_RAD, 5.00*DEG_2_RAD, 5.00*DEG_2_RAD }},   /* ThetaErrHardThrREA, rad */
      {{ 4.00*DEG_2_RAD, 4.00*DEG_2_RAD, 4.00*DEG_2_RAD }},   /* ThetaErrSoftThrREA, rad */
      {{ 1.00*DEG_2_RAD, 1.00*DEG_2_RAD, 1.00*DEG_2_RAD }},   /* OmegaErrHardThrREA, rad/sec */
      {{ 1.00*DEG_2_RAD, 1.00*DEG_2_RAD, 1.00*DEG_2_RAD }},   /* OmegaErrSoftThrREA, rad/sec */

      4*NUM_AC_CYCLES,                                        /* ThetaErrHardCntREA, cnt */
      4*NUM_AC_CYCLES,                                        /* ThetaErrSoftCntREA, cnt */
      4*NUM_AC_CYCLES,                                        /* OmegaErrHardCntREA, cnt */
      4*NUM_AC_CYCLES,                                        /* OmegaErrSoftCntREA, cnt */

      0.40*DEG_2_RAD,                                         /* StaXResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaYResidualThr, rad */
      0.40*DEG_2_RAD,                                         /* StaZResidualThr, rad */
      4,                                                      /* DeltaSysMomThr, N-m-s */

      300*NUM_AC_CYCLES,                                      /* ResidualTestCnt, cnt */
      1,                                                      /* DeltaSysMomCnt, cnt */
      { 0, 0 }                                                /* SpareWord */
    },
  }
};

ac_tgt_pnt_table_type  AcTgtPntTable =
{
  SQR(0.10 * DEG_2_RAD),                                      /* OmegaEstMagSqrLmt, rad/sec */
  (1.0 * DEG_2_RAD),                                          /* CaptureAngle, rad */
  (0.001 * DEG_2_RAD),                                        /* OmegaBdyWrtRefMagInc, rad/sec */
  (0.65 * DEG_2_RAD),                                         /* OmegaSlewLmtInit, rad/sec */
  {{ 0.00000000000000,
     0.00000000000000,
     0.00000000000000,
     1.00000000000000 }},                                     /* DeltaQInit, ND */
  {{ 0.0, 1.0, 0.0 }},                                        /* SadAxisBdy, ND */
  (5.0 * DEG_2_RAD),                                          /* TwoAxisSteeringDeadband, rad */
  0.01*DEG_2_RAD,                                             /* SmallSlewThr, ND */
  15 * MIN_2_SEC*NUM_AC_CYCLES,                               /* NullOmegaPhaseCnt, cnt */
  30 * NUM_AC_CYCLES,                                         /* OmegaSettlingCntInit, cnt */
  (FALSE),                                                    /* EnableResetStopSlewAtt, ND */
  RAMP_TYPE_LINEAR                                            /* SlewRampTypeInit */
};

