/************************************************************************************************
Copyright (c) <year>, <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** \brief EDU-CIAA-NXP board configuration implementation
 **
 ** \addtogroup board Board support
 ** \brief Board agnostic configuration module
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "board.h"
#include "chip.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/**
 * @brief Structure for initial base clock states
 */
struct CLK_BASE_STATES {
    CHIP_CGU_BASE_CLK_T clk; /*!< Base clock */
    CHIP_CGU_CLKIN_T clkin;  /*!< Base clock source, see UM for allowable souorces per base clock */
    bool autoblock_enab;     /*!< Set to true to enable autoblocking on frequency change */
    bool powerdn;            /*!< Set to true if the base clock is initially powered down */
};

/* === Private variable declarations =========================================================== */

/**
 * @brief Constant with required clock states to configure board
 */
static const struct CLK_BASE_STATES InitClkStates[] = {
#ifdef USE_RMII
    /* Ethernet Clock base */
    {CLK_BASE_PHY_TX, CLKIN_ENET_TX, true, false},
    {CLK_BASE_PHY_RX, CLKIN_ENET_TX, true, false},
#endif
    /* Clocks derived from dividers */
    {CLK_BASE_USB0, CLKIN_IDIVD, true, true},
};

/* === Private function declarations =========================================================== */

/**
 * @brief Function defined by ARM to initializate SemiHosting transfer mode
 */
extern void initialise_monitor_handles(void);

/* === Public variable definitions ============================================================= */

/**
 * @brief Global variable with external clock frecuency required by LPC Open drivers
 */
const uint32_t ExtRateIn = 0;

/**
 * @brief Global variable with external xtal frecuency required by LPC Open drivers
 */
const uint32_t OscRateIn = 12000000;

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static void SetupClocking(void) {
    Chip_CREG_SetFlashAcceleration(MAX_CLOCK_FREQ);
    Chip_SetupCoreClock(CLKIN_CRYSTAL, MAX_CLOCK_FREQ, true);

    /* Setup system base clocks and initial states. This won't enable and
       disable individual clocks, but sets up the base clock sources for
       each individual peripheral clock. */
    for (uint32_t i = 0; i < (sizeof(InitClkStates) / sizeof(InitClkStates[0])); ++i) {
        const struct CLK_BASE_STATES * c = &InitClkStates[i];
        Chip_Clock_SetBaseClock(c->clk, c->clkin, c->autoblock_enab, c->powerdn);
    }

    /* Reset and enable 32Khz oscillator */
    LPC_CREG->CREG0 &= ~((1 << 3) | (1 << 2));
    LPC_CREG->CREG0 |= (1 << 1) | (1 << 0);
}

/* === Public function implementation ========================================================== */

void BoardSetup(void) {
    SetupClocking();
    SystemCoreClockUpdate();

    /*
    If this function is called before enabling the semihosting in the server,
    a HardFault may occur due to an unexpected debug event and, therefore,
    the program does not execute when the board is not in debugging
    */
#if (ENABLE_ARM_SEMIHOSTING)
    initialise_monitor_handles();
#endif
}

/* === End of documentation ====================================================================
 */

/** @} End of module definition for doxygen */
