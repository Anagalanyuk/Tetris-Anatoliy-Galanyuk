
#include "Tetris.h"

#include "MooveKey.h"

#include "Figure.h"

#include<ctime>

Tetris::Tetris() : Parent(100, 80)
{
	mObj1X = 23;
	mObj1Y = 20;
	mObj2X = 7;
	mObj2Y = 1;
}

void Tetris::SetFigure(int x, int y, Figure item)
{
	int index = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			char foo = item.GetGeometry()[index];
			if (item.GetGeometry()[index] == mFigureCell)
			{
				SetChar(x + j, y + i, mFigureCell);
			}
			index++;
		}
	}
}

void Tetris::SetString(int x, int y, string item)
{
	for (unsigned int i = 0; i < item.length(); ++i)
	{
		SetChar(x, y, item[i]);
		x++;
	}
}

void Tetris::CheckingLine()
{
	int counrFigureCell = 0;

	for (int columns = mObj1Y - 5; columns > 1; --columns)
	{
		for (int rows = 1; rows < mObj1X - 7; ++rows)
		{
			if (GetChar(rows, columns) == mFigureCell)
			{
				counrFigureCell++;
			}
		}

		if (counrFigureCell == (mObj1X - 8))
		{
			for (int i = columns; i > 1; --i)
			{
				for (int j = 1; j < mObj1X - 7; ++j)
				{
					wchar_t temp = GetChar(j, i - 1);
					SetChar(j, i, temp);
				}
			}
			columns++;
			counrFigureCell = 0;
			mScore += 100;
		}
		else
		{
			counrFigureCell = 0;
		}
	}
}

void Tetris::ClearGeometry(int x, int y, Figure item)
{
	int index = 0;

	for (int i = 0; i < mRows; ++i)
	{
		for (int j = 0; j < mColumns; ++j)
		{
			if (GetChar(x + j, y + i) == mFigureCell &&
				item.GetGeometry()[index] == mFigureCell)
			{
				SetChar(x + j, y + i, mBorderCell);
			}
			index++;
		}
	}
}

void Tetris::ClearNextFigure(const int x, const int y)
{
	for (int i = 0; i < mRows; ++i)
	{
		for (int j = 0; j < mColumns; ++j)
		{
			if (GetChar(x + j, y + i) == mFigureCell)
			{
				SetChar(x + j, y + i, L' ');
			}
		}
	}
}

void Tetris::IsCreateFigure()
{
	ClearNextFigure(mObj1X - 5, mObj1Y - 19);
	mNextFigure = RandomFigure();
	SetFigure(mObj1X - 5, mObj1Y - 19, mNextFigure);
	mIsCreateFigure = false;
}

void Tetris::IsGameOver()
{
	int countCell = 0;

	for (int i = 0; i < 5; i++)
	{
		if (GetChar((mObj2X - 2) + i, 2) == mFigureCell)
		{
			mIsPlayGame = false;
		}
	}
}

bool Tetris::IsRotate(const int x, const int y, Figure item)
{
	bool isRotate = true;
	int index = 0;
	char figure[4][4];

	for (int i = 3; i >= 0; --i)
	{
		for (int j = 3; j >= 0; --j)
		{
			figure[j][i] = item.GetGeometry()[index];
			index++;
		}
	}

	for (int i = 0; i < 4 && isRotate; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (figure[i][j] == mFigureCell &&
				GetChar(x + j, y + i) == mBorder ||
				figure[i][j] == mFigureCell &&
				GetChar(x + j, y + i) == mFigureCell)
			{
				isRotate = false;
				break;
			}
		}
	}
	return isRotate;
}

void Tetris::KeyPressed(int btnCode)
{
	mooveDown = false;
	if (btnCode == downArrow)
	{
		mSpeedApdate = 0.0075;
		mooveDown = true;
	}
	else if (btnCode == leftArrow)
	{
		mooveDown = true;
		mIsMooveLeft = true;
		ClearGeometry(mObj2X, mObj2Y - 1, mFigure);

		if (MooveLeft(mObj2X - 1, mObj2Y - 1, mFigure))
		{
			mObj2X--;
		}
	}
	else if (btnCode == rightArrow)
	{
		mIsMooveRight = true;
		mooveDown = true;
		ClearGeometry(mObj2X, mObj2Y - 1, mFigure);

		if (MooveRight(mObj2X, mObj2Y - 1, mFigure))
		{
			mObj2X++;
		}
	}
	else if (btnCode == space)
	{
		ClearGeometry(mObj2X, mObj2Y - 1, mFigure);
		if (IsRotate(mObj2X, mObj2Y, mFigure))
		{
			mFigure.FigureRotate();
			mIsRotate = true;
		}
	}
}

