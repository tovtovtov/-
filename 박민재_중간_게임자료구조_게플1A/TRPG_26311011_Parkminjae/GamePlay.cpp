#include "GamePlay.h"
#include <iostream>

using namespace std;

GamePlay::GamePlay()
{
	m_BattleCount = 0;

	random_device rd;
	m_Random.seed(rd());
}

void GamePlay::Start()
{
	ShowStartScreen();

	// 맵 Surface
	StartBattle(BATTLE_1, BATTLE_1_COUNT);

	if (m_Player.IsDead())
	{
		ShowResult(false);
		return;
	}
		
	StartBattle(BATTLE_2, BATTLE_2_COUNT);

	if (m_Player.IsDead())
	{
		ShowResult(false);
		return;
	}

	StartBattle(BATTLE_3, BATTLE_3_COUNT);

	if (m_Player.IsDead())
	{
		ShowResult(false);
		return;
	}

	// 맵 Deep
	StartBattle(BATTLE_4, BATTLE_4_COUNT);

	if (m_Player.IsDead())
	{
		ShowResult(false);
		return;
	}

	StartBattle(BATTLE_5, BATTLE_5_COUNT);

	if (m_Player.IsDead())
	{
		ShowResult(false);
		return;
	}

	ShowResult(true);
}

void GamePlay::StartBattle(const MonsterType battleData[], int monsterCount)
{
	m_BattleCount++;

	system("cls"); // 화면 정리

	m_BattleList.Clear(); // 초기화

	m_BattleList.AddPlayer(&m_Player); // 플레이어 추가


	for (int i = 0; i < monsterCount; i++)
	{
		// 해당 전투에 등장할 몬스터 종류와 수, 각 객체의 데이터 로딩
		Monster* monster = new Monster(battleData[i]);
		m_BattleList.AddMonster(monster);
	}

	while (!m_Player.IsDead() && m_BattleList.HasMonster())
	{
		BattleNode* current = m_BattleList.GetCurrent();

		// 플레이어 턴
		if (current->type == BattleNodeType::PLAYER)
		{
			ShowBattleScreen();
			PlayerTurn();
		}
		else
		{
			MonsterTurn();
		}

		m_BattleList.NextTurn();
	}

	// 플레이어 사망 시
	if (m_Player.IsDead())
	{
		cout << "플레이어 사망" << '\n';
		return;
	}

	// 모든 몬스터 처치 성공 시
	ShowBattleResult();
}

void GamePlay::PlayerTurn()
{
	int choice;

	bool itemUsed = false;

	while (true)
	{
		cout << '\n';
		cout << "1. 공격" << '\n';

		if (!m_BattleList.HasMonster())
		{
			return;
		}

		if (!itemUsed)
		{
			cout << "2. 아이템 사용" << '\n';
		}

		cout << "선택 : ";
		cin >> choice;

		switch (choice)
		{
		case ATTACK:
		{
			BattleNode* current = m_BattleList.GetCurrent();

			current = current->next;

			while (current->type != BattleNodeType::MONSTER)
			{
				current = current->next;
			}

			Monster* monster = current->monster;

			int finalDamage = monster->TakeDamage(m_Player.GetAttack());

			

			cout << '\n';
			cout << "플레이어의 공격!" << '\n';
			cout << monster->GetName()
				<< "에게 "
				<< finalDamage
				<< "의 피해를 입혔습니다." << '\n';

			if (monster->IsDead())
				m_BattleList.RemoveMonster(monster);

			// 공격 시 턴 종료
			return;
		}
		case USE_ITEM:
		{
			if (itemUsed)
			{
				cout << "이번 턴에는 이미 아이템을 사용했습니다." << '\n';
				break;
			}

			if (UseItem())
			{
				itemUsed = true;
			}
			// 턴 당 1회 아이템 사용 가능
			break;
		}
		default:
		{
			cout << "잘못된 선택입니다." << '\n';
			break;
		}
		}
	}
	
}

void GamePlay::MonsterTurn()
{
	BattleNode* current = m_BattleList.GetCurrent();

	if (current->type != BattleNodeType::MONSTER)
		return;

	Monster* monster = current->monster;

	int finalDamage = m_Player.TakeDamage(monster->GetAttack());

	cout << '\n';
	cout << monster->GetName()
		<< "의 공격!" << '\n';

	cout << "플레이어에게 "
		<< finalDamage
		<< "의 피해를 입혔습니다." << '\n';
}

void GamePlay::ShowPlayerStatus()
{
	cout << PLAYER_TITLE << '\n';

	cout << "레벨   : " << m_Player.GetLevel() << '\n';

	cout << "체력   : "
		<< m_Player.GetHp()
		<< " / "
		<< m_Player.GetMaxHp()
		<< '\n';

	cout << "공격력 : "
		<< m_Player.GetAttack()
		<< '\n';

	cout << "방어력 : "
		<< m_Player.GetDefense()
		<< '\n';
}


void GamePlay::LevelUpPlayer()
{
	m_Player.LevelUp();
}

void GamePlay::GetBattleReward()
{
	std::uniform_int_distribution<int> dist(0, 9);

	// 아이템 2개 획득
	for (int i = 0; i < 2; i++)
	{
		int itemIndex = dist(m_Random);

		// 이미 획득한 아이템이면 다시 뽑기
		while (CheckItemList(itemIndex))
		{
			itemIndex = dist(m_Random);
		}

		// 획득한 아이템 기록
		m_ItemList.push_back(itemIndex);

		ItemType itemType =
			static_cast<ItemType>(itemIndex);

		// 플레이어 인벤토리에 추가
		if (m_Player.AddItem(itemType))
		{
			Item* item =
				m_Player.GetInventoryItem(
					m_Player.GetInventoryCount() - 1
				);

			std::cout << "아이템 획득 : "
				<< item->GetName()
				<< '\n';
		}
	}
}

