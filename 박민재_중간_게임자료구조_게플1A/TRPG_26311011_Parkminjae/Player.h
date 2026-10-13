#pragma once
#include "GameData.h"
#include "Item.h"

class Player
{
private:
	int m_CurHp;
	int m_MaxHp;
	int m_Attack;
	int m_Defense;
	int m_Level;

	Item m_Inventory[10];
	int m_InventoryCount;

public:
	Player();

	int TakeDamage(int damage);
	void LevelUp();

	bool IsDead() const;

	int GetHp() const;
	int GetMaxHp() const;
	int GetAttack() const;
	int GetDefense() const;
	int GetLevel() const;

	bool AddItem(ItemType type);
	bool RemoveItem(int index);

	int GetInventoryCount() const;
	Item* GetInventoryItem(int index);

	void Heal(int value);
	void IncreaseAttack(int value);
	void IncreaseDefense(int value);
	void IncreaseMaxHp(int value);
};

