#include "Monster.h"
#include "Item.h"

Monster::Monster(MonsterType type)
{
	m_Type = type;

	// MonsterType에 따라 기본 데이터 세팅
	const MonsterData& data = MONSTER_DATA[static_cast<int>(type)];

	m_Name = data.name;
	m_MaxHp = data.maxHp;
	m_CurHp = data.maxHp;
	m_Attack = data.attack;
	m_Defense = data.defense;
}

int Monster::TakeDamage(int damage)
{
	int finalDamage = damage - m_Defense;

	if (finalDamage < 1)
		finalDamage = 1;

	m_CurHp -= finalDamage;

	if (m_CurHp < 0)
		m_CurHp = 0;

	return finalDamage;
}

bool Monster::IsDead() const
{
	return m_CurHp <= 0;
}

const char* Monster::GetName() const
{
	return m_Name;
}

int Monster::GetHp() const
{
	return m_CurHp;
}

int Monster::GetMaxHp() const
{
	return m_MaxHp;
}

int Monster::GetAttack() const
{
	return m_Attack;
}

int Monster::GetDefense() const
{
	return m_Defense;
}

MonsterType Monster::GetType() const
{
	return m_Type;
}