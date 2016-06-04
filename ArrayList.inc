/*
---------------------------------------

			ArrayList in PAWN	

			@author: Ino
			@version: 1.0.0
			@release: 03/06/2016
			@build: 1	
			@download: github.com/Ino42O/PawnArrayList

---------------------------------------

	Functions list:

		* ArrayList:NewArrayList<TYPE>(capacity)
		* ArrayList::Destroy (ArrayList:ArrayListID);
		* ArrayList::IsValid (ArrayList:ArrayListID);
		* ArrayList::Add (ArrayList:ArrayListID, value);
		* ArrayList::Remove (ArrayList:ArrayListID, index);
		* ArrayList::Size (ArrayList:ArrayListID);
		* ArrayList::Capacity (ArrayList:ArrayListID);
		* ArrayList::Get (ArrayList:ArrayListID, index);
		* ArrayList::EnsureCapacity (ArrayList:ArrayListID, newcapacity);
		* ArrayList::Clear (ArrayList:ArrayListID);
		* ArrayList::IndexOf (ArrayList:ArrayListID, value);

 	

 	Changelog:

 		03-06-2016:
 			* Initial release



 	Available types:

 		* FLOAT
 		* INTEGER

---------------------------------------
*/

#include <a_samp>

// Defines (don't change)
#define MAX_ARRAY_LIST 			(0x1000)
#define MAX_ARRAY_CAPACITY 		(0xFFFF)
#define INTEGER 				(0x1A4)
#define FLOAT 					(0x420)
#define INVALID_ARRAY_LIST		(ArrayList:-1)
#define ArrayList:: 			arraylistFunction

#define _INC_ARRAYLIST // For another includes which want use this one

// Script
#define ARRAYLIST_UPDATE 		("03/06/2016")
#define ARRAYLIST_VERSION 		("1.0.0")
#define ARRAYLIST_BUILD 		(1)
//#define ARRAYLIST_DEBUG 		// unavailable right now


// Macros
#define NewArrayList<%0>(%1) \
	ArrayList:ArrayList::Create(%0, %1)

// Declarations
enum E_ARRAY_LIST
{
	bool:al_used,
		 al_capacity,
		 al_type,
		 al_size
}
static eArrayList[MAX_ARRAY_LIST][E_ARRAY_LIST];



// Forward
forward ArrayList:ArrayList::Create(type, capacity);


// Function for include
static stock findArrayListID()
{
	new id = -1;

	for (new i = 0; i < MAX_ARRAY_LIST; i++)
	{
		if (!eArrayList[i][al_used])
		{
			id = i;
			break;
		}
	}

	return (id != -1) ? id : -1;
}


