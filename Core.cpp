#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

CCore* CCore::m_pInst = NULL;

CCore::CCore()
{
	m_bLoop = true;
	srand((unsigned int)time(0));
}


CCore::~CCore()
{
	CShapeManager::DestroyInst();
	CStageManager::DestroyInst();
}

bool CCore::Init()
{
	// �ܼ�â �ڵ� ����
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	//�������� �����ڸ� �ʱ�ȭ�Ѵ�.
	if (!CStageManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	while (m_bLoop)
	{
		system("cls");
		CStageManager::GetInst()->Run();
		CShapeManager::GetInst()->Update();
		CShapeManager::GetInst()->Render();
		Sleep(10);
	}
}

void CCore::SetConsolePos(int x, int y)
{
	// ��ĭ�� 2����Ʈ�� ����ϱ� ������ *2�� ������.
	COORD pos = { (x+1) * 2, y };
	SetConsoleCursorPosition(m_hConsole, pos);
}
