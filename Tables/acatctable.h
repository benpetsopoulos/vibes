 /*********************************************************************************************************************
 *
 *  File:                acatctable.h
 *
 *  Last modification:   2012-11-15
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

#ifndef _acatctable_h_
#define _acatctable_h_

#pragma pack(4)

/*
** Spacecraft Attitude Control Parameter Table ...
*/

typedef struct ac_atc_table_
{
  dReal    Inertia11Lim[2];                     /* Inertia Matrix Element Limits (kg-m^2) */
  dReal    Inertia12Lim[2];                     /* [0] = Min, [1] = Max                   */
  dReal    Inertia13Lim[2];                     /* [ 11 12 13 ]                           */
  dReal    Inertia22Lim[2];                     /* [    22 23 ]                           */
  dReal    Inertia23Lim[2];                     /* [       33 ]                           */
  dReal    Inertia33Lim[2];                     

  uMatrix  IscInit;                             /* Initialized Inertia Values */
  
  uWord    EnableCtlTorque[NUM_AC_MODE];        /* Flag To Enable Control Torque */
  uWord    EnableGyrTorque[NUM_AC_MODE];        /* Flag To Enable Gyroscopic FF Torque */
  uWord    EnableCmdTorque[NUM_AC_MODE];        /* Flag To Enable Commanded FF Torque */

  uWord    PassiveModeEnabled[NUM_PAYLOAD_STATES]; /* Flag that prevents autopilot effort during payload slews */

  uWord    EnableLPF[NUM_AC_MODE][NUM_SC_CFG];  /* Flag To Enable Low Pass Filter */

  lpf_param_type  TorqueFilX;                   /* X Axis Torque LPF Parameters */
  lpf_param_type  TorqueFilY;                   /* Y Axis Torque LPF Parameters */
  lpf_param_type  TorqueFilZ;                   /* Z Axis Torque LPF Parameters */

  uWord     MaxPassiveDurationCnt;              /* Max Counts to Remain in AP Passive Mode */
  uWord     Spare[3];                           /* Spare */

  struct {
    uVector  RateNullThetaErrBdyLmt;            /* Rate Null S/C Attitude Error Limit, rad */
    uVector  CSAThetaErrBdyLmt;                 /* CSA S/C Attitude Error Limit, rad */
    uVector  CSPThetaErrBdyLmt;                 /* CSP S/C Attitude Error Limit, rad */
    uVector  TgtPntThetaErrBdyLmt;              /* Target Point S/C Attitude Error Limit, rad */
    uVector  NormalThetaErrBdyLmt;              /* Normal S/C Attitude Error Limit, rad */
    uVector  MissionThetaErrBdyLmt;             /* Mission S/C Attitude Error Limit, rad */
    uVector  DeltaVThetaErrBdyLmtBRE;           /* DeltaV S/C Attitude Error Limit For BRE, rad */
    uVector  DeltaVThetaErrBdyLmtREA;           /* DeltaV S/C Attitude Error Limit For REA, rad */

    uVector  RateNullOmegaErrBdyLmt;            /* Rate Null S/C Rate Error Limit, rad/sec */
    uVector  CSAOmegaErrBdyLmt;                 /* CSA S/C Rate Error Limit, rad/sec */
    uVector  CSPOmegaErrBdyLmt;                 /* CSP S/C Rate Error Limit, rad/sec */
    uVector  TgtPntOmegaErrBdyLmt;              /* Target Point S/C Rate Error Limit, rad/sec */
    uVector  NormalOmegaErrBdyLmt;              /* Normal S/C Rate Error Limit, rad/sec */
    uVector  MissionOmegaErrBdyLmt;             /* Mission S/C Rate Error Limit, rad/sec */
    uVector  DeltaVOmegaErrBdyLmtBRE;           /* DeltaV S/C Rate Error Limit For BRE, rad/sec */
    uVector  DeltaVOmegaErrBdyLmtREA;           /* DeltaV S/C Rate Error Limit For REA, rad/sec */

    uVector  RateNullIntegralErrBdyLmt;         /* Rate Null S/C Integral Error Limit, sec */
    uVector  CSAIntegralErrBdyLmt;              /* CSA S/C Integral Error Limit, sec */
    uVector  CSPIntegralErrBdyLmt;              /* CSP S/C Integral Error Limit, sec */
    uVector  TgtPntIntegralErrBdyLmt;           /* Target Point S/C Integral Error Limit, sec */
    uVector  NormalIntegralErrBdyLmt;           /* Normal S/C Integral Error Limit, sec */
    uVector  MissionIntegralErrBdyLmt;          /* Mission S/C Integral Error Limit, sec */
    uVector  DeltaVIntegralErrBdyLmtBRE;        /* DeltaV S/C Integral Error Limit For BRE, sec */
    uVector  DeltaVIntegralErrBdyLmtREA;        /* DeltaV S/C Integral Error Limit For REA, sec */
  } Lmt;

  uVector  Cp[NUM_AC_MODE][NUM_SC_CFG];         /* PID Attitude Control Gains, 1/sec^2 */
  uVector  Cr[NUM_AC_MODE][NUM_SC_CFG];         /* PID Rate Control Gains, 1/sec */
  uVector  Ci[NUM_AC_MODE][NUM_SC_CFG];         /* PID Integral Control Gains, 1/sec^3 */

  struct {
    struct {
      uVector  ThetaErrHardThr;                 /* SunAcq Attitude Error Hard Threshold, rad */
      uVector  ThetaErrSoftThr;                 /* SunAcq Attitude Error Soft Threshold, rad */
      uVector  OmegaErrHardThr;                 /* SunAcq Rate Error Hard Threshold, rad/sec */
      uVector  OmegaErrSoftThr;                 /* SunAcq Rate Error Soft Threshold, rad/sec */

      uWord    ThetaErrHardCnt;                 /* SunAcq Attitude Error Hard Count, cnt */
      uWord    ThetaErrSoftCnt;                 /* SunAcq Attitude Error Soft Count, cnt */
      uWord    OmegaErrHardCnt;                 /* SunAcq Rate Error Hard Count, cnt */
      uWord    OmegaErrSoftCnt;                 /* SunAcq Rate Error Soft Count, cnt */

      dReal    StaXResidualThr;                 /* SunAcq Sta X Axis Residual Threshold, rad */
      dReal    StaYResidualThr;                 /* SunAcq Sta Y Axis Residual Threshold, rad */
      dReal    StaZResidualThr;                 /* SunAcq Sta Z Axix Residual Threshold, rad */
      dReal    DeltaSysMomThr;                  /* SunAcq Delta-Momentum Threshold, N-m-s */

      uWord    ResidualTestCnt;                 /* SunAcq Residual Test Count, cnt */
      uWord    DeltaSysMomCnt;                  /* SunAcq Delta-Momentum Test Count, cnt*/
      uWord    SpareWord[2];                    /* Pad structure */
    } SunAcq;

    struct {
      uVector  ThetaErrHardThr;                 /* TgtPnt Attitude Error Hard Threshold, rad */
      uVector  ThetaErrSoftThr;                 /* TgtPnt Attitude Error Soft Threshold, rad */
      uVector  OmegaErrHardThr;                 /* TgtPnt Rate Error Hard Threshold, rad/sec */
      uVector  OmegaErrSoftThr;                 /* TgtPnt Rate Error Soft Threshold, rad/sec */

      uWord    ThetaErrHardCnt;                 /* TgtPnt Attitude Error Hard Count, cnt */
      uWord    ThetaErrSoftCnt;                 /* TgtPnt Attitude Error Soft Count, cnt */
      uWord    OmegaErrHardCnt;                 /* TgtPnt Rate Error Hard Count, cnt */
      uWord    OmegaErrSoftCnt;                 /* TgtPnt Rate Error Soft Count, cnt */

      dReal    StaXResidualThr;                 /* TgtPnt Sta X Axis Residual Threshold, rad */
      dReal    StaYResidualThr;                 /* TgtPnt Sta Y Axis Residual Threshold, rad */
      dReal    StaZResidualThr;                 /* TgtPnt Sta Z Axix Residual Threshold, rad */
      dReal    DeltaSysMomThr;                  /* TgtPnt Delta-Momentum Threshold, N-m-s */

      uWord    ResidualTestCnt;                 /* TgtPnt Residual Test Count, cnt */
      uWord    DeltaSysMomCnt;                  /* TgtPnt Delta-Momentum Test Count, cnt*/
      uWord    SpareWord[2];                    /* Pad structure */
    } TgtPnt;

    struct {
      uVector  ThetaErrHardThr;                 /* Normal Attitude Error Hard Threshold, rad */
      uVector  ThetaErrSoftThr;                 /* Normal Attitude Error Soft Threshold, rad */
      uVector  OmegaErrHardThr;                 /* Normal Rate Error Hard Threshold, rad/sec */
      uVector  OmegaErrSoftThr;                 /* Normal Rate Error Soft Threshold, rad/sec */

      uWord    ThetaErrHardCnt;                 /* Normal Attitude Error Hard Count, cnt */
      uWord    ThetaErrSoftCnt;                 /* Normal Attitude Error Soft Count, cnt */
      uWord    OmegaErrHardCnt;                 /* Normal Rate Error Hard Count, cnt */
      uWord    OmegaErrSoftCnt;                 /* Normal Rate Error Soft Count, cnt */

      dReal    StaXResidualThr;                 /* Normal Sta X Axis Residual Threshold, rad */
      dReal    StaYResidualThr;                 /* Normal Sta Y Axis Residual Threshold, rad */
      dReal    StaZResidualThr;                 /* Normal Sta Z Axix Residual Threshold, rad */
      dReal    DeltaSysMomThr;                  /* Normal Delta-Momentum Threshold, N-m-s */

      uWord    ResidualTestCnt;                 /* Normal Residual Test Count, cnt */
      uWord    DeltaSysMomCnt;                  /* Normal Delta-Momentum Test Count, cnt*/
      uWord    SpareWord[2];                    /* Pad structure */
    } Normal;

    struct {
      uVector  ThetaErrHardThr;                     /* Mission Attitude Error Hard Threshold, rad */
      uVector  ThetaErrSoftThr;                     /* Mission Attitude Error Soft Threshold, rad */
      uVector  OmegaErrHardThrStationary;           /* Mission Rate Error Hard Stationary Payload Threshold, rad/sec */
      uVector  OmegaErrSoftThrStationary;           /* Mission Rate Error Soft Stationary Payload Threshold, rad/sec */
      uVector  OmegaErrHardThrMoving;               /* Mission Rate Error Hard Moving Payload Threshold, rad/sec */
      uVector  OmegaErrSoftThrMoving;               /* Mission Rate Error Soft Moving Payload Threshold, rad/sec */
                                                    
      uWord    ThetaErrHardCnt;                     /* Mission Attitude Error Hard Count, cnt */
      uWord    ThetaErrSoftCnt;                     /* Mission Attitude Error Soft Count, cnt */
      uWord    OmegaErrHardCnt;                     /* Mission Rate Error Hard Count, cnt */
      uWord    OmegaErrSoftCnt;                     /* Mission Rate Error Soft Count, cnt */
                                                    
      dReal    StaXResidualThr;                     /* Mission Sta X Axis Residual Threshold, rad */
      dReal    StaYResidualThr;                     /* Mission Sta Y Axis Residual Threshold, rad */
      dReal    StaZResidualThr;                     /* Mission Sta Z Axix Residual Threshold, rad */
      dReal    DeltaSysMomThr;                      /* Mission Delta-Momentum Threshold, N-m-s */
                                                    
      uWord    ResidualTestCnt;                     /* Mission Residual Test Count, cnt */
      uWord    DeltaSysMomCnt;                      /* Mission Delta-Momentum Test Count, cnt*/
      uWord    MplSlewingState[NUM_PAYLOAD_STATES]; /* Mission Payload Slewing State */
      uWord    SpareWord[2];                        /* Pad structure */
    } Mission;

    struct {
      uVector  ThetaErrHardThrBRE;              /* DeltaV Attitude Error Hard Threshold For BRE, rad */
      uVector  ThetaErrSoftThrBRE;              /* DeltaV Attitude Error Soft Threshold For BRE, rad */
      uVector  OmegaErrHardThrBRE;              /* DeltaV Rate Error Hard Threshold For BRE, rad/sec */
      uVector  OmegaErrSoftThrBRE;              /* DeltaV Rate Error Soft Threshold For BRE, rad/sec */

      uWord    ThetaErrHardCntBRE;              /* DeltaV Attitude Error Hard Count For BRE, cnt */
      uWord    ThetaErrSoftCntBRE;              /* DeltaV Attitude Error Soft Count For BRE, cnt */
      uWord    OmegaErrHardCntBRE;              /* DeltaV Rate Error Hard Count For BRE, cnt */
      uWord    OmegaErrSoftCntBRE;              /* DeltaV Rate Error Soft Count For BRE, cnt */

      uVector  ThetaErrHardThrREA;              /* DeltaV Attitude Error Hard Threshold For REA, rad */
      uVector  ThetaErrSoftThrREA;              /* DeltaV Attitude Error Soft Threshold For REA, rad */
      uVector  OmegaErrHardThrREA;              /* DeltaV Rate Error Hard Threshold For REA, rad/sec */
      uVector  OmegaErrSoftThrREA;              /* DeltaV Rate Error Soft Threshold For REA, rad/sec */

      uWord    ThetaErrHardCntREA;              /* DeltaV Attitude Error Hard Count For REA, cnt */
      uWord    ThetaErrSoftCntREA;              /* DeltaV Attitude Error Soft Count For REA, cnt */
      uWord    OmegaErrHardCntREA;              /* DeltaV Rate Error Hard Count For REA, cnt */
      uWord    OmegaErrSoftCntREA;              /* DeltaV Rate Error Soft Count For REA, cnt */

      dReal    StaXResidualThr;                 /* DeltaV Sta X Axis Residual Threshold, rad */
      dReal    StaYResidualThr;                 /* DeltaV Sta Y Axis Residual Threshold, rad */
      dReal    StaZResidualThr;                 /* DeltaV Sta Z Axix Residual Threshold, rad */
      dReal    DeltaSysMomThr;                  /* DeltaV Delta-Momentum Threshold, N-m-s */

      uWord    ResidualTestCnt;                 /* DeltaV Residual Test Count, cnt */
      uWord    DeltaSysMomCnt;                  /* DeltaV Delta-Momentum Test Count, cnt*/
      uWord    SpareWord[2];                    /* Pad structure */
    } DeltaV;
  } Fdc;
} ac_atc_table_type;

