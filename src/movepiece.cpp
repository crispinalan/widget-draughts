#include "movepiece.h"

MovePiece::MovePiece()
{
}

MovePiece::~MovePiece()
{
}

MovePiece::MovePiece(int row1, int col1, int row2, int col2)
{
			r1=row1;
			c1=col1;
			r2=row2;
			c2=col2;
			
}

void MovePiece::Change(int row1, int col1, int row2, int col2)
{
	r1=row1;
	c1=col1;
	r2=row2;
	c2=col2;
}