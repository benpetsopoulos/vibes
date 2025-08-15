 /*********************************************************************************************************************
 *
 *  File:                adtable.h
 *
 *  Last modification:   2012-12-03
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

#ifndef _adtable_h_
#define _adtable_h_

#pragma pack(4)

/*
** Spacecraft Attitude Determination Parameter Table ...
*/

typedef struct ad_table_ {

  dReal    PInitial[2][6];                               /* P Initial, r^2, (r/s)^2 */
  dReal    PDivergenceThr[2][6];                         /* P Divergence Threshold, r^2, (r/s)^2 */
  dReal    PCoarseConvergenceThr[2][6];                  /* P Coarse Convergence Threshold, r^2, (r/s)^2 */
  dReal    PFineConvergenceThr[2][6];                    /* P Fine Convergence Threshold, r^2, (r/s)^2 */

  dReal    k[3];                                         /* Sensor Frame Residual Validation Parameters, sigma^2 */

  dReal    ResEditAngleThr[3];                           /* Sensor Frame Residual Edit Angle Threshold, rad */

  dReal    NoIruQ[2][6][6];                              /* State Noise Covariance Matrix, Q, Without An IRU */

  dReal    Kd[2][3];                                     /* Disturbance Acceleration Estimation Gains, 1/s^2 */

  uVector  AlphaDstEstBdyLmt;                            /* AlphaDstEstBdyLmt, rad/sec^2 */

  uVector  SysMomEstBdyLmt;                              /* System Momentum Body Estimate Limit, N-m-s */

  dReal    KStaRateUpdateGain;                           /* STA Omega Update Gain */

  uWord    DisGyroBiasEstInPldState[NUM_PAYLOAD_STATES]; /* Which payload modes disable IRU Bias Estimation Updates [TRUE/FALSE] */

} ad_table_type, * ad_table_ptr;

#endif

/************************************/
#pragma pack()       /* Green Hills */
/************************************/