/* Target Pointing Parameter Table */
typedef struct ac_tgt_pnt_table_
{
  dReal        OmegaEstMagSqrLmt;               /* Rate Estimate Magnitude Squared Limit, rad/sec */
  dReal        CaptureAngle;                    /* Capture Angle, rad */
  dReal        OmegaBdyWrtRefMagInc;            /* Body Rate Magnitude Increment, cnt */
  dReal        OmegaSlewLmtInit;                /* Initial Maximum Slew Rate, rad/sec */
  uQuaternion  DeltaQInit;                      /* Initial Delta Quaternion, ND */
  uVector      SadAxisBdy;                      /* Solar Array Drive Axis In Body Coordinates, ND */
  dReal        TwoAxisSteeringDeadband;         /* Deadband For Two-Axis Steering, rad */
  dReal        SmallSlewThr;                    /* Threshold on Performing Slew About Arbitrary Euler Axis, ND */
  uWord        NullOmegaPhaseCnt;               /* Rate Null Phase Count, cnt */
  uWord        OmegaSettlingCntInit;            /* Rate Settling Count, cnt */
  uWord        EnableResetStopSlewAtt;          /* Reset The Commanded Attitude After Nulling Rates Following A Stop Slew Command, ND */
  uWord        SlewRampTypeInit;                /* Initial Slew Ramp Type */
} ac_tgt_pnt_table_type;

#endif /* _acatctable_h_ */

/************************************/
#pragma pack()       /* Green Hills */
/************************************/
