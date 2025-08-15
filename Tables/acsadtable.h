 /*********************************************************************************************************************
 *
 *  File:                acsadtable.h
 *
 *  Last modification:   2012-10-12
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
 


/************************************/
#pragma pack()       /* Green Hills */
/************************************/

#ifndef _acsadtable_h_
#define _acsadtable_h_

#include "acstypes.h"
#include "acsad.h"

#pragma pack(4)

/*
** SAD Defines ...
*/
typedef struct ac_sad_table_ {
  uMatrix  DcmBdyToSad[NUM_OF_SAD];                   /* SC Body to SAD 0 deg reference rotation matrix */
  dReal    SadRotDir[NUM_OF_SAD];                     /* Sign representing the positive direction of SAD rotation */
  
  uWord    PotOffset[NUM_OF_SAD][NUM_OF_POT];         /* Offset of pot relative to mechanical zero SAD position, steps. "PotiOffset_main_Motor#" and "PotiOffset_red_Motor#" from TC_SetConfig*/
  uWord    ElecTravel[NUM_OF_SAD][NUM_OF_POT];        /* Active range of potentiometer, steps. "Electrical Travel_main_Motor#" and "Electrical Travel_red_Motor#" from TC_SetConfig*/
  uWord    MaxPotValue[NUM_OF_SAD];                   /* Max feedback value of pot, steps. "Max_Poti_value_Motor#" from TC_SetConfig*/
  uWord    MinPotValue[NUM_OF_SAD];                   /* Min feedback value of pot, steps. "Min_Poti_value_Motor#" from TC_SetConfig*/
  dReal    RadToStepScaleFactor;                      /* Conversion scale factor for steps to rad */
  dReal    PotFilterA1;                               /* Potentiometer Data Filter, A1 Coefficient */
  dReal    PotFilterB1;                               /* Potentiometer Data Filter, B1 Coefficient */
  dReal    PotDeadbandSize[NUM_OF_SAD][NUM_OF_POT];   /* Size of pot deadband, rad */
  dReal    PotDeadbandMargin[NUM_OF_SAD][NUM_OF_POT]; /* Pot Deadband Margin, rad */
  dReal    AngleCtrlDeadband;                         /* Max error before commanding step, rad */
  dReal    MedModeLoThr;                              /* Error low threshold to use Medium Motor Mode, rad */
  dReal    HighModeLoThr;                             /* Error low threshold to use High Motor Mode, rad */
  uWord    MaxSteps[NUM_MOTOR_MODES];                 /* Maximum number of steps per control cycle, Normal rate, steps */
  uWord    CycleMask;                                 /* Cycle mask for SAD processing */
  uWord    FrameMask;                                 /* Frame mask for SAD processing */
  uWord    Spare;                                     /* Padding */
  uWord    PowerOffCnt;                               /* SADE power off counter initial value, SAD Cycles */
  dReal    WarmupTime;                                /* Duration for SADE warmup period, SADE cycles */
  uByte    UseHighInAcsMode[NUM_AC_MODE];             /* Flag to allow High Motor Mode for each ACS Mode */

  struct ac_sad_fdc_table_ {
    dReal  AngleErrorThreshold;                       /* Maximum angle error between commanded and measured angle, radians */
    dReal  SunAngleErrorThreshold;                    /* Maximum angle error between a SA and the projection of the SCtoSun vector on the X/Z plane, radians*/
    uWord  PotAngleErrorCnt;                          /* Pot Angle Error counter initial value, SAD Cycles */
    uWord  SunAngleErrorCnt;                          /* Sun Angle Error counter initial value, SAD Cycles */
    uWord  PowerStatusOffCnt;                         /* SADE Power Status Off counter initial value, SAD Cycles */
    uWord  Spare;
  } Fdc;

} ac_sad_table_type;

#endif

/************************************/
#pragma pack()       /* Green Hills */
/************************************/
