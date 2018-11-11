
#pragma once

#include "BaseApp.h"

class Tetris : public BaseApp
{
	typedef BaseApp Parent;

private:
	int mObj1XOld;
	int mObj1YOld;
	int mObj1X;
	int mObj1Y;
	int mObj2X;
	int mObj2Y;

	const int  mColumns = 4;
	const wchar_t mBorder = L'#';
	const wchar_t mBorderCell = L'.';
	const wchar_t mFigureCell = L'0';
	const int  mRows = 4;

	string mCount;
	Figure mFigure;
	float mGameSpeed = 0;
	bool mIsCreateFigure = true;
	bool mIsDowmMoove = true;
	bool mooveDown = true;
	bool mIsMoove = true;
	bool mIsMooveLeft = false;
	bool mIsMooveRight = false;
	Figure mNextFigure;
	float mSpeedApdate = 0.001;
	bool mIsRender = true;
	bool mIsRotate = false;
	int mScore = 0;
	string smScore;

public:
	Tetris();
	void SetFigure(const int x, const int y, Figure item);
	void SetString(const int x, const int y, string item);

	void CheckingLine();
	void ClearGeometry(const int x, const int y, Figure item);
	void ClearNextFigure(const int x, const int y);
	void IsCreateFigure();
	void IsGameOver();
	bool IsRotate(const int x, const int y, Figure item);
	virtual void KeyPressed(int btnCode);
	void IsMooveDown();
	bool MooveLeft(const int x, const int y, Figure item);
	bool MooveNext(const int x, const int y, Figure item);
	bool MooveRight(const int x, const int y, Figure item);
	void ShowField();
	Figure RandomFigure();
	virtual void UpdateF(float deltaTime);
};