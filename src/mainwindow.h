#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <wx/wx.h>
#include <iostream>
#include <vector>
#include "movepiece.h"





using namespace std; 

const int ROWS =8;
const int COLS=8;

const int EMPTY=1;
const int WHITE=2;
const int BLACK=3;
const int WKING =4;
const int BKING=5;

const int MAX_DEPTH=24;

const int CHECKER  =	100; // a checkers' worth
const int KING     =	130; // a kings' worth
const int BACKRANK1 =	30; //back rank positions
const int BACKRANK2 =	20; //back rank
const int BACKRANK3 =	10; //back rank
const int CENTRALRANKS= 5;


class MainWindow : public wxFrame
{
public:
	MainWindow();
	~MainWindow();

    int squareSize=80;

	void PaintEvent(wxPaintEvent & evt);
    void PaintNow();    
    void render(wxDC& dc);		
	void OnMouseLeftDown(wxMouseEvent& event);
    void OnMouseLeftUp(wxMouseEvent& event);
	void OnReSize(wxSizeEvent& event);
	
	void ResetBoard();			
	
	int board [8][8]; //xy position matrix
	int c[8][8]={
			{0,2,0,2,0,2,0,2},  //WHITE (moves down)
			{2,0,2,0,2,0,2,0}, 
			{0,2,0,2,0,2,0,2}, 
			{1,0,1,0,1,0,1,0}, 
			{0,1,0,1,0,1,0,1}, 
			{3,0,3,0,3,0,3,0},
			{0,3,0,3,0,3,0,3}, //BLACK (moves up)
			{3,0,3,0,3,0,3,0}};
	
	
     bool ConvertMousePosToRowAndColumn(const wxPoint& pos, int& row, int& col) const;
        
        int m_rowLeftMDown;
        int m_colLeftMDown;        
        int m_rowLeftMUp;
        int m_colLeftMUp;

        int white;
        int black;
        int canJump = 0;      
		int searchDepth=0;
      
        bool playerFinished = false;
        wxString statusText = "";		

        bool isWhite(int player);
        bool isBlack(int player);
        bool isComputer(int player);
        int switchPlayer(int player);
        void swap(int grid[ROWS][COLS], int row1, int col1, int row2, int col2);
       
        int makeComputerMove(int grid[ROWS][COLS], int player, int row1, int col1, int row2, int col2);
        int checkMove(int grid[ROWS][COLS], int player, int row1, int col1, int row2, int col2);
        int testMove(int grid[ROWS][COLS], int player, int row1, int col1, int row2, int col2);

        int legalMoves(int player, int grid[ROWS][COLS]);
        int checkJump(int grid[ROWS][COLS], int player, int rr, int cc);

        void computerMove(int grid[ROWS][COLS], int player);

        int testComputer(int grid[ROWS][COLS], int player);

        vector<MovePiece> computerCheck(int grid[ROWS][COLS], int player);

        int evaluation1(int grid[ROWS][COLS], int player);
		int evaluation2(int grid[ROWS][COLS], int player);
		int evaluation3(int grid[ROWS][COLS], int player);
        MovePiece* minimax(int grid[8][8], int player);

        int maxMove(int grid[8][8],
            MovePiece* bestMove,
            int player,           
            int alpha,
            int beta,
            int bottom,
            int depth);

        int minMove(int grid[8][8],
            MovePiece* bestMove,
            int player,            
            int alpha,
            int beta,
            int bottom,
            int depth);

        void GenerateComputerMove();
        
		bool isMoveValid2(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);
        bool isRegularMove(int grid[ROWS][COLS], int r1, int c1, int r2, int c2);
        // bool isJumpMove()
        int numberWhitePiecesOnBoard(int grid[ROWS][COLS]);
        int numberBlackPiecesOnBoard(int grid[ROWS][COLS]);

		wxMenuBar *m_MenuBar=nullptr;	
		wxStatusBar* statusbar=nullptr;
		
		void OnMenuExit(wxCommandEvent &evt);
		void OnMenuResetBoard(wxCommandEvent &evt);
		void OnMenuAbout(wxCommandEvent &evt);
		
		//Event table
      	DECLARE_EVENT_TABLE()	
		enum {
	    // declare event ids
		MENU_Exit =wxID_HIGHEST + 1,
		MENU_RESET,
		MENU_ABOUT
	 };
};

#endif // MAINWINDOW_H
