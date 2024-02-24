#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <ctime>
#include "CellsWindow.h"

#define Width 100
#define Height 100



class MainWindow : public olc::PixelGameEngine {
public:
	CellsWindow CW1;

	MainWindow() { 
		sAppName = "Conway's Game of Life";
	}

public:
	bool OnUserCreate() {
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) {
		Clear(olc::BLACK);

		// Inputs
		int MouseX = GetMouseX(); MouseX -= MouseX % 2;
		int MouseY = GetMouseY(); MouseY -= MouseY % 2;
		{
			CW1.MouseInput(MouseX, MouseY, olc::Mouse::LEFT, GetMouse(olc::Mouse::LEFT).bHeld);
			CW1.MouseInput(MouseX, MouseY, olc::Mouse::RIGHT, GetMouse(olc::Mouse::RIGHT).bHeld);

			// Pause
			if (GetKey(olc::Key::SPACE).bPressed) {
				CW1.Pause = !CW1.Pause;
			}
			// Clear
			if (GetKey(olc::Key::C).bPressed) {
				for (int x = 0; x < CW1.SizeX / 2; x++)
					for (int y = 0; y < CW1.SizeY / 2; y++) {
						CW1.Cells[x][y] = 0;
					}
			}
			// Rules
			if (GetKey(olc::Key::R).bPressed) {
				std::cout << "-=-\n";

				std::cout << "Enter new birth matrix: 0 1 2 3 4 5 6 7 8 \n";

				std::cout << "Enter new birth matrix: "; 
				for (int x = 0; x < 9; x++) {
					std::cin >> CW1.NtoLive[x];
				}
				std::cout << "Enter new death matrix:   ";
				for (int x = 0; x < 9; x++) {
					std::cin >> CW1.NtoDie[x];
				}
				std::cout << '\n';
			}
			//  Tick
			if (GetKey(olc::Key::T).bPressed) {
				std::cout << "-=-\n";
				std::cout << "Tick was: " << CW1.Tick << '\n';
				std::cout << "Enter new Tick: "; std::cin >> CW1.Tick;
				std::cout << '\n';
			}
		}
		
		// Logic update
		{
			CW1.UpdateCellsWindow();
		}



		// Render update
		{

			DrawLine(CW1.PositionX - 2, CW1.PositionY - 2, (CW1.SizeX + CW1.PositionX), CW1.PositionY - 2,						CW1.Pause ? olc::RED: olc::GREEN);
			DrawLine((CW1.SizeX + CW1.PositionX), CW1.PositionY - 2, (CW1.SizeX + CW1.PositionX), (CW1.SizeY + CW1.PositionY),	CW1.Pause ? olc::RED: olc::GREEN);
			DrawLine((CW1.SizeX + CW1.PositionX), (CW1.SizeY + CW1.PositionY), CW1.PositionX - 2, (CW1.SizeY + CW1.PositionY),	CW1.Pause ? olc::RED: olc::GREEN);
			DrawLine(CW1.PositionX - 2, (CW1.SizeY + CW1.PositionY), CW1.PositionX - 2, CW1.PositionY - 2,						CW1.Pause ? olc::RED: olc::GREEN);

			for (int x = 0; x < CW1.SizeX/2; x ++)
				for (int y = 0; y < CW1.SizeY/2; y ++) {
					if (CW1.Cells[x][y] != 0) 
						Draw(x*2 + CW1.PositionX, y*2 + CW1.PositionY, olc::DARK_GREEN);
				}

			if (CW1.IsMouseInside(MouseX, MouseY)) {
			Draw(MouseX, MouseY, olc::GREEN);
			}

		}

		return true;
	}
};





int main() {
	MainWindow demo;
	if (demo.Construct(Width, Height, 7, 7))
		demo.Start();

	return 0;
}
