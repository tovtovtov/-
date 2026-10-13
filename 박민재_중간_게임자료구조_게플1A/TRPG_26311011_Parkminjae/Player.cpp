#include "Player.h"

// 플레이어 객체 기본 데이터 세팅
Player::Player()
{
	m_CurHp = PLAYER_START_HP;
	m_MaxHp = PLAYER_START_HP;
	m_Attack = PLAYER_START_ATTACK;
	m_Defense = PLAYER_START_DEFENSE;
	m_Level = PLAYER_START_LEVEL;

	m_InventoryCount = 0;
}

int Player::TakeDamage(int damage)
{
	int finalDamage = damage - m_Defense;

	if (finalDamage < 1)
		finalDamage = 1;

	m_CurHp -= finalDamage;

	if (m_CurHp < 0)
		m_CurHp = 0;

	return finalDamage;
}

void Player::LevelUp()
{
	m_Level++;
	// 최대 체력 증가 및 체력 회복
	m_MaxHp += LEVELUP_HP;
	m_CurHp = m_MaxHp;

	// 공격력, 방어력 증가
	m_Attack += LEVELUP_ATTACK;
	m_Defense += LEVELUP_DEFENSE;
}

bool Player::IsDead() const
{
	return m_CurHp <= 0;
}

int Player::GetHp() const
{
	return m_CurHp;
}

int Player::GetMaxHp() const
{
	return m_MaxHp;
}

int Player::GetAttack() const
{
	return m_Attack;
}

int Player::GetDefense() const
{
	return m_Defense;
}

int Player::GetLevel() const
{
	return m_Level;
}

bool Player::AddItem(ItemType type)
{
	// 인벤토리가 가득 찬 경우
	if (m_InventoryCount >= 10)
		return false;

	// 아이템 객체 생성 및 저장
	m_Inventory[m_InventoryCount] = Item(type);

	m_InventoryCount++;

	return true;
}

bool Player::RemoveItem(int index)
{
	if (index < 0 || index >= m_InventoryCount)
		return false;

	for (int i = index; i < m_InventoryCount - 1; i++)
	{
		m_Inventory[i] = m_Inventory[i + 1];
	}

	m_InventoryCount--;

	return true;
}

int Player::GetInventoryCount() const
{
	return m_InventoryCount;
}

Item* Player::GetInventoryItem(int index)
{
	if (index < 0 || index >= m_InventoryCount)
		return nullptr;

	return &m_Inventory[index];
}

void Player::Heal(int value)
{
	m_CurHp += value;

	if (m_CurHp > m_MaxHp)
		m_CurHp = m_MaxHp;
}

void Player::IncreaseAttack(int value)
{
	m_Attack += value;
}

void Player::IncreaseDefense(int value)
{
	m_Defense += value;
}

void Player::IncreaseMaxHp(int value)
{
	m_MaxHp += value;

	m_CurHp = m_MaxHp;
}

