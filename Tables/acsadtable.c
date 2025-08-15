 /*********************************************************************************************************************
 *
 *  File:                acsadtable.c
 *
 *  Last modification:   2014-02-20
 *
 *  Author:
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


#include "acsdefines.h"
#include "acsadtable.h"

ac_sad_table_type AcSadTable =
{
  { { { {  1,  0,  0 },                     /* DcmBdyToSad[0], -Y SA */
        {  0,  1,  0 },
        {  0,  0,  1 } } },
    { { { -1,  0,  0 },                     /* DcmBdyToSad[1], +Y SA */
        {  0, -1,  0 },
        {  0,  0,  1 } } } },
        {  1, -1 },                         /* SadRotDir */

#if ( SV_ID == 1 )
/* Ref: SADA FM Calibration Report SERAPHIM-RSZ-RP-0027 rev. 1.0, SADE FM03 Cal. Params Table 6.1.3 */
/*   MAINPOT, REDPOT                           PotOffset[SadID][PotID] */
   { { 28738, 57526 },                      /* SAD1 */
     { 28670, 57487 } },                    /* SAD2 */

/*   MAINPOT, REDPOT                           ElecTravel[SadID][PotID] */
   { { 57226, 57247 },                      /* SAD1 */
     { 57251, 57242 } },                    /* SAD2 */

     {  3300, 3283  },                      /* MaxPotValue[SadID] */
     {     2,    2  },                      /* MinPotValue[SadID] */

#elif ( SV_ID == 2 )
/* Ref: SADA PFM Calibration Report SERAPHIM-RSZ-RP-0033 rev. 1.0, SADE FM02 Cal. Params Table 6.1.4.1 */
/*   MAINPOT, REDPOT                           PotOffset[SadID][PotID] */
   { { 28835, 57595 },                      /* SAD1 */
     { 28844, 39    } },                    /* SAD2 */

/*   MAINPOT, REDPOT                           ElecTravel[SadID][PotID] */
   { { 57255, 57230 },                      /* SAD1 */
     { 57297, 57259 } },                    /* SAD2 */

     {  3282, 3282  },                      /* MaxPotValue[SadID] */
     {     1,    1  },                      /* MinPotValue[SadID] */

#elif ( SV_ID == 3 )
/* Ref: SADA FM Calibration Report SERAPHIM-RSZ-RP-0027 rev. 1.0, SADE FM04 Cal. Params Table 6.1.4 */
/*   MAINPOT, REDPOT                           PotOffset[SadID][PotID] */
   { { 28706, 57515 },                      /* SAD1 */
     { 28741, 57584 } },                    /* SAD2 */

/*   MAINPOT, REDPOT                           ElecTravel[SadID][PotID] */
   { { 57183, 57270 },                      /* SAD1 */
     { 57244, 57208 } },                    /* SAD2 */

     {  3300, 3282  },                      /* MaxPotValue[SadID] */
     {     2,    2  },                      /* MinPotValue[SadID] */

#elif ( SV_ID == 4 )
/* Ref: SADA FM Calibration Report FOXHOUND-RSS-RP-0021 rev. 1.0, SADE FM04 Cal. Params Table 7.1.4.1 */
/*   MAINPOT, REDPOT                           PotOffset[SadID][PotID] */
   { { 28669, 57454 },                      /* SAD1 */
     { 28694, 57482 } },                    /* SAD2 */

/*   MAINPOT, REDPOT                           ElecTravel[SadID][PotID] */
   { { 57189, 57197 },                      /* SAD1 */
     { 57224, 57190 } },                    /* SAD2 */

     {  3106, 3092  },                      /* MaxPotValue[SadID] */
     {     3,    2  },                      /* MinPotValue[SadID] */

#elif ( SV_ID == 5 )
/* Ref: SADA FM Calibration Report FOXHOUND-RSS-RP-0028 rev. 1.0, SADE FM006 Cal. Params Table 7.1.4.1 */
/*   MAINPOT, REDPOT                           PotOffset[SadID][PotID] */
   { { 28690, 57456 },                      /* SAD1 */
     { 28723, 57547 } },                    /* SAD2 */

/*   MAINPOT, REDPOT                           ElecTravel[SadID][PotID] */
   { { 57244, 57220 },                      /* SAD1 */
     { 57162, 57168 } },                    /* SAD2 */

     {  3084, 3192  },                      /* MaxPotValue[SadID] */
     {     3,    3  },                      /* MinPotValue[SadID] */

#elif ( SV_ID == 6 )
/* Ref: SADA FM Calibration Report FOXHOUND-RSS-RP-0036 rev. 1.0, SADE FM005 Cal. Params Table 7.1.4.1 */
/*   MAINPOT, REDPOT                           PotOffset[SadID][PotID] */
   { { 28871, 57549 },                      /* SAD1 */
     { 28968, 260     } },                    /* SAD2 */

