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

#include "ClientListener.h"

#include "SignalHandler.h"

ClientListener g_clientListener;

bool hasPlayersConnected()
{
    int count = playerhelpers->GetNumPlayers();
    if (count == 0)
    {
        int maxplayers = playerhelpers->GetMaxClients();
        for (int i = 1; i <= maxplayers; ++i)
        {
            IGamePlayer *pPlayer = playerhelpers->GetGamePlayer(i);
            if ((pPlayer->IsConnected()) && !(pPlayer->IsInGame()))
                return true;
        }
        return false;
    }
    else
        return true;
}

void ClientListener::OnClientDisconnected(int client)
{
    if (playerhelpers->GetGamePlayer(client)->IsFakeClient())
        return;

    switch (g_signalStatus)
    {
    case SIGTERM:
        if (!hasPlayersConnected())
        {
            untrapTERM();
            raiseTERM();
        }
        break;
    default:
        break;
    }
}