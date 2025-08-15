 /*********************************************************************************************************************
 *
 *  File:                adtable.c
 *
 *  Last modification:   2012-11-16
 *
 *  Author:              P. R. Shah, W. M. Miller
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
** Spacecraft Attitude Determination Parameter Table ...
*/

#include "acstypes.h"
#include "acsdefines.h"
#include "adtable.h"

ad_table_type AdTable = {
{
  { SQR( 0.05 * DEG_2_RAD)        , /* [rad^2           ] PInitial[0][0], Gyroed */
    SQR( 0.05 * DEG_2_RAD)        , /* [rad^2           ] PInitial[0][1], Gyroed */
    SQR( 0.05 * DEG_2_RAD)        , /* [rad^2           ] PInitial[0][2], Gyroed */
    SQR( 1.0 * ARCSEC_2_RAD)      , /* [(rad/sec)^2     ] PInitial[0][3], Gyroed */
    SQR( 1.0 * ARCSEC_2_RAD)      , /* [(rad/sec)^2     ] PInitial[0][4], Gyroed */
    SQR( 1.0 * ARCSEC_2_RAD) }    , /* [(rad/sec)^2     ] PInitial[0][5], Gyroed */
  { SQR( 0.05 * DEG_2_RAD)        , /* [rad^2           ] PInitial[1][0], Gyroless */
    SQR( 0.05 * DEG_2_RAD)        , /* [rad^2           ] PInitial[1][1], Gyroless */
    SQR( 0.05 * DEG_2_RAD)        , /* [rad^2           ] PInitial[1][2], Gyroless */
    SQR( 1.0 * ARCSEC_2_RAD)      , /* [(rad/sec)^2     ] PInitial[1][3], Gyroless */
    SQR( 1.0 * ARCSEC_2_RAD)      , /* [(rad/sec)^2     ] PInitial[1][4], Gyroless */
    SQR( 1.0 * ARCSEC_2_RAD) }      /* [(rad/sec)^2     ] PInitial[1][5], Gyroless */
},
{
  { SQR(  0.1 * DEG_2_RAD)        , /* [rad^2           ] PDivergenceThr[0][0], Gyroed */
    SQR(  0.1 * DEG_2_RAD)        , /* [rad^2           ] PDivergenceThr[0][1], Gyroed */
    SQR(  0.1 * DEG_2_RAD)        , /* [rad^2           ] PDivergenceThr[0][2], Gyroed */
    SQR( 15.0 * ARCSEC_2_RAD)     , /* [(rad/sec)^2     ] PDivergenceThr[0][3], Gyroed */
    SQR( 15.0 * ARCSEC_2_RAD)     , /* [(rad/sec)^2     ] PDivergenceThr[0][4], Gyroed */
    SQR( 15.0 * ARCSEC_2_RAD) }   , /* [(rad/sec)^2     ] PDivergenceThr[0][5], Gyroed */
  { SQR(  0.1 * DEG_2_RAD)        , /* [rad^2           ] PDivergenceThr[1][0], Gyroless */
    SQR(  0.1 * DEG_2_RAD)        , /* [rad^2           ] PDivergenceThr[1][1], Gyroless */
    SQR(  0.1 * DEG_2_RAD)        , /* [rad^2           ] PDivergenceThr[1][2], Gyroless */
    SQR(100.0 * ARCSEC_2_RAD)     , /* [(rad/sec)^2     ] PDivergenceThr[1][3], Gyroless */
    SQR(100.0 * ARCSEC_2_RAD)     , /* [(rad/sec)^2     ] PDivergenceThr[1][4], Gyroless */
    SQR(100.0 * ARCSEC_2_RAD) }     /* [(rad/sec)^2     ] PDivergenceThr[1][5], Gyroless */
},
{
  { SQR(25.0 * ARCSEC_2_RAD)      , /* [rad^2           ] PCoarseConvergenceThr[0][0], Gyroed */
    SQR(25.0 * ARCSEC_2_RAD)      , /* [rad^2           ] PCoarseConvergenceThr[0][1], Gyroed */
    SQR(25.0 * ARCSEC_2_RAD)      , /* [rad^2           ] PCoarseConvergenceThr[0][2], Gyroed */
    SQR( 0.7 * ARCSEC_2_RAD)      , /* [(rad/sec)^2     ] PCoarseConvergenceThr[0][3], Gyroed */
    SQR( 0.7 * ARCSEC_2_RAD)      , /* [(rad/sec)^2     ] PCoarseConvergenceThr[0][4], Gyroed */
    SQR( 0.7 * ARCSEC_2_RAD) }    , /* [(rad/sec)^2     ] PCoarseConvergenceThr[0][5], Gyroed */
  { SQR(50.0 * ARCSEC_2_RAD)      , /* [rad^2           ] PCoarseConvergenceThr[1][0], Gyroless */
    SQR(50.0 * ARCSEC_2_RAD)      , /* [rad^2           ] PCoarseConvergenceThr[1][1], Gyroless */
    SQR(50.0 * ARCSEC_2_RAD)      , /* [rad^2           ] PCoarseConvergenceThr[1][2], Gyroless */
    SQR(10.0 * ARCSEC_2_RAD)      , /* [(rad/sec)^2    ] PCoarseConvergenceThr[1][3], Gyroless */
    SQR(10.0 * ARCSEC_2_RAD)      , /* [(rad/sec)^2    ] PCoarseConvergenceThr[1][4], Gyroless */
    SQR(10.0 * ARCSEC_2_RAD) }      /* [(rad/sec)^2    ] PCoarseConvergenceThr[1][5], Gyroless */
},
{
  { SQR( 5.0 * ARCSEC_2_RAD)      , /* [rad^2          ] PFineConvergenceThr[0][0], Gyroed */
    SQR( 5.0  * ARCSEC_2_RAD)     , /* [rad^2          ] PFineConvergenceThr[0][1], Gyroed */
    SQR( 5.0 * ARCSEC_2_RAD)      , /* [rad^2          ] PFineConvergenceThr[0][2], Gyroed */
    SQR( 0.2  * ARCSEC_2_RAD)     , /* [(rad/sec)^2    ] PFineConvergenceThr[0][3], Gyroed */
    SQR( 0.2  * ARCSEC_2_RAD)     , /* [(rad/sec)^2    ] PFineConvergenceThr[0][4], Gyroed */
    SQR( 0.2  * ARCSEC_2_RAD) }   , /* [(rad/sec)^2    ] PFineConvergenceThr[0][5], Gyroed */
  { SQR(25.0 * ARCSEC_2_RAD)      , /* [rad^2          ] PFineConvergenceThr[1][0], Gyroless */
    SQR(25.0 * ARCSEC_2_RAD)      , /* [rad^2          ] PFineConvergenceThr[1][1], Gyroless */
    SQR(25.0 * ARCSEC_2_RAD)      , /* [rad^2          ] PFineConvergenceThr[1][2], Gyroless */
    SQR( 5.0  * ARCSEC_2_RAD)     , /* [(rad/sec)^2    ] PFineConvergenceThr[1][3], Gyroless */
    SQR( 5.0  * ARCSEC_2_RAD)     , /* [(rad/sec)^2    ] PFineConvergenceThr[1][4], Gyroless */
    SQR( 5.0  * ARCSEC_2_RAD) }     /* [(rad/sec)^2    ] PFineConvergenceThr[1][5], Gyroless */
},
{
  360.0                            , /* [ND              ] k[0] */
  360.0                            , /* [ND              ] k[1] */
  360.0                              /* [ND              ] k[2] */
},
{
  180.0 * ARCSEC_2_RAD            , /* [rad             ] ResEditAngleThr[0] */
  180.0 * ARCSEC_2_RAD            , /* [rad             ] ResEditAngleThr[1] */
  360.0 * ARCSEC_2_RAD              /* [rad             ] ResEditAngleThr[2] */
},
                                    /* NoIruQ */
  { { {  0.33e-08,  0.0,       0.0,      -0.30e-11,  0.0,       0.0},           /* SELECT_JET */
      {  0.0,       0.33e-08,  0.0,       0.0,      -0.30e-11,  0.0},           /* Qfinal from DN-STAR-ADCS-015  */
      {  0.0,       0.0,       0.33e-08,  0.0,       0.0,      -0.30e-11},
      { -0.30e-11,  0.0,       0.0,       0.60e-011, 0.0,       0.0},
      {  0.0,      -0.30e-11,  0.0,       0.0,       0.60e-011, 0.0},
      {  0.0,       0.0,      -0.30e-11,  0.0,       0.0,       0.60e-11} },

    { {  0.33e-08,  0.0,       0.0,      -0.30e-11,  0.0,       0.0},           /* SELECT_RWA */
      {  0.0,       0.33e-08,  0.0,       0.0,      -0.30e-11,  0.0},           /* Qfinal from DN-STAR-ADCS-015  */
      {  0.0,       0.0,       0.33e-08,  0.0,       0.0,      -0.30e-11},
      { -0.30e-11,  0.0,       0.0,       0.60e-011, 0.0,       0.0},
      {  0.0,      -0.30e-11,  0.0,       0.0,       0.60e-011, 0.0},
      {  0.0,       0.0,      -0.30e-11,  0.0,       0.0,       0.60e-11} } },

                                    /* Kd, 1/s^2 */
  { { 1.0e-4, 1.0e-4, 1.0e-4},      /* SELECT_JET */
    { 1.0e-6, 1.0e-6, 1.0e-6} },    /* SELECT_RWA */

  {{ 5.0E-3, 5.0E-3, 5.0E-3 }},     /* AlphaDstEstBdyLmt, rad/sec^2 */

  {{ 2250000*DEG_2_RAD,             /* SysMomEstBdyLmt[0], N-m-s */
     2250000*DEG_2_RAD,             /* SysMomEstBdyLmt[1], N-m-s */
     2250000*DEG_2_RAD }},          /* SysMomEstBdyLmt[2], N-m-s */

  { 0.25 },                         /* KStaRateUpdateGain (SORCE used 0.25) */

  {                                 /* DisGyroBiasEstInPldState */
    FALSE                         , /* [True/False      ] PD_FAULT       */
    FALSE                         , /* [True/False      ] PD_IDLE        */
    FALSE                         , /* [True/False      ] PD_HOLD        */
    TRUE                          , /* [True/False      ] PD_SLEWING     */
    FALSE                         , /* [True/False      ] PD_TRACKING    */
    TRUE                          , /* [True/False      ] PD_DECELERATE  */
    FALSE                         , /* [True/False      ] PD_TRACK_TABLE */
    TRUE                            /* [True/False      ] PD_COMM_ANGLE  */
  }
};

