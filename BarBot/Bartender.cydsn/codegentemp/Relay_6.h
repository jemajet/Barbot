/*******************************************************************************
* File Name: Relay_6.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Relay_6_H) /* Pins Relay_6_H */
#define CY_PINS_Relay_6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Relay_6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Relay_6__PORT == 15 && ((Relay_6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Relay_6_Write(uint8 value);
void    Relay_6_SetDriveMode(uint8 mode);
uint8   Relay_6_ReadDataReg(void);
uint8   Relay_6_Read(void);
void    Relay_6_SetInterruptMode(uint16 position, uint16 mode);
uint8   Relay_6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Relay_6_SetDriveMode() function.
     *  @{
     */
        #define Relay_6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Relay_6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Relay_6_DM_RES_UP          PIN_DM_RES_UP
        #define Relay_6_DM_RES_DWN         PIN_DM_RES_DWN
        #define Relay_6_DM_OD_LO           PIN_DM_OD_LO
        #define Relay_6_DM_OD_HI           PIN_DM_OD_HI
        #define Relay_6_DM_STRONG          PIN_DM_STRONG
        #define Relay_6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Relay_6_MASK               Relay_6__MASK
#define Relay_6_SHIFT              Relay_6__SHIFT
#define Relay_6_WIDTH              1u

/* Interrupt constants */
#if defined(Relay_6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Relay_6_SetInterruptMode() function.
     *  @{
     */
        #define Relay_6_INTR_NONE      (uint16)(0x0000u)
        #define Relay_6_INTR_RISING    (uint16)(0x0001u)
        #define Relay_6_INTR_FALLING   (uint16)(0x0002u)
        #define Relay_6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Relay_6_INTR_MASK      (0x01u) 
#endif /* (Relay_6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Relay_6_PS                     (* (reg8 *) Relay_6__PS)
/* Data Register */
#define Relay_6_DR                     (* (reg8 *) Relay_6__DR)
/* Port Number */
#define Relay_6_PRT_NUM                (* (reg8 *) Relay_6__PRT) 
/* Connect to Analog Globals */                                                  
#define Relay_6_AG                     (* (reg8 *) Relay_6__AG)                       
/* Analog MUX bux enable */
#define Relay_6_AMUX                   (* (reg8 *) Relay_6__AMUX) 
/* Bidirectional Enable */                                                        
#define Relay_6_BIE                    (* (reg8 *) Relay_6__BIE)
/* Bit-mask for Aliased Register Access */
#define Relay_6_BIT_MASK               (* (reg8 *) Relay_6__BIT_MASK)
/* Bypass Enable */
#define Relay_6_BYP                    (* (reg8 *) Relay_6__BYP)
/* Port wide control signals */                                                   
#define Relay_6_CTL                    (* (reg8 *) Relay_6__CTL)
/* Drive Modes */
#define Relay_6_DM0                    (* (reg8 *) Relay_6__DM0) 
#define Relay_6_DM1                    (* (reg8 *) Relay_6__DM1)
#define Relay_6_DM2                    (* (reg8 *) Relay_6__DM2) 
/* Input Buffer Disable Override */
#define Relay_6_INP_DIS                (* (reg8 *) Relay_6__INP_DIS)
/* LCD Common or Segment Drive */
#define Relay_6_LCD_COM_SEG            (* (reg8 *) Relay_6__LCD_COM_SEG)
/* Enable Segment LCD */
#define Relay_6_LCD_EN                 (* (reg8 *) Relay_6__LCD_EN)
/* Slew Rate Control */
#define Relay_6_SLW                    (* (reg8 *) Relay_6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Relay_6_PRTDSI__CAPS_SEL       (* (reg8 *) Relay_6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Relay_6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Relay_6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Relay_6_PRTDSI__OE_SEL0        (* (reg8 *) Relay_6__PRTDSI__OE_SEL0) 
#define Relay_6_PRTDSI__OE_SEL1        (* (reg8 *) Relay_6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Relay_6_PRTDSI__OUT_SEL0       (* (reg8 *) Relay_6__PRTDSI__OUT_SEL0) 
#define Relay_6_PRTDSI__OUT_SEL1       (* (reg8 *) Relay_6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Relay_6_PRTDSI__SYNC_OUT       (* (reg8 *) Relay_6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Relay_6__SIO_CFG)
    #define Relay_6_SIO_HYST_EN        (* (reg8 *) Relay_6__SIO_HYST_EN)
    #define Relay_6_SIO_REG_HIFREQ     (* (reg8 *) Relay_6__SIO_REG_HIFREQ)
    #define Relay_6_SIO_CFG            (* (reg8 *) Relay_6__SIO_CFG)
    #define Relay_6_SIO_DIFF           (* (reg8 *) Relay_6__SIO_DIFF)
#endif /* (Relay_6__SIO_CFG) */

/* Interrupt Registers */
#if defined(Relay_6__INTSTAT)
    #define Relay_6_INTSTAT            (* (reg8 *) Relay_6__INTSTAT)
    #define Relay_6_SNAP               (* (reg8 *) Relay_6__SNAP)
    
	#define Relay_6_0_INTTYPE_REG 		(* (reg8 *) Relay_6__0__INTTYPE)
#endif /* (Relay_6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Relay_6_H */


/* [] END OF FILE */
