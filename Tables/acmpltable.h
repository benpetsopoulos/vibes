/*********************************************************************************************************************
*
*  File:                acmpltable.h
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

/************************************/
#pragma pack()       /* Green Hills */
/************************************/


#ifndef _acmpltable_h_
#define _acmpltable_h_

#pragma pack(4)

/* MPL Parameter Table */
typedef struct ac_mpl_table_
{
  dReal    IscAzAngle;          /* Mission Payload Azimuth Gimbal Orientation For IscInit */
  dReal    IscElAngle;          /* Mission Payload Elivation Gimbal Orientation For IscInit */

  uMatrix  IazLocal;            /* Mission Payload Azimuth Gimbal Inertia, Local Gimbal Frame */
  uMatrix  IelLocal;            /* Mission Payload Elevation Gimbal Inertia, Local Gimbal Frame */

  dReal    MassAz;              /* Mission Payload Azimuth Gimbal Mass, kg */
  dReal    MassEl;              /* Mission Payload Elevation Gimbal Mass, kg */

  uVector  AzCmLocal;           /* Mission Payload Azimuth Gimbal Center of Mass, Local AzGimbal Frame, m */
  uVector  ElCmLocal;           /* Mission Payload Elevation Gimbal Center of Mass, Local ElGimbal Frame, m */

  uVector  AzFrameAttach;       /* Mission Payload Azimuth Gimbal Frame Attach Point, S/C Body (Base Link) Frame, m */
  uVector  ElFrameAttach;       /* Mission Payload Elevation Gimbal Frame Attach Point, AzGimbal (Base Link) Frame, m */
} ac_mpl_table_type;

#endif

/************************************/
#pragma pack()       /* Green Hills */
/************************************/
