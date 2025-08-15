 /*********************************************************************************************************************
 *
 *  File:                acstatable.c
 *
 *  Last modification:   2014-09-12
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

/*
** Star Tracker Parameter Table ...
*/

#include "acstatable.h"
#include "acatd.h"

ac_sta_table_type AcStaTable = {

   { 262.5E-3,                 262.5E-3 },                                            /* StaMesDelay[STA1], [STA2] (sec) */
   { 0.0 },                                                                           /* IruToAcDelay (sec) */
   { 3.0 },                                                                           /* WarmUpTime (sec) */
   { 2.0E-05 },                                                                       /* CoiScaleFactor (sec/count) */
   { 1.0 },                                                                           /* LinearVelocityLsbX (m/s/count) */
   { 1.0 },                                                                           /* LinearVelocityLsbY (m/s/count) */
   { 1.0 },                                                                           /* LinearVelocityLsbZ (m/s/count) */
   { 0.1 },                                                                           /* XYQualityIndexLsb (arcsec/count)*/
   { 0.1 },                                                                           /* ZQualityIndexLsb (arcsec/count)*/
 { {                                                                                  /* QBdyToSta[STA1] */
#if   (SV_ID == 1)                                                                    /* SV1 Alignment From YYYY/MM/DD */
     0.595752843342,
    -0.241359981871,
     0.709990316835,
     0.287641598987
#elif (SV_ID == 2)                                                                    /* SV2 Alignment From YYYY/MM/DD */
     0.595752843342,
    -0.241359981871,
     0.709990316835,
     0.287641598987
#elif (SV_ID == 3)                                                                    /* SV3 Alignment From YYYY/MM/DD */
     0.595752843342,
    -0.241359981871,
     0.709990316835,
     0.287641598987
#elif (SV_ID == 4)                                                                    /* SV4 Alignment From YYYY/MM/DD */
     0.595752843342,
    -0.241359981871,
     0.709990316835,
     0.287641598987
#elif (SV_ID == 5)                                                                    /* SV5 Alignment From YYYY/MM/DD */
     0.595752843342,
    -0.241359981871,
     0.709990316835,
     0.287641598987
#elif (SV_ID == 6)                                                                    /* SV6 Alignment From YYYY/MM/DD */
     0.595752843342,
    -0.241359981871,
     0.709990316835,
     0.287641598987
#else                                                                                 /* Ideal Alignment */
     0.595752843342,
    -0.241359981871,
     0.709990316835,
     0.287641598987
#endif
 },
 {                                                                                    /* QBdyToSta[STA2] */
#if   (SV_ID == 1)                                                                    /* SV1 Alignment From YYYY/MM/DD */
     0.241359981871,
    -0.595752843342,
     0.287641598987,
     0.709990316835
#elif (SV_ID == 2)                                                                    /* SV2 Alignment From YYYY/MM/DD */
     0.241359981871,
    -0.595752843342,
     0.287641598987,
     0.709990316835
#elif (SV_ID == 3)                                                                    /* SV3 Alignment From YYYY/MM/DD */
     0.241359981871,
    -0.595752843342,
     0.287641598987,
     0.709990316835
#elif (SV_ID == 4)                                                                    /* SV4 Alignment From YYYY/MM/DD */
     0.241359981871,
    -0.595752843342,
     0.287641598987,
     0.709990316835
#elif (SV_ID == 5)                                                                    /* SV5 Alignment From YYYY/MM/DD */
     0.241359981871,
    -0.595752843342,
     0.287641598987,
     0.709990316835
#elif (SV_ID == 6)                                                                    /* SV6 Alignment From YYYY/MM/DD */
     0.241359981871,
    -0.595752843342,
     0.287641598987,
     0.709990316835
#else                                                                                 /* Ideal Alignment */
     0.241359981871,
    -0.595752843342,
     0.287641598987,
     0.709990316835
#endif
}},






{
  {
    {
      /* StaNoiseCov [STA_OH1] (rad^2) */
      /* Reference: Table 1 in "Seraphim Star Tracker Assembly   */
      /* Performance Specification", 6554-PF4660, Rev -, 04/12/18 */
      { SQR( ( 3.8 / 3.0 ) * ARCSEC_2_RAD ), 0.0,                                 0.0                                },
      { 0.0,                                 SQR( ( 3.8 / 3.0 ) * ARCSEC_2_RAD ), 0.0                                },
      { 0.0,                                 0.0,                                 SQR( ( 31 / 3.0 ) * ARCSEC_2_RAD ) }
    }
  },

  {
    {
      /* StaNoiseCov [STA_OH2] (rad^2) */
      /* Reference: Table 1 in "Seraphim Star Tracker Assembly   */
      /* Performance Specification", 6554-PF4660, Rev -, 04/12/18 */
      { SQR( ( 3.8 / 3.0 ) * ARCSEC_2_RAD ), 0.0,                                 0.0                                },
      { 0.0,                                 SQR( ( 3.8 / 3.0 ) * ARCSEC_2_RAD ), 0.0                                },
      { 0.0,                                 0.0,                                 SQR( ( 31 / 3.0 ) * ARCSEC_2_RAD ) }
    }
  }
},


 {{{ 0.0,  0.0, 1.0 }},                                              /* BoresightSta[STA_OH1] */
  {{ 0.0,  0.0, 1.0 }}},                                             /* BoresightSta[STA_OH2] */

 { { 60, 60, 600},                                                   /* QualityIndexThr[STA_OH1], (arcsec) */
   { 60, 60, 600} },                                                 /* QualityIndexThr[STA_OH2], (arcsec) */


   { STA_AUTO_ACQ_MODE },                                            /* VelCmdModeMin */
   { STA_AUTO_TRK_MODE },                                            /* VelCmdModeMax */

   { 0x0070 },                                                       /* SecondStatusMask                        (Big Endian Bit order) */
   { 0x0050 },                                                       /* SecondStatusDesired                     (Big Endian Bit order) */
   { 0x0FFE },                                                       /* HealthStatusMask                        (Big Endian Bit order) */
   { 0x0000 },                                                       /* HealthStatusDesired                     (Big Endian Bit order) */
   { 0x007F,     0x007F },                                           /* SyntDefOhMask[STA_OH1], [STA_OH2]       (Big Endian Bit order) */
   { 0x0000,     0x0000 },                                           /* SyntDefOhDesired[STA_OH1], [STA_OH2]    (Big Endian Bit order) */
     0,                                                              /* SpareWord                                                      */
     3*NUM_STA_CYCLES,                                               /* PowerOffCnt,                            (ACS Cycles)           */

 {                                                                   /**** FDC ****/
   { ( 21.0 + 1.0 ) * DEG_2_RAD, ( 21.0 + 1.0 ) * DEG_2_RAD },       /* EarthOccultationThr[STA1], rad             ( RP__00002103_D__Perf_HYDRA_TC Section 9.3)*/
   { 0.882947592858927, 0.882947592858927 },                         /* SolarOccultationThr[STA1], cos(27.0+1 deg) ( RP__00002103_D__Perf_HYDRA_TC Section 9.3) */
   { 0.93969262078591, 0.93969262078591 },                           /* LunarOccultationThr[STA1], cos(20 deg) */

   { 20*NUM_STA_CYCLES, 20 * NUM_STA_CYCLES },                       /* DataValidityFailCnt[STA1, STA2],       cnt */
   { 15*MIN_2_SEC*NUM_STA_CYCLES, 15 * MIN_2_SEC*NUM_STA_CYCLES },   /* DataQualityFailCnt[STA1, STA2],        cnt */
   { 20*NUM_STA_CYCLES },                                            /* StaDataValidityFailCnt                 cnt */
   { 20*NUM_STA_CYCLES },                                            /* PowerStatusOffCnt                      cnt */
   { COARSE_CONVERGED },                                             /* OccultationADKFThr,                        */


   { STA_AUTO_TRK_MODE },                                            /* ExpectedOpModeMin[STA1]                    */
   { STA_AUTO_TRK_MODE },                                            /* ExpectedOpModeMax[STA1]                    */
   { { STA_OH_TRACKING },                                            /* OhDesiredSeqStatusMin [ STA_OH1 ]          */
     { STA_OH_TRACKING } },                                          /* OhDesiredSeqStatusMin [ STA_OH2 ]          */
   { { STA_OH_TRACKING },                                            /* OhDesiredSeqStatusMax [ STA_OH1 ]          */
     { STA_OH_TRACKING } },                                          /* OhDesiredSeqStatusMax [ STA_OH2 ]          */
     30*NUM_AC_CYCLES,                                               /* StaCorrectCnt,             cnt */
     20*NUM_AC_CYCLES,                                               /* StaVerifyCnt,              cnt */
     0                                                               /* SpareWord */
 },

   0xAAAA,                                                           /* CycleMask, Cycle 1, 3, 5, ... (5 Hz)      */
   0xFFFE,                                                           /* FrameMask, Every Frame 1 - 15             */
 { 0x0400 },                                                         /* VelCmdCycleMask[STA1], Cycle 3 (1 Hz)     */
 { 0xFFFE }                                                          /* VelCmdFrameMask[STA1], Every Frame 1 - 15 */

};