// Available functions
/*----------------------------------------------------------------------------

	Function:
		ArrayList::IsValid

	Params:
		@ArrayList:ArrayListID

	Notes:
		Check if list exist	

----------------------------------------------------------------------------*/
stock ArrayList::IsValid(ArrayList:ArrayListID)
{
	return (eArrayList[_:ArrayListID][al_used]);
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::Create - NewArrayList<>()

	Params:
		@type (FLOAT / INTEGER)
		@capacity

	Notes:
		New list in heap

----------------------------------------------------------------------------*/
stock ArrayList:ArrayList::Create(type, capacity)
{
	if (capacity < 1 || capacity > MAX_ARRAY_CAPACITY)
		return INVALID_ARRAY_LIST;

	new ArrayListID = findArrayListID();

	if (ArrayListID == -1)
		return INVALID_ARRAY_LIST;

	eArrayList[_:ArrayListID][al_used] = true;
	eArrayList[_:ArrayListID][al_capacity] = capacity;
	eArrayList[_:ArrayListID][al_size] = 0;

	switch (type)
	{
		case INTEGER:
		{
			eArrayList[_:ArrayListID][al_type] = INTEGER;
		}
		case FLOAT:
		{
			eArrayList[_:ArrayListID][al_type] = FLOAT;
		}
		default:
		{
			return INVALID_ARRAY_LIST;
		}
	}

	return ArrayList:ArrayListID;
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::Destroy

	Params:
		@ArrayList:ArrayListID

	Notes:
		Destroy list if exist

----------------------------------------------------------------------------*/
stock ArrayList::Destroy(ArrayList:ArrayListID)
{
	if (!ArrayList::IsValid(ArrayListID))
		return (false);

	eArrayList[_:ArrayListID][al_used] = false;

	return (true);
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::Add

	Params:
		@ArrayList:ArrayListID
		@value

	Notes:
		Add item on first empty slot

----------------------------------------------------------------------------*/
stock ArrayList::Add(ArrayList:ArrayListID, { _, Float}:var, tag = tagof(var))
{
	if (eArrayList[_:ArrayListID][al_size] >= eArrayList[_:ArrayListID][al_capacity])
		return (false);
	
	eArrayList[_:ArrayListID][al_used] = true;

	new 
		id = _:ArrayListID,
		size = eArrayList[_:ArrayListID][al_size],
		value[0x40];

	if (tag == tagof(Float:)) // Float
	{
		if (eArrayList[_:ArrayListID][al_type] != FLOAT)
			return (false);

		format (value, 0x40, "%f", var);
		setproperty(0, "", (id + size), value);
	}
	else // Integer
	{
		if (eArrayList[_:ArrayListID][al_type] != INTEGER)
			return (false);

		format (value, 0x40, "%i", var);
		setproperty(0, "", (id + size), value);
	}

	eArrayList[_:ArrayListID][al_size] ++;
	return (true);
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::Size

	Params:
		@ArrayList:ArrayListID

	Notes:
		Return size of array list

----------------------------------------------------------------------------*/
stock ArrayList::Size(ArrayList:ArrayListID)
{
	if (!ArrayList::IsValid(ArrayListID))
		return (false);

	return eArrayList[_:ArrayListID][al_size];
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::Capacity

	Params:
		@ArrayList:ArrayListID

	Notes:
		Return the capacity of list

----------------------------------------------------------------------------*/
stock ArrayList::Capacity(ArrayList:ArrayListID)
{
	if (!ArrayList::IsValid(ArrayListID))
		return (false);

	return eArrayList[_:ArrayListID][al_capacity];
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::Get

	Params:
		@ArrayList:ArrayListID
		@index

	Notes:
		Return value from choosen index

----------------------------------------------------------------------------*/
stock ArrayList::Get(ArrayList:ArrayListID, index)
{
	if (!ArrayList::IsValid(ArrayListID))
		return (false);

	if (index > ArrayList::Size(ArrayListID))
		return (false);

	new 
		value[0x40],
		address = (_:ArrayListID + index);

	getproperty(0, "", address, value);
	strunpack(value, value, 0x40);
	
	switch (eArrayList[_:ArrayListID][al_type])
	{
		case INTEGER:
		{
			return strval(value);
		}
		case FLOAT:
		{
			return _:(floatstr(value));
		}
		default:
		{
			return -1;
		}
	}

	return -1;
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::EnsureCapacity

	Params:
		@ArrayList:ArrayListID
		@newcapacity

	Notes:
		This will change capacity of list

----------------------------------------------------------------------------*/
stock ArrayList::EnsureCapacity(ArrayList:ArrayListID, newcapacity)
{
	if (!ArrayList::IsValid(ArrayListID))
		return (false);

	if (newcapacity < 1 || newcapacity > MAX_ARRAY_CAPACITY)
		return (false);

	eArrayList[_:ArrayListID][al_capacity] = newcapacity;

	return (true);
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::Remove

	Params:
		@ArrayList:ArrayListID
		@position

	Notes:
		Remove value from choosen position and auto-fill that slot

----------------------------------------------------------------------------*/
stock ArrayList::Remove(ArrayList:ArrayListID, position)
{
	if (!ArrayList::IsValid(ArrayListID))
		return (false);

	if (eArrayList[_:ArrayListID][al_size] < position)
		return (false);

	for (new i = position, size = eArrayList[_:ArrayListID][al_size]; i < size;
		i++)
	{
		new 
			value[0x40];

		getproperty(0, "", ((_:ArrayListID + i) + 1), value);
		strunpack(value, value, 0x40);
		setproperty(0, "", (_:ArrayListID + i), value);
	}

	eArrayList[_:ArrayListID][al_size] --;
	return (true);
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::Clear

	Params:
		@ArrayList:ArrayListID

	Notes:
		Clear all slots

----------------------------------------------------------------------------*/
stock ArrayList::Clear(ArrayList:ArrayListID)
{
	if (!ArrayList::IsValid(ArrayListID))
		return (false);

	for (new i = 0, size = eArrayList[_:ArrayListID][al_size]; i < size; i++)
	{
		deleteproperty(0, "", (i + _:ArrayListID));
	}
	eArrayList[_:ArrayListID][al_size] = 0;
	return (true);
}


/*----------------------------------------------------------------------------

	Function:
		ArrayList::IndexOf

	Params:
		@ArrayList:ArrayListID
		@value

	Notes:
		Return index of value

----------------------------------------------------------------------------*/
stock ArrayList::IndexOf(ArrayList:ArrayListID, { _, Float}:value, tag = tagof(value))
{
	if (!ArrayList::IsValid(ArrayListID))
		return (false);

	new 
		index = -1,
		found,
		vc[0x40];


	if (tag == tagof(Float:)) // Float
	{
		if (eArrayList[_:ArrayListID][al_type] != FLOAT)
			return -1;

		format (vc, 0x40, "%f", value);
	}
	else // Integer
	{
		if (eArrayList[_:ArrayListID][al_type] != INTEGER)
			return -1;

		format (vc, 0x40, "%i", value);
	}
	

	for (new i = 0; i < eArrayList[_:ArrayListID][al_size]; i++)
	{
		new 
			v[0x40];

		getproperty(0, "", (_:ArrayListID + i), v);
		strunpack(v, v, sizeof(v));

		if(!strcmp(vc, v))
		{
			found = true;
			index = (_:ArrayListID + i);
			break;
		}
	}

	if (found)
		return index;

	return -1;
}