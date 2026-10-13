#include "BattleList.h"

BattleList::BattleList()
{
	m_Head = nullptr;
	m_Current = nullptr;
}

BattleList::~BattleList()
{
	Clear();
}

// 리스트에 플레이어 노드 추가
void BattleList::AddPlayer(Player* player)
{
	BattleNode* newNode = new BattleNode;

	// 플레이어 객체가 담긴 노드 생성
	newNode->type = BattleNodeType::PLAYER;
	newNode->player = player;
	newNode->monster = nullptr;

	// 리스트에 플레이어 노드만 추가될 경우
	if (m_Head == nullptr)
	{
		m_Head = newNode;
		newNode->next = newNode;

		m_Current = newNode;

		return;
	}

	BattleNode* current = m_Head;

	// 마지막 노드의 헤드 연결 확인
	while (current->next != m_Head)
	{
		current = current->next;
	}

	current->next = newNode;
	newNode->next = m_Head;
}


// AddPlayer와 같은 구조
void BattleList::AddMonster(Monster* monster)
{
	BattleNode* newNode = new BattleNode;

	newNode->type = BattleNodeType::MONSTER;
	newNode->player = nullptr;
	newNode->monster = monster;

	if (m_Head == nullptr)
	{
		m_Head = newNode;
		newNode->next = newNode;

		m_Current = newNode;

		return;
	}

	BattleNode* current = m_Head;

	while (current->next != m_Head)
	{
		current = current->next;
	}

	current->next = newNode;
	newNode->next = m_Head;
}

void BattleList::NextTurn()
{
	if (m_Current != nullptr)
		m_Current = m_Current->next;
}

BattleNode* BattleList::GetCurrent() const
{
	return m_Current;
}

void BattleList::RemoveMonster(Monster* monster)
{
	if (m_Head == nullptr)
		return;

	BattleNode* current = m_Head;
	BattleNode* pre = nullptr;

	while (true)
	{
		// 삭제할 몬스터의 노드 찾기
		if (current->type == BattleNodeType::MONSTER && current->monster == monster)
		{
			// 리스트에 노드가 하나만 있을 경우 예외 처리
			if (current->next == current)
			{
				delete current;

				m_Head = nullptr;
				m_Current = nullptr;

				return;
			}

			// 노드 제거 시작
			pre = m_Head;

			while (pre->next != current)
			{
				pre = pre->next;
			}

			// 노드 연결 제거
			pre->next = current->next;

			// 현재 턴인 노드의 경우
			if (m_Current == current)
				m_Current = current->next;

			// 헤드일 경우
			if (m_Head == current)
				m_Head = current->next;

			delete current; // 객체 삭제
			
			return;
		}
		// 찾지 못한 경우 다음 노드 이동
		current = current->next;

		// 리스트 내 모든 노드 검사 후
		if (current == m_Head)
		{
			break;
		}
	}
}

bool BattleList::HasMonster() const
{
	if (m_Head == nullptr)
		return false;

	BattleNode* current = m_Head;

	while (true)
	{
		if (current->type == BattleNodeType::MONSTER)
			return true;

		current = current->next;

		if (current == m_Head)
			break;
	}

	return false;
}

void BattleList::Clear()
{
	if (m_Head == nullptr)
		return;

	BattleNode* current = m_Head->next;

	// 헤드를 제외한 모든 몬스터 노드 제거
	while (current != m_Head)
	{
		BattleNode* next = current->next;
		
		// 노드 내부 객체 제거
		if (current->type == BattleNodeType::MONSTER)
			delete current->monster;
		// 노드 제거
		delete current;

		current = next;
	}

	// 만약 헤드 노드가 몬스터일 경우
	if (m_Head->type == BattleNodeType::MONSTER)
		delete m_Head->monster;

	delete m_Head;

	m_Head = nullptr;
	m_Current = nullptr;

}
