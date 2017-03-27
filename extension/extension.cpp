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

#include "extension.h"

#include "Signal.hpp"

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */

SignalExtension g_Signal;		/**< Global singleton for extension's main interface */

SMEXT_LINK(&g_Signal);

bool Signal::SDK_OnLoad(char *error, size_t maxlength, bool late)
{ 
    if (!Signal::SetTrap())
    {
        snprintf(error, maxlength, "Error setting signal handler!");
        return false;
    }

    g_pSignalForward = forwards->CreateForward("OnSignal", ET_Event, 1, NULL, Param_Cell);
    
    return true;
}

void Signal::SDK_OnUnload()
{
    forwards->ReleaseForward(g_pSignalForward);
    Signal::RemoveTrap();
}
