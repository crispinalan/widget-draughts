#ifndef MOVEPIECE_H
#define MOVEPIECE_H

class MovePiece
{
public:
	MovePiece();
	~MovePiece();
	
	int r1; //row1
		int c1; //col1
		int r2; //row2
		int c2; //col2		
		MovePiece(int row1, int col1, int row2, int col2);
		void Change(int row1, int col1, int row2, int col2);			
		

};

#endif // MOVEPIECE_H
