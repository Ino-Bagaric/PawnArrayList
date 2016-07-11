//
//		SA:MP Simple Inventory System with ArrayList
//		
//		Writed by Ino
//
// 		11/07/2016
//

#include <a_samp>
#include <ArrayList> // Include ArrayList for PAWN
#include <sscanf2> // Sscanf for cmd
#include <zcmd> // ZCMD commands


// Defines
#undef MAX_PLAYERS
#define MAX_PLAYERS 			(50)
#define MAX_ITEMS 				(10) // Max items per player in inventory
#define INVENTORY_DIALOG		(8080)


// Enumerator
enum E_INVENTORY
{
	bool:	i_used,
			i_item_type,
			i_item_amount
}
new 
	PlayerInventory[MAX_PLAYERS][E_INVENTORY][MAX_ITEMS];


// Items
new ItemArray [] [] =
{
	{1, "Desert Eagle"},
	{2, "Medkit"},
	{3, "Burger"}
};


// Declare lists
new 
	ArrayList:InventoryList[MAX_PLAYERS];


// Callbacks
public OnPlayerConnect(playerid)
{
	// Create list
	InventoryList[playerid] = NewArrayList<INTEGER>(MAX_ITEMS); 
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	// Clear array
	ClearInventory(playerid);

	// Destroy list
	ArrayList::Destroy(InventoryList[playerid]);
	return 1;
}


// Functions
stock ClearInventory(playerid)
{
	for (new i = 0; i < MAX_ITEMS; i++)
	{
		PlayerInventory[playerid][i_used][i] = false;
	}
	ArrayList::Clear(InventoryList[playerid]);
	return 1;
}

stock AddItemInInventory(playerid, item_type, item_amount)
{
	if (ArrayList::Size(InventoryList[playerid]) < MAX_ITEMS)
	{
		new 
			empty_id = ArrayList::Size(InventoryList[playerid]);

		ArrayList::Add(InventoryList[playerid], empty_id);

		PlayerInventory[playerid][i_used][empty_id] = true;
		PlayerInventory[playerid][i_item_type][empty_id] = item_type;
		PlayerInventory[playerid][i_item_amount][empty_id] = item_amount;

		SendClientMessage(playerid, -1, "Item added");
	}
	else SendClientMessage(playerid, -1, "Error: Your inventory is full!");
	return 1;
}

stock RemoveItemFromInventory(playerid, slot)
{
	slot = slot - 1;

	if (slot < ArrayList::Size(InventoryList[playerid]))
	{
		new 
			s = ArrayList::Get(InventoryList[playerid], slot);

		PlayerInventory[playerid][i_used][s] = false;
		PlayerInventory[playerid][i_item_type][s] = -1;
		PlayerInventory[playerid][i_item_amount][s] = -1;

		ArrayList::Remove(InventoryList[playerid], s);

		SendClientMessage(playerid, -1, "Item removed");
	}
	else SendClientMessage(playerid, -1, "Error: Choosen slot is empty.");
	return 1;
}

stock ShowInventory(playerid)
{
	new 
		buffer[1024],
		item_name[24],
		amount,
		get_id = -1;

	if (ArrayList::Size(InventoryList[playerid]) > 0)
	{
		for (new i = 0; i < ArrayList::Size(InventoryList[playerid]); i++)
		{
			get_id = ArrayList::Get(InventoryList[playerid], i);

			format (item_name, sizeof(item_name), "%s", ItemArray[ PlayerInventory[playerid][i_item_type][get_id] - 1 ][1]);
			amount = PlayerInventory[playerid][i_item_amount][get_id];
			format (buffer, sizeof(buffer), "%s{90C3D4}%d {FFFFFF}%s (%d)\n", buffer, (i + 1), item_name, amount);

			get_id = -1;
		}
		for (new j = ArrayList::Size(InventoryList[playerid]); j < MAX_ITEMS; j++)
		{		
			format (buffer, sizeof(buffer), "%s{90C3D4}%d {FFFFFF}empty slot (0)\n", buffer, (j + 1));
		}
	}
	else format (buffer, sizeof(buffer), "Your inventory is empty");

	ShowPlayerDialog(playerid, INVENTORY_DIALOG, DIALOG_STYLE_LIST, "Inventory", buffer, "Close", "");
	return 1;
}


// Commands
CMD:inventory(playerid, params[])
{
	ShowInventory(playerid);
	return 1;
}

CMD:add(playerid, params[])
{
	new 
		item,
		amount;

	if (!sscanf(params, "ii", item, amount))
	{	
		AddItemInInventory(playerid, item, amount);
	}
	else SendClientMessage(playerid, -1, "Usage: /add [ITEM TYPE] [AMOUNT]");
	return 1;
}

CMD:remove(playerid, params[])
{
	new 
		slot;

	if (!sscanf(params, "i", slot))
	{	
		RemoveItemFromInventory(playerid, slot);
	}
	else SendClientMessage(playerid, -1, "Usage: /remove [SLOT ID]");
	return 1;
}