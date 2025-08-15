 /*********************************************************************************************************************
 *
 *  File:                acscephtable.h
 *
 *  Last modification:   2012-12-07
 *
 *  Author:              P. R. Shah, H. J. Weigl, J. E. Jones
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

#ifndef _acscephtable_h_
#define _acscephtable_h_

#pragma pack(4)

/*
** Spacecraft Ephemeris Parameter Table ...
*/

typedef struct ac_sceph_table_ {

  dReal    ScEphDtThr;            /* ScEphDtThr For Propagating Eph, sec */
  dReal    ScEphTimeWarnHiThr;    /* ScEphTimeWarnHiThr For Eph UpdateTime Check, sec */
  dReal    RscMagThr;             /* RscMagThr, m */
  dReal    PositionLmt;           /* PositionLmt For Accepting New EPV, m */
  dReal    VelocityLmt;           /* VelocityLmt For Accepting New EPV, m/s */

  dReal    SunMu;                 /* SunMu, m^3/s^2 */
  dReal    MoonMu;                /* MoonMu, m^3/s^2 */

  dReal    ScMassLim[2];          /* Spacecraft Mass Bounds, kg */
  dReal    MassInit;              /* Initial Spacecraft Mass, kg */

  uVector  ScCmInit;              /* Initial Spacecraft Center of Mass, m */

  dReal    ScCmLimX[2];           /* Spacecraft Center of Mass X Limits, m */
  dReal    ScCmLimY[2];           /* Spacecraft Center of Mass Y Limits, m */
  dReal    ScCmLimZ[2];           /* Spacecraft Center of Mass Z Limits, m */

  dReal    EarthRadius;           /* EarthRadius At Equator, m */
  dReal    EarthMu;               /* EarthMu, m^3/s^2 */
  dReal    EarthEccentricity;     /* Earth Eccentricity, unitless */
                                  /* From JGM-3 Geopotential Model ... */
  dReal    J2;                    /* J2 Zonal Harmonic */
  dReal    J3;                    /* J3 Zonal Harmonic */
  dReal    J4;                    /* J4 Zonal Harmonic */
  dReal    CS22;                  /* CS22, Sectoral Harmonic, Sqrt (C22^2 + S22^2) */
  dReal    ANG22;                 /* ANG22, Result Of atan2(S22, C22), rad,  */
  dReal    DvEstAutoSelAccelThr;  /* DeltaV Estimate Auto Select Acceleration Threshold, m/s^2 */

  struct {
    dReal    DeltaPropTime;        /* Delta from TimeSinceJ2000Sec that AN/GOODS should propagate forward (sec) */
    uWord    PrecisionThr;         /* GOODS Precision Update Threshold (an_precision_enum) */
    uWord    QualityThr;           /* GOODS State Quality Update Threshold (an_quality_enum) */
    uWord    SpareWord[2];         /* SpareWord */
  } Goods;
  
  uDword    SpoofUnusedReasonMask;  /* Bit mask for reason a satellite is not used in the GPSR position fix */
  uWord     SpareWord[2];           /* SpareWord */

} ac_sceph_table_type;

#endif

/************************************/
#pragma pack()       /* Green Hills */
/************************************/

