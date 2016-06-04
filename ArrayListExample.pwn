// Example script for use ArrayList in PAWN

#include <a_samp>
#include <ArrayList> // Include ArrayList for PAWN

// Declare new list - 'playersList'
new ArrayList:playersList;

public OnFilterScriptInit()
{
	// Create new ArrayList

	// @playersList - Address
	// @ <INTEGER> - Creating list which accepting just integer values, it can be <FLOAT> too
	// @ (MAX_PLAYERS) - Creating capacity of list, that is of cource changeable
	//
	// Capacity is possible to change by following function - ArrayList::EnsureCapacity (ArrayList:ArrayListID, newcapacity);
	playersList = NewArrayList<INTEGER>(MAX_PLAYERS); 

	// An example ArrayList::EnsureCapacity

	// @playersList - Address
	// @420 - New capacity value of this list

	//		ArrayList::EnsureCapacity(playersList, 420);


	// Loop timer
	SetTimer("updateplayers", 1000, true);
	return (true);
}

public OnFilterScriptExit()
{
	// Destroy created list
	ArrayList::Destroy(playersList);
	return (true);
}

public OnPlayerConnect(playerid)
{
	// Add player's id on the list
	// This will add my id into list (playersList) on first empty slot
	ArrayList::Add(playersList, playerid);
	return (true);
}

public OnPlayerDisconnect(playerid, reason)
{
	// Remove player's id from the list
	// IndexOf will find index in array by player's id
	ArrayList::Remove(playersList, ArrayList::IndexOf(playersList, playerid));
	return (true);
}

// Simple timer
forward updateplayers();
public updateplayers()
{
	// Check if is list size > 0
	// If yes, loop all online players
	if (ArrayList::Size(playersList) > 0)
	{
		// Just a tick
		new timer = GetTickCount();

		// Loop which will go trough all online players, just online players!
		for (new i = 0; i < ArrayList::Size(playersList); i++) // Loop just online players
		{
			// Message...
			printf ("Looped player ID - %i", ArrayList::Get (playersList, i);
		}

		// And info at end
		printf ("Loop is completed in %dms with %d players", (GetTickCount() - timer), ArrayList::Size(playersList));

	}
	else print ("Nobody is online, don't need loop"); // Jump here if is server empty, no need empty loop lol
	return (true);
}

