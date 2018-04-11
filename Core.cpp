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
	// 콘솔창 핸들 생성
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	//스테이지 관리자를 초기화한다.
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
	// 한칸은 2바이트를 사용하기 때문에 *2를 해줬음.
	COORD pos = { (x+1) * 2, y };
	SetConsoleCursorPosition(m_hConsole, pos);
}
