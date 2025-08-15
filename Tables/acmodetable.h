 /*********************************************************************************************************************
 *
 *  File:                acmodetable.h
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
 

#pragma pack()

#ifndef _acmodetable_h_
#define _acmodetable_h_

#pragma pack(4)

/*
** Spacecraft Attitude Control (AC) Task Mode Table ...
*/

typedef struct ac_mode_table_ {

   uByte Mode[NUM_AC_MODE][NUM_AC_MODE];

   uByte Att [NUM_OF_ATT][NUM_AC_MODE];

} ac_mode_table_type, *ac_mode_table_ptr;

#endif /* _acmodetable_h_ */

#pragma pack()
