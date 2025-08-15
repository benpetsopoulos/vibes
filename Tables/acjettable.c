 /*********************************************************************************************************************
 *
 *  File:                acjettable.c
 *
 *  Last modification:   2014-11-06
 *
 *  Author:              P. R. Shah, W. Miller, M. Pressl
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
** Jet Parameter Table ...
*/

#include "acstypes.h"
#include "acsdefines.h"
#include "fswJET.h"
#include "acjet.h"
#include "acjettable.h"

ac_jet_table_type AcJetTable = {

                                                         /* ControlJet[15][8], ND */
  {{ REA3,  REA5,  REA11,  REA9,  REA1,  REA7,  REA4,      REA10    }, /* CNT_HIGH_TORQUE    */
   { REA3,  REA5,  REA11,  REA9,  REA8,  REA2,  REA12,     REA6     }, /* CNT_MED_TORQUE     */
   { REA2,  REA8,  REA12,  REA6,  REA10, REA4,  NULL_JET,  NULL_JET }, /* CNT_REA_EVEN       */
   { REA3,  REA5,  REA11,  REA9,  REA8,  REA2,  REA12,     REA6     }, /* CNT_XZ_Y_SPARE_1   */
   { REA3,  REA5,  REA11,  REA9,  REA8,  REA2,  REA12,     REA6     }, /* CNT_XZ_Y_SPARE_2   */
   { REA3,  REA5,  REA9,   REA11, REA1,  REA7,  NULL_JET,  NULL_JET }, /* CNT_REA_ODD        */
   { REA3,  REA5,  REA9,   REA11, REA7,  REA1,  REA10,     REA4     }, /* CNT_REA_ODD_Z_EVEN */
   { REA2,  REA8,  REA12,  REA6,  REA7,  REA1,  REA4,      REA10    }, /* CNT_YZ_X_SPARE_1   */
   { REA2,  REA8,  REA12,  REA6,  REA7,  REA1,  REA4,      REA10    },
   { REA2,  REA8,  REA12,  REA6,  REA7,  REA1,  REA4,      REA10    },
   { REA2,  REA8,  REA12,  REA6,  REA7,  REA1,  REA4,      REA10    }, /* CNT_LOW_TORQUE     */
   { REA10, REA7,  REA4,   REA1,  REA3,  REA5,  REA9,      REA11    }, /* CNT_XY_Z_SPARE_1   */
   { REA10, REA7,  REA4,   REA1,  REA3,  REA5,  REA9,      REA11    },
   { REA10, REA7,  REA4,   REA1,  REA3,  REA5,  REA9,      REA11    },
   { REA10, REA7,  REA4,   REA1,  REA3,  REA5,  REA9,      REA11    }},
                                                         /* PosDeltaVJet[8][2], ND */
  {{ REA1,     REA7     },      /* DV_BRE_PRI */
   { REA1,     REA7     },      /* DV_BRE_RED */
   { REA6,     REA8     },      /* DV_REA_NEGXBDY */
   { REA2,     REA12    },      /* DV_REA_POSXBDY */
   { REA9,     REA11    },      /* DV_REA_POSYBDY */
   { REA3,     REA5     },      /* DV_REA_NEGYBDY */
   { REA1,     REA7     },      /* DV_REA_POSZBDY */
   { REA4,     REA10    }},     /* DV_REA_NEGZBDY */
                                                         /* NegDeltaVJet[8][2], ND */
  {{ REA4,     REA10    },      /* DV_BRE_PRI */
   { REA4,     REA10    },      /* DV_BRE_RED */
   { REA2,     REA12    },      /* DV_REA_NEGXBDY */
   { REA6,     REA8     },      /* DV_REA_POSXBDY */
   { REA3,     REA5     },      /* DV_REA_POSYBDY */
   { REA9,     REA11    },      /* DV_REA_NEGYBDY */
   { REA4,     REA10    },      /* DV_REA_POSZBDY */
   { REA1,     REA7     }},     /* DV_REA_NEGZBDY */

                                                         /* ControlAxis[15][3], ND */
  {{ Z_AXIS,  X_AXIS,  Y_AXIS  }, /* CNT_HIGH_TORQUE    */
   { Z_AXIS,  X_AXIS,  Y_AXIS  }, /* CNT_MED_TORQUE     */
   { Y_AXIS,  Z_AXIS,  X_AXIS  }, /* CNT_REA_EVEN       */
   { Z_AXIS,  X_AXIS,  Y_AXIS  }, /* CNT_XZ_Y_SPARE_1   */
   { Z_AXIS,  X_AXIS,  Y_AXIS  }, /* CNT_XZ_Y_SPARE_2   */
   { Z_AXIS,  X_AXIS,  Y_AXIS  }, /* CNT_REA_ODD        */
   { Z_AXIS,  X_AXIS,  Y_AXIS  }, /* CNT_REA_ODD_Z_EVEN */
   { Y_AXIS,  Z_AXIS,  X_AXIS  }, /* CNT_YZ_X_SPARE_1   */
   { Y_AXIS,  Z_AXIS,  X_AXIS  },
   { Y_AXIS,  Z_AXIS,  X_AXIS  },
   { Y_AXIS,  Z_AXIS,  X_AXIS  }, /* CNT_LOW_TORQUE     */
   { X_AXIS,  Y_AXIS,  Z_AXIS  }, /* CNT_XY_Z_SPARE_1   */
   { X_AXIS,  Y_AXIS,  Z_AXIS  },
   { X_AXIS,  Y_AXIS,  Z_AXIS  },
   { X_AXIS,  Y_AXIS,  Z_AXIS  }},

  { 16,  16,  16,  16,                                   /* MinNumOfLsb[14], cnt */
    16,  16,  16,  16,
    16,  16,  16,  16,
    50,  50            },

  3,                                                     /* SustFireCnts, cnt */

  /* Standby  RateNull   CSA      CSP    DeltaV   Normal   TgtPnt   Mission */   /* EnableRwaTorqueMix[3][8], ND */
  {{  FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE  },   /* Stowed */
   {  FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE,   FALSE  },   /* Deploying */
   {  FALSE,   FALSE,   FALSE,   FALSE,   TRUE,    TRUE,    TRUE,    TRUE   }},  /* Deployed */

  10*NUM_AC_CYCLES,                                      /* DeltaVTransitionCnt, cnt */
  FALSE,                                                 /* EnableRiu2JetCmdInit, ND */
  0,                                                     /* Pad structure */

  {                                                      /* OffDelay[14], sec */
    0.012,
    0.012,
    0.012,
    0.012,
    0.012,
    0.012,
    0.012,
    0.012,
    0.012,
    0.012,
    0.012,
    0.012,
    0.0,
    0.0
  },

  0.001,                                                 /* JetSecPerLsb, sec */

  0.050,                                                 /* JetSecondsRemainingThr, sec */

  {      /*JetForceMag[14], N*/
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    0.6735,
    22.0454,
    22.0454
  },


  {      /*JetIsp[14], sec */
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    216.1127,
    312.7700,
    312.7700,
  },

                                                         /* JetNormTorq[14][3], m */
{{  0.4007,   0.6381,   0.0000 },
 {  0.0000,  -0.9257,  -0.4611 },
 { -0.8653,   0.0000,   0.6381 },
 { -0.4007,   0.6817,   0.0000 },
 {  0.3442,   0.0000,  -0.6817 },
 {  0.0000,  -0.4047,   0.4611 },
 { -0.3836,  -0.6817,   0.0000 },
 {  0.0000,   0.9257,  -0.4440 },
 {  0.8653,   0.0000,   0.6817 },
 {  0.3836,  -0.6381,   0.0000 },
 { -0.3442,   0.0000,  -0.6381 },
 {  0.0000,   0.4047,   0.4440 },
 {  0.0023,   0.0048,   0.0001 },
 {  0.0023,   0.0048,   0.0001 } },



                                                          /* JetForceUnit[14][3], ND */
/* Keep REAs at Ideal Alignments to Avoid Undesirable Simplex Behavior */
{{   0.0000,   0.0000,   1.0000 },
 {   1.0000,   0.0000,   0.0000 },
 {   0.0000,  -1.0000,   0.0000 },
 {   0.0000,   0.0000,  -1.0000 },
 {   0.0000,  -1.0000,   0.0000 },
 {  -1.0000,   0.0000,   0.0000 },
 {   0.0000,   0.0000,   1.0000 },
 {  -1.0000,   0.0000,   0.0000 },
 {   0.0000,   1.0000,   0.0000 },
 {   0.0000,   0.0000,  -1.0000 },
 {   0.0000,   1.0000,   0.0000 },
 {   1.0000,   0.0000,   0.0000 },
 {  -0.0213,  -0.0049,   0.9998 },
 {  -0.0213,  -0.0049,   0.9998 }},


  {{ 0.50*DEG_2_RAD, 0.50*DEG_2_RAD, 0.50*DEG_2_RAD }},  /* ThetaErrThrBRE, rad */
  {{ 0.25*DEG_2_RAD, 0.25*DEG_2_RAD, 0.25*DEG_2_RAD }},  /* ThetaErrThrREA, rad */

  {{ 0.05*DEG_2_RAD, 0.05*DEG_2_RAD, 0.05*DEG_2_RAD }},  /* OmegaErrThrBRE, rad/sec */
  {{ 0.05*DEG_2_RAD, 0.05*DEG_2_RAD, 0.05*DEG_2_RAD }},  /* OmegaErrThrREA, rad/sec */

  0.50,                                                  /* InitDeltaVTrqBiasScaleFactorBRE */
  0.20,                                                  /* InitDeltaVTrqBiasScaleFactorREA */

  1.30,                                                  /* ResDeltaVTrqBiasScaleFactorBRE */
  1.50,                                                  /* ResDeltaVTrqBiasScaleFactorREA */

  0.60,                                                  /* ResDeltaVIntErrScaleFactorBRE */
  1.50,                                                  /* ResDeltaVIntErrScaleFactorREA */
  1.0,                                                   /* ResSimplexDeltaVIntErrGain */
  0.001,                                                 /* MinDeltaVCmdMag, m/sec */
  10.0,                                                  /* MinBreDeltaVOnTime, sec */
  2.0,                                                   /* DeltaVTimerScaleFactor */
  72.0,                                                  /* DeltaVTimerMinTimeEst, sec */
  0.62969,                                               /* SimplexTorqueSlewLmt - Ref: http://vasvn/svn/Seraphim/tools/thrusterAnalysis/DN117/Torque_maps r2145, taSimplex.m (rev C BOL) */
  0.21784,                                               /* PseudoInvTorqueSlewLmt - Ref: http://vasvn/svn/Seraphim/tools/thrusterAnalysis/DN117/Torque_maps r2145, taPseudo.m  (rev C EOL) */
  2,                                                     /* MaxBurnDurationSF */
   {
     2.0,                                                /* UpperBoundLmt */
     -10.0,                                              /* ForceScaleFactorDefaultCost */
     -10.0,                                              /* TorqueScaleFactorDefaultCost */
       1.0,                                              /* Force Command Limit, N */
     { TRUE,  TRUE,  TRUE,  TRUE,                        /* JetInSimplex[12] */
       TRUE,  TRUE,  TRUE,  TRUE,
       TRUE,  TRUE,  TRUE,  TRUE },
     { REA1, REA2, REA3, REA4, REA8,  REA10 },           /* InitialBasisVariables[6] */
     { REA5, REA6, REA7, REA9, REA11, REA12,
       FORCE_SF_INDEX, TORQUE_SF_INDEX },                /* InitialNonBasisVariables[8] */
       100,                                              /* SimplexInterationLmt, cnt */
       0                                                 /* SpareWord */
   },
   DV_BRE_PRI,                                           /* DeltaVThrSetForMnvMgrCmd, ac_dv_id_type */
   CNT_MED_TORQUE,                                       /* ControlThrSetForMnvMgrCmd, ac_cnt_id_type */
   DV_REA_POSZBDY,                                       /* ReaTurnToBurnThrSet , ac_dv_id_type */
   0                                                     /* SpareWord1 */
};

