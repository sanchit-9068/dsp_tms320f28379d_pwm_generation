

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define EPWM1_TIMER_TBPRD  1500U


#define EPWM2_TIMER_TBPRD  1500U


#define EPWM3_TIMER_TBPRD  1500U


#define EPWM_CMP_UP           1U
#define EPWM_CMP_DOWN         0U

//
// Globals
//

void initEPWM1(void);
void initEPWM2(void);
void initEPWM3(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();


    //
    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 as ePWM1A/1B, ePWM2A/2B and
    // ePWM3A/3B pins respectively
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initEPWM1();
    initEPWM2();
    initEPWM3();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);



    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        NOP;
    }
}


//
// initEPWM1 - Configure ePWM1
//
void initEPWM1()
{
    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(myEPWM1_BASE, EPWM1_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0U);
    //
    // Set Compare values
    //
    EPWM_setCounterCompareValue(myEPWM1_BASE,
                                EPWM_COUNTER_COMPARE_A,
                                750);
    EPWM_setCounterCompareValue(myEPWM1_BASE,
                                EPWM_COUNTER_COMPARE_B,
                                750);

    //
    // Set up counter mode
    //
    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    EPWM_setClockPrescaler(myEPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    //
    EPWM_setActionQualifierAction(myEPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_TOGGLE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(myEPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(myEPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(myEPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

}

//
// initEPWM2 - Configure ePWM2
//
void initEPWM2()
{
    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(myEPWM2_BASE, EPWM2_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM2_BASE, EPWM2_TIMER_TBPRD/6);
    EPWM_setTimeBaseCounter(myEPWM2_BASE, 0U);

    //
    // Set Compare values
    //
    EPWM_setCounterCompareValue(myEPWM2_BASE,
                                EPWM_COUNTER_COMPARE_A,
                                750);
    EPWM_setCounterCompareValue(myEPWM2_BASE,
                                EPWM_COUNTER_COMPARE_B,
                                750);

    //
    // Set-up counter mode
    //
    EPWM_setTimeBaseCounterMode(myEPWM2_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_enablePhaseShiftLoad(myEPWM2_BASE);
    EPWM_setClockPrescaler(myEPWM2_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set-up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set Action qualifier
    //
    EPWM_setActionQualifierAction(myEPWM2_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(myEPWM2_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(myEPWM2_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM2_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

}
//
// initEPWM3 - Configure ePWM3
//
void initEPWM3(void)
{
    //
       // Set-up TBCLK
       //
       EPWM_setTimeBasePeriod(myEPWM3_BASE, EPWM2_TIMER_TBPRD);
       EPWM_setPhaseShift(myEPWM3_BASE, EPWM2_TIMER_TBPRD/1.2);
       EPWM_setTimeBaseCounter(myEPWM3_BASE, 0U);

       //
       // Set Compare values
       //
       EPWM_setCounterCompareValue(myEPWM3_BASE,
                                   EPWM_COUNTER_COMPARE_A,
                                   750);
       EPWM_setCounterCompareValue(myEPWM3_BASE,
                                   EPWM_COUNTER_COMPARE_B,
                                   750);

       //
       // Set-up counter mode
       //
       EPWM_setTimeBaseCounterMode(myEPWM3_BASE, EPWM_COUNTER_MODE_UP_DOWN);
       EPWM_enablePhaseShiftLoad(myEPWM3_BASE);
       EPWM_setClockPrescaler(myEPWM3_BASE,
                              EPWM_CLOCK_DIVIDER_1,
                              EPWM_HSCLOCK_DIVIDER_1);

       //
       // Set-up shadowing
       //
       EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE,
                                            EPWM_COUNTER_COMPARE_A,
                                            EPWM_COMP_LOAD_ON_CNTR_ZERO);
       EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE,
                                            EPWM_COUNTER_COMPARE_B,
                                            EPWM_COMP_LOAD_ON_CNTR_ZERO);

       //
       // Set Action qualifier
       //
       EPWM_setActionQualifierAction(myEPWM3_BASE,
                                     EPWM_AQ_OUTPUT_A,
                                     EPWM_AQ_OUTPUT_HIGH,
                                     EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
       EPWM_setActionQualifierAction(myEPWM3_BASE,
                                     EPWM_AQ_OUTPUT_A,
                                     EPWM_AQ_OUTPUT_LOW,
                                     EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
       EPWM_setActionQualifierAction(myEPWM3_BASE,
                                     EPWM_AQ_OUTPUT_B,
                                     EPWM_AQ_OUTPUT_LOW,
                                     EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
       EPWM_setActionQualifierAction(myEPWM3_BASE,
                                     EPWM_AQ_OUTPUT_B,
                                     EPWM_AQ_OUTPUT_HIGH,
                                     EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

}
