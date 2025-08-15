/*********************************************************************************************************************
*
*  File:                acmpltable.c
*
*  Last modification:   2022-04-21
*
*  Author:              A. Napiecek
*
*  COPYRIGHT (C):       2022. Northrop Grumman Corporation.  Unless otherwise marked, all files
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
** MPL Parameter Table ...
*/

#include "acstypes.h"
#include "acsdefines.h"
#include "acmpltable.h"

ac_mpl_table_type AcMplTable = {
  (90.0 * DEG_2_RAD),                         /* IscAzAngle, rad */
  (0.0  * DEG_2_RAD),                         /* IscElAngle, rad */

  {{{  12.05927,   -0.10415,    3.28974 },    /* IazLocal, kg-m^2, Mass Props Rev E */
    {  -0.10415,   19.76431,    0.04727 },
    {   3.28974,    0.04727,    9.20206 }}},

  {{{  26.25555,    0.31184,   -1.33969 },    /* IelLocal, kg-m^2, Mass Props Rev E */
    {   0.31184,   29.28359,   -2.10382 },
    {  -1.33969,   -2.10382,   10.63511 }}},

  73.672,                                     /* MassAz, kg , Mass Props Rev E */
  110.944,                                    /* MassEl, kg , Mass Props Rev E */

  { -0.07049, 0.00000,  0.28360 },            /* AzCmLocal (m), Mass Props Rev E */
  {  0.04680, 0.00000, -0.00001 },            /* ElCmLocal (m), Mass Props Rev E */

  {  0.00000, 0.00000,  1.83388 },            /* AzFrameAttach (m), Mass Props Rev E */
  {  0.00000, 0.00000,  0.92443 }             /* ElFrameAttach (m), Mass Props Rev E */
};
