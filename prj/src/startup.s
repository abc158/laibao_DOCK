;/*---------------------------------------------------------------------------------------------------------*/
;/* Amicro Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (c) 2016 by Amicro Semiconductor Inc.                                                         */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup.s
;  Version          : V0.00
;  Date             : 2016-09-02
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

;*******************************************************************************
; Stack Configuration.    Stack Size (in Bytes)
;*******************************************************************************
Stack_Size          EQU     (1024*2)

                    AREA    STACK, NOINIT, READWRITE, ALIGN = 3
Stack_Mem           SPACE   Stack_Size
__initial_sp

;*******************************************************************************
; Heap Configuration.    Heap Size (in Bytes)
;*******************************************************************************
Heap_Size           EQU     0

                    AREA    HEAP, NOINIT, READWRITE, ALIGN = 3
__heap_base
Heap_Mem            SPACE   Heap_Size
__heap_limit


                    PRESERVE8
                    THUMB

;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;*******************************************************************************
                    AREA    RESET, CODE, READONLY
                    EXPORT  __Vectors

__Vectors           DCD  __initial_sp                       ; Top Address of Stack
                    DCD  Reset_Handler                      ; Reset Handler
                    DCD  NMI_Handler                        ; NMI Handler
                    DCD  HardFault_Handler                  ; Hard Fault Handler
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  0                                  ; Reserved
                    DCD  SVC_Handler                        ; SVCall Handler
                    DCD  DebugMon_Handler                   ; Debug Monitor Handler
                    DCD  0                                  ; Reserved
                    DCD  PendSV_Handler                     ; PendSV Handler
                    DCD  SysTick_Handler                    ; SysTick Handler

                    ; External Interrupt Handler
                    DCD  CKRDY_IRQHandler
                    DCD  LVD_IRQHandler
                    DCD  WDT_IRQHandler
                    DCD  RTC_IRQHandler
                    DCD  FLASH_IRQHandler
                    DCD  EVWUP_IRQHandler
                    DCD  LPWUP_POR_IRQHandler
                    DCD  EXTI0_1_2_3_IRQHandler
                    DCD  EXTI4_5_6_7_IRQHandler
                    DCD  EXTI8_9_10_11_IRQHandler
                    DCD  EXTI12_13_14_15_IRQHandler
                    DCD  ADC_IRQHandler            
                    DCD  GPTM0_IRQHandler
                    DCD  GPTM1_IRQHandler
                    DCD  GPTM2_IRQHandler
                    DCD  GPTM3_IRQHandler
                    DCD  I2C0_IRQHandler
                    DCD  SPI0_SPI1_IRQHandler
                    DCD  UART0_IRQHandler
                    DCD  UART1_IRQHandler
                    DCD  UART2_IRQHandler
                    DCD  UART3_IRQHandler	
                    DCD  UART4_IRQHandler
                    DCD  UART5_IRQHandler
                    DCD  PDMA_CH0_IRQHandler
                    DCD  PDMA_CH1_IRQHandler
                    DCD  PDMA_CH2_IRQHandler
                    DCD  PDMA_CH3_IRQHandler
                    DCD  PDMA_CH4_CH5IRQHandler
                    DCD  PDMA_CH6_CH7_IRQHandler
                    DCD  COMP_IRQHandler
                    DCD  CAN_IRQHandler

; Reset handler routine
Reset_Handler       PROC
                    EXPORT  Reset_Handler                   [WEAK]
                    IMPORT  SystemInit
                    IMPORT  __main
                    LDR     R0, =SystemInit
                    BLX     R0
                    LDR     R0, =__main
                    BX      R0
					NOP
					NOP
					NOP
                    ENDP

; Exception Handlers
NMI_Handler         PROC
                    EXPORT  NMI_Handler                     [WEAK]
                    B       .
                    ENDP

HardFault_Handler   PROC
                    EXPORT  HardFault_Handler               [WEAK]
                    B       .
                    ENDP

SVC_Handler         PROC
                    EXPORT  SVC_Handler                     [WEAK]
                    B       .
                    ENDP

DebugMon_Handler    PROC
                    EXPORT  DebugMon_Handler                [WEAK]
                    B       .
                    ENDP