/*   MAINPOT, REDPOT                           ElecTravel[SadID][PotID] */
   { { 57169, 57174 },                      /* SAD1 */
     { 57190, 57182 } },                    /* SAD2 */

     {  3090, 3135  },                      /* MaxPotValue[SadID] */
     {     3,    3  },                      /* MinPotValue[SadID] */

#else
/* Ref: SADE ICD SERAPHIM-NT-ICD-1000 Rev. 5 Section 5.8.4.1.3 */
/*   MAINPOT, REDPOT                           PotOffset[SadID][PotID] */
   { {     0, 28800 },                      /* SAD1 */
     {     0, 28800 } },                    /* SAD2 */

/*   MAINPOT, REDPOT                           ElecTravel[SadID][PotID] */
   { { 57599, 57599 },                      /* SAD1 */
     { 57599, 57599 } },                    /* SAD2 */

     {  3680, 3680  },                      /* MaxPotValue[SadID] */
     {     0,    0  },                      /* MinPotValue[SadID] */
#endif

           1 / 0.00625 / DEG_2_RAD,         /* RadToStepScaleFactor, Conversion factor from rad to SAD steps, step/rad */
                                            /*   Ref: Seraphim SADE ICD, SERAPHIM-NT-ICD-1000 Issue 5.0 08/28/2019, Secion 6.2 */
           0.5,                             /* PotFilterA1 */
           0.5,                             /* PotFilterB1 */

/* Ref: Seraphim SADA DD, SERAPHIM-RSZ-DD-0001 Issue 1.0 10.01.2019, Secion 5.3.3.5 */
/*           MAINPOT, REDPOT                   PotDeadbandSize[SadID][PotID], Nominally step once every 10 cycles (1Hz), rad */
   { { 3.5*DEG_2_RAD, 3.5*DEG_2_RAD },      /* SAD1 */
     { 3.5*DEG_2_RAD, 3.5*DEG_2_RAD }  },   /* SAD2 */

/*           MAINPOT, REDPOT                   PotDeadbandMargin[SadID][PotID], Pot Deadband Margin, rad */
   { { 1*DEG_2_RAD, 1*DEG_2_RAD },          /* SAD1 */
     { 1*DEG_2_RAD, 1*DEG_2_RAD }  },       /* SAD2 */

           0.00417 * 10 * DEG_2_RAD,        /* AngleCtrlDeadband, Nominally step once every 10 cycles (1Hz), rad */
           2 * 0.00417 * DEG_2_RAD,         /* MedModeLoThr, Error low threshold to use Medium Motor Mode, rad */
                                            /*   ( sized to fall behind up to two Low Mode 1Hz cycle's rotation beyond the deadband ) */
           2 * 0.2 * DEG_2_RAD,             /* HighModeLoThr, Error low threshold to use High Motor Mode, rad */
                                            /*   ( max rotation of Medium Mode in 2 1Hz cycles )  */
        {  0,                               /* MaxSteps, Maximum number of steps per control cycle, [HOLD_MODE, LOW_MODE, MED_MODE, HIGH_MODE] */
           (uWord) (0.00417/0.00625*77/80), /*   ( sized as rotation rate [deg/sec] / deg per step * 77 / 80 minor frames) */
           (uWord) (0.2/0.00625*77/80),     /*   Ref: Seraphim SADE ICD, SERAPHIM-NT-ICD-1000 Issue 5.0 28.08.2019, Secion 5.8.4.1.1 */
           (uWord) (1.0/0.00625*77/80) },
           0x0400,                          /* CycleMask, SAD Command Cycle Mask, Cycle 10 (minor frame 77) */
           0xFFFE,                          /* FrameMask, SAD Frame Mask, Every Frame 1 Hz */
           0,                               /* Padding */
           3,                               /* SADE power off counter initial value, SAD Cycles */
           25,                              /* WarmupTime, Duration for SADE warmup period, SADE cycles */
                                            /*   Ref: Seraphim SADE ICD, SERAPHIM-NT-ICD-1000 Issue 5.0 28.08.2019, Secion 5.5.1 */
                                            /* UseHighInAcsMode, Flag to allow High Motor Mode for each ACS Mode */
        {  TRUE,                            /*   Standby         */
           TRUE,                            /*   RateNulling     */
           TRUE,                            /*   SunAcquisition  */
           TRUE,                            /*   SunPointing     */
           TRUE,                            /*   DeltaV          */
           TRUE,                            /*   Normal          */
           TRUE,                            /*   Target Pointing */
           FALSE },                         /*   Mission         */

  {                            /* Fdc */
         20.0 * DEG_2_RAD,     /* AngleErrorThreshold, Maximum angle error between commanded and measured angle, radians */
         25.0 * DEG_2_RAD,     /* SunAngleErrorThreshold, Maximum angle error between SA and sun, radians */
         60,                   /* PotAngleErrorCnt, Pot Angle Error counter initial value, SAD Cycles */
         15*60,                /* SunAngleErrCnt, Sun Angle Error counter initial value, SAD Cycles */
         20,                   /* PowerStatusOffCnt, SADE Power Status Off counter initial value, SAD Cycles */
         0                    /* Spare */
  }
};
