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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <wx/wx.h>
#include <vector>

#include <iostream>
#include <list>
#include <vector>
#include <wx/wx.h>
#include <string>

using namespace std;

const int BOARDSIZE=8;

const int WHITE=1; //Declare game consts
const int BLACK=2;
const int WKING=3;
const int BKING=4;
const int EMPTY=0;



struct Point {
public:
    int row;
    int col;
    //Point(int _row, int _col) : row(_row), col(_col) {}
};

struct Move {
public:
    Point start;
    Point finish;
	//Move() : start(0, 0), finish(0, 0) {}
	
};

class Board
{
private:
    int** board;
   
public:
    
	Board();
    Board(int** b);
	
	int squareSize=80;
    
	bool movesEqual(Move one, Move two);    
    Board* clone();
    int getPiece(int i, int j);
    int getPiece(Point p);
    Point getMidSquare(Move move);
       
    void getAllMovesWhite(vector<Move>& moves);
	void getAllMovesBlack(vector<Move>& moves);
	
    void getLegalJumpMovesWhite(int r, int c,vector<Move>& moves);
	void getLegalJumpMovesBlack(int r, int c, vector<Move>& moves);
    void getLegalMovesWhite(int r, int c, vector<Move>& moves);
	void getLegalMovesBlack(int r, int c, vector<Move>& moves);
    
	void setUpBoard();	
	bool possibleSquare(const int& i,const int& j);
	void resetBoard();
		
	bool makeWhiteMove(int r1,int c1, int r2, int c2);
	
	void makeComputerMovement();
	bool isAIMoveAJump(Move move);
	bool isBlackMoveAJump(int r1, int c1, int r2, int c2);
    bool isWhiteMoveAJump(int r1, int c1, int r2, int c2);
    void render(wxDC& dc);
	void showWhiteJumpMoves();
	bool canJumpAgainBlack(int row, int col);
	bool canJumpAgainWhite(int row, int col);	
	bool isBlack(int player);
	bool isWhite(int player);
	
	int numberWhitePiecesOnBoard();
	int numberWhiteKingsOnBoard();
	int numberBlackPiecesOnBoard();
	int numberBlackKingsOnBoard();
	
	bool checkForBlackJump();
	
	bool isWhiteMoveAJump(int row, int col);
	bool isBlackMoveAJump(int row, int col);
		
		
	Move bestBlackMove;
	int blackScore(Board board);
	int whiteScore(Board board);
	bool blackMove(int level=6);
	bool whiteMove(int level=6);
		

};



class MainWindow : public wxFrame
{
public:
	MainWindow();
	~MainWindow();
	
	
	int squareSize=80;
	void paintEvent(wxPaintEvent & evt);
    void paintNow();    
    void render(wxDC& dc);		
	void onMouseLeftDown(wxMouseEvent& event);
    void onMouseLeftUp(wxMouseEvent& event);
	void onReSize(wxSizeEvent& event);	
	void resetBoard();	
	
	bool convertMousePosToXY(const wxPoint& pos, int& x, int& y) const;
	bool ConvertMousePosToRowAndColumn(const wxPoint& pos, int& row, int& col) const;
    
	int m_rowLeftMDown;
	int m_colLeftMDown;        
	int m_rowLeftMUp;
	int m_colLeftMUp;
	
	
	bool playerFinished = false;
			
	Board board;
	
    wxString statusText = "";	
	wxStatusBar* statusbar=nullptr;

	
	wxMenuBar *m_MenuBar=nullptr;
	void OnMenuExit(wxCommandEvent &evt);
	void OnMenuResetBoard(wxCommandEvent &evt);
	void OnMenuAbout(wxCommandEvent &evt);
	enum {
	    // declare event ids
		MENU_Exit =wxID_HIGHEST + 1,
		MENU_RESET,
		MENU_ABOUT
	 };
	
	//Event table
	DECLARE_EVENT_TABLE()
};

#endif // MAINWINDOW_H