bool GamePlay::UseItem()
{
	ShowInventory();

	int count = m_Player.GetInventoryCount();

	if (count == 0)
		return false;

	int choice;

	cout << "사용할 아이템 : ";
	cin >> choice;

	int index = choice - 1;

	if (index < 0 || index >= count)
	{
		cout << "잘못된 선택입니다." << '\n';
		return false;
	}

	Item* item = m_Player.GetInventoryItem(index);

	ItemType type = item->GetType();
	int value = item->GetValue();

	switch (type)
	{
	case ItemType::LOW_POTION:
		m_Player.Heal(value);

		cout << "하급 포션을 사용했습니다." << '\n';
		break;

	case ItemType::HIGH_POTION:
		m_Player.Heal(value);

		cout << "상급 포션을 사용했습니다." << '\n';
		break;

	case ItemType::FULL_POTION:
		m_Player.Heal(value);

		cout << "풀포션을 사용했습니다." << '\n';
		break;

	case ItemType::ATK_UP_POTION:
		m_Player.IncreaseAttack(value);

		cout << "공격력이 증가했습니다." << '\n';
		break;

	case ItemType::DEF_UP_POTION:
		m_Player.IncreaseDefense(value);

		cout << "방어력이 증가했습니다." << '\n';
		break;

	case ItemType::HP_UP_POTION:
		m_Player.IncreaseMaxHp(value);

		cout << "최대 체력이 증가했습니다." << '\n';
		break;

	case ItemType::LONG_SWORD:
		m_Player.IncreaseAttack(value);

		cout << "공격력이 증가했습니다." << '\n';
		break;

	case ItemType::SHIELD:
		m_Player.IncreaseDefense(value);

		cout << "방어력이 증가했습니다." << '\n';
		break;

	case ItemType::ARMOR:
		m_Player.IncreaseDefense(value);

		cout << "방어력이 증가했습니다." << '\n';
		break;

	case ItemType::BOMB:
	{
		BattleNode* current = m_BattleList.GetCurrent();

		current = current->next;

		while (current->type != BattleNodeType::MONSTER)
		{
			current = current->next;
		}

		Monster* monster = current->monster;

		monster->TakeDamage(value);

		cout << monster->GetName()
			<< "에게 폭탄 데미지 "
			<< value
			<< "을(를) 입혔습니다." << '\n';

		if (monster->IsDead())
		{
			cout << monster->GetName()
				<< "을(를) 처치했습니다." << '\n';

			m_BattleList.RemoveMonster(monster);
		}

		break;
	}
	}

	m_Player.RemoveItem(index);

	return true;
}

void GamePlay::ShowInventory()
{
	cout << '\n';
	cout << "[아이템]" << '\n';

	int count = m_Player.GetInventoryCount();

	if (count == 0)
	{
		cout << "보유한 아이템이 없습니다." << '\n';
		return;
	}

	for (int i = 0; i < count; i++)
	{
		Item* item = m_Player.GetInventoryItem(i);

		cout << i + 1
			<< ". "
			<< item->GetName()
			<< '\n';
	}
}

bool GamePlay::CheckItemList(int itemIndex)
{
	for (int i = 0; i < m_ItemList.size(); i++)
	{
		if (m_ItemList[i] == itemIndex)
			return true;
	}

	return false;
}

void GamePlay::ShowStartScreen()
{
	cout << TITLE << '\n';

	cout << GAME_START << '\n';

	cout << "아무 키나 입력하면 시작합니다." << '\n';

	cin.ignore();
	cin.get();
}

void GamePlay::ShowBattleScreen()
{
	cout << '\n' << BATTLE_TITLE << '\n';

	cout << "                 BATTLE " << m_BattleCount << '\n';

	cout << BATTLE_TITLE << '\n';

	ShowPlayerStatus();

	cout << '\n' << LINE << '\n';

	ShowMonsterList();

	cout << LINE << '\n';
}

void GamePlay::ShowBattleResult()
{
	cout << '\n';
	cout << "========================================" << '\n';
	cout << "              BATTLE CLEAR" << '\n';
	cout << "========================================" << '\n';
	cout << '\n';

	GetBattleReward();
	LevelUpPlayer();

	cout << '\n';
	cout << "다음 전투를 시작하려면 Enter를 누르세요." << '\n';

	cin.ignore();
	cin.get();
}

void GamePlay::ShowMonsterList()
{
	cout << ENEMY_TITLE << '\n';

	BattleNode* current = m_BattleList.GetCurrent();

	if (current == nullptr)
		return;

	current = current->next;

	int monsterNumber = 1;

	while (true)
	{
		if (current->type == BattleNodeType::MONSTER)
		{
			Monster* monster = current->monster;

			cout << '\n';

			cout << monsterNumber
				<< ". "
				<< monster->GetName()
				<< '\n';

			cout << "   체력   : "
				<< monster->GetHp()
				<< " / "
				<< monster->GetMaxHp()
				<< '\n';

			cout << "   공격력 : "
				<< monster->GetAttack()
				<< '\n';

			cout << "   방어력 : "
				<< monster->GetDefense()
				<< '\n';

			monsterNumber++;
		}

		current = current->next;

		if (current == m_BattleList.GetCurrent())
		{
			break;
		}
	}
}

void GamePlay::ShowResult(bool success)
{
	cout << '\n';

	if (success)
	{
		cout << DUNGEON_CLEAR << '\n';
		cout << '\n';

		cout << CLEAR_MESSAGE << '\n';
	}
	else
	{
		cout << DUNGEON_FAILED << '\n';
		cout << '\n';

		cout << FAILED_MESSAGE << '\n';
	}

	cout << '\n';
}
