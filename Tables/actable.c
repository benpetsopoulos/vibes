 /*********************************************************************************************************************
 *
 *  File:                actable.c
 *
 *  Last modification:   2015-12-14
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


/*
** Attitude Control (AC) Parameter Table ...
*/

#include "acstypes.h"
#include "acsdefines.h"
#include "actable.h"

ac_table_type AcTable =
{
  NUM_AC_CYCLES,        /* CycleMax Max 0.10 Sec Cycles (From 1 - 10) */
  15,                   /* FrameMax Max 1.0 Sec Frames (From 1 - 15) */
  0x0002,               /* SolarCycleMask, Sun Ephemeris Cycle Mask, Cycle 1 */
  0xFFFE,               /* SolarFrameMask, Sun Ephemeris Frame Mask, Every Frame 1 - 15 */
  0x0002,               /* LunarCycleMask, Moon Ephemeris Cycle Mask, Cycle 1 */
  0xFFFE,               /* LunarFrameMask, Moon Ephemeris Frame Mask, Every Frame 1 - 15 */
  0xAAAA,               /* KFCycleMask, Kalman Filter Cycle Mask, Cycle 1, 3, 5, ... (5 Hz) */
  0xFFFE,               /* KFFrameMask, Kalman Filter Frame Mask, Every Frame 1 - 15 */
  0x0004,               /* AnCmdCycleMask, AN Command Cycle Mask, Cycle 2 */
  0xFFFE,               /* AnCmdFrameMask, AN Command Frame Mask, Every Frame 1 - 15 */
  { 0, 0 },             /* SpareWord */

  1.5 * AC_CYCLE_TIME,  /* ElapsedTimeDtThr                  (sec)      */
  0.0,                  /* EpochBias                         (day)      */
  4.89590917379201,     /* GHA_J2000                         (rad)      */
  7.2921151467E-05,     /* EARTH_RATE                        (rad/s)    */

  /* RateNull  */
  { {{ 0.0 * DEG_2_RAD,
       0.0 * DEG_2_RAD,
       0.0 * DEG_2_RAD }},      /* OmegaCmd                  (rad/s)    */
    {  0.1 * DEG_2_RAD,         /* OmegaErrThr  (Nominal)    (rad/s)    */
       0.4 * DEG_2_RAD },       /*          (IRU Failure)    (rad/s)    */
    (  300 * NUM_AC_CYCLES ),   /* OmegaSettlingCnt          (cycles)   */
    { 0, 0, 0 }                 /* SpareWord                            */
  },

  /*
  ** Sun Acquisition ...
  */

  { { 5.0 * DEG_2_RAD,          /* ThetaErrThr  (Nominal)    (rad)      */
      5.0 * DEG_2_RAD },        /*         (RIU1 Failure)    (rad)      */
    { 0.1 * DEG_2_RAD,          /* OmegaErrThr  (Nominal)    (rad/s)    */
      0.15 * DEG_2_RAD },       /*          (IRU Failure)    (rad/s)    */
    ( 60 * NUM_AC_CYCLES ),     /* ThetaSettlingCnt          (cycles)   */
    { 0, 0, 0 }                 /* Pad structure                        */
  },

  /*
  ** Sun Pointing ...
  */

  { {{ 0.0 * DEG_2_RAD,
       0.0 * DEG_2_RAD,
       0.0 * DEG_2_RAD }},      /* OmegaCmd                  (rad/s)    */
    {{ 0.0 * DEG_2_RAD,
       0.0 * DEG_2_RAD,
       0.0 * DEG_2_RAD }},      /* ThetaOffsetBdyInit        (rad)      */
     30.0 * DEG_2_RAD,          /* MaxOffsetAngle            (rad)      */
     FALSE,                     /* AxisPositiveInit: -Z to sun          */
     5 * NUM_AC_CYCLES,         /* StartEclipseCount         (cycles)   */
     { 0, 0 }                   /* Pad structure                        */
  },

  /*
  ** AC Task Fault Detection ...
  */

  {
    3 * NUM_AC_CYCLES,              /* Riu1FaultTestCnt,       RIU1 Persistency Counter (cycles)           */
    5 * MIN_2_SEC * NUM_AC_CYCLES,  /* KfNotStartedStateCnt,   KF NOT_STARTED Persistency Counter (cycles) */
    { 0, 0 }                        /* SpareWord                                                           */
  }
};

