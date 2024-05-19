#pragma once
#include "UIElement.h"
#include <ctime>


enum CellState {
	Dead		= 0,
	Alive		= 1,
	ReadyToDie	= 2,
	ReadyToBorn	= 3
};



class CellsWindow : public UIElement {
private:
	std::time_t dt = std::time(nullptr);
public:				 // 0  1  2  3  4  5  6  7  8
	bool NtoLive[9] = { 0, 0, 0, 1, 0, 0, 0, 0, 0 };
	bool NtoDie[9]  = { 1, 1, 0, 0, 1, 1, 1, 1, 1 };
	std::vector<std::vector<CellState>> Cells;	 
	bool torMode = true;
	bool pause = false;
	int tickRate = 1;


	CellsWindow() {
		width = 80; // Should be divisible by 2
		height = 80; // Should be divisible by 2
		x = 10;
		y = 10;
		Cells.resize(height/2, std::vector<CellState>(width/2, Dead));
	}

	void Logic() {
		int neighborsCount = 0;

		// Logic
		if ((std::time(nullptr) - dt) >= tickRate && !pause) {
			dt = std::time(nullptr);
			// Rules check
			for (int x = 0; x < width / 2; x++)
				for (int y = 0; y < height / 2; y++) {
					neighborsCount = 0;
					// Neighbours check
					if (torMode == true) {
						for (int Nx = 0; Nx < 3; ++Nx) {
							for (int Ny = 0; Ny < 3; ++Ny) {

								if ((Nx == 1) && (Ny == 1)) continue;

								if (Cells[(x - 1 + Nx + width / 2) % (width / 2)][(y - 1 + Ny + height / 2) % (height / 2)] == Alive
								 || Cells[(x - 1 + Nx + width / 2) % (width / 2)][(y - 1 + Ny + height / 2) % (height / 2)] == ReadyToDie) neighborsCount++;
							}
						}
						if ((NtoDie[neighborsCount]  == 1) && (Cells[x][y] == Alive)) Cells[x][y] = ReadyToDie;	 // To Die
						if ((NtoLive[neighborsCount] == 1) && (Cells[x][y] == Dead)) Cells[x][y] = ReadyToBorn; // To Born
					}
					else {
						for (int Nx = 0; Nx < 3; ++Nx) {
							if ((x - 1 + Nx) < 0 || (x - 1 + Nx) >= width / 2) continue;
							for (int Ny = 0; Ny < 3; ++Ny) {
								if ((y - 1 + Ny) < 0 || (y - 1 + Ny) >= height / 2) continue;

								if ((Nx == 1) && (Ny == 1)) continue;

								if (Cells[x - 1 + Nx][y - 1 + Ny] == Alive
								 || Cells[x - 1 + Nx][y - 1 + Ny] == ReadyToDie) neighborsCount++;
							}
						}
						if ((NtoDie[neighborsCount]	 == 1) && (Cells[x][y] == Alive)) Cells[x][y] = ReadyToDie;	 // To Die
						if ((NtoLive[neighborsCount] == 1) && (Cells[x][y] == Dead)) Cells[x][y] = ReadyToBorn; // To Born
					}
				}

			// Life cycle
			for (int x = 0; x < width / 2; x++)
				for (int y = 0; y < height / 2; y++) {
					if (Cells[x][y] == 2) Cells[x][y] = Dead;
					if (Cells[x][y] == 3) Cells[x][y] = Alive;
				}
		}
	}

	void Input() {
		/*Drawing cells*/
		if (Window.GetMouse(olc::Mouse::LEFT).bHeld && IsMouseOver()) {
			olc::vi2d mousePos = Window.GetMousePos();
			mousePos.x -= mousePos.x % 2;
			mousePos.y -= mousePos.y % 2;
			Cells[(mousePos.x - x) / 2][(mousePos.y - y) / 2] = Alive;
		}

		/* Killing cells*/
		if (Window.GetMouse(olc::Mouse::RIGHT).bHeld && IsMouseOver()) {
			olc::vi2d mousePos = Window.GetMousePos();
			mousePos.x -= mousePos.x % 2;
			mousePos.y -= mousePos.y % 2;
			Cells[(mousePos.x - x) / 2][(mousePos.y - y) / 2] = Dead;
		}

		/*Pause*/
		if (Window.GetKey(olc::Key::SPACE).bPressed) {
			pause = !pause;
		}

		/*Clear*/
		if (Window.GetKey(olc::Key::C).bPressed) {
			for (int x = 0; x < width / 2; x++)
				for (int y = 0; y < height / 2; y++) {
					Cells[x][y] = Dead;
				}
		}

		/*Rules*/
		if (Window.GetKey(olc::Key::R).bPressed) {
			std::cout << "-=-\n";

			std::cout << "Enter new birth matrix: 0 1 2 3 4 5 6 7 8 \n";

			std::cout << "Enter new birth matrix: ";
			for (int x = 0; x < 9; x++) {
				std::cin >> NtoLive[x];
			}
			std::cout << "Enter new death matrix:   ";
			for (int x = 0; x < 9; x++) {
				std::cin >> NtoDie[x];
			}
			std::cout << '\n';
		}

		/*Tick*/
		if (Window.GetKey(olc::Key::T).bPressed) {
			std::cout << "-=-\n";
			std::cout << "Tick was: " << tickRate << '\n';
			std::cout << "Enter new Tick: "; std::cin >> tickRate;
			std::cout << '\n';
		}
	}

	void Update() override {
		Logic();
		Input();
	}

	void Render () override {
		/*Borders*/ {
			Window.DrawLine(x - 2, y - 2, x + width, y - 2, pause ? olc::RED : olc::WHITE);
			Window.DrawLine(x + width, y - 2, x + width, y + height, pause ? olc::RED : olc::WHITE);
			Window.DrawLine(x + width, y + height, x - 2, y + height, pause ? olc::RED : olc::WHITE);
			Window.DrawLine(x - 2, y + height, x - 2, y - 2, pause ? olc::RED : olc::WHITE);

			for (int i = 0; i < width / 2; i++)
				for (int j = 0; j < height / 2; j++) {
					if (Cells[i][j] != 0)
						Window.Draw(i * 2 + x, j * 2 + y, olc::DARK_GREEN);
				}
		}

		/*Draw custom mouse cursor*/ {
			olc::vi2d mousePos = Window.GetMousePos();
			mousePos.x -= mousePos.x % 2;
			mousePos.y -= mousePos.y % 2;
			if (IsMouseOver()) {
				Window.Draw(mousePos, olc::GREEN);
			}
		}
		
	}
};


