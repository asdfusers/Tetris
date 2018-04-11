#include "Shape.h"
#include "Core.h"
#include "Stage.h"
#include "StageManager.h"

CShape::CShape()
{
	m_iDir = RD_UP;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_cShape[i][j] = '1'; // 빈공간
		}
		cout << endl;
	}
	m_iWidthCnt = 0;
}


CShape::~CShape()
{
}

bool CShape::Init()
{
	m_tPivot.x = 0;
	m_tPivot.y = 3;

	return true;
}

void CShape::Rotation()
{
}

void CShape::Render()
{
	for (int i = 0; i < 4; i++)
	{
		int iYIndex = m_tPos.y - (3 - i);
		
		if (iYIndex < 0)
			continue;
	
		for (int j = 0; j < 4; j++)
		{
			if (m_tPos.x + j >= STAGE_WIDTH)
				continue;

			if (m_cShape[i][j] == '0')
			{
				//콘솔창에 출력할 좌표를 설정한 후에 출력한다.
				CCore::GetInst()->SetConsolePos(m_tPos.x + j, iYIndex);

				cout << "■";
			}
		}
		cout << endl;
	}
}

void CShape::RenderNext()
{
	for (int i = 0; i < 4; i++)
	{
		int iYIndex = m_tPos.y - (3 - i);

		if (iYIndex < 0)
			continue;

		for (int j = 0; j < 4; j++)
		{

			if (m_cShape[i][j] == '0')
			{
				//콘솔창에 출력할 좌표를 설정한 후에 출력한다.
				CCore::GetInst()->SetConsolePos(m_tPos.x + j, iYIndex);
				cout << "■";
			}
		
		}
		cout << endl;
	}
}

//true를 리턴할 경우 바닥에 닿았음. false일 경우 바닥에 닿지 않음.
bool CShape::MoveDown()
{
	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_cShape[i][j] == '0')
			{
				if (pStage->CheckBlock(m_tPos.x + j, m_tPos.y - (2 - i)))
				{
					//바닥에 닿을때 현재 플럭이 0이면 종료.
					for (int k = 0; k < 4; ++k)
					{
						for (int l = 0; l < 4; ++l)
						{
							if (m_cShape[k][l] == '0')
							{
								if (m_tPos.y - (3 - k) < 0)
								{
									CCore::GetInst()->End();
									break;
								}
							}
						}

					}
					
					return true;
				}
			}
		}
	}

	++m_tPos.y;

	return false;
}

void CShape::MoveLeft()
{
	if (m_tPos.x == 0)
		return;

	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_cShape[i][j] == '0')
			{
				if (pStage->CheckBlock(m_tPos.x + j - 1, m_tPos.y - (3 - i)))
				{
					return;
				}
			}
		}
	}
	--m_tPos.x;
}

void CShape::MoveRight()
{
	if (m_tPos.x + m_iWidthCnt == STAGE_WIDTH)
		return;

	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_cShape[i][j] == '0')
			{
				if (pStage->CheckBlock(m_tPos.x + j + 1, m_tPos.y - (3 - i)))
				{
					return;
				}
			}
		}

	}
	++m_tPos.x;
}
