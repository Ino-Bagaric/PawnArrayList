# PawnArrayList
ArrayList in PAWN



- **How to use**
	```pawn
	#include <ArrayList>
	```


- **Functions List**

	- ArrayList:NewArrayList<TYPE>(capacity);
	- ArrayList::Destroy (ArrayList:ArrayListID);
	- ArrayList::IsValid (ArrayList:ArrayListID);
	- ArrayList::Add (ArrayList:ArrayListID, value);
	- ArrayList::Remove (ArrayList:ArrayListID, index);
	- ArrayList::Size (ArrayList:ArrayListID);
	- ArrayList::Capacity (ArrayList:ArrayListID);
	- ArrayList::Get (ArrayList:ArrayListID, index);
	- ArrayList::EnsureCapacity (ArrayList:ArrayListID, newcapacity);
	- ArrayList::Clear (ArrayList:ArrayListID);
	- ArrayList::IndexOf (ArrayList:ArrayListID, value);



- **Available Types**
	- FLOAT
	- INTEGER


- **Example instance**
```pawn
  new ArrayList:myList;
  
  myList = NewArrayList<INTEGER>(5);
  
  ArrayList::Add (myList, 420);
  ArrayList::Add (myList, 41564);
  ArrayList::Add (myList, 123456);
  
  for (new i = 0, size = ArrayList::Size(myList); i < size; i++)
  {
      printf ("Value - %d | Index - %d", ArrayList::Get (myList, i), i);
  }
```
