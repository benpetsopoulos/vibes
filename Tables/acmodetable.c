 /*********************************************************************************************************************
 *
 *  File:                acmodetable.c
 *
 *  Last modification:   2013-09-19
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


/*
** Spacecraft Attitude Control (AC) Task Mode Table ...
*/

#include "acstypes.h"
#include "acsdefines.h"
#include "acatc.h"
#include "acmodetable.h"

ac_mode_table_type  AcModeTable = {

  /* AcModeTable.Mode[RequestedMode][CurrentMode] */
  /* S  RN  SAQ SPt  DV Nml Tgt  M */
                                        /* _RequestedMode_ */
  {{ 0,  0,  0,  0,  0,  0,  0,  0 },   /* Standby */
   { 1,  0,  1,  1,  1,  1,  1,  1 },   /* RateNulling */
   { 0,  1,  0,  1,  1,  0,  0,  0 },   /* SunAcquisition */
   { 0,  0,  1,  0,  1,  0,  0,  0 },   /* SunPointing */
   { 0,  0,  0,  1,  0,  1,  1,  0 },   /* DeltaV */
   { 1,  0,  0,  1,  1,  0,  1,  1 },   /* Normal */
   { 0,  0,  0,  0,  0,  0,  0,  0 },   /* Target Pointing */
   { 0,  0,  0,  0,  0,  1,  0,  0 }},  /* Mission */

  /* AcModeTable.Att[RequestedAtt][CurrentMode] */
  /* S  RN  SAQ SPt  DV Nml Tgt  M */
                                        /* _RequestedAtt_ */
  {{ 1,  0,  0,  0,  0,  1,  1,  1 },   /* Current */
   { 1,  0,  0,  0,  0,  1,  1,  1 },   /* ThreeAxis */
   { 1,  1,  1,  1,  0,  0,  0,  0 },   /* Css */
   { 1,  0,  0,  0,  0,  1,  1,  1 },   /* Equatorial */
   { 1,  0,  0,  0,  0,  1,  1,  1 },   /* Lvlh */
   { 1,  0,  0,  0,  0,  1,  1,  1 },   /* TwoAxis */
   { 0,  0,  0,  0,  0,  0,  0,  0 },   /* Spare */
   { 1,  0,  0,  0,  0,  1,  1,  1 }}   /* SunEph */

};

