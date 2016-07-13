/*
 * Copyright (c) 2014-2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== blink.c ========
 */

#include <stdbool.h>

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>

/* Example/Board Header files */
#include "Board.h"

#include <ti/hap/ip/HAPEngine.h>
#include <ti/mfi/mfiauth.h>

#include "netwifi.h"
#include "accessory.h"

#define POLLFXNTIMEOUT 3000
#define DEBOUNCETIME 200 //in milliseconds

void gpioButtonFxn0(void);
void gpioButtonFxn1(void);
int waitForButton();

HAPEngine_Handle  engineHandle;
char apName[] = "blink";
int prevTicks, curTicks, msPeriod;

void gpioButtonFxn0(void)
{
}

void gpioButtonFxn1(void)
{
#if 0
    curTicks = Clock_getTicks();
    msPeriod = Clock_tickPeriod / 1000;
    if ((curTicks - prevTicks) >= (DEBOUNCETIME/msPeriod)) {
        GPIO_toggle(Board_LED0);
        if (engineHandle) {
            /* aID 1, sIndex 0, cIndex 0 */
            HAPEngine_updateCharacteristic(engineHandle, 1, 0, 0);
        }
    }
    prevTicks = curTicks;
    GPIO_clearInt(Board_BUTTON1);
#endif
}

/* Fxn to poll for button press to run WAC at network bootup*/
int waitForButton()
{
#if 0
    static int curButton, prevButton;

    GPIO_toggle(Board_LED0);
    curButton = GPIO_read(Board_BUTTON0);
    if ((curButton == 0) && (prevButton != 0)) {
#endif
        return NETWIFI_RUNWAC;
#if 0
        }
    prevButton = curButton;
    return NETWIFI_PROCEED;
#endif
}

/*
 *  ======== serverFxn ========
 *  Initializes WiFi module and runs HAPEngine server
 *
 */
Void serverFxn(UArg arg0, UArg arg1)
{
    int status;
    HAPEngine_AccessoryDesc *accs[1];
    long IPAddress;
    HAPEngine_Params params;
    long slResult;
    _u8 macAddr[SL_MAC_ADDR_LEN];
    _u16 macAddrLen = SL_MAC_ADDR_LEN;
    char macAddrBuf[20];

    IPAddress = NetWiFi_waitForNetwork(apName,
                                       waitForButton, POLLFXNTIMEOUT);

    Assert_isTrue(IPAddress > 0, NULL);

    System_printf("CC3200 has connected to AP and acquired an IP address.\n");
    System_printf("IP Address: %d.%d.%d.%d\n", SL_IPV4_BYTE(IPAddress,3),
                  SL_IPV4_BYTE(IPAddress,2), SL_IPV4_BYTE(IPAddress,1),
                  SL_IPV4_BYTE(IPAddress,0));
    System_flush();

    /* Init HAPEngine */
    HAPEngine_init();

    /* Initialize accessory descriptor with run-time supplied info */
    status = accessory_init(&accessory_services);
    Assert_isTrue(status == HAPEngine_EOK, NULL);
    HAPEngine_Params_init(&params);

    /* Conditionally add MFi-based pairing (if the chip is detected) */
    status = MFiAuth_setDevice("0", 0x10);
    System_printf("MFiAuth: %d\n", status);
    if (status == 0) {
        params.mfiRespAndCertFxn = &MFiAuth_getRespAndCert;
    }

    /* acquire MAC addr (as a globally unique id) */
    slResult = sl_NetCfgGet(SL_NETCFG_MAC_ADDRESS_GET, NULL, &macAddrLen,
            macAddr);
    Assert_isTrue(slResult == 0, NULL);

    System_sprintf(macAddrBuf, "%02x:%02x:%02x:%02x:%02x:%02x", macAddr[0],
            macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);

    /* Create HAP Engine */
    accs[0] = &accessory_services;
    engineHandle = HAPEngine_create(accs, 1, macAddrBuf, HAPEngine_CI_LIGHTBULB,
            &blink_getSetupCodeFxn, &params);
    Assert_isTrue(engineHandle != NULL, NULL);

    /*
     * Run HAP server. This internally loops handling client requests
     * and may never return.
     */
    status = HAPEngine_serve(engineHandle, NULL, 0);
    Assert_isTrue(status == HAPEngine_EOK, NULL);

    /* delete the HAPEngine */
    status = HAPEngine_delete(&engineHandle);
    Assert_isTrue(status == HAPEngine_EOK, NULL);

    HAPEngine_exit();
}

/*
 *  ======== main ========
 */
int main(void)
{
    Memory_Stats stats;
    Task_Params taskParams;

    /* Call board init functions. */
    Board_initGeneral();
    Board_initGPIO();
    Board_initSPI();
    Board_initI2C();

    /* Initialize interrupts for all ports that need them */
    GPIO_setCallback(Board_BUTTON1, gpioButtonFxn1);

    /* Enable interrupts */
    //GPIO_enableInt(Board_BUTTON1);

    Memory_getStats(NULL, &stats);
    System_printf("%d %d %d\n", stats.totalSize, stats.totalFreeSize,
            stats.largestFreeSize);

    /* Initialize the Spawn Task Mailbox */
    VStartSimpleLinkSpawnTask(3);

    /* Create task for HAP server */
    Task_Params_init(&taskParams);
    taskParams.instance->name = "HAP";
    taskParams.stackSize = 5 * 1024;
    taskParams.priority = 1;
    Task_create(serverFxn, &taskParams, NULL);

    /* Start BIOS */
    BIOS_start();

    return (0);
}
