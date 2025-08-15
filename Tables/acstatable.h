 /*********************************************************************************************************************
 *
 *  File:                acstatable.h 
 *
 *  Last modification:   2013-09-13
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
 

/************************************/
#pragma pack()       /* Green Hills */
/************************************/
/*
** Star Tracker Parameter Table ...
*/

#include "acstypes.h"
#include "acsdefines.h"
#include "fswSTA.h"

#ifndef _acstatable_h_
#define _acstatable_h_

#pragma pack(4)    /* Default alignment is 8 on some platforms */

typedef struct ac_sta_table_ {

  dReal            StaMesDelay[NUM_OF_STA_OH];               /* Delay from STA COI to IRU 1553 Schedule Read, sec */
  dReal            IruToAcDelay;                             /* Delay from IRU 1553 Schedule Read to AC Task Execution, sec */
  dReal            WarmUpTime;                               /* Warm Up Time, sec */
  dReal            CoiScaleFactor;
  dReal            LinearVelocityLsbX;
  dReal            LinearVelocityLsbY;
  dReal            LinearVelocityLsbZ;
  dReal            XYQualityIndexLsb;
  dReal            ZQualityIndexLsb;
  uQuaternion      QBdyToSta[NUM_OF_STA_OH];
  uMatrix          StaNoiseCov[NUM_OF_STA_OH];               /* Measurement Noise Covariance, STA Frame, rad^2 */
  uVector          BoresightSta[NUM_OF_STA_OH];              /* Boresight of Tracker in STA Frame */

  uVector          QualityIndexThr[NUM_OF_STA_OH];           /* Quality Index Thresholds in STA Frame [arcsec] */

  uWord            VelCmdModeMin;
  uWord            VelCmdModeMax;

  uWord            SecondStatusMask;                         /* Mask for Second Status Check */
  uWord            SecondStatusDesired;                      /* Desired Second Status Value */
  uWord            HealthStatusMask;                         /* Mask for STA Health Status Check */
  uWord            HealtStatusDesired;                       /* Desired Health Status Value */
  uWord            SyntDefOhMask[NUM_OF_STA_OH];             /* Mask for SyntDefOh word Check */
  uWord            SyntDefOhDesired[NUM_OF_STA_OH];          /* Desired SyntDefOh Value */
  uWord            SpareWord;                                /* SpareWord */
  uWord            PowerOffCnt;                              /* IRU power off counter initial value [ACS Cycles] */

  struct ac_sta_fdc_table_ {
    dReal          EarthOccultationThr[NUM_OF_STA_OH];       /* Plus Margin, radians */
    dReal          SolarOccultationThr[NUM_OF_STA_OH];
    dReal          LunarOccultationThr[NUM_OF_STA_OH];

    uWord          DataValidityFailCnt[NUM_OF_STA_OH];       /* OH Data Validity Test Failure Count, cnt */
    uWord          DataQualityFailCnt[NUM_OF_STA_OH];        /* Data Quality Test Failure Count, cnt */

    uWord          StaDataValidityFailCnt;                   /* STA Data Validity Test Failure Count, cnt */
    uWord          PowerStatusOffCnt;                        /* Power Status Off Test Count, cnt */
    uWord          OccultationADKFThr;                       /* ADKF Occultation Threshold, */
    uWord          ExpectedOpModeMin;

    uWord          ExpectedOpModeMax;
    uWord          OhDesiredSeqStatusMin[NUM_OF_STA_OH];     /* Minimum Desired Sequencing Status for an Optical Head */
    uWord          OhDesiredSeqStatusMax[NUM_OF_STA_OH];     /* Maximum Desired Sequencing Status for an Optical Head */
    uWord          StaCorrectCnt;                            /* STA Correction Count, cnt */
    uWord          StaVerifyCnt;                             /* STA Verification Count, cnt */
    uWord          SpareWord;                                /* SpareWord */
  } Fdc;

  uWord            CycleMask;                                /* Cycle Mask For STA Processing */
  uWord            FrameMask;                                /* Frame Mask For STA Processing */
  uWord            VelCmdCycleMask;                          /* Cycle Mask For STA Velocity Command */
  uWord            VelCmdFrameMask;                          /* Frame Mask For STA Velocity Command */

} ac_sta_table_type, * ac_sta_table_ptr;

#endif

/************************************/
#pragma pack()      /* Green Hills  */
/************************************/