PendSV_Handler      PROC
                    EXPORT  PendSV_Handler                  [WEAK]
                    B       .
                    ENDP

SysTick_Handler     PROC
                    EXPORT  SysTick_Handler                 [WEAK]
                    B       .
                    ENDP

Default_Handler     PROC
                    EXPORT  CKRDY_IRQHandler                [WEAK]
                    EXPORT  LVD_IRQHandler                  [WEAK]
                    EXPORT  WDT_IRQHandler                  [WEAK]
                    EXPORT  RTC_IRQHandler                  [WEAK]
                    EXPORT  FLASH_IRQHandler                [WEAK]
                    EXPORT  EVWUP_IRQHandler                [WEAK]
                    EXPORT  LPWUP_POR_IRQHandler            [WEAK]
                    EXPORT  EXTI0_1_2_3_IRQHandler          [WEAK]
                    EXPORT  EXTI4_5_6_7_IRQHandler          [WEAK]
                    EXPORT  EXTI8_9_10_11_IRQHandler        [WEAK]
                    EXPORT  EXTI12_13_14_15_IRQHandler      [WEAK]
                    EXPORT  ADC_IRQHandler                  [WEAK]
                    EXPORT  GPTM0_IRQHandler                [WEAK]
                    EXPORT  GPTM1_IRQHandler                [WEAK]
                    EXPORT  GPTM2_IRQHandler                [WEAK]
                    EXPORT  GPTM3_IRQHandler                [WEAK]
                    EXPORT  I2C0_IRQHandler                 [WEAK]
                    EXPORT  SPI0_SPI1_IRQHandler            [WEAK]
                    EXPORT  UART0_IRQHandler                [WEAK]
                    EXPORT  UART1_IRQHandler                [WEAK]
                    EXPORT  UART2_IRQHandler                [WEAK]
                    EXPORT  UART3_IRQHandler                [WEAK]
                    EXPORT  UART4_IRQHandler                [WEAK]     
                    EXPORT  UART5_IRQHandler                [WEAK]
                    EXPORT  PDMA_CH0_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH1_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH2_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH3_IRQHandler             [WEAK]
                    EXPORT  PDMA_CH4_CH5IRQHandler          [WEAK]
                    EXPORT  PDMA_CH6_CH7_IRQHandler         [WEAK]
                    EXPORT  COMP_IRQHandler                 [WEAK]
                    EXPORT  CAN_IRQHandler                  [WEAK]
             
CKRDY_IRQHandler
LVD_IRQHandler                  
WDT_IRQHandler                  
RTC_IRQHandler                  
FLASH_IRQHandler                
EVWUP_IRQHandler                
LPWUP_POR_IRQHandler            
EXTI0_1_2_3_IRQHandler          
EXTI4_5_6_7_IRQHandler          
EXTI8_9_10_11_IRQHandler        
EXTI12_13_14_15_IRQHandler      
ADC_IRQHandler                  
GPTM0_IRQHandler                
GPTM1_IRQHandler                
GPTM2_IRQHandler                
GPTM3_IRQHandler                
I2C0_IRQHandler                 
SPI0_SPI1_IRQHandler                 
UART0_IRQHandler                
UART1_IRQHandler                
UART2_IRQHandler                
UART3_IRQHandler                
UART4_IRQHandler                
UART5_IRQHandler                
PDMA_CH0_IRQHandler             
PDMA_CH1_IRQHandler             
PDMA_CH2_IRQHandler             
PDMA_CH3_IRQHandler             
PDMA_CH4_CH5IRQHandler          
PDMA_CH6_CH7_IRQHandler         
COMP_IRQHandler                 
CAN_IRQHandler                  

                    B       .
                    ENDP

                    ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                    IF      :DEF:__MICROLIB

                    EXPORT  __initial_sp
                    EXPORT  __heap_base
                    EXPORT  __heap_limit

                    ELSE

                    IMPORT  __use_two_region_memory
                    EXPORT  __user_initial_stackheap
__user_initial_stackheap

                    LDR     R0, =  Heap_Mem
                    LDR     R1, = (Stack_Mem + Stack_Size)
                    LDR     R2, = (Heap_Mem + Heap_Size)
                    LDR     R3, = Stack_Mem
                    BX      LR

                    ALIGN

                    ENDIF

                    END
