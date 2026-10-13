#pragma once
#include "Player.h"
#include "Monster.h"
#include "BattleList.h"
#include "PrintMacro.h"
#include <random>
#include <vector>

using namespace std;

enum {
	ATTACK = 1,
	USE_ITEM = 2
};

class GamePlay
{
private:
	Player m_Player;

	int m_BattleCount;

	BattleList m_BattleList;

	vector<int> m_ItemList;

	mt19937 m_Random;

	void StartBattle(const MonsterType battleData[], int monsterCount);

	void PlayerTurn();
	void MonsterTurn();

	void ShowPlayerStatus();

	void LevelUpPlayer();

	void GetBattleReward();
	bool UseItem();
	void ShowInventory();

	bool CheckItemList(int itemIndex);

	void ShowStartScreen();
	void ShowBattleScreen();
	void ShowBattleResult();
	void ShowMonsterList();
	void ShowResult(bool success);

public:
	GamePlay();

	void Start();
};

