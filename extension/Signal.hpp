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

#ifndef SIGNAL_H
#define SIGNAL_H

#include "smsdk_ext.h"

typedef void (*sig_fn)(int);

template <auto n>
class Signal
{
public:
    bool SetTrap();
    bool RemoveTrap();
    void Raise();
private:
    static sig_fn m_fnOldTrap;
};

extern IForward *g_pSignalForward;

#endif // SIGNAL_H