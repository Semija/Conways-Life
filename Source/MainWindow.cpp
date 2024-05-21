#include "MainWindow.h"
#include "UI/Button.h"
#include "UI/CellsWindow.h"



CellsWindow CW1(10, 12, 80, 80);
PauseButton BPause(8, 1);

RuleButton RLive0(17, 1);
RuleButton RLive1(20, 1);
RuleButton RLive2(23, 1);
RuleButton RLive3(26, 1);
RuleButton RLive4(29, 1);
RuleButton RLive5(32, 1);
RuleButton RLive6(35, 1);
RuleButton RLive7(38, 1);
RuleButton RLive8(41, 1);


RuleButton RDie0(17, 4);
RuleButton RDie1(20, 4);
RuleButton RDie2(23, 4);
RuleButton RDie3(26, 4);
RuleButton RDie4(29, 4);
RuleButton RDie5(32, 4);
RuleButton RDie6(35, 4);
RuleButton RDie7(38, 4);
RuleButton RDie8(41, 4);





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

	/*Update logic and inputs*/ {
		CW1.Update();
		BPause.Update(CW1);

		RLive0.Update(CW1.NtoLive, 0);
		RLive1.Update(CW1.NtoLive, 1);
		RLive2.Update(CW1.NtoLive, 2);
		RLive3.Update(CW1.NtoLive, 3);
		RLive4.Update(CW1.NtoLive, 4);
		RLive5.Update(CW1.NtoLive, 5);
		RLive6.Update(CW1.NtoLive, 6);
		RLive7.Update(CW1.NtoLive, 7);
		RLive8.Update(CW1.NtoLive, 8);

		RDie0.Update(CW1.NtoDie, 0);
		RDie1.Update(CW1.NtoDie, 1);
		RDie2.Update(CW1.NtoDie, 2);
		RDie3.Update(CW1.NtoDie, 3);
		RDie4.Update(CW1.NtoDie, 4);
		RDie5.Update(CW1.NtoDie, 5);
		RDie6.Update(CW1.NtoDie, 6);
		RDie7.Update(CW1.NtoDie, 7);
		RDie8.Update(CW1.NtoDie, 8);
	}

	/*Render*/ {
		CW1.Render();
		BPause.Render();

		RLive0.Render();
		RLive1.Render();
		RLive2.Render();
		RLive3.Render();
		RLive4.Render();
		RLive5.Render();
		RLive6.Render();
		RLive7.Render();
		RLive8.Render();

		RDie0.Render();
		RDie1.Render();
		RDie2.Render();
		RDie3.Render();
		RDie4.Render();
		RDie5.Render();
		RDie6.Render();
		RDie7.Render();
		RDie8.Render();
	}

	return true;
}


