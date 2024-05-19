#pragma once
#include "UIElement.h"
#include <ctime>



class CellsWindow : public UIElement {
private:
	std::time_t dt = std::time(nullptr);

public:
	char** Cells;	 // 0  1  2  3  4  5  6  7  8
	bool NtoLive[9] = { 0, 0, 0, 1, 0, 0, 0, 0, 0 };
	bool NtoDie[9]  = { 1, 1, 0, 0, 1, 1, 1, 1, 1 };

	bool TorMode = 1;

	bool Pause = false;
	int Tick = 1;



	CellsWindow() {
		width = 80; // Should be divisible by 2
		height = 80; // Should be divisible by 2
		x = 10;
		y = 10;



		Cells = new char* [width / 2];
		for (int x = 0; x < width / 2; x++) {
			Cells[x] = new char[height / 2];
		}

		for (int x = 0; x < width / 2; x++) {
			for (int y = 0; y < height / 2; y++) {
				Cells[x][y] = 0;
			}
		}
	}

	~CellsWindow() {
		for (int x = 0; x < width / 2; x++) {
			delete Cells[x];
		}
		delete Cells;
	}



	void Logic() {
		int Neighbors = 0;

		// Logic
		if ((std::time(nullptr) - dt) >= Tick && !Pause) {
			dt = std::time(nullptr);
			// Rules check
			for (int x = 0; x < width / 2; x++)
				for (int y = 0; y < height / 2; y++) {

					Neighbors = 0;
					// Neighbours check
					if (TorMode == true) {
						for (int Nx = 0; Nx < 3; ++Nx) {
							for (int Ny = 0; Ny < 3; ++Ny) {

								if ((Nx == 1) && (Ny == 1)) continue;

								if (Cells[(x - 1 + Nx + width / 2) % (width / 2)][(y - 1 + Ny + height / 2) % (height / 2)] == 1
									|| Cells[(x - 1 + Nx + width / 2) % (width / 2)][(y - 1 + Ny + height / 2) % (height / 2)] == 3) Neighbors++;
							}
						}
						if ((NtoLive[Neighbors] == 1) && (Cells[x][y] == 0)) Cells[x][y] = 2; // To Born
						if ((NtoDie[Neighbors] == 1) && (Cells[x][y] == 1)) Cells[x][y] = 3; // To Die
					}
					else {
						for (int Nx = 0; Nx < 3; ++Nx) {
							if ((x - 1 + Nx) < 0 || (x - 1 + Nx) >= width / 2) continue;
							for (int Ny = 0; Ny < 3; ++Ny) {
								if ((y - 1 + Ny) < 0 || (y - 1 + Ny) >= height / 2) continue;

								if ((Nx == 1) && (Ny == 1)) continue;

								if (Cells[x - 1 + Nx][y - 1 + Ny] == 1
									|| Cells[x - 1 + Nx][y - 1 + Ny] == 3) Neighbors++;
							}
						}
						if ((NtoLive[Neighbors] == 1) && (Cells[x][y] == 0)) Cells[x][y] = 2; // To Born
						if ((NtoDie[Neighbors] == 1) && (Cells[x][y] == 1)) Cells[x][y] = 3; // To Die
					}
				}


			// Life cycle
			for (int x = 0; x < width / 2; x++)
				for (int y = 0; y < height / 2; y++) {
					if (Cells[x][y] == 2) Cells[x][y] = 1;
					if (Cells[x][y] == 3) Cells[x][y] = 0;
				}
		}
	}

	void Input() {
		// Pause
		if (Window.GetKey(olc::Key::SPACE).bPressed) {
			Pause = !Pause;
		}

		// Clear
		if (Window.GetKey(olc::Key::C).bPressed) {
			for (int x = 0; x < width / 2; x++)
				for (int y = 0; y < height / 2; y++) {
					Cells[x][y] = 0;
				}
		}

		// Rules
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

		// Tick
		if (Window.GetKey(olc::Key::T).bPressed) {
			std::cout << "-=-\n";
			std::cout << "Tick was: " << Tick << '\n';
			std::cout << "Enter new Tick: "; std::cin >> Tick;
			std::cout << '\n';
		}

		// Drawing
		if (Window.GetMouse(olc::Mouse::LEFT).bHeld && IsMouseOver()) {
			olc::vi2d mousePos = Window.GetMousePos();
			mousePos.x -= mousePos.x % 2;
			mousePos.y -= mousePos.y % 2;
			Cells[(mousePos.x - x) / 2][(mousePos.y - y) / 2] = 1;
		}

	}

	void Update() {
		Logic();
		Input();
	}

	void Render () override {
		// Draw custom mouse cursor
		olc::vi2d mousePos = Window.GetMousePos();
		mousePos.x -= mousePos.x % 2;
		mousePos.y -= mousePos.y % 2;
		if (IsMouseOver()) {
			Window.Draw(mousePos, olc::GREEN);
		}

		// Borders
		Window.DrawLine(x - 2, y - 2, x + width, y - 2, Pause ? olc::RED : olc::WHITE);
		Window.DrawLine(x + width, y - 2, x + width, y + height, Pause ? olc::RED : olc::WHITE);
		Window.DrawLine(x + width, y + height, x - 2, y + height, Pause ? olc::RED : olc::WHITE);
		Window.DrawLine(x - 2, y + height, x - 2, y - 2, Pause ? olc::RED : olc::WHITE);

		for (int i = 0; i < width / 2; i++)
			for (int j = 0; j < height / 2; j++) {
				if (Cells[i][j] != 0)
					Window.Draw(i * 2 + x, j * 2 + y, olc::DARK_GREEN);
			}
	}
};


