/***************************************************************************
 *   Author Alan Crispin aka. crispina                                     *
 *   crispinalan@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/
 
#include "mainwindow.h"

Board::Board() {
    //squareSize =80;
	setUpBoard();
}

Board::Board(int** b) {
	board = b;
}


int Board::getPiece(int i, int j) {
    return board[i][j];
}

bool Board::possibleSquare(const int& i, const int& j)
{
	return (i + j) % 2 == 1;
}

void Board::setUpBoard() {
// set up draughts

    board = new int*[BOARDSIZE];
	for (int i = 0; i < BOARDSIZE; i++) {
	    board[i] = new int[BOARDSIZE];
	}
	
int piece = EMPTY; 

 for(int row = 0; row < BOARDSIZE; row++) {
    for(int col = 0; col < BOARDSIZE; col++) {
		
		if (row==0 || row==1 || row ==2)
		{
			if (possibleSquare(row,col))
			{
				piece =BLACK;
				board[row][col]=piece;
			}
			
		}
			
		else if(row==5 || row==6 || row==7)
		{
		  if (possibleSquare(row,col))
		  {
			  piece=WHITE;  
			  board[row][col]=piece;
			}
			
		}
		else{
			piece =EMPTY;
			board[row][col]= piece;		   			
		}		
		
	}
 }

}

void Board::resetBoard(){
	
	delete board; //delete pointers created with new
	
	board = new int*[BOARDSIZE];
	for (int i = 0; i < BOARDSIZE; i++) {
	    board[i] = new int[BOARDSIZE];
	}
	int piece = EMPTY; 

 for(int row = 0; row < BOARDSIZE; row++) {
    for(int col = 0; col < BOARDSIZE; col++) {
		
		if (row==0 || row==1 || row ==2)
		{
			if (possibleSquare(row,col))
			{
				piece =BLACK;
				board[row][col]=piece;
			}
			
		}
			
		else if(row==5 || row==6 || row==7)
		{
		  if (possibleSquare(row,col))
		  {
			  piece=WHITE;  
			  board[row][col]=piece;
			}
			
		}
		else{
			piece =EMPTY;
			board[row][col]= piece;		   			
		}		
		
	}
 }
}


void Board::getAllMovesWhite(vector<Move>& moves) {   
	    
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            int piece = getPiece(i, j);
			if(piece==WHITE || piece==WKING){
				 getLegalJumpMovesWhite(i, j, moves);
            }
        }
    }
    if (moves.empty()) {//no jumps
        for (int i = 0; i < BOARDSIZE; i++) {
            for (int j = 0; j < BOARDSIZE; j++) {
                int piece = getPiece(i, j);
                if (piece == WHITE || piece == WKING) {                    
                    getLegalMovesWhite(i, j, moves);
                }
            }
        }
    }
}

void Board::getAllMovesBlack(vector<Move>& moves)
{
	for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            int piece = getPiece(i, j);
			if(piece==BLACK || piece==BKING){
				 getLegalJumpMovesBlack(i, j, moves);
            }
        }
    }
    if (moves.empty()) {//no jumps
        for (int i = 0; i < BOARDSIZE; i++) {
            for (int j = 0; j < BOARDSIZE; j++) {
                int piece = getPiece(i, j);
                if (piece == BLACK || piece == BKING) {                    
                    getLegalMovesBlack(i, j, moves);
                }
            }
        }
	}
}
void Board::getLegalJumpMovesWhite(int r, int c, vector<Move>& moves)
{
	Point start = {r, c};
    vector<Point> possible_moves;
    if (getPiece(r, c) == WHITE) {
		
		possible_moves.push_back({r - 2, c + 2});
        possible_moves.push_back({r - 2, c - 2});
          
    } else if (getPiece(r, c) == WKING) {
        possible_moves.push_back({r + 2, c + 2});
        possible_moves.push_back({r + 2, c - 2});
        possible_moves.push_back({r - 2, c + 2});
        possible_moves.push_back({r - 2, c - 2});
    }
    int n = possible_moves.size();
    for (int i = 0; i < n; i++) {
        Point temp = possible_moves[i];
        Move m = {start, temp};
        Point mid = getMidSquare(m);
        if (temp.row >= 0 && temp.row < 8 && temp.col >= 0 && temp.col < 8 
				&& getPiece(temp.row, temp.col) == EMPTY 
				&& (getPiece(mid)==BLACK || getPiece(mid)==BKING)) {
					
            moves.push_back(m);
        }
    }
	
}
void Board::getLegalJumpMovesBlack(int r, int c, vector<Move>& moves)
{
	Point start = {r, c};
    vector<Point> possible_moves;
    
    if (getPiece(r, c) == BLACK) {
       
		possible_moves.push_back({r + 2, c + 2});
        possible_moves.push_back({r + 2, c - 2});
				
    } else if (getPiece(r, c) == BKING) {
        possible_moves.push_back({r + 2, c + 2});
        possible_moves.push_back({r + 2, c - 2});
        possible_moves.push_back({r - 2, c + 2});
        possible_moves.push_back({r - 2, c - 2});
    }
    int n = possible_moves.size();
    for (int i = 0; i < n; i++) {
        Point temp = possible_moves[i];
        Move m = {start, temp};
        Point mid = getMidSquare(m);
        if (temp.row >= 0 && temp.row < 8 && temp.col >= 0 && temp.col < 8 
				&& getPiece(temp.row, temp.col) == EMPTY 
				&& (getPiece(mid)==WHITE || getPiece(mid)== WKING)) {
					
            moves.push_back(m);
        }
    }
}
void Board::getLegalMovesWhite(int r, int c, vector<Move>& moves)
{
	int piece = board[r][c];
    if (piece == EMPTY) {        
        return;
    }
    
    if (piece == WHITE) {
        int rowChange = -1;
        int newRow = r + rowChange;
        if (newRow >= 0 && newRow < 8) {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
        }
    } else if (piece ==WKING){
        int newRow = r + 1;
        if (newRow < 8) {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
        }
        newRow = r - 1;
        if (newRow >= 0) {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
        }
    }
}
void Board::getLegalMovesBlack(int r, int c, vector<Move>& moves)
{
	int piece = board[r][c];
    if (piece == EMPTY) {        
        return;
    }
    
    if (piece == BLACK) {
        int rowChange = +1;
        int newRow = r + rowChange;
        if (newRow >= 0 && newRow < 8) {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
        }
    } else if (piece ==BKING){
        int newRow = r + 1;
        if (newRow < 8) {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
        }
        newRow = r - 1;
        if (newRow >= 0) {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) {
                moves.push_back({r, c, newRow, newCol});
            }
        }
    }
}


int Board::getPiece(Point p) {
    return board[p.row][p.col];
}

Point Board::getMidSquare(Move m) {
    Point middle = {(m.start.row + m.finish.row) / 2, (m.start.col + m.finish.col) / 2};
    return middle;
}


bool Board::movesEqual(Move one, Move two) {
    return one.start.row == two.start.row && one.start.col == two.start.col && one.finish.row == two.finish.row && one.finish.col == two.finish.col;
}

void Board::render(wxDC& dc)
{
	//int squareSize=80;
	wxRect squareRect(wxSize(squareSize, squareSize));	
		
	//Display the entire board
	for(int row = 0; row<BOARDSIZE; ++row){		
		for(int col = 0; col<BOARDSIZE; ++col)
		{
			if((row+col)%2 == 0)
			{
				dc.SetBrush(*wxWHITE_BRUSH);
				dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen	
				dc.DrawRectangle(squareRect);				
			}			
			else{				
				dc.SetBrush(*wxLIGHT_GREY_BRUSH);
				dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen					
				dc.DrawRectangle(squareRect);
				
				int p = board[row][col];
				
			   
				if(p == WHITE) {
					dc.SetBrush(*wxWHITE_BRUSH); 										
					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;					
					dc.DrawCircle(xc, yc, radius);	
				}
				
				if(p== WKING) 
					
					{
					dc.SetBrush(*wxWHITE_BRUSH); // filling
					dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red king outline

					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);	
					dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen	
				    }
					
				if(p == BLACK){
					dc.SetBrush(*wxBLACK_BRUSH); // filling				
					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);	
					}
				
				if(p == BKING) 					
					{
					dc.SetBrush(*wxBLACK_BRUSH); // filling					
					dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red king outline

					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);
					dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset
					}					
			
			}//else
		
		squareRect.Offset(squareSize,0);
		
	}//col
		squareRect.Offset(0,squareSize); //new line
		squareRect.SetLeft(0);	
	}//row	
}

int Board::numberWhitePiecesOnBoard()
{
	int numberWhitePieces=0;	  
 		
	for(int row=0; row<BOARDSIZE; row++){
		for(int col=0; col<BOARDSIZE; col++){
			if(board[row][col]==WHITE){
				numberWhitePieces++;				
			}			
		}
	}	
	return numberWhitePieces;
}

int Board::numberWhiteKingsOnBoard()
{
	int numberWhiteKings=0;	 		
	for(int row=0; row<BOARDSIZE; row++){
		for(int col=0; col<BOARDSIZE; col++){			
			if(board[row][col]==WKING){
				numberWhiteKings++ ;				
			}	
		}
	}	
	return numberWhiteKings;
}

int Board::numberBlackPiecesOnBoard()
{
   int numberBlackPieces=0;
 		
	for(int row=0; row<8; row++){
		for(int col=0; col<8; col++){					
			if(board[row][col]==BLACK){
				numberBlackPieces++;				
			}	
		}
	}	
	return numberBlackPieces;
}

int Board::numberBlackKingsOnBoard()
{	
	int numberBlackKings=0; 		
	for(int row=0; row<8; row++){
		for(int col=0; col<8; col++){					
			if(board[row][col]==BKING){
				numberBlackKings++;				
			}			
			
		}
	}	
	return numberBlackKings;
}

bool Board::makeWhiteMove(int r1, int c1, int r2, int c2)
{
	
	int startRow = r1;
    int startCol = c1;   
    int endRow = r2;
    int endCol = c2;
	
	Move move;
	move.start.row=r1;
	move.start.col=c1;
	move.finish.row=r2;
	move.finish.col=c2;
	
	//Check if white piece
	int current_piece = getPiece(startRow, startCol);
	
	if(current_piece==BLACK|| current_piece ==BKING)
	{	
	return false;	
	}
	
		
	vector<Move> possible_moves;    
    getAllMovesWhite(possible_moves);
    bool move_in_list = false;
    int n = possible_moves.size();
	
    
	for (int i = 0; i < n && !move_in_list; i++) {  
		move_in_list = movesEqual(possible_moves[i], move);
    }
    if (move_in_list) {      
       
		if (startRow - 1 == endRow) {
            board[startRow][startCol] = EMPTY;
            board[endRow][endCol] = current_piece;
        } else {	
           
            board[startRow][startCol] = EMPTY;
            board[endRow][endCol] = current_piece;
            Point middle_square = getMidSquare(move);            			
            board[middle_square.row][middle_square.col] = EMPTY;
        }
        if (endRow == 0) {
            board[endRow][endCol] = WKING;            
        }        
		return true;
    } else {        
		return false;
    }	
}


bool Board::isBlackMoveAJump(int r1, int c1, int r2, int c2)
{
	//May need refining to separate regular piece from king moves	
	if(r1 - r2 == -2 || r1 - r2 == 2){  //pieces and kings
	    if(c1 - c2 == -2 || c1 - c2 == 2){			
			return true;
		}
	}	
	else {		
		return false;
	}
return false;	
}

bool Board::isWhiteMoveAJump(int r1, int c1, int r2, int c2)
{
	if(r1 - r2 == -2 || r1 - r2 == 2){  //-2 for piece +2 for king
	    if(c1 - c2 == -2 || c1 - c2 == 2){			
			return true;
		}
	}	
	else {		
		return false;
	}
return false;	
}


bool Board::canJumpAgainBlack(int row, int col)
{
	
	vector<Move> jumps;	
	getLegalJumpMovesBlack(row, col,jumps);
	int num_jumps = jumps.size();
	if(num_jumps>0) return true;
	else return false;
}

bool Board::canJumpAgainWhite(int row, int col)
{
	vector<Move> jumps;	
	getLegalJumpMovesWhite(row, col,jumps);
	int num_jumps = jumps.size();
	if(num_jumps>0) return true;
	else return false;
}

bool Board::isBlack(int player)
{
if((player== BLACK) || (player==BKING)){
		return true;
	}
	else{
		return false;
}
}
bool Board::isWhite(int player)
{
	if((player== WHITE) || (player==WKING)){
		return true;
	}
	else{
		return false;
	}
}

int Board::blackScore(Board board)
{
	int king_weight =2;
	int blackScore =(king_weight * board.numberBlackKingsOnBoard() 
							+ board.numberBlackPiecesOnBoard()) 
			- (king_weight * board.numberWhiteKingsOnBoard() 
			   + board.numberWhitePiecesOnBoard());			   
	return blackScore;
}

int Board::whiteScore(Board board)
{
	int king_weight =2;
	int whiteScore=(king_weight * board.numberWhiteKingsOnBoard() 
   + board.numberWhitePiecesOnBoard()) 
			- (king_weight * board.numberBlackKingsOnBoard()
                  + board.numberBlackPiecesOnBoard()); 	
    return 	whiteScore;
}


Board* Board::clone() {
    int** new_board = new int*[8];
    for (int i = 0; i < 8; i++) {
        new_board[i] = new int[8];
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            new_board[i][j] = board[i][j];
        }
    }    
	Board* b = new Board(new_board);
    return b;
}

void Board::makeComputerMovement()
{
		
	blackMove();
//	cout<< "Best black move (row,col): ("<<bestBlackMove.start.row<<","<<bestBlackMove.start.col
//					<<") to (" <<bestBlackMove.finish.row<<","<<bestBlackMove.finish.col<<")"<<endl;
//  
  
   if((board[bestBlackMove.start.row][bestBlackMove.start.col]==BLACK))
   {
    board[bestBlackMove.start.row][bestBlackMove.start.col]=EMPTY;
    board[bestBlackMove.finish.row][bestBlackMove.finish.col]=BLACK;
	  
    if (abs(bestBlackMove.start.row - bestBlackMove.finish.row) == 2){
	//jumping
    Point middle_square = getMidSquare(bestBlackMove);
    board[middle_square.row][middle_square.col] = EMPTY;
     }
	
	if (bestBlackMove.finish.row == 7) {
           board[bestBlackMove.finish.row][bestBlackMove.finish.col]=BKING;        
	}
	
	//check if black can jump again
	if (isBlackMoveAJump(bestBlackMove.start.row, bestBlackMove.start.col,
								bestBlackMove.finish.row,bestBlackMove.finish.col)
		 && canJumpAgainBlack(bestBlackMove.finish.row,bestBlackMove.finish.col))	
	{	  
	  makeComputerMovement(); //recursion
	}	
   }
   
   else if ((board[bestBlackMove.start.row][bestBlackMove.start.col]==BKING))
   {
	board[bestBlackMove.start.row][bestBlackMove.start.col]=EMPTY;
    board[bestBlackMove.finish.row][bestBlackMove.finish.col]=BKING;
	  
    if (abs(bestBlackMove.start.row - bestBlackMove.finish.row) == 2){
	//jumping
    Point middle_square = getMidSquare(bestBlackMove);
    board[middle_square.row][middle_square.col] = EMPTY;
     }
	
	//check if black can jump again
	if (isBlackMoveAJump(bestBlackMove.start.row, bestBlackMove.start.col,
								bestBlackMove.finish.row,bestBlackMove.finish.col)
		 && canJumpAgainBlack(bestBlackMove.finish.row,bestBlackMove.finish.col))	
	{
	   makeComputerMovement(); //recursion
	}
   }
}


bool Board::blackMove(int level)
{
	if (level == 0) {
        return blackScore(board);
    }
	
  std::vector<Move> possible_moves;;  
  getAllMovesBlack(possible_moves);
  
  if (possible_moves.empty())
  {   
    return false;
  }
	int n = possible_moves.size();
	int maxScore = -20;
	Board tempBoard;
	Move bestMove=possible_moves[0];
	bestBlackMove=possible_moves[0];
	Move move;
   // test all possible moves
   for (int i = 0; i < n; i++) {            
	      move =possible_moves[i]; 
          // "*clone"  is a clone of the current board object, allocated on the stack
		  tempBoard = *clone(); 		
			
			if(tempBoard.board[move.start.row][move.start.col]==BLACK){
			// Make black regular move		
			tempBoard.board[move.start.row][move.start.col]=EMPTY;
			tempBoard.board[move.finish.row][move.finish.col]=BLACK;
	  
	       if (abs(move.start.row - move.finish.row) == 2){
		   //jumping
		    Point middle_square = getMidSquare(move);
		    tempBoard.board[middle_square.row][middle_square.col] = EMPTY;
	       }	
			
			if (move.finish.row == 7) {
            tempBoard.board[move.finish.row][move.finish.col]=BKING;           
           }
		   
		   }
		   
		   else if(tempBoard.board[move.start.row][move.start.col]==BKING)
		   {
			
			tempBoard.board[move.start.row][move.start.col]=EMPTY;
			tempBoard.board[move.finish.row][move.finish.col]=BKING;
	  
	       if (abs(move.start.row - move.finish.row) == 2){
		   //jumping
		    Point middle_square = getMidSquare(move);
		    tempBoard.board[middle_square.row][middle_square.col] = EMPTY;
	       }
			//triple kings?
		   }

			if (level == 0 || tempBoard.whiteMove(level - 1))
            {
              int result = blackScore(tempBoard);
			if (maxScore < result) //minimiser
             {
             maxScore = result;
             bestMove = move;
             }
            } 
           else
           {
            maxScore = 100;
            bestMove = move;
           }
   }			
  
  
  bestBlackMove=bestMove;    
 
  return maxScore;	
}



bool Board::whiteMove(int level)
{
	if (level == 0) {
        return whiteScore(board);
    }
	
  std::vector<Move> possible_moves;;  
  getAllMovesWhite(possible_moves);
  
  if (possible_moves.empty())
  {   
    return false;
  }
	int n = possible_moves.size();
	int maxScore = 20;
	Board tempBoard;
	Move bestMove=possible_moves[0];
	Move move;
   // test all possible moves on tempboard
   for (int i = 0; i < n; i++) {
            
	       move=possible_moves[i]; 
	       tempBoard = *clone();
		   
			if((tempBoard.board[move.start.row][move.start.col]==WHITE)){
			// Make white regular move			
			tempBoard.board[move.start.row][move.start.col]=EMPTY;
			tempBoard.board[move.finish.row][move.finish.col]=WHITE;
	  
	       if (abs(move.start.row - move.finish.row) == 2){
		   //jumping
		    Point middle_square = getMidSquare(move);
		    tempBoard.board[middle_square.row][middle_square.col] = EMPTY;
	       }			
			
			if (move.finish.row == 0) {
            tempBoard.board[move.finish.row][move.finish.col]=WKING;            
           }
		}
		
		else if((tempBoard.board[move.start.row][move.start.col]==WKING)){
			// Make white regular king move			
			tempBoard.board[move.start.row][move.start.col]=EMPTY;
			tempBoard.board[move.finish.row][move.finish.col]=WKING;
	  
	       if (abs(move.start.row - move.finish.row) == 2){
		   //jumping
		    Point middle_square = getMidSquare(move);
		    tempBoard.board[middle_square.row][middle_square.col] = EMPTY;
	       }			
			
		}						
			
			if (level == 0 || tempBoard.blackMove(level - 1))
            {
              int result = whiteScore(tempBoard);
			if (maxScore > result) //maximizer
             {
             maxScore = result;
             bestMove = move;
             }
            } 
           else
           {
            maxScore = -100;
            bestMove = move;
           }
   }		

  return maxScore;	
}


