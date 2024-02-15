#pragma once
#include <ctime>



class CellsWindow {
public:
	char** Cells;	 // 0  1  2  3  4  5  6  7  8
	bool NtoLive[9] = { 0, 0, 0, 1, 0, 0, 0, 0, 0 };
	bool NtoDie[9] =  { 1, 1, 0, 0, 1, 1, 1, 1, 1 };

	bool TorMode = 1;

	int SizeX = 80; // Should be divisible by 2
	int SizeY = 80;
	int PositionX = 10;
	int PositionY = 10;



	std::time_t result = std::time(nullptr);
	bool Pause = false;
	int Tick = 1;

	CellsWindow() {

		Cells = new char* [SizeX / 2];
		for (int x = 0; x < SizeX / 2; x++) {
			Cells[x] = new char[SizeY / 2];
		}

		for (int x = 0; x < SizeX / 2; x++) {
			for (int y = 0; y < SizeY / 2; y++) {
				Cells[x][y] = 0;
			}
		}
	}

	~CellsWindow() {
		for (int x = 0; x < SizeX / 2; x++) {
			delete Cells[x];
		}
		delete Cells;
	}

	bool IsMouseInside(int MouseX, int MouseY) {
		if (MouseX >= PositionX && MouseX < (PositionX + SizeX)) {
			if (MouseY >= PositionY && MouseY < (PositionY + SizeY)) return true;
		}
		return false;
	}

	void MouseInput(int MouseX, int MouseY, int MouseButton, bool State) {

		if (IsMouseInside(MouseX, MouseY)) {
			MouseX = (MouseX - PositionX) / 2;
			MouseY = (MouseY - PositionY) / 2;

			// Left Click draw
			if (MouseButton == 0 && State == 1) {
				Cells[MouseX][MouseY] = 1;
			}
			// Right Click draw
			if (MouseButton == 1 && State == 1) {
				Cells[MouseX][MouseY] = 0;
			}
		}
	}

	void UpdateCellsWindow() {
		int Neighbors = 0;

		// Logic
		if ((std::time(nullptr) - result) >= Tick && !Pause) {
			result = std::time(nullptr);
			// Rules check
			for (int x = 0; x < SizeX / 2; x++)
				for (int y = 0; y < SizeY / 2; y++) {

					Neighbors = 0;
					// Neighbours check
					if (TorMode == true) {
						for (int Nx = 0; Nx < 3; ++Nx) {
							for (int Ny = 0; Ny < 3; ++Ny) {

								if ((Nx == 1) && (Ny == 1)) continue;

								if (Cells[(x - 1 + Nx + SizeX / 2) % (SizeX / 2)][(y - 1 + Ny + SizeY / 2) % (SizeY / 2)] == 1
									|| Cells[(x - 1 + Nx + SizeX / 2) % (SizeX / 2)][(y - 1 + Ny + SizeY / 2) % (SizeY / 2)] == 3) Neighbors++;
							}
						}
						if ((NtoLive[Neighbors] == 1) && (Cells[x][y] == 0)) Cells[x][y] = 2; // Born
						if ((NtoDie[Neighbors] == 1) && (Cells[x][y] == 1)) Cells[x][y] = 3; // Death
					}
					else {
						for (int Nx = 0; Nx < 3; ++Nx) {
							if ((x - 1 + Nx) < 0 || (x - 1 + Nx) >= SizeX / 2) continue;
							for (int Ny = 0; Ny < 3; ++Ny) {
								if ((y - 1 + Ny) < 0 || (y - 1 + Ny) >= SizeY / 2) continue;

								if ((Nx == 1) && (Ny == 1)) continue;

								if (Cells[x - 1 + Nx][y - 1 + Ny] == 1
									|| Cells[x - 1 + Nx][y - 1 + Ny] == 3) Neighbors++;
							}
						}
						if ((NtoLive[Neighbors] == 1) && (Cells[x][y] == 0)) Cells[x][y] = 2; // Born
						if ((NtoDie[Neighbors] == 1) && (Cells[x][y] == 1)) Cells[x][y] = 3; // Death
					}
				}



			// Life cycle
			for (int x = 0; x < SizeX / 2; x++)
				for (int y = 0; y < SizeY / 2; y++) {
					if (Cells[x][y] == 2) Cells[x][y] = 1;
					if (Cells[x][y] == 3) Cells[x][y] = 0;
				}
		}

	}

};


