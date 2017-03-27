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

#include "Signal.hpp"

#include <csignal>
#include <cstddef>

volatile std::sig_atomic_t g_signalStatus;
IForward *g_pSignalForward = nullptr;

void signal_handler (int sig)
{
    g_pSignalForward->PushCell(sig);
    g_pSignalForward->Execute(nullptr);
}

template <int n>
sig_fn Signal<n>::m_fnOldTrap = nullptr;

template <int n>
bool Signal<n>::SetTrap()
{
    sig_fn oldTrap = signal(n, signal_handler);
    if (oldTrap == SIG_ERR)
        return false;
    else if (oldTrap != signal_handler)
        m_fnOldTrap = oldTrap;
    return true;
}

template <int n>
bool Signal<n>::RemoveTrap()
{
    if (!m_fnOldTrap)
        return false;
    return (signal(n, m_fnOldTrap) != SIG_ERR);
}

template <int n>
void Signal<n>::Raise()
{
    raise(n);
}