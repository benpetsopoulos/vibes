 /*********************************************************************************************************************
 *
 *  File:                acsolartable.h
 *
 *  Last modification:   2012-10-12
 *
 *  Author:              P. R. Shah
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

/************************************/
#pragma pack()       /* Green Hills */
/************************************/

#ifndef _acsolartable_h_
#define _acsolartable_h_

#pragma pack(4)

/*
** Solar Ephemeris Parameter Table (Coefficients From 1997 Astronomical Almanac) ...
*/

typedef struct ac_solar_table_ {

  dReal  SMSE0;     /* Inclination Of Ecliptic Equation Coefficient (rad) */
  dReal  SMSE1;     /* Inclination Of Ecliptic Equation Frequency Constant (rad/day) */
  dReal  SMMA1;     /* Mean Anomaly Equation Coefficient (rad) */
  dReal  SMMA2;     /* Mean Anomaly Equation Frequency Constant (rad/day) */
  dReal  SMML1;     /* Mean Longitude Equation Coefficient (rad) */
  dReal  SMML2;     /* Mean Longitude Equation Frequency Coefficient (rad/day) */
  dReal  SMEL1;     /* Mean Longitude Correction Equation Coefficient (rad) */
  dReal  SMEL2;     /* Mean Longitude Correction Equation Coefficient (rad) */
  dReal  SMGPL;     /* General Precession In Longitude At J2000.0 (rad/day) */
  dReal  SMR1;      /* Distance From Earth To Sun Coefficient (a.u.) */
  dReal  SMR2;      /* Distance From Earth To Sun Coefficient (a.u.) */
  dReal  SMR3;      /* Distance From Earth To Sun Coefficient (a.u.) */
  dReal  RS0;       /* Nominal Earth To Sun Distance (m) */

  dword  ComputeVelocityCnt;  /* Sun Velocity Computation Period, LSB = 1 sec (cnt) */
  dword  SpareDword;          /* Pad structure */

} ac_solar_table_type;

#endif

/************************************/
#pragma pack()       /* Green Hills */
/************************************/
