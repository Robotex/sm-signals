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

public void OnPluginStart()
{

}

bool g_isSignaled = false;
 
public void OnSignal(int signal)
{
	if (signal == 15)
	{
		g_isSignaled = true;
		if (!IsServerProcessing())
			ServerCommand("quit");
	}    
}

public void OnMapEnd()
{

}

