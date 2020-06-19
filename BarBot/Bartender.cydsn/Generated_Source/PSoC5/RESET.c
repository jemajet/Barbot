/*******************************************************************************
* File Name: RESET.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "RESET.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 RESET__PORT == 15 && ((RESET__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: RESET_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void RESET_Write(uint8 value) 
{
    uint8 staticBits = (RESET_DR & (uint8)(~RESET_MASK));
    RESET_DR = staticBits | ((uint8)(value << RESET_SHIFT) & RESET_MASK);
}


/*******************************************************************************
* Function Name: RESET_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RESET_DM_STRONG     Strong Drive 
*  RESET_DM_OD_HI      Open Drain, Drives High 
*  RESET_DM_OD_LO      Open Drain, Drives Low 
*  RESET_DM_RES_UP     Resistive Pull Up 
*  RESET_DM_RES_DWN    Resistive Pull Down 
*  RESET_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RESET_DM_DIG_HIZ    High Impedance Digital 
*  RESET_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RESET_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(RESET_0, mode);
}


/*******************************************************************************
* Function Name: RESET_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro RESET_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RESET_Read(void) 
{
    return (RESET_PS & RESET_MASK) >> RESET_SHIFT;
}


/*******************************************************************************
* Function Name: RESET_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 RESET_ReadDataReg(void) 
{
    return (RESET_DR & RESET_MASK) >> RESET_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RESET_INTSTAT) 

    /*******************************************************************************
    * Function Name: RESET_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 RESET_ClearInterrupt(void) 
    {
        return (RESET_INTSTAT & RESET_MASK) >> RESET_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
