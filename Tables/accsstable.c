 /*********************************************************************************************************************
 *
 *  File:                accsstable.c
 *
 *  Last modification:   2015-12-14
 *
 *  Author:              GALEX
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



#include <math.h>
#include "acstypes.h"
#include "acsdefines.h"
#include "accsstable.h"

ac_css_table_type AcCssTable = {

  
  { /* RIU1    RIU2 */          /* AtoDGainFactor (doubled for GaAs CSSs per DN-HORNET-CDH-052) */
#if   (SV_ID == 1)
    { 3.1810, 2.8390 },         /* CSS #1    */
    { 2.9697, 3.0503 },         /* CSS #2    */
    { 3.1770, 2.8430 },         /* CSS #3    */
    { 2.9708, 3.0492 },         /* CSS #4    */
    { 3.1802, 2.8398 },         /* CSS #5    */
    { 2.9689, 3.0511 },         /* CSS #6    */
    { 3.1838, 2.8362 },         /* CSS #7    */
    { 2.9677, 3.0523 },         /* CSS #8    */
    { 2.9451, 3.0749 },         /* CSS #9    */
    { 2.9494, 3.0706 },         /* CSS #10   */
    { 2.9971, 3.0229 },         /* CSS #11   */
    { 2.9973, 3.0227 },         /* CSS #12   */
    { 2.9420, 3.0780 },         /* CSS #13   */
    { 2.9392, 3.0808 },         /* CSS #14   */
    { 2.9940, 3.0260 },         /* CSS #15   */
    { 2.9939, 3.0261 }          /* CSS #16   */
#elif (SV_ID == 2)
    { 3.1986, 2.8214 },         /* CSS #1    */
    { 2.9654, 3.0546 },         /* CSS #2    */
    { 3.1954, 2.8246 },         /* CSS #3    */
    { 2.9648, 3.0552 },         /* CSS #4    */
    { 3.1973, 2.8227 },         /* CSS #5    */
    { 2.9572, 3.0628 },         /* CSS #6    */
    { 3.1949, 2.8251 },         /* CSS #7    */
    { 2.9601, 3.0599 },         /* CSS #8    */
    { 2.9460, 3.0740 },         /* CSS #9    */
    { 2.9447, 3.0753 },         /* CSS #10   */
    { 3.0021, 3.0179 },         /* CSS #11   */
    { 3.0029, 3.0171 },         /* CSS #12   */
    { 2.9439, 3.0761 },         /* CSS #13   */
    { 2.9462, 3.0738 },         /* CSS #14   */
    { 3.0032, 3.0168 },         /* CSS #15   */
    { 3.0039, 3.0161 }          /* CSS #16   */
#elif (SV_ID == 3)
    { 3.2005, 2.8195 },         /* CSS #1    */
    { 2.9806, 3.0394 },         /* CSS #2    */
    { 3.2005, 2.8195 },         /* CSS #3    */
    { 2.9819, 3.0381 },         /* CSS #4    */
    { 3.1992, 2.8208 },         /* CSS #5    */
    { 2.9787, 3.0413 },         /* CSS #6    */
    { 3.2019, 2.8181 },         /* CSS #7    */
    { 2.9796, 3.0404 },         /* CSS #8    */
    { 2.9478, 3.0722 },         /* CSS #9    */
    { 2.9491, 3.0709 },         /* CSS #10   */
    { 3.0095, 3.0105 },         /* CSS #11   */
    { 3.0120, 3.0080 },         /* CSS #12   */
    { 2.9486, 3.0714 },         /* CSS #13   */
    { 2.9485, 3.0715 },         /* CSS #14   */
    { 3.0075, 3.0125 },         /* CSS #15   */
    { 3.0120, 3.0080 }          /* CSS #16   */
#elif (SV_ID == 4)
    { 3.3205, 2.6995},          /* CSS #1    */
    { 2.9892, 3.0308},          /* CSS #2    */
    { 3.3186, 2.7014},          /* CSS #3    */
    { 2.9872, 3.0328},          /* CSS #4    */
    { 3.3208, 2.6992},          /* CSS #5    */
    { 2.9867, 3.0333},          /* CSS #6    */
    { 3.3234, 2.6966},          /* CSS #7    */
    { 2.9875, 3.0325},          /* CSS #8    */
    { 2.9956, 3.0244},          /* CSS #9    */
    { 2.9921, 3.0279},          /* CSS #10   */
    { 3.0550, 2.9650},          /* CSS #11   */
    { 3.0540, 2.9660},          /* CSS #12   */
    { 2.9952, 3.0248},          /* CSS #13   */
    { 2.9937, 3.0263},          /* CSS #14   */
    { 3.0543, 2.9657},          /* CSS #15   */
    { 3.0542, 2.9658}           /* CSS #16   */
