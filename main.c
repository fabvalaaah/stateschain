/*
 * MIT License
 * 
 * Copyright (c) 2018 Fabvalaaah - fabvalaaah@laposte.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * DONATION:
 * As I share these sources for commercial use too, maybe you could consider
 * sending me a reward (even a tiny one) to my Ethereum wallet at the address
 * 0x1fEaa1E88203cc13ffE9BAe434385350bBf10868
 * If so, I would be forever grateful to you and motivated to keep up the good
 * work for sure :oD Thanks in advance !
 * 
 * FEEDBACK:
 * You like my work? It helps you? You plan to use/reuse/transform it? You have
 * suggestions or questions about it? Just want to say "hi"? Let me know your
 * feedbacks by mail to the address fabvalaaah@laposte.net
 * 
 * DISCLAIMER:
 * I am not responsible in any way of any consequence of the usage
 * of this piece of software. You are warned, use it at your own risks.
 */

/* 
 * File:   main.c
 * Author: Fabvalaaah
 *
 * 01/14/2018
 */

#include <stdlib.h>

#include "StateJobs.h"
#include "StatesChain.h"

int main() {
    int exitValue = EXIT_SUCCESS;
    _State* curState;
    _StatesChain* statesChain = createStatesChain();
    int job1Param = 42;

    if (!statesChain) {
        exitValue = EXIT_FAILURE;
        goto CLEAN;
    }

    /* Preparing the STATELIST */
    curState = createState(job1, &job1Param, 0);
    if (!curState) {
        exitValue = EXIT_FAILURE;
        goto CLEAN;
    }
    addStateToStatesChain(statesChain, curState);

    curState = createState(job2, NULL, 2000);
    if (!curState) {
        exitValue = EXIT_FAILURE;
        goto CLEAN;
    }
    addStateToStatesChain(statesChain, curState);

    curState = createState(job3, NULL, 0);
    if (!curState) {
        exitValue = EXIT_FAILURE;
        goto CLEAN;
    }
    addStateToStatesChain(statesChain, curState);

    curState = createState(job4, NULL, 0);
    if (!curState) {
        exitValue = EXIT_FAILURE;
        goto CLEAN;
    }
    addStateToStatesChain(statesChain, curState);

    curState = createState(job5, NULL, 4000);
    if (!curState) {
        exitValue = EXIT_FAILURE;
        goto CLEAN;
    }
    addStateToStatesChain(statesChain, curState);

    curState = createState(job6, NULL, 3000);
    if (!curState) {
        exitValue = EXIT_FAILURE;
        goto CLEAN;
    }
    addStateToStatesChain(statesChain, curState);

    /* Simulate the infinite loop */
    while (1) {
        if (!executeStatesChain(statesChain)) { /* NULL if init is over */
            destroyStatesChain(&statesChain); /* Free the states chain */
            printf("MAIN WORK !\n");
        } else {
            /* 
             * The code that has to be fired in the current loop while the delta
             * time between the current job and the next one is not satisfied.
             */
        }
    }
    /* ------- */

CLEAN:
    destroyStatesChain(&statesChain); /* Free the states chain */
    return (exitValue);
}