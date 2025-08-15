 /*********************************************************************************************************************
 *
 *  File:                acscephtable.c
 *
 *  Last modification:   2025-01-29
 *
 *  Author:              P. R. Shah, H. J. Weigl, J. E. Jones, N. W. Wright
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
** Spacecraft Ephemeris Parameter Table ...
*/

#include "acstypes.h"
#include "acsdefines.h"
#include "acscephtable.h"

ac_sceph_table_type  AcScEphTable =
{
  20.0,                                /* ScEphDtThr For Propagating Eph, sec */
  1.0 * DAY_2_SEC,                     /* ScEphTimeWarnHiThr For Eph UpdateTime Check, sec */
  6378136.6,                           /* RscMagThr, m */
  150.0 * 1000.0,                      /* PositionLmt For Accepting New EPV, m */
  1.5   * 1000.0,                      /* VelocityLmt For Accepting New EPV, m/s */

  1.32712442079556E+20,                /* SunMu (m^3/s^2) */
  4.90279918585524E+12,                /* MoonMu (m^3/s^2) */

  { 764.09939-50, 897.40621+50},       /* ScMassLim, kg, rev J Mass Properties */
  897.39939,                           /* MassInit Initial Spacecraft Mass, kg, rev J Mass Properties*/

  { -0.02304, -0.00087, 1.06976 },     /* ScCmInit Initial Spacecraft Center of Mass (m), rev J Mass Properties MOL */

  { -0.05005, 0.02501},                /* ScCmLimX Spacecraft CM X Limits (m), rev J Mass Properties +/- 25 mm */
  { -0.02595, 0.02485},                /* ScCmLimY Spacecraft CM Y Limits (m), rev J Mass Properties +/- 25 mm */
  {  0.93031, 1.26569},                /* ScCmLimZ Spacecraft CM Z Limits (m), rev J Mass Properties +/- 100 mm */

  6.37813660000000E+06,                /* EarthRadius At Equator, m */
  3.98600441800000E+14,                /* EarthMu (m^3/s^2) */
  0.081819300876173,                   /* Earth Eccentricity Received from Tim Berman - 9/28/2018 */
                                       /* From JGM-3 Geopotential Model ... */
  1.08262668355315E-03,                /* J2 Zonal Harmonic */
 -2.53265648533224E-06,                /* J3 Zonal Harmonic */
 -1.61962159136700E-06,                /* J4 Zonal Harmonic */
  1.81543019473806E-06,                /* CS22, Sectoral Harmonic, Sqrt (C22^2 + S22^2) */
 -5.21112788884155E-01,                /* ANG22, Result Of atan2(S22, C22), rad,  */
  0.01,                                /* DeltaV Estimate Auto Select Acceleration Threshold, m/s^2 */

  {                                    /* Goods ... */
  0.5,                                 /* DeltaPropTime (sec) */
  PRECISION_LOW,                       /* PrecisionThr (an_precision_enum) */
  QUALITY_LOW,                         /* QualityThr (an_quality_enum) */
  {0,0}                                /* Spare */
  },

  0xFFFFFFFF,                          /* SpoofUnusedReasonMask */
  {0,0}                                /* Spare */
};