#elif (SV_ID == 5)
    { 3.2905, 2.7295},          /* CSS #1    */
    { 2.9737, 3.0463},          /* CSS #2    */
    { 3.2913, 2.7287},          /* CSS #3    */
    { 2.9716, 3.0484},          /* CSS #4    */
    { 3.2920, 2.7280},          /* CSS #5    */
    { 2.9687, 3.0513},          /* CSS #6    */
    { 3.2948, 2.7252},          /* CSS #7    */
    { 2.9693, 3.0507},          /* CSS #8    */
    { 2.9662, 3.0538},          /* CSS #9    */
    { 2.9656, 3.0544},          /* CSS #10   */
    { 3.0393, 2.9807},          /* CSS #11   */
    { 3.0402, 2.9798},          /* CSS #12   */
    { 2.9631, 3.0569},          /* CSS #13   */
    { 2.9650, 3.0550},          /* CSS #14   */
    { 3.0413, 2.9787},          /* CSS #15   */
    { 3.0422, 2.9778},          /* CSS #16   */
#elif (SV_ID == 6)
    { 3.2162, 2.8038},          /* CSS #1    */
    { 2.9809, 3.0391},          /* CSS #2    */
    { 3.2151, 2.8049},          /* CSS #3    */
    { 2.9814, 3.0386},          /* CSS #4    */
    { 3.2172, 2.8028},          /* CSS #5    */
    { 2.9810, 3.0390},          /* CSS #6    */
    { 3.2213, 2.7987},          /* CSS #7    */
    { 2.9801, 3.0399},          /* CSS #8    */
    { 2.9592, 3.0608},          /* CSS #9    */
    { 2.9569, 3.0631},          /* CSS #10   */
    { 3.0192, 3.0008},          /* CSS #11   */
    { 3.0190, 3.0010},          /* CSS #12   */
    { 2.9609, 3.0591},          /* CSS #13   */
    { 2.9580, 3.0620},          /* CSS #14   */
    { 3.0192, 3.0008},          /* CSS #15   */
    { 3.0193, 3.0007},          /* CSS #16   */
#else 
    { 3.01  , 3.01  },          /* CSS #1    */
    { 3.01  , 3.01  },          /* CSS #2    */
    { 3.01  , 3.01  },          /* CSS #3    */
    { 3.01  , 3.01  },          /* CSS #4    */
    { 3.01  , 3.01  },          /* CSS #5    */
    { 3.01  , 3.01  },          /* CSS #6    */
    { 3.01  , 3.01  },          /* CSS #7    */
    { 3.01  , 3.01  },          /* CSS #8    */
    { 3.01  , 3.01  },          /* CSS #9    */
    { 3.01  , 3.01  },          /* CSS #10   */
    { 3.01  , 3.01  },          /* CSS #11   */
    { 3.01  , 3.01  },          /* CSS #12   */
    { 3.01  , 3.01  },          /* CSS #13   */
    { 3.01  , 3.01  },          /* CSS #14   */
    { 3.01  , 3.01  },          /* CSS #15   */
    { 3.01  , 3.01  }           /* CSS #16   */
