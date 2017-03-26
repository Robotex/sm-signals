/**
 * vim: set ts=4 :
 * =============================================================================
 * Signal Extension for SourceMod
 * Copyright (C) 2017 Robotex.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Version: $Id$
 */

#include "SignalHandler.h"

#include <cstdlib>
#include "ClientListener.h"

volatile std::sig_atomic_t g_signalStatus = 0;
typedef void (*sig_fn)(int);
sig_fn sigfn;

void signal_handler (int sig)
{
    g_signalStatus = sig;

    if (!hasPlayersConnected())
    {
        untrapTERM();
        raiseTERM();
    }
}

bool trapTERM()
{
    sigfn = signal(SIGTERM, signal_handler);
    return sigfn != SIG_ERR;
}

bool untrapTERM()
{
    return signal(SIGTERM, sigfn) == signal_handler;
}

void raiseTERM()
{
    if (raise(SIGTERM) != 0)
        exit(0);
}