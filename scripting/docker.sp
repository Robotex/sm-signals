#include <sourcemod>
#include <signals>

#pragma semicolon 1
#pragma newdecls required

public Plugin myinfo =
{
	name = "Docker",
	author = "Robotex",
	description = "Handle Docker stop and kill commands",
	version = "0.1",
	url = "http://github.com/Robotex"
};

bool g_isSignaled = false;
bool g_isMapTransitioning = false;
 
public void OnSignal(int signal)
{
	if (signal == 15)
	{
		g_isSignaled = true;
		if (!IsServerProcessing())
			ServerCommand("quit");
	}    
}

public void OnClientDisconnect_Post(int client)
{
	if (g_isSignaled && !HasPlayersConnected() && !g_isMapTransitioning)
		ServerCommand("quit");
}

public void OnMapStart()
{
	g_isMapTransitioning = false;
}

public void OnMapEnd()
{
	g_isMapTransitioning = true;
}

public bool HasPlayersConnected()
{
    int count = GetClientCount(true);
    if (count == 0)
    {
        int maxplayers = GetMaxClients();
        for (int i = 1; i <= maxplayers; ++i)
        {
            if (IsClientConnected(i) && !IsClientInGame(i))
                return true;
        }
        return false;
    }
    else
        return true;
}
