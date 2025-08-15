 /*********************************************************************************************************************
 *
 *  File:                acrwatable.h
 *
 *  Last modification:   2012-11-15
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

#ifndef _acrwatable_h_
#define _acrwatable_h_

#pragma pack(4)

/*
** Reaction Wheel Assembly Parameter Table ...
*/

typedef struct {
  dReal      Inertia[NUM_OF_RWA];               /* RW Rotor Inertia, kg*m^2 */
  dReal      DcmRwaToBdy[3][NUM_OF_RWA];        /* RWA To Body Transformation Matrix, ND */
  dReal      DcmBdyToRwa[NUM_OF_RWA][3];        /* Body To RWA Transformation Matrix, ND */
  dReal      NullSpace[NUM_OF_RWA];             /* RWA Pyramid Null Space Vector, ND */
  uWord      NumOfRwaTachCycles;                /* Max Number Of RWA Tachometer Cycles, cnt */
  uWord      MaxTachCountValue;                 /* 14 Bit Tachometer Counter Limit, cnt */
  uWord      DeltaTachCountThr;                 /* Delta Tachometer Count Threshold, cnt */
  uWord      Pad;
  dReal      Pulse2Angle;                       /* Tachometer Pulses Per Revolution, rad/pulse */
  dReal      Torque2VoltSF[NUM_OF_RWA];         /* RW Torque To Volt Scale Factor, V/Nm */
  dReal      Torque2VoltBias[NUM_OF_RWA];       /* RW Voltage Bias For Torque To Volt Conversion, V */
  dReal      CmdVolt2CntBias;                   /* RW Count Bias For Volt To Count Conversion, cnt */
  dReal      CmdVolt2CntSF;                     /* RW Volts To Counts Scale Factor, cnt/V */

  dReal      TorqueSlewLmt[NUM_OF_RWA];         /* Max RW Torque For Slew Generation, Nm */
  dReal      TorqueCmdMaxLmt[NUM_OF_RWA];       /* Max RW Torque, Nm */
  dReal      TorqueScNullCtlMaxLmt[NUM_OF_RWA]; /* RWA Max SC Null Control Torque Limit, Nm */
  dReal      BiasSpeedGain;                     /* Bias Speed Control Gain, Nm/(rad/sec) */
  dReal      BiasSpeedTorqueLmt;                /* Max Bias Speed Control Torque, Nm */
  dReal      DefaultSpeedCmd[NUM_OF_RWA];       /* Default RW Speed Command, rad/sec */
  dReal      SpeedCmdMax;                       /* RWA Max Commanded Speed, rad/sec */
  dReal      ViscousFrcSF[NUM_OF_RWA];          /* RWA Viscous Friction SF, Nm/(rad/sec) */
  dReal      Kest[2];                           /* RWA Estimator Gains */
  dReal      Kcnt[2];                           /* RWA Speed Control Gains */
  dReal      TorqueStictionMax[NUM_OF_RWA];     /* RWA Max Stiction Torque,Nm */

  struct {
    uWord  PowerStatusOffCnt[NUM_OF_RWA];       /* RWA Power Status Off Count, cnt */
    uWord  SpeedErrCnt[NUM_OF_RWA];             /* RWA Speed Error Test Count, cnt */
    uWord  RwaCorrectCnt;                       /* RWA Correction Count, cnt */
    uWord  RwaVerifyCnt;                        /* RWA Verification Count, cnt */
    uWord  Spare[2];                            /* Spare */
    dReal  SpeedErrThr[NUM_OF_RWA];             /* RWA Speed Error Threshold, rad/sec */
  } Fdc;

} ac_rwa_table_type, *ac_rwa_table_ptr;

#endif

/************************************/
#pragma pack()       /* Green Hills */
/************************************/
