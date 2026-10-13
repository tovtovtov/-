#pragma once
#include "Player.h"
#include "Monster.h"

enum class BattleNodeType
{
	PLAYER,
	MONSTER
};

// 타입에 따른 객체 노드
struct BattleNode
{
	BattleNodeType type;

	Player* player;
	Monster* monster;

	BattleNode* next;
};

class BattleList
{
private:
	BattleNode* m_Head;
	BattleNode* m_Current;

public:
	BattleList();
	~BattleList();

	void AddPlayer(Player* player);				// 플레이어 노드 연결
	void AddMonster(Monster* monster);			// 몬스터 노드 연결

	void NextTurn();

	BattleNode* GetCurrent() const;

	void RemoveMonster(Monster* monster);		// 사망한 몬스터 노드 제거

	bool HasMonster() const;					// 리스트 내 몬스터 노드 존재 확인

	void Clear();
};

