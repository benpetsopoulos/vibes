 /*********************************************************************************************************************
 *
 *  File:                acjettable.h
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


#ifndef _acjettable_h_
#define _acjettable_h_

#pragma pack(4)

/*
** Jet Parameter Table ...
*/

typedef struct ac_jet_table_ {

  uWord        ControlJet[NUM_OF_CNT_JET][MAX_CONTROL_JETS];    /* Attitude Control Jet Sets, ND ([15][8]) */
  uWord        PosDeltaVJet[NUM_OF_DV_JET][MAX_DELTA_V_JETS];   /* Jets Contributing Pos DeltaV, ND ([8][2]) */
  uWord        NegDeltaVJet[NUM_OF_DV_JET][MAX_DELTA_V_JETS];   /* Jets Contributing Neg DeltaV, ND ([8][2]) */
  uWord        ControlAxis[NUM_OF_CNT_JET][3];                  /* Primary Axes (First 4 Jets) and Secondary Axis (Last 2 or 4 Jets) ([15][3]) */
  uWord        MinNumOfLsb[NUM_OF_JET];                         /* Minimum Number Of LSBs To Fire Jet, cnt */
  uWord        SustFireCnts;                                    /* Counts Added To Timer Load To Sustain Firing, cnt */
  uWord        EnableRwaTorqueMix[NUM_SC_CFG][NUM_AC_MODE];     /* Flag To Enable RWA Torque Mixing, ND */

  dword        DeltaVTransitionCnt;                             /* Transition From Delta V Count, cnt */
  uWord        EnableRiu2JetCmdInit;                            /* Initializes Flag to Enable RIU2 Jet Commands, ND */
  uWord        SpareWord;                                       /* Pad structure */

  dReal        OffDelay[NUM_OF_JET];            /* Delay For Jet To Shut Off, sec */
  dReal        JetSecPerLsb;                    /* Jet Seconds Per LSB, sec */
  dReal        JetSecondsRemainingThr;          /* Remaining Jet Seconds Threshold, sec */

  dReal        JetForceMag[NUM_OF_JET];         /* Jet Thrust, N */
  dReal        JetIsp[NUM_OF_JET];              /* Jet Specific Impulse, sec */
  dReal        JetNormTorq[NUM_OF_JET][3];      /* R X JetForceUnit, m */
  dReal        JetForceUnit[NUM_OF_JET][3];     /* Jet Force Unit Vector in the Body Frame */

  uVector      ThetaErrThrBRE;                  /* Transition From Delta V Attitude Error Threshold For BRE, rad */
  uVector      ThetaErrThrREA;                  /* Transition From Delta V Attitude Error Threshold For REA, rad */
  uVector      OmegaErrThrBRE;                  /* Transition From Delta V Rate Error Threshold For BRE, rad/sec */
  uVector      OmegaErrThrREA;                  /* Transition From Delta V Rate Error Threshold For REA, rad/sec */

  dReal        InitDeltaVTrqBiasScaleFactorBRE; /* Delta V Torque Bias Scale Factor Applied During Start of BRE Delta V */
  dReal        InitDeltaVTrqBiasScaleFactorREA; /* Delta V Torque Bias Scale Factor Applied During Start of REA Delta V */
  dReal        ResDeltaVTrqBiasScaleFactorBRE;  /* Delta V Torque Bias Scale Factor Applied During Tailoff (Residual) of BRE Delta V */
  dReal        ResDeltaVTrqBiasScaleFactorREA;  /* Delta V Torque Bias Scale Factor Applied During Tailoff (Residual) of REA Delta V */
  dReal        ResDeltaVIntErrScaleFactorBRE;   /* Integral Error Limit Bdy State Scale Factor Applied During Residual BRE Delta V */
  dReal        ResDeltaVIntErrScaleFactorREA;   /* Integral Error Limit Bdy State Scale Factor Applied During Residual REA Delta V */
  dReal        ResSimplexDeltaVIntErrGain;      /* Tuning Parameter for the Exit Transient Scaling of Simplex Delta V Burns */
  dReal        MinDeltaVCmdMag;                 /* Minimum Magnitude Delta V That Is Commanded To The Jets, m/s */
  dReal        MinBreDeltaVOnTime;              /* Minimum Duration For A BRE Delta V, sec */
  dReal        DeltaVTimerScaleFactor;          /* Scale Factor to Adjust The Simplex Timer */
  dReal        DeltaVTimerMinTimeEst;           /* Minimum Estimated Duration For The Simplex Timer, sec */

  dReal        SimplexTorqueSlewLmt;            /* Max Jet Torque For Simplex Slew Generation, Nm */
  dReal        PseudoInvTorqueSlewLmt;          /* Max Jet Torque For Pseudo Inverse Slew Generation, Nm */
  dReal        MaxBurnDurationSF;               /* Saftey Factor For Elapsed Burn Duration Exceeds Max Duration Before Abort */

  struct {
    dReal      UpperBoundLmt;                   /* Default value for UpperBounds */
    dReal      ForceScaleFactorDefaultCost;     /* Default cost for the force scale factor */
    dReal      TorqueScaleFactorDefaultCost;    /* Default cost for the torque scale factor */
    dReal      ForceCmdBdyLmt;                  /* Force Command Limit, N */
    uWord      JetInSimplex[NUM_OF_REA];        /* Flag To Include Jet In Simplex */
    uWord      InitialBasisVariables[NC_6DOF];
    uWord      InitialNonBasisVariables[ND_6DOF-NC_6DOF];
    uWord      SimplexIterationLmt;             /* Simplex Iteration Limit */
    uWord      SpareWord;                       /* Pad structure */
  } Simplex;

  uWord        DeltaVThrSetForMnvMgrCmd;        /* Delta V thruster set to use for Maneuver Manager commanded maneuvers - Pseudo Inverse Solution */
  uWord        ControlThrSetForMnvMgrCmd;       /* Control thruster set to use for Maneuver Manager commnaded maneuvers - Pseudo Inverse Solution */
  uWord        ReaTurnToBurnThrSet;             /* REA Thruster Set to align with thrust vector for a REA turn to burn */
  uWord        SpareWord1;

} ac_jet_table_type, * ac_jet_table_ptr;

/************************************/
#pragma pack()       /* Green Hills */
/************************************/

#endif
