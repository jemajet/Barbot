/*******************************************************************************
* File Name: Down_Button.h  
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

#if !defined(CY_PINS_Down_Button_H) /* Pins Down_Button_H */
#define CY_PINS_Down_Button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Down_Button_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Down_Button__PORT == 15 && ((Down_Button__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Down_Button_Write(uint8 value);
void    Down_Button_SetDriveMode(uint8 mode);
uint8   Down_Button_ReadDataReg(void);
uint8   Down_Button_Read(void);
void    Down_Button_SetInterruptMode(uint16 position, uint16 mode);
uint8   Down_Button_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Down_Button_SetDriveMode() function.
     *  @{
     */
        #define Down_Button_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Down_Button_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Down_Button_DM_RES_UP          PIN_DM_RES_UP
        #define Down_Button_DM_RES_DWN         PIN_DM_RES_DWN
        #define Down_Button_DM_OD_LO           PIN_DM_OD_LO
        #define Down_Button_DM_OD_HI           PIN_DM_OD_HI
        #define Down_Button_DM_STRONG          PIN_DM_STRONG
        #define Down_Button_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Down_Button_MASK               Down_Button__MASK
#define Down_Button_SHIFT              Down_Button__SHIFT
#define Down_Button_WIDTH              1u

/* Interrupt constants */
#if defined(Down_Button__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Down_Button_SetInterruptMode() function.
     *  @{
     */
        #define Down_Button_INTR_NONE      (uint16)(0x0000u)
        #define Down_Button_INTR_RISING    (uint16)(0x0001u)
        #define Down_Button_INTR_FALLING   (uint16)(0x0002u)
        #define Down_Button_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Down_Button_INTR_MASK      (0x01u) 
#endif /* (Down_Button__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Down_Button_PS                     (* (reg8 *) Down_Button__PS)
/* Data Register */
#define Down_Button_DR                     (* (reg8 *) Down_Button__DR)
/* Port Number */
#define Down_Button_PRT_NUM                (* (reg8 *) Down_Button__PRT) 
/* Connect to Analog Globals */                                                  
#define Down_Button_AG                     (* (reg8 *) Down_Button__AG)                       
/* Analog MUX bux enable */
#define Down_Button_AMUX                   (* (reg8 *) Down_Button__AMUX) 
/* Bidirectional Enable */                                                        
#define Down_Button_BIE                    (* (reg8 *) Down_Button__BIE)
/* Bit-mask for Aliased Register Access */
#define Down_Button_BIT_MASK               (* (reg8 *) Down_Button__BIT_MASK)
/* Bypass Enable */
#define Down_Button_BYP                    (* (reg8 *) Down_Button__BYP)
/* Port wide control signals */                                                   
#define Down_Button_CTL                    (* (reg8 *) Down_Button__CTL)
/* Drive Modes */
#define Down_Button_DM0                    (* (reg8 *) Down_Button__DM0) 
#define Down_Button_DM1                    (* (reg8 *) Down_Button__DM1)
#define Down_Button_DM2                    (* (reg8 *) Down_Button__DM2) 
/* Input Buffer Disable Override */
#define Down_Button_INP_DIS                (* (reg8 *) Down_Button__INP_DIS)
/* LCD Common or Segment Drive */
#define Down_Button_LCD_COM_SEG            (* (reg8 *) Down_Button__LCD_COM_SEG)
/* Enable Segment LCD */
#define Down_Button_LCD_EN                 (* (reg8 *) Down_Button__LCD_EN)
/* Slew Rate Control */
#define Down_Button_SLW                    (* (reg8 *) Down_Button__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Down_Button_PRTDSI__CAPS_SEL       (* (reg8 *) Down_Button__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Down_Button_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Down_Button__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Down_Button_PRTDSI__OE_SEL0        (* (reg8 *) Down_Button__PRTDSI__OE_SEL0) 
#define Down_Button_PRTDSI__OE_SEL1        (* (reg8 *) Down_Button__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Down_Button_PRTDSI__OUT_SEL0       (* (reg8 *) Down_Button__PRTDSI__OUT_SEL0) 
#define Down_Button_PRTDSI__OUT_SEL1       (* (reg8 *) Down_Button__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Down_Button_PRTDSI__SYNC_OUT       (* (reg8 *) Down_Button__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Down_Button__SIO_CFG)
    #define Down_Button_SIO_HYST_EN        (* (reg8 *) Down_Button__SIO_HYST_EN)
    #define Down_Button_SIO_REG_HIFREQ     (* (reg8 *) Down_Button__SIO_REG_HIFREQ)
    #define Down_Button_SIO_CFG            (* (reg8 *) Down_Button__SIO_CFG)
    #define Down_Button_SIO_DIFF           (* (reg8 *) Down_Button__SIO_DIFF)
#endif /* (Down_Button__SIO_CFG) */

/* Interrupt Registers */
#if defined(Down_Button__INTSTAT)
    #define Down_Button_INTSTAT            (* (reg8 *) Down_Button__INTSTAT)
    #define Down_Button_SNAP               (* (reg8 *) Down_Button__SNAP)
    
	#define Down_Button_0_INTTYPE_REG 		(* (reg8 *) Down_Button__0__INTTYPE)
#endif /* (Down_Button__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Down_Button_H */


/* [] END OF FILE */
