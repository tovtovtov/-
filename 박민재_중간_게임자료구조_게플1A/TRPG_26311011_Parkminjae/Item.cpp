#include "Item.h"

Item::Item()
{
	m_Type = ItemType::LOW_POTION;
	m_Name = ITEM_DATA[0].name;
	m_Value = ITEM_DATA[0].value;
}

Item::Item(ItemType type)
{
	m_Type = type;

	const ItemData& data = ITEM_DATA[static_cast<int>(type)];

	m_Name = data.name;
	m_Value = data.value;
}

ItemType Item::GetType() const
{
	return m_Type;
}

const char* Item::GetName() const
{
	return m_Name;
}

int Item::GetValue() const
{
	return m_Value;
}