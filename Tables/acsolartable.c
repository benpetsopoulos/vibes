 /*********************************************************************************************************************
 *
 *  File:                acsolartable.c
 *
 *  Last modification:   2011-12-13
 *
 *  Author:              P. R. Shah
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
** Solar Ephemeris Parameter Table ...
*/

#include "acstypes.h"
#include "acsdefines.h"
#include "acsolartable.h"

ac_solar_table_type  AcSolarTable =
{
  23.439279  * DEG_2_RAD,                       /* SMSE0 */
  0.00000040 * DEG_2_RAD,                       /* SMSE1 */
  357.528    * DEG_2_RAD,                       /* SMMA1 */
  0.9856003  * DEG_2_RAD,                       /* SMMA2 */
  280.460    * DEG_2_RAD,                       /* SMML1, 280.47169 */
  0.9856474  * DEG_2_RAD,                       /* SMML2 */
  1.915      * DEG_2_RAD,                       /* SMEL1 */
  0.020      * DEG_2_RAD,                       /* SMEL2 */
  5028.7800  * ARCSEC_2_RAD / CENTURY_2_DAY,    /* SMGPL */
  1.00014,                                      /* SMR1 */
  0.01671,                                      /* SMR2 */
  0.00014,                                      /* SMR3 */
  149597871465.6,                               /* RS0 */

  30,                                           /* ComputeVelocityCnt */
  0                                             /* Pad structure */
};

