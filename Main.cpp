#include <memory>
#include <unordered_map>

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOCOMM 1
#define NOMINMAX 1
#include <Windows.h>

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_TWindow
#define Uses_TView
#define Uses_TCheckBoxes
#define Uses_TRadioButtons
#define Uses_TSItem
#define Uses_TInputLine
#define Uses_TLabel
#include <tvision/tv.h>

#include "Player.h"
#include "Game logic.h"
#include "ConstructionFunction.h"

static constexpr int cmNewWin{ 200 };

class TTestApp : public TApplication
{
public:
	TTestApp() : TProgInit{ initStatusLine, initMenuBar,
		initDeskTop }
	{
	}

	static TMenuBar* initMenuBar(TRect r)
	{
		r.b.y = r.a.y + 1; // One line below the top
		return new TMenuBar{ r,
		*new TSubMenu{"~F~ile", kbAltF} +
		*new TMenuItem{"~N~ew", cmNewWin, kbF2, hcNoContext, "F2"} +
		newLine() + *new TMenuItem{"~E~x~it", cmQuit, kbAltX, hcNoContext, "Alt-X"} +
		*new TSubMenu{"~W~indow", kbAltW} + *new TMenuItem{"~N~ext", cmNext, kbF6, hcNoContext, "F6"} +
											*new TMenuItem{"~Z~oom", cmZoom, kbF5, hcNoContext, "F5" }
		};
	}

	static TStatusLine* initStatusLine(TRect r)
	{
		r.a.y = r.b.y - 1; // One line above the bottom

		return new TStatusLine{ r,
			*new TStatusDef{ 0, 0xFFFF } + // Help contexts
			*new TStatusItem{ "~Alt-X~ Exit", kbAltX, cmQuit } +
			*new TStatusItem{ "~Alt-F3~ Close", kbAltF3, cmClose } };
	}
};

int main()
{
	std::cout << "TUI test? ";
	char input{};
	std::cin >> input;
	
	if (input == 'y')
	{
		TTestApp test{};
		test.run();
	}

	else
	{
		// Enable support of cyrillic
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		auto roomMap{ constructRoomMap() };

		auto objectMap{ constructObjects(roomMap) };

		populateRooms(roomMap, objectMap);

		Player player{ roomMap.at("Стыковочный отсек").get() };

		bool gameIsOver{ false };
		while (!gameIsOver)
		{
			gameLoop(player);
		}
	}

	return 0;
}