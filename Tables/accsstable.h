 /*********************************************************************************************************************
 *
 *  File:                accsstable.h
 *
 *  Last modification:   2013-06-06 
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


/************************************/
#pragma pack()       /* Green Hills */
/************************************/

#ifndef _accsstable_h_
#define _accsstable_h_

#pragma pack(4)

typedef struct {
    dReal   AtoDGainFactor[NUM_OF_CSS][NUM_OF_RIU];
    dReal   ScaleFactor;
    uWord   RateCycleMask;
    uWord   RateFrameMask;
    uWord   Spare1[2];
    dReal   SdotFiltera1;
    dReal   SdotFilterb1;
    dReal   CoplanarLimit;

    dReal   AlbedoThr[NUM_OF_CSS];
    dReal   MaxDetectorCurrent[NUM_OF_CSS];           /* Max value for valid detector current (Amp) */
    dReal   MinDetectorCurrent[NUM_OF_CSS];           /* Min value for valid detector current (Amp) */

    uVector CssBoresightBdy0[NUM_OF_CSS][NUM_SC_CFG]; /* Initial Unit Vector for CSS Boresight in SC Body Frame */ 

    uWord   FailTimeOut;                              /* BlindZoneTimer Default */
    uWord   StartEclipseCount;                        
    uWord   EndEclipseCount;                          
    uWord   MaxEclipseDuration[NUM_SC_CFG];
    uWord   Spare2[2];
                                                      
    uWord   EnableRiu2Tlm[NUM_OF_CSS];                /* Enable Flag For RIU Interface */
    uWord   CssLocation[NUM_OF_CSS];                  
    uWord   AllowCSS[NUM_OF_CSS][NUM_SC_CFG];         /* Flag To Allow the Use of a CSS */
                                                      
    struct {                                          
      uWord   CurrentTestCnt[NUM_OF_CSS];             
      dReal   MaxDetectorCurrent[NUM_OF_CSS];         /* Max value for valid detector current + noise + albedo (Amp) */
    } Fdc;

} ac_css_table_type, *ac_css_table_ptr;

#endif

/************************************/
#pragma pack()       /* Green Hills */
/************************************/
