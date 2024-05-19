#pragma once
#include "Engine/olcPixelGameEngine.h"



class MainWindow : public olc::PixelGameEngine {
private:
	MainWindow();
	MainWindow(const MainWindow&)				= delete;
	MainWindow(MainWindow&&)					= delete;
	MainWindow& operator=(const MainWindow&)	= delete;
	MainWindow& operator=(MainWindow&&)			= delete;

public:
	// Singleton to be sure that we have only one window overall
	static MainWindow& GetInstance();
	// Called once at the start
	bool OnUserCreate() override;
	// Called once per frame
	bool OnUserUpdate(float fElapsedTime) override;
};