void Tetris::IsMooveDown()
{
	ClearGeometry(mObj2X, mObj2Y - 1, mFigure);

	if (MooveNext(mObj2X, mObj2Y, mFigure))
	{
		SetFigure(mObj2X, mObj2Y, mFigure);
		mObj2Y++;
	}
	else
	{
		SetFigure(mObj2X, mObj2Y - 1, mFigure);
		mObj2X = 7;
		mObj2Y = 2;
		mFigure.SetGeometry(mNextFigure);
		mIsMoove = true;
		CheckingLine();
		mIsCreateFigure = true;
		IsGameOver();
		mSpeedApdate = 0.001;
	}
}

bool Tetris::MooveLeft(const int x, const int y, Figure item)
{
	mIsMooveLeft = true;
	int index = 0;
	for (int i = 0; i < mRows && mIsMooveLeft; ++i)
	{
		for (int j = 0; j < mColumns; ++j)
		{
			if (item.GetGeometry()[index] == mFigureCell &&
				GetChar(x + j, y + i) != mBorderCell)
			{
				mIsMooveLeft = false;
				break;
			}
			index++;
		}
	}
	return mIsMooveLeft;
}

bool Tetris::MooveNext(int x, int y, Figure item)
{
	int index = 0;

	for (int i = 0; i < mRows; ++i)
	{
		for (int j = 0; j < mColumns; ++j)
		{
			if (item.GetGeometry()[index] == mFigureCell &&
				GetChar(x + j, y + i) != mBorderCell)
			{
				mIsMoove = false;
				break;
			}
			index++;
		}
	}
	return mIsMoove;
}

bool Tetris::MooveRight(const int x, const int y, Figure item)
{
	mIsMooveRight = true;
	int index = 0;

	for (int i = 1; i < mRows + 1 && mIsMooveRight; ++i)
	{
		for (int j = 0; j < mColumns; ++j)
		{
			if (item.GetGeometry()[index] == mFigureCell &&
				GetChar(x + j + 1, y + i) != mBorderCell)
			{
				mIsMooveRight = false;
				break;
			}
			index++;
		}
	}
	return mIsMooveRight;
}

Figure Tetris::RandomFigure()
{
	int mRandomFigure = 0;
	mRandomFigure = rand() % (8 - 1) + 1;
	switch (mRandomFigure)
	{
	case 1:
	{

		mNextFigure.CreateFigureI();
		break;
	}
	case 2:
	{
		mNextFigure.CreateFigureJ();
		break;
	}
	case 3:
	{
		mNextFigure.CreateFigureL();
		break;
	}
	case 4:
	{
		mNextFigure.CreateFigureO();
		break;
	}
	case 5:
	{
		mNextFigure.CreateFigureS();
		break;
	}
	case 6:
	{
		mNextFigure.CreateFigureZ();
		break;
	}
	case 7:
	{
		mNextFigure.CreateFigureT();
		break;
	}
	}
	return mNextFigure;
}

void Tetris::UpdateF(float deltaTime)
{
	if (mGameSpeed > deltaTime)
	{
		if (mIsRender)
		{
			ShowField();
		}

		if (mIsCreateFigure)
		{
			IsCreateFigure();
		}

		if (!mIsMooveLeft && !mIsMooveRight)
		{
			IsMooveDown();
		}
		else
		{
			SetFigure(mObj2X, mObj2Y - 1, mFigure);
		}

		mIsMooveLeft = false;
		mIsMooveRight = false;
		mIsRotate = false;
		smScore = to_string(mScore);
		SetString(mObj1X - 11, mObj1Y - 2, smScore);
		mGameSpeed = 0;
	}
	else
	{
		if (!mIsMooveLeft && !mIsMooveRight)
		{
			ClearGeometry(mObj2X, mObj2Y - 1, mFigure);
			SetFigure(mObj2X, mObj2Y - 1, mFigure);
		}
		else
		{
			SetFigure(mObj2X, mObj2Y - 1, mFigure);
		}
	}
	mGameSpeed += mSpeedApdate;
}

void Tetris::ShowField()
{
	srand((int)std::time(nullptr));

	for (int i = 0; i < mObj1X; ++i)
	{
		SetChar(i, 0, mBorder);
		SetChar(i, mObj1Y - 4, mBorder);
		SetChar(i, mObj1Y, mBorder);
	}

	for (int i = 0; i < mObj1Y + 1; ++i)
	{
		SetChar(0, i, mBorder);
		if (i < mObj1Y - 4)
		{
			SetChar(mObj1X - 7, i, mBorder);
		}
		SetChar(mObj1X, i, mBorder);
	}

	for (int i = 1; i < mObj1X - 7; ++i)
	{
		for (int j = 1; j < mObj1Y - 4; ++j)
		{
			SetChar(i, j, mBorderCell);
		}
	}

	SetString(mObj1X - 20, mObj1Y - 2, "> Score: ");
	SetString(mObj1X - 11, mObj1Y - 2, smScore);
	mIsRender = false;
	mFigure.CreateFigureI();
}