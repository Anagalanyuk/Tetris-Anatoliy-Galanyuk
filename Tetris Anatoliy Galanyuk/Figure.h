#pragma once

class Figure
{
private:
	int mColumns = 4;
	int mRows = 4;
	char mGeometryFigure[4][4];
	char mCell = '0';
	char mSpace = ' ';

public:

	void CreateFigureI()
	{
		ClearGeometry();
		for (int i = 0; i < 4; ++i)
		{
			mGeometryFigure[i][2] = mCell;
		}
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 1; j < 4; ++j)
			{
				if (j != 2)
				{
					mGeometryFigure[i][j] = mSpace;
				}
			}
		}
	}

	void CreateFigureL()
	{
		ClearGeometry();
		mGeometryFigure[1][1] = mCell;
		mGeometryFigure[2][1] = mCell;
		mGeometryFigure[3][1] = mCell;
		mGeometryFigure[3][2] = mCell;

	}
	void CreateFigureJ()
	{
		ClearGeometry();
		mGeometryFigure[1][2] = mCell;
		mGeometryFigure[2][2] = mCell;
		mGeometryFigure[3][2] = mCell;
		mGeometryFigure[3][1] = mCell;
	}

    void CreateFigureO()
	{
		ClearGeometry();
		mGeometryFigure[1][1] = mCell;
		mGeometryFigure[1][2] = mCell;
		mGeometryFigure[2][1] = mCell;
		mGeometryFigure[2][2] = mCell;
	}

	void CreateFigureZ()
	{
		ClearGeometry();
		mGeometryFigure[1][0] = mCell;
		mGeometryFigure[1][1] = mCell;
		mGeometryFigure[2][1] = mCell;
		mGeometryFigure[2][2] = mCell;
	}

	void CreateFigureS()
	{
		ClearGeometry();
		mGeometryFigure[1][1] = mCell;
		mGeometryFigure[1][2] = mCell;
		mGeometryFigure[2][0] = mCell;
		mGeometryFigure[2][1] = mCell;
	}

	void CreateFigureT()
	{
		ClearGeometry();
		mGeometryFigure[1][1] = mCell;
		mGeometryFigure[2][1] = mCell;
		mGeometryFigure[2][2] = mCell;
		mGeometryFigure[3][1] = mCell;
	}

	char* GetGeometry()
	{
		return *mGeometryFigure;
	}

	void SetGeometry(Figure item)
	{
		int index = 0;
		for (int i = 0; i < mRows; ++i)
		{
			for (int j = 0; j < mColumns; ++j)
			{
				mGeometryFigure[i][j] = item.GetGeometry()[index];
				index++;
			}
		}
	}

	void FigureRotate()
	{
		char rotate[4][4];
		int rows = 3;
		int columns = 0;
		for (int i = 0; i < mRows; ++i)
		{
			for (int j = 0; j < mColumns; ++j)
			{
				rotate[i][j] = mGeometryFigure[rows][columns];
				rows--;
			}
			rows = 3;
			columns++;
		}

		for (int i = 0; i < mRows; ++i)
		{
			for (int j = 0; j < mColumns; ++j)
			{
				mGeometryFigure[i][j] = rotate[i][j];
			}
		}
	}

	void ClearGeometry()
	{
		for (int i = 0; i < mRows; ++i)
		{
			for (int j = 0; j < mColumns; ++j)
			{
				mGeometryFigure[i][j] = mSpace;
			}
		}
	}
};