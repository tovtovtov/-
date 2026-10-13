#pragma once
#include "GameData.h"

class Monster
{
private:
	MonsterType m_Type;

	const char* m_Name;

	int m_CurHp;
	int m_MaxHp;
	int m_Attack;
	int m_Defense;

public:
	Monster(MonsterType type);

	int TakeDamage(int damage);

	bool IsDead() const;

	const char* GetName() const;
	int GetHp() const;
	int GetMaxHp() const;
	int GetAttack() const;
	int GetDefense() const;
	MonsterType GetType() const;
};