#endif
  },     

    40.08,                                     /* ScaleFactor */
    0x0002,                                    /* RateCycleMask, Calculate CSS Derived Rate Vector Cycle Mask (1 Hz) */
    0xFFFE,                                    /* RateFrameMask, Calculate CSS Derived Rate Vector Frame Mask, Every Frame 1 - 15  */
    { 0, 0 },                                  /* Padding */
    0.5,                                       /* SdotFiltera1 */
    0.5,                                       /* SdotFilterb1 */
    5.0*DEG_2_RAD,                             /* CoplanarLimit */

  {
    0.0207,                                    /* AlbedoThr, Amp (0.37 * 0.069) Looking +Z in Stowed Configuration */
    0.0207,                                    /* AlbedoThr, Amp (0.30 * 0.069) Otherwise */
    0.0255,
    0.0255,
    0.0207,
    0.0207,
    0.0255,
    0.0255,
    0.0255,
    0.0255,
    0.0207,
    0.0207,
    0.0255,
    0.0255,
    0.0207,
    0.0207
  },
  {                                            /* MaxDetectorCurrent, Amp */
#if   (SV_ID == 1)
  /* Ideal Max Current for GaAs Solar Cells */
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069
#elif (SV_ID == 2)
  /* Ideal Max Current for GaAs Solar Cells */
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069
#elif (SV_ID == 3)
  /* Ideal Max Current for GaAs Solar Cells */
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069
#elif (SV_ID == 4)
  /* Ideal Max Current for GaAs Solar Cells */
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069
#elif (SV_ID == 5)
  /* Ideal Max Current for GaAs Solar Cells */
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069
#elif (SV_ID == 6)
  /* Ideal Max Current for GaAs Solar Cells */
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069
#else /* Ideal Max Current for GaAs Solar Cells */
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069,
      0.069
#endif
  },
  {
   -0.002,                                   /* MinDetectorCurrent, Amp */
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002,
   -0.002 },

   /* CssBoresightBdy0 */
  { { { {  0.57735, -0.57735,  0.57735 } },                    /* CSS#1 .... Stowed */
      { {    0.002,    0.052,    0.102 } },                    /* CSS#1 .... Deploying */
      { {  0.57735,  0.57735,  0.57735 } } },                  /* CSS#1 .... Deployed */
    { { {  0.57735,  0.57735,  0.57735 } },                    /* CSS#2 .... Stowed */
      { {    0.005,    0.055,    0.105 } },                    /* CSS#2 .... Deploying */
      { {  0.57735, -0.57735,  0.57735 } } },                  /* CSS#2 .... Deployed */
    { { {  0.57735,  0.57735,  0.57735 } },                    /* CSS#3 .... Stowed */
      { {    0.008,    0.058,    0.108 } },                    /* CSS#3 .... Deploying */
      { {  0.57735,  0.57735, -0.57735 } } },                  /* CSS#3 .... Deployed */
    { { {  0.57735, -0.57735,  0.57735 } },                    /* CSS#4 .... Stowed */
      { {    0.011,    0.061,    0.111 } },                    /* CSS#4 .... Deploying */
      { {  0.57735, -0.57735, -0.57735 } } },                  /* CSS#4 .... Deployed */
    { { { -0.57735, -0.57735,  0.57735 } },                    /* CSS#5 .... Stowed */
      { {    0.014,    0.064,    0.114 } },                    /* CSS#5 .... Deploying */
      { { -0.57735,  0.57735,  0.57735 } } },                  /* CSS#5 .... Deployed */
    { { { -0.57735,  0.57735,  0.57735 } },                    /* CSS#6 .... Stowed */
      { {    0.017,    0.067,    0.117 } },                    /* CSS#6 .... Deploying */
      { { -0.57735, -0.57735,  0.57735 } } },                  /* CSS#6 .... Deployed */
    { { { -0.57735,  0.57735,  0.57735 } },                    /* CSS#7 .... Stowed */
      { {    0.020,    0.070,    0.120 } },                    /* CSS#7 .... Deploying */
      { { -0.57735,  0.57735, -0.57735 } } },                  /* CSS#7 .... Deployed */
    { { { -0.57735, -0.57735,  0.57735 } },                    /* CSS#8 .... Stowed */
      { {    0.023,    0.073,    0.123 } },                    /* CSS#8 .... Deploying */
      { { -0.57735, -0.57735, -0.57735 } } },                  /* CSS#8 .... Deployed */
    { { {  0.40558,  0.40558,  0.81915 } },                    /* CSS#9 .... Stowed */
      { {  0.40558,  0.40558,  0.81915 } },                    /* CSS#9 .... Deploying */
      { {  0.40558,  0.40558,  0.81915 } } },                  /* CSS#9 .... Deployed */
    { { {  0.40558, -0.40558,  0.81915 } },                    /* CSS#10 ... Stowed */
      { {  0.40558, -0.40558,  0.81915 } },                    /* CSS#10 ... Deploying */
      { {  0.40558, -0.40558,  0.81915 } } },                  /* CSS#10 ... Deployed */
    { { {  0.40558,  0.40558, -0.81915 } },                    /* CSS#11 ... Stowed */
      { {  0.40558,  0.40558, -0.81915 } },                    /* CSS#11 ... Deploying */
      { {  0.40558,  0.40558, -0.81915 } } },                  /* CSS#11 ... Deployed */
    { { {  0.40558, -0.40558, -0.81915 } },                    /* CSS#12 ... Stowed */
      { {  0.40558, -0.40558, -0.81915 } },                    /* CSS#12 ... Deploying */
      { {  0.40558, -0.40558, -0.81915 } } },                  /* CSS#12 ... Deployed */
    { { { -0.40558,  0.40558,  0.81915 } },                    /* CSS#13 ... Stowed */
      { { -0.40558,  0.40558,  0.81915 } },                    /* CSS#13 ... Deploying */
      { { -0.40558,  0.40558,  0.81915 } } },                  /* CSS#13 ... Deployed */
    { { { -0.40558, -0.40558,  0.81915 } },                    /* CSS#14 ... Stowed */
      { { -0.40558, -0.40558,  0.81915 } },                    /* CSS#14 ... Deploying */
      { { -0.40558, -0.40558,  0.81915 } } },                  /* CSS#14 ... Deployed */
    { { { -0.40558,  0.40558, -0.81915 } },                    /* CSS#15 ... Stowed */
      { { -0.40558,  0.40558, -0.81915 } },                    /* CSS#15 ... Deploying */
      { { -0.40558,  0.40558, -0.81915 } } },                  /* CSS#15 ... Deployed */
    { { { -0.40558, -0.40558, -0.81915 } },                    /* CSS#16 ... Stowed */
      { { -0.40558, -0.40558, -0.81915 } },                    /* CSS#16 ... Deploying */
      { { -0.40558, -0.40558, -0.81915 } } } },                /* CSS#16 ... Deployed */

    6 * MIN_2_SEC * NUM_AC_CYCLES,                             /* FailTimeOut, cycles */
    2 * NUM_AC_CYCLES,                                         /* StartEclipseCount */
    2 * NUM_AC_CYCLES,                                         /* EndEclipseCount */
    {                                                          /* MaxEclipseDuration (72 min.)*/
       0 * MIN_2_SEC * NUM_AC_CYCLES,                          /* Stowed    */
       0 * MIN_2_SEC * NUM_AC_CYCLES,                          /* Deploying */
      72 * MIN_2_SEC * NUM_AC_CYCLES                           /* Deployed  */
    },
    {0,0},                                                     /* Spare */
    /* EnableRiu2Tlm */
    { FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE,
      FALSE
    },

    /* CssLocation */
    { CSS_LOC_SAD2,
      CSS_LOC_SAD1,
      CSS_LOC_SAD2,
      CSS_LOC_SAD1,
      CSS_LOC_SAD2,
      CSS_LOC_SAD1,
      CSS_LOC_SAD2,
      CSS_LOC_SAD1,
      CSS_LOC_BDY,
      CSS_LOC_BDY,
      CSS_LOC_BDY,
      CSS_LOC_BDY,
      CSS_LOC_BDY,
      CSS_LOC_BDY,
      CSS_LOC_BDY,
      CSS_LOC_BDY
    },

  /* Stowed  Deploying  Deployed */          /* --- AllowCSS, NA ... */
  { { FALSE,    FALSE,      TRUE },          /* CSS #1    */
    { FALSE,    FALSE,      TRUE },          /* CSS #2    */
    { TRUE ,    FALSE,      TRUE },          /* CSS #3    */
    { TRUE ,    FALSE,      TRUE },          /* CSS #4    */
    { FALSE,    FALSE,      TRUE },          /* CSS #5    */
    { FALSE,    FALSE,      TRUE },          /* CSS #6    */
    { TRUE ,    FALSE,      TRUE },          /* CSS #7    */
    { TRUE ,    FALSE,      TRUE },          /* CSS #8    */
    { TRUE ,    TRUE ,      TRUE },          /* CSS #9    */
    { TRUE ,    TRUE ,      TRUE },          /* CSS #10   */
    { TRUE ,    TRUE ,      TRUE },          /* CSS #11   */
    { TRUE ,    TRUE ,      TRUE },          /* CSS #12   */
    { TRUE ,    TRUE ,      TRUE },          /* CSS #13   */
    { TRUE ,    TRUE ,      TRUE },          /* CSS #14   */
    { TRUE ,    TRUE ,      TRUE },          /* CSS #15   */
    { TRUE ,    TRUE ,      TRUE } },        /* CSS #16   */

    {
      { 5*NUM_AC_CYCLES,                        /* Fdc.CurrentTestCnt, cnt */
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES,
        5*NUM_AC_CYCLES
      },

      { 0.0941,                                  /* MaxDetectorCurrent + (AlbedoThr + 3-sigma noise)*1.2,      Fdc.MaxDetectorCurrent, Amp */
        0.0941,                                  /* MaxDetectorCurrent + (0.0255    + 0.000188     )*1.2 Looking +Z in Stowed Configuration*/
        0.0998,                                  /* MaxDetectorCurrent + (0.0207    + 0.000188     )*1.2 Otherwise */
        0.0998,
        0.0941,
        0.0941,
        0.0998,
        0.0998,
        0.0998,
        0.0998,
        0.0941,
        0.0941,
        0.0998,
        0.0998,
        0.0941,
        0.0941
      }
    }
};

