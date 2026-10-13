#pragma once

// ========================================
// 레벨업 시 증가하는 스탯
// ========================================
#define LEVELUP_HP 10
#define LEVELUP_ATTACK 5
#define LEVELUP_DEFENSE 3

// ========================================
// 몬스터 종류
// ========================================
enum class MonsterType
{
	SLIME,
	GOBLIN,
	ORC,
	GIANT,
	DRAGON
};

// ========================================
// 아이템 종류
// ========================================
enum class ItemType
{
	LOW_POTION,					// 하급 포션
	HIGH_POTION,				// 상급 포션
	FULL_POTION,				// 완전 회복 포션

	ATK_UP_POTION,				// 공격력 영구 증가
	DEF_UP_POTION,				// 방어력 영구 증가
	HP_UP_POTION,				// 최대 체력 증가

	LONG_SWORD,					// 롱소드, 높은 공격력 보너스
	SHIELD,						// 방패, 적당한 방어력 보너스
	ARMOR,						// 갑옷, 높은 방어력 보너스

	BOMB						// 강력한 데미지
};

// ========================================
// 맵 종류
// ========================================
enum class MapType
{
	SURFACE,
	DEEP
};

// ========================================
// 몬스터 데이터
// ========================================
struct MonsterData
{
	const char* name;
	int maxHp;
	int attack;
	int defense;

};

// ========================================
// 아이템 데이터
// ========================================
struct ItemData
{
	const char* name;
	ItemType type;
	int value;
};

// ========================================
// 몬스터 기본 데이터
// ========================================

const MonsterData MONSTER_DATA[5] = // 이름, maxHp, Atk, Def
{
	{"슬라임", 30, 15, 5},
	{"고블린", 40, 20, 10},
	{"오크", 50, 30, 15},
	{"거인", 150, 40, 20},
	{"드래곤", 300, 70, 35}
};

// ========================================
// 아이템 기본 데이터
// ========================================
const ItemData ITEM_DATA[10] = // 이름, type, 수치(회복량, 증가량, 공격 횟수, 데미지)
{
	{"하급 포션", ItemType::LOW_POTION, 30},
	{"상급 포션", ItemType::HIGH_POTION, 60},
	{"풀포션", ItemType::FULL_POTION, 999},

	{"공격력 증가 물약", ItemType::ATK_UP_POTION, 5},
	{"방어력 증가 물약", ItemType::DEF_UP_POTION, 5},
	{"최대 체력 증가 물약", ItemType::HP_UP_POTION, 20},

	{"롱소드", ItemType::LONG_SWORD, 30},
	{"강철 방패", ItemType::SHIELD, 10},
	{"강철 갑옷", ItemType::ARMOR, 20},

	{"폭탄", ItemType::BOMB, 70},
};

// ========================================
// 플레이어 기본 스탯
// ========================================
const int PLAYER_START_HP = 100;
const int PLAYER_START_ATTACK = 20;
const int PLAYER_START_DEFENSE = 10;
const int PLAYER_START_LEVEL = 1;

// ========================================
// 전투별 출현 몬스터 설정
// ========================================

const MonsterType BATTLE_1[] =
{
	MonsterType::SLIME,
	MonsterType::SLIME,
	MonsterType::SLIME
};

const MonsterType BATTLE_2[] =
{
	MonsterType::GOBLIN,
	MonsterType::GOBLIN,
	MonsterType::GOBLIN
};

const MonsterType BATTLE_3[] =
{
	MonsterType::SLIME,
	MonsterType::ORC,
	MonsterType::ORC
};

const MonsterType BATTLE_4[] =
{
	MonsterType::ORC,
	MonsterType::ORC,
	MonsterType::GIANT
};

const MonsterType BATTLE_5[] =
{
	MonsterType::GIANT,
	MonsterType::GIANT,
	MonsterType::DRAGON,
};

// 배열 크기
const int BATTLE_1_COUNT = 3;
const int BATTLE_2_COUNT = 3;
const int BATTLE_3_COUNT = 3;
const int BATTLE_4_COUNT = 3;
const int BATTLE_5_COUNT = 3;