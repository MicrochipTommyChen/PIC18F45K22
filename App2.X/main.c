/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC18F45K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#define  RESET_VECTOR   0x0500
#define  FLASH_MEM_SIZE 0x8000

void EraseResetVector (void);
void Signal_BL_Requested (void);

/*
                         Main application
 */
    uint8_t    writeData = 0xAA;
    uint8_t    writeData2 = 0x55;
    uint32_t    flashAddr = 0x7FFE;
    uint32_t    flashAddr2 = 0x7FFF;
    uint8_t    Buf[ERASE_FLASH_BLOCKSIZE];
  
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    //FLASH_WriteByte(flashAddr, Buf, writeData);
    //FLASH_WriteByte(flashAddr2, Buf, writeData2);
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        // Add your application code
        //FLASH_WriteByte(flashAddr, Buf, writeData);
        while (1)
        {
            //__delay_ms(100);
            if (BUTTON_GetValue()  == LOW)
            {
                INTERRUPT_GlobalInterruptDisable();
                INTERRUPT_PeripheralInterruptDisable();
                Signal_BL_Requested ();
                EraseResetVector ();
                while (BUTTON_GetValue() == LOW);
                RESET();
            }            
        }
    }
}

void Signal_BL_Requested ()
{
    FLASH_WriteByte(FLASH_MEM_SIZE - 1, Buf, 0x00);
    FLASH_WriteByte(FLASH_MEM_SIZE - 2, Buf, 0x00);
}

void EraseResetVector ()
{    
    FLASH_WriteByte(RESET_VECTOR, Buf, 0x00);
    FLASH_WriteByte(RESET_VECTOR + 1, Buf, 0x00);
}
/**
 End of File
*/