 /*********************************************************************************************************************
 *
 *  File:                actable.h
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
 


/************************************/
#pragma pack()       /* Green Hills */
/************************************/

/*
** AC Parameter Table ...
*/

#ifndef _actable_h_
#define _actable_h_

#pragma pack(4)

typedef struct ac_table_ {

  uWord   CycleMax;
  uWord   FrameMax;

  uWord   SolarCycleMask;
  uWord   SolarFrameMask;
  uWord   LunarCycleMask;
  uWord   LunarFrameMask;
  uWord   KFCycleMask;
  uWord   KFFrameMask;
  uWord   AnCmdCycleMask;
  uWord   AnCmdFrameMask;
  uWord   SpareWord[2];

  dReal   ElapsedTimeDtThr;       /* Mission Elapsed Delta Time Threshold (sec) */
  dReal   EpochBias;              /* Bias From J2000.0 Epoch (days) */
  dReal   GHA_J2000;              /* Greenwich Hour Angle At J2000.0, rad */
  dReal   EARTH_RATE;             /* Earth Rate, rad/sec */

  /*
  ** Rate Nulling ...
  */

  struct ac_ratenull_ {
    uVector  OmegaCmd;
    dReal    OmegaErrThr[2];      /* Transition Threshold from SunAcq to SunPnt [Nominal, During IRU failure] */
    uWord    OmegaSettlingCnt;
    uWord    SpareWord[3];        /* Pad structure */
  } RateNull;

  /*
  ** Sun Acquisition ...
  */

  struct ac_sunacq_ {
    dReal    ThetaErrThr[2];      /* Transition Threshold from SunAcq to SunPnt [Nominal, During dual SAD (e.g. RIU1) failure] */
    dReal    OmegaErrThr[2];      /* Transition Threshold from SunAcq to SunPnt [Nominal, During IRU failure] */
    uWord    ThetaSettlingCnt;
    uWord    SpareWord[3];        /* Pad structure */
  } SunAcq;

  /*
  ** Sun Pointing ...
  */

  struct ac_sunpnt_ {
    uVector  OmegaCmd;
    uVector  ThetaOffsetBdyInit;
    dReal    MaxOffsetAngle;             /* Limit the offset angle (rad) */
    uWord    AxisPositiveInit;           /* -Z or +Z Axis to Sun */
    uWord    StartEclipseCount;
    uWord    SpareWord[2];               /* Pad structure */
  } SunPnt;

  /*
  ** AC Task Fault Detection ...
  */

  struct
  {
    uWord   Riu1FaultTestCnt;
    uWord   KfNotStartedStateCnt;
    uWord   SpareWord[2];                /* Pad structure */
  } Fdc;

} ac_table_type;

#endif

/************************************/
#pragma pack()       /* Green Hills */
/************************************/
