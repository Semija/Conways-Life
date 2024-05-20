#include "MainWindow.h"
#include "UI/CellsWindow.h"



CellsWindow CW1(10, 10, 80, 80);



MainWindow::MainWindow() {
	sAppName = "Conway's Game of Life";
}

MainWindow& MainWindow::GetInstance() {
	static MainWindow instance;
	return instance;
}

bool MainWindow::OnUserCreate() {
	return true;
}

bool MainWindow::OnUserUpdate(float fElapsedTime) {
	Clear(olc::BLACK);

	// Update logic and inputs
	{
		CW1.Update();
	}

	// Render 
	{
		CW1.Render();
	}

	return true;
}


