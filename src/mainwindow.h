/***************************************************************************
 Author Alan Crispin aka. crispina                                    
crispinalan@gmail.com         
 
   Copyright  2020  Alan Crispin

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <wx/wx.h>

#include <vector>
#include <iostream>
#include <vector>
#include <string>


using namespace std;

#define WHITE_M 'w'
#define WHITE_K 'K'
#define BLACK_M 'b'
#define BLACK_K 'Q'
#define EMPTY ' '

const int BOARDSIZE=8;
const int squareSize=80;

typedef enum {WHITE =0, BLACK=1} COLOUR;

struct Pos{
public:
	int x; 
	int y; 	
};

struct Movement{
public:
	Pos start;
	std::vector<Pos> dests;
	int numberOfCaptures;
};


class MainWindow : public wxFrame
{
public:
	MainWindow();
	~MainWindow();
	
	char theBoard[BOARDSIZE][BOARDSIZE];
	
	//globals
	bool firstClick =true;
	Movement blackMove {};
	int x1=0;
	int y1=0;
	int x2=0;
	int y2=0;
	char currentPiece=BLACK_M;
	COLOUR currentPlayer =BLACK;
	COLOUR aiColour=WHITE;
	std::vector<Movement> moves; 
	
	Movement bestMoveWhite {};
	Movement bestMoveBlack {};
	Movement bestMove{};
	int maxDepth=8;
	bool playerFinished = false;
	
	
	//board methods
	void setupBoard(char board[BOARDSIZE][BOARDSIZE]);		
	void duplicateBoard(char board1[BOARDSIZE][BOARDSIZE], char board2[BOARDSIZE][BOARDSIZE]);
	
	
	//paint and render
	void paintEvent(wxPaintEvent & evt);
    void paintNow();    
    void render(wxDC& dc);	//display board	
	
	//mouse event
	void onMouseLeftDown(wxMouseEvent& event);
  		
	bool convertMousePosToXY(const wxPoint& pos, int& x, int& y) const;
	
	
	//Helpers
	bool isValidPos(Pos pos);
	int isKing(char piece);
	int isOpposite(COLOUR player, char piece);
	COLOUR getOppositeColour(COLOUR player);
	int isEndOfBoard(Pos piece, COLOUR player); 
	Pos getNextDiag(Pos from, Pos to);
	Pos getPrevDiag(Pos from, Pos to);
	int getDiagDirection(Pos from, Pos to);		
	bool destinationsValid(std::vector<Pos> dests);
	int getBestCaptureCount(std::vector<Movement> moves);	
	char getPiece(char board[BOARDSIZE][BOARDSIZE],int x,int y);
	int numberWhitePiecesOnBoard(char board[BOARDSIZE][BOARDSIZE]);
	int numberBlackPiecesOnBoard(char board[BOARDSIZE][BOARDSIZE]);
	
		
	//Moves
	std::vector<Movement> getPawnMoves(char board[BOARDSIZE][BOARDSIZE], COLOUR player, Pos pos1);
	
	int getPawnCaptureMoves(Pos pos1, Pos pos2, char board[BOARDSIZE][BOARDSIZE], 
	COLOUR player, int countCaptures, std::vector<Pos> destPositions);
	
	std::vector<Movement> getKingMoves(char board[BOARDSIZE][BOARDSIZE], COLOUR player, Pos pos1);
	
	int getKingCaptureMoves(Pos pos1, Pos pos2, char board[BOARDSIZE][BOARDSIZE], 
	COLOUR player, int countCaptures, std::vector<Pos> destPositions);	
	
    void addMove(Pos piece, std::vector<Pos> destinationsList, int captureCount);
	
	std::vector<Movement> filterMovesOnCaptureCount(std::vector<Movement> moves);
	
	//get all moves	
	std::vector<Movement> getAllMoves(char board[BOARDSIZE][BOARDSIZE], COLOUR player);
	
	void makeMove(char board[BOARDSIZE][BOARDSIZE], Movement  move);
	
	bool findMakeBlackMove(char board[BOARDSIZE][BOARDSIZE], int x1,int y1, int x2, int y2);
	
	//recursion
	int alphabeta(char board[BOARDSIZE][BOARDSIZE], int depth, int alpha, int beta, COLOUR player, Movement &bestMovement);
	void makeBestAIMovement(char board[BOARDSIZE][BOARDSIZE]);
	//scores
	int getPieceScore(char piece, COLOUR player);
	int calcScore(char board[BOARDSIZE][BOARDSIZE], COLOUR player);
	
	bool checkForWin(char board[BOARDSIZE][BOARDSIZE], COLOUR player);
	
	
		
	//statusbar
    wxString statusText = "";	
	wxStatusBar* statusbar=nullptr;

	
	//menubar	
	wxMenuBar *m_MenuBar=nullptr;
	void OnMenuExit(wxCommandEvent &evt);
	void OnMenuResetBoard(wxCommandEvent &evt);
	void OnMenuEasyGame(wxCommandEvent &evt);
	void OnMenuMediumGame(wxCommandEvent &evt);
	void OnMenuHardGame(wxCommandEvent &evt);
	
	void OnMenuAbout(wxCommandEvent &evt);
	enum {
	    // declare event ids
		MENU_Exit =wxID_HIGHEST + 1,
		MENU_EASY,
		MENU_MEDIUM,
		MENU_HARD,
		
		MENU_RESET,
		MENU_ABOUT
	 };
	
	//Event table
	DECLARE_EVENT_TABLE()
};

#endif // MAINWINDOW_H


