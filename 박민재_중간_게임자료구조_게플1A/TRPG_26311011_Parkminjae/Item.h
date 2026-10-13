#pragma once

#include "GameData.h"

class Item
{
private:
	ItemType m_Type;
	const char* m_Name;
	int m_Value;

public:
	Item();
	Item(ItemType type);

	ItemType GetType() const;
	const char* GetName() const;
	int GetValue() const;
};

