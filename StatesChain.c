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
 * File:   StatesChain.c
 * Author: Fabvalaaah
 *
 * 01/14/2018
 */

#include <stdlib.h>
#include <sys/time.h>

#include "StatesChain.h"

_StatesChain* createStatesChain() {
    _StatesChain* statesChain;

    if (!(statesChain = malloc(sizeof (_StatesChain)))) {
        return NULL;
    }

    statesChain->head = NULL;
    statesChain->tail = NULL;
    statesChain->iterator = NULL;

    return statesChain;
}

void deleteStateChain(_StatesChain** statesChain) {
    if (*statesChain) {
        free(*statesChain);
        *statesChain = NULL;
    }
}

void subDestroyStateChain(_State* state) {
    if (state) {
        subDestroyStateChain(state->next);
        destroyState(&state);
    }
}

void destroyStatesChain(_StatesChain** statesChain) {
    if (*statesChain) {
        subDestroyStateChain((*statesChain)->head);
        deleteStateChain(statesChain);
    }
}

void addStateToStatesChain(_StatesChain* statesChain, _State* state) {
    if (!statesChain || !state) {
        return;
    }

    if (!statesChain->head) { /* When the chain is empty */
        statesChain->head = state;
        statesChain->tail = state;
        statesChain->iterator = state;
    } else {
        statesChain->tail->next = state;
        statesChain->tail = state;
    }

    /* state->next = stateChain->head; */ /* Needed for a circular chain */
}

_State* executeStatesChain(_StatesChain* statesChain) {
    struct timeval tv;
    unsigned long now;
    _State* it;

    if (!statesChain || !(it = statesChain->iterator)) {
        return NULL;
    }

    switch (it->status) {
        case WAITING:
        {
            executeStateJob(it);
            break;
        }
        case PENDING:
        {
            gettimeofday(&tv, NULL);
            now =
                    (unsigned long) (tv.tv_sec) * 1000 +
                    (unsigned long) (tv.tv_usec) / 1000;
            if (now - it->timestamp >= it->delta) {
                it->status = ENDED;
                statesChain->iterator = it->next;
            }
            break;
        }
        case ENDED:
        {
            it->status = WAITING; /* Needed for a circular chain */
            statesChain->iterator = it->next;
        }
    }

    return it;
}