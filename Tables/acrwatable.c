 /*********************************************************************************************************************
 *
 *  File:                acrwatable.c
 *
 *  Last modification:   2014-09-17
 *
 *  Author:              W. Miller
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
** Reaction Wheel Assembly Parameter Table ...
*/

#include <math.h>
#include "acstypes.h"
#include "acsdefines.h"
#include "acrwatable.h"

ac_rwa_table_type AcRwaTable = {
  {                                                 /* Inertia, Nms^2 */
    /* Teldix RDR-12 Nominal Inertia*/
    0.019099,             /* RWA1 */
    0.019099,             /* RWA2 */
    0.019099,             /* RWA3 */
    0.019099              /* RWA4 */
  },

/* Tetrahedral configuration, Alpha=45 deg, Beta=20 deg */
#if ( SV_ID == 1 )
  /* DcmRwaToBdy, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.664463024388675,  0.664463024388675,  0.664463024388675, -0.664463024388675 },
   { -0.664463024388675, -0.664463024388675,  0.664463024388675,  0.664463024388675 },
   { -0.342020143325669, -0.342020143325669, -0.342020143325669, -0.342020143325669 }},

  /* DcmBdyToRwa, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856,  0.376243659652856, -0.730951100040772 },
   { -0.376243659652856,  0.376243659652856, -0.730951100040772 }},

#elif ( SV_ID == 2 )
  /* DcmRwaToBdy, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.664463024388675,  0.664463024388675,  0.664463024388675, -0.664463024388675 },
   { -0.664463024388675, -0.664463024388675,  0.664463024388675,  0.664463024388675 },
   { -0.342020143325669, -0.342020143325669, -0.342020143325669, -0.342020143325669 }},

  /* DcmBdyToRwa, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856,  0.376243659652856, -0.730951100040772 },
   { -0.376243659652856,  0.376243659652856, -0.730951100040772 }},

#elif ( SV_ID == 3 )
  /* DcmRwaToBdy, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Sect. 4*/
  {{ -0.664463024388675,  0.664463024388675,  0.664463024388675, -0.664463024388675 },
   { -0.664463024388675, -0.664463024388675,  0.664463024388675,  0.664463024388675 },
   { -0.342020143325669, -0.342020143325669, -0.342020143325669, -0.342020143325669 }},

  /* DcmBdyToRwa, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856,  0.376243659652856, -0.730951100040772 },
   { -0.376243659652856,  0.376243659652856, -0.730951100040772 }},

#elif ( SV_ID == 4 )
  /* DcmRwaToBdy, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Sect. 4*/
  {{ -0.664463024388675,  0.664463024388675,  0.664463024388675, -0.664463024388675 },
   { -0.664463024388675, -0.664463024388675,  0.664463024388675,  0.664463024388675 },
   { -0.342020143325669, -0.342020143325669, -0.342020143325669, -0.342020143325669 }},

  /* DcmBdyToRwa, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856,  0.376243659652856, -0.730951100040772 },
   { -0.376243659652856,  0.376243659652856, -0.730951100040772 }},

#elif ( SV_ID == 5 )
  /* DcmRwaToBdy, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Sect. 4*/
  {{ -0.664463024388675,  0.664463024388675,  0.664463024388675, -0.664463024388675 },
   { -0.664463024388675, -0.664463024388675,  0.664463024388675,  0.664463024388675 },
   { -0.342020143325669, -0.342020143325669, -0.342020143325669, -0.342020143325669 }},

  /* DcmBdyToRwa, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856,  0.376243659652856, -0.730951100040772 },
   { -0.376243659652856,  0.376243659652856, -0.730951100040772 }},

#elif ( SV_ID == 6 )
  /* DcmRwaToBdy, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Sect. 4*/
  {{ -0.664463024388675,  0.664463024388675,  0.664463024388675, -0.664463024388675 },
   { -0.664463024388675, -0.664463024388675,  0.664463024388675,  0.664463024388675 },
   { -0.342020143325669, -0.342020143325669, -0.342020143325669, -0.342020143325669 }},

  /* DcmBdyToRwa, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856,  0.376243659652856, -0.730951100040772 },
   { -0.376243659652856,  0.376243659652856, -0.730951100040772 }},

#else
  /* DcmRwaToBdy, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Sect. 4*/
  {{ -0.664463024388675,  0.664463024388675,  0.664463024388675, -0.664463024388675 },
   { -0.664463024388675, -0.664463024388675,  0.664463024388675,  0.664463024388675 },
   { -0.342020143325669, -0.342020143325669, -0.342020143325669, -0.342020143325669 } },

  /* DcmBdyToRwa, ND */
  /* Ref: DN-SERAPHIM-GNC-111 Rev- Sect. 4*/
  {{ -0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856, -0.376243659652856, -0.730951100040772 },
   {  0.376243659652856,  0.376243659652856, -0.730951100040772 },
   { -0.376243659652856,  0.376243659652856, -0.730951100040772 } },

#endif

  { -1, 1, -1, 1 },                                 /* NullSpace, ND*/
  6*NUM_AC_CYCLES,                                  /* NumOfRwaTachCycles, cnt */
  16383,                                            /* MaxTachCountValue, 0x3FFF, cnt */
  1,                                                /* DeltaTachCountThr, cnt */
  0,                                                /* Padding for alignment */
  TWO_PI / 24.0,                                    /* Teldix Pulse2Angle, rad/pulse, 75119-801_C_Interface_Control_Document 4.4.5.3*/
  { 133.333, 133.333, 133.333, 133.333 },           /* Teldix Torque2VoltSF, V/Nm, RWA Spec 6554-PF4640 Rev B Sect. 3.2.1.1.2 */
  { 0.0,  0.0,  0.0,  0.0 },                        /* Torque2VoltBias, V */
  0,                                                /* CmdVolt2CntBias, cnt */
  204.8,                                            /* CmdVolt2CntSF, cnt/V */
  { 0.0375,  0.0375,  0.0375,  0.0375  },           /* TorqueSlewLmt, Nm */
  { 0.075,   0.075,   0.075,   0.075   },           /* Teldix TorqueCmdMaxLmt, Nm */
  { 0.055,   0.055,   0.055,   0.055   },           /* Teldix TorqueScNullCtlMaxLmt, Nm */
  1.6E-05,                                          /* BiasSpeedGain, Nm/(rad/sec) */
  0.030,                                            /* BiasSpeedTorqueLmt, Nm */
  { 0.0, 0.0, 0.0, 0.0 },                           /* DefaultSpeedCmd, rad/sec */
  6000.0*RPM_2_RPS,                                 /* Teldix SpeedCmdMax, rad/sec, RWA Spec 6554-PF4640 Rev B Sect. 3.2.1.1*/

  {                                                 /* ViscousFrcSF, Nm/(rad/sec) */
    1.671e-5,              /* RWA1 */
    1.671e-5,              /* RWA2 */
    1.671e-5,              /* RWA3 */
    1.671e-5,              /* RWA4 */
  },
  { 2.10E-1, 2.74E-4 },                             /* Teldix Kest */
  { 0.071,   1.00    },                             /* Teldix Kcnt */
  { 0.020,  0.020,  0.020,   0.020 },               /* Teldix TorqueStictionMax, Nm */
  {                                                 /* Fdc */
    { 10*NUM_AC_CYCLES, 10*NUM_AC_CYCLES, 10*NUM_AC_CYCLES, 10*NUM_AC_CYCLES },  /* PowerStatusOffCnt, cnt */
    { 10*NUM_AC_CYCLES, 10*NUM_AC_CYCLES, 10*NUM_AC_CYCLES, 10*NUM_AC_CYCLES },  /* SpeedErrCnt, cnt */
      60*NUM_AC_CYCLES,                                                          /* RwaCorrectCnt, cnt */
     120*NUM_AC_CYCLES,                                                          /* RwaVerifyCnt, cnt */
     { 0, 0},                                                                    /* Spare */
    { 105.0*RPM_2_RPS,  105.0*RPM_2_RPS,  105.0*RPM_2_RPS, 105.0*RPM_2_RPS }     /* SpeedErrThr, rad/sec */
  }
};
