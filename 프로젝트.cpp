/* lw, sw, add, sub, and, or, slt, beq */
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <TCHAR.H>
#include <string.h>
#define BUTTON_WIDTH 60
#define BUTTON_HEIGHT 30

#define LW 1
#define SW 2
#define ADD 3
#define SUB 4
#define AND 5
#define OR 6
#define SLT 7
#define BEQ 8

typedef struct Opcode {
	static const int LWten = 35;
	static const TCHAR LWtwo[7];
	static const int SWten = 43;
	static const TCHAR SWtwo[7];
	static const int BEQten = 4;
	static const TCHAR BEQtwo[7];
	static const int Rten = 0;
	static const TCHAR Rtwo[7];
} Opcode;
const TCHAR Opcode::LWtwo[7] = _T("100011");
const TCHAR Opcode::SWtwo[7] = _T("101011");
const TCHAR Opcode::BEQtwo[7] = _T("000100");
const TCHAR Opcode::Rtwo[7] = _T("000000");

typedef struct Funct {
	static const int ADDten = 32;
	static const TCHAR ADDtwo[7];
	static const int SUBten = 34;
	static const TCHAR SUBtwo[7];
	static const int ANDten = 36;
	static const TCHAR ANDtwo[7];
	static const int ORten = 37;
	static const TCHAR ORtwo[7];
	static const int SLTten = 42;
	static const TCHAR SLTtwo[7];
} Funct;
const TCHAR Funct::ADDtwo[7] = _T("100000");
const TCHAR Funct::SUBtwo[7] = _T("100010");
const TCHAR Funct::ANDtwo[7] = _T("100100");
const TCHAR Funct::ORtwo[7] = _T("100101");
const TCHAR Funct::SLTtwo[7] = _T("101010");

class Instruction {
public:
	int type;
	TCHAR machineLan[40];

	Instruction(int type) {
		this->type = type;
	}

	virtual TCHAR* getOpcode() { return NULL; };
	virtual TCHAR* getRt() { return NULL; };
	virtual TCHAR* getRs() { return NULL; };
	virtual TCHAR* getRd() { return NULL; };
	virtual TCHAR* getShamt() { return NULL; };
	virtual TCHAR* getFunct() { return NULL; };
	virtual TCHAR* getAddr() { return NULL; };

	virtual void setRtToBin() {};
	virtual void setRsToBin() {};
	virtual void setRdToBin() {};
	virtual void setAddrToBin() {};
};

class RType : public Instruction {
	TCHAR opcode[7], rs[6], rt[6], rd[6], shamt[6], funct[7];

public:
	RType(int type, TCHAR* opcode, TCHAR* rs, TCHAR* rt, TCHAR* rd, TCHAR* shamt, TCHAR* funct) : Instruction(type) {
		_tcscpy_s(this->opcode, _countof(this->opcode), opcode);
		_tcscpy_s(this->rs, _countof(this->rs), rs);
		_tcscpy_s(this->rt, _countof(this->rt), rt);
		_tcscpy_s(this->rd, _countof(this->rd), rd);
		_tcscpy_s(this->shamt, _countof(this->shamt), shamt);
		_tcscpy_s(this->funct, _countof(this->funct), funct);
	}

	virtual TCHAR* getOpcode() {
		return opcode;
	};
	virtual TCHAR* getRt() {
		return rt;
	};
	virtual TCHAR* getRs() {
		return rs;
	};
	virtual TCHAR* getRd() {
		return rd;
	};
	virtual TCHAR* getShamt() {
		return shamt;
	};
	virtual TCHAR* getFunct() {
		return funct;
	};

	virtual void setRtToBin() {
		int num = _tstoi(rt);
		int i, digit;
		int binary, result = 0;
		TCHAR tmp[6];

		_tcscpy_s(rt, _countof(rt), _T(""));
		for (i = 1, digit = 0; num > 0; i *= 10, digit++)
		{
			binary = num % 2;
			result += binary * i;
			num /= 2;
		}
		for (i = 1; i <= 5-digit; i++) {
			_tcscat_s(rt, _T("0"));
		}
		wsprintf(tmp, _T("%d"), result);
		_tcscat_s(rt, tmp);
	};
	virtual void setRsToBin() {
		int num = _tstoi(rs);
		int i, digit;
		int binary, result = 0;
		TCHAR tmp[6];

		_tcscpy_s(rs, _countof(rt), _T(""));
		for (i = 1, digit = 0; num > 0; i *= 10, digit++)
		{
			binary = num % 2;
			result += binary * i;
			num /= 2;
		}
		for (i = 1; i <= 5-digit; i++) {
			_tcscat_s(rs, _T("0"));
		}
		wsprintf(tmp, _T("%d"), result);
		_tcscat_s(rs, tmp);
	};
	virtual void setRdToBin() {
		int num = _tstoi(rd);
		int i, digit;
		int binary, result = 0;
		TCHAR tmp[6];

		_tcscpy_s(rd, _countof(rd), _T(""));
		for (i = 1, digit = 0; num > 0; i *= 10, digit++)
		{
			binary = num % 2;
			result += binary * i;
			num /= 2;
		}
		for (i = 1; i <= (5-digit); i++) {
			_tcscat_s(rd, _T("0"));
		}
		wsprintf(tmp, _T("%d"), result);
		_tcscat_s(rd, tmp);
	};
};

class IType : public Instruction {
	TCHAR opcode[7], rs[6], rt[6], address[17];

public:
	IType(int type, TCHAR* opcode, TCHAR* rs, TCHAR* rt, TCHAR* address) : Instruction(type) {
		_tcscpy_s(this->rt, _countof(this->rt), rt);
		_tcscpy_s(this->address, _countof(this->address), address);
		_tcscpy_s(this->rs, _countof(this->rs), rs);
		_tcscpy_s(this->opcode, _countof(this->opcode), opcode);
	}

	virtual TCHAR* getOpcode() {
		return opcode;
	};
	virtual TCHAR* getRt() {
		return rt;
	};
	virtual TCHAR* getRs() {
		return rs;
	};
	virtual TCHAR* getAddr() {
		return address;
	};

	virtual void setRtToBin() {
		int num = _tstoi(rt);
		int i, digit;
		int binary, result = 0;
		TCHAR tmp[6];

		_tcscpy_s(rt, _countof(rt), _T(""));
		for (i = 1, digit = 0; num > 0; i *= 10, digit++)
		{
			binary = num % 2;
			result += binary * i;
			num /= 2;
		}
		for (i = 1; i <= 5-digit; i++) {
			_tcscat_s(rt, _T("0"));
		}
		wsprintf(tmp, _T("%d"), result);
		_tcscat_s(rt, tmp);
	};
	virtual void setRsToBin() {
		int num = _tstoi(rs);
		int i, digit;
		int binary, result = 0;
		TCHAR tmp[6];

		_tcscpy_s(rs, _countof(rs), _T(""));
		for (i = 1, digit = 0; num > 0; i *= 10, digit++)
		{
			binary = num % 2;
			result += binary * i;
			num /= 2;
		}
		for (i = 1; i <= 5-digit; i++) {
			_tcscat_s(rs, _T("0"));
		}
		wsprintf(tmp, _T("%d"), result);
		_tcscat_s(rs, tmp);
	};
	virtual void setAddrToBin() {
		int num = _tstoi(address);
		int i, digit;
		int binary, result = 0;
		TCHAR tmp[17];

		_tcscpy_s(address, _countof(address), _T(""));
		for (i = 1, digit = 0; num > 0; i *= 10, digit++)
		{
			binary = num % 2;
			result += binary * i;
			num /= 2;
		}
		for (i = 1; i <= 16-digit; i++) {
			_tcscat_s(address, _T("0"));
		}
		wsprintf(tmp, _T("%d"), result);
		_tcscat_s(address, tmp);
	};
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM IParam);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX WndClass;
	hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("컴퓨터구조 학습도우미"),
		WS_OVERLAPPEDWINDOW,
		100,
		50,
		1100,
		650,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

#define IDC_BUTTON1 100
#define IDC_COMBO2 102
#define IDC_BUTTON2_INPUT 103
#define IDC_BUTTON2_FINISH 104
#define IDC_BUTTON2_DELETE 106
#define IDC_BUTTON3 107

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;
	RECT rc;
	RECT clientRect;

	// 컨트롤 윈도우
	static HWND hButton1;
	static HWND hCombo2, hButton2_input, hButton2_finish, hButton2_delete;
	static HWND hButton3;
	TCHAR editStr[100];
	static int comboIndex;

	// 명령어 집합
	static TCHAR instructions[10][40];
	static int instructionCount;
	static Instruction *instList[10];

	// 비트맵
	static HDC memDC;
	static HBITMAP loveBitmap, oldLoveBitmap;

	// 화면 타입
	static int type;
	static int stepProgressed;

	// 화면 윗 부분
	static RECT topRt, stepRt;
	static RECT topTextRt, step1Rt, step2Rt, step3Rt, step4Rt, step5Rt;
	static HFONT topTextFont, topTextOldFont;
	static HFONT stepFont, stepOldFont;
	static HFONT step1Font, step1OldFont, step2Font, step2OldFont, step3Font, step3OldFont;
	static HWND hEdit;

	// 화면 아래 부분
	static RECT bottomRt;
	static HFONT bottomTextFont, bottomTextOldFont;

	// 두 번째 화면
	static RECT exOfInst;

	// 세 번째 화면
	static RECT commandInputtedRt, inputToMachineLanRt, machineLanRt;

	switch (iMsg)
	{
	case WM_CREATE:
		// 타입을 1로 초기화
		type = stepProgressed = 1;
		// 명령어 개수 0으로 초기화
		instructionCount = 0;
		// comboindex를 0으로 초기화
		comboIndex = 0;
		// 윈도우 컨트롤 생성
		hButton1 = CreateWindow(
			_T("button"),
			_T("시작"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0,
			0,
			100,
			25,
			hwnd,
			(HMENU)IDC_BUTTON1,
			hInst,
			NULL
		);
		hCombo2 = CreateWindow(
			_T("combobox"),
			NULL,
			WS_CHILD | WS_VISIBLE | CBS_SIMPLE,
			0,
			0,
			200,
			300,
			hwnd,
			(HMENU)IDC_COMBO2,
			hInst,
			NULL
		);
		hButton2_finish = CreateWindow(
			_T("button"),
			_T("완료"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0,
			0,
			70,
			25,
			hwnd,
			(HMENU)IDC_BUTTON2_FINISH,
			hInst,
			NULL
		);
		hButton2_input = CreateWindow(
			_T("button"),
			_T("입력"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0,
			0,
			70,
			25,
			hwnd,
			(HMENU)IDC_BUTTON2_INPUT,
			hInst,
			NULL
		);
		hButton2_delete = CreateWindow(
			_T("button"),
			_T("삭제"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0,
			0,
			80,
			25,
			hwnd,
			(HMENU)IDC_BUTTON2_DELETE,
			hInst,
			NULL
		);
		hButton3 = CreateWindow(
			_T("button"),
			_T("종료"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0,
			0,
			100,
			25,
			hwnd,
			(HMENU)IDC_BUTTON3,
			hInst,
			NULL
		);

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		// 윈도우 화면 크기 구하기
		GetClientRect(hwnd, &rt);

		//////////////////////////
		///* 화면 윗부분 영역 *///
		//////////////////////////

		// made by
		SetTextColor(hdc, RGB(128, 128, 128));
		DrawText(hdc, _T("@SimDaSong"), -1, &rt, DT_RIGHT);
		SetTextColor(hdc, RGB(0, 0, 0));

		// 경계선 
		topRt = rt;
		topRt.bottom = 95;
		MoveToEx(hdc, rt.left, topRt.bottom, NULL);
		LineTo(hdc, rt.right, topRt.bottom);

		// 메인 텍스트
		topTextRt = topRt;
		topTextRt.top = 10;
		topTextRt.left = 30;
		topTextRt.right = 170;
		topTextRt.bottom = 95;
		topTextFont = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, _T("맑은 고딕"));
		topTextOldFont = (HFONT)SelectObject(hdc, topTextFont);
		DrawText(hdc, _T("컴퓨터구조\n학습도우미"), -1, &topTextRt, DT_CENTER);
		SelectObject(hdc, topTextOldFont);
		DeleteObject(topTextFont);

		// stepRt
		stepRt = topRt;
		stepRt.left = rt.right - 800;
		if (stepRt.left - topTextRt.right <= 65) stepRt.left = topTextRt.right + 65;
		else if (stepRt.left - topTextRt.right >= 200) stepRt.left = topTextRt.right + 200;
		stepRt.right = rt.right - 225;
		if (stepRt.right - stepRt.left >= 700) stepRt.right = stepRt.left + 700;

		if (stepRt.right - stepRt.left <= 320) stepRt.right = stepRt.left + 320;
		stepRt.top = 20;

		// step 텍스트
		topTextFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, _T("맑은 고딕"));
		topTextOldFont = (HFONT)SelectObject(hdc, topTextFont);

		step1Rt = stepRt;
		step1Rt.right = stepRt.left + (stepRt.right - stepRt.left) / 3;
		step2Rt = step1Rt;
		step2Rt.left = step1Rt.right;
		step2Rt.right = step1Rt.right + (stepRt.right - stepRt.left) / 3;
		step3Rt = step2Rt;
		step3Rt.left = step2Rt.right;
		step3Rt.right = stepRt.right;


		DrawText(hdc, _T("step1"), -1, &step1Rt, DT_CENTER);
		step1Rt.top += 35;
		DrawText(hdc, _T("초기화면"), -1, &step1Rt, DT_CENTER);

		if (stepProgressed == 1)
			SetTextColor(hdc, RGB(128, 128, 128));

		DrawText(hdc, _T("step2"), -1, &step2Rt, DT_CENTER);
		step2Rt.top += 35;
		DrawText(hdc, _T("어셈블리\n명령어"), -1, &step2Rt, DT_CENTER);
		
		if (stepProgressed == 2)
			SetTextColor(hdc, RGB(128, 128, 128));

		DrawText(hdc, _T("step3"), -1, &step3Rt, DT_CENTER);
		step3Rt.top += 35;
		DrawText(hdc, _T("기계어\n형태"), -1, &step3Rt, DT_CENTER);
		
		SelectObject(hdc, topTextOldFont);
		DeleteObject(topTextFont);

		SetTextColor(hdc, RGB(0, 0, 0));

		// 진행 상황
		int circleX, circleY;
		circleY = stepRt.top + (stepRt.bottom - stepRt.top) / 2 - 11;

		MoveToEx(hdc, step1Rt.left + (step1Rt.right - step1Rt.left) / 2, circleY, NULL);
		LineTo(hdc, step3Rt.left + (step3Rt.right - step3Rt.left) / 2, circleY);

		circleX = step1Rt.left + (step1Rt.right - step1Rt.left) / 2;
		Ellipse(hdc, circleX - 5, circleY - 5, circleX + 5, circleY + 5);
		circleX = step2Rt.left + (step2Rt.right - step2Rt.left) / 2;
		Ellipse(hdc, circleX - 5, circleY - 5, circleX + 5, circleY + 5);
		circleX = step3Rt.left + (step3Rt.right - step3Rt.left) / 2;
		Ellipse(hdc, circleX - 5, circleY - 5, circleX + 5, circleY + 5);
		
		bottomRt = rt;
		bottomRt.top = topRt.bottom;

		rc = bottomRt;

		// bottom 폰트 설정. 에디트 컨트롤의 폰트를 설정하기 위함
		bottomTextFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _T("맑은 고딕"));
		bottomTextOldFont = (HFONT)SelectObject(hdc, bottomTextFont);

		switch (type) {
		case 1:
			///* 초기 화면 *///

			// 다른 윈도우 컨트롤들이 보이지 않게
			ShowWindow(hButton2_input, SW_HIDE);
			ShowWindow(hButton2_finish, SW_HIDE);
			ShowWindow(hButton2_delete, SW_HIDE);
			ShowWindow(hCombo2, SW_HIDE);
			ShowWindow(hButton3, SW_HIDE);
			
			rc.top += (rc.bottom - rc.top) / 4;
			DrawText(hdc, _T("안녕하세요!\n저는 컴퓨터구조 학습도우미입니다.\n시작하시려면 아래 버튼을 눌러주세요."), -1, &rc, DT_CENTER);
			rc.top += 70;
			MoveWindow(hButton1, (rt.right - rt.left - BUTTON_WIDTH) / 2, rc.top, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
			ShowWindow(hButton1, SW_SHOW);
			break;
		case 2:
			///* 시작 버튼을 눌렀을 때 *///

			// 다른 윈도우 컨트롤들이 보이지 않게
			ShowWindow(hButton1, SW_HIDE);
			ShowWindow(hButton3, SW_HIDE);
			
			rc.top += (rc.bottom - rc.top) / 15;
			DrawText(hdc, _T("어셈블리 명령어를 입력해주세요(최대 10개)\n입력 가능한 명령어는 sw, lw, add, sub, and, or, slt, beq 입니다.\n(완료 버튼을 누르면 다음 화면으로 넘어갑니다.)"), -1, &rc, DT_CENTER);

			rc.top += (rc.bottom - rc.top) / 6;

			exOfInst = rc;
			exOfInst.left = rt.left;
			exOfInst.right = (rt.right - rt.left) / 2 - 70;
			exOfInst.top += 5;
			DrawText(hdc,
				_T("※ 명령어 형식의 예 ※\n\nlw $1,5($2)\nadd $1,$2,$3\nslt $1,$2,$3\nbeq $1,$2,5\n\n변수 피연산자는 '$'+'숫자' 형태만 가능하며\n변위는 '숫자' 형태만 가능합니다.\n피연산자 사이에는\n띄어쓰기가 없어야 합니다!"),
				-1, &exOfInst, DT_CENTER);

			MoveWindow(hButton2_input, (rt.right - rt.left) / 2 + 110, rc.top, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
			ShowWindow(hButton2_input, SW_SHOW);
			MoveWindow(hButton2_finish, (rt.right - rt.left) / 2 - 35, rc.top + 250 + 20, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
			ShowWindow(hButton2_finish, SW_SHOW);
			MoveWindow(hButton2_delete, (rt.right - rt.left) / 2 + 110, rc.top + 30, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
			ShowWindow(hButton2_delete, SW_SHOW);
			MoveWindow(hCombo2, (rt.right - rt.left) / 2 - 100, rc.top, 200, 250, TRUE);
			ShowWindow(hCombo2, SW_SHOW);
			break;
		case 3:
			///* 완료 버튼을 눌렀을 때 *///

			// 다른 윈도우 컨트롤들이 보이지 않게
			ShowWindow(hButton1, SW_HIDE);
			ShowWindow(hButton2_input, SW_HIDE);
			ShowWindow(hButton2_finish, SW_HIDE);
			ShowWindow(hButton2_delete, SW_HIDE);
			ShowWindow(hCombo2, SW_HIDE);

			MoveWindow(hButton3, rt.right - rt.left - 10 - BUTTON_WIDTH, rt.bottom - rt.top - 10 - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
			ShowWindow(hButton3, SW_SHOW);

			rc.top += (rc.bottom - rc.top) / 20;
			DrawText(hdc, _T("해당 언어의 기계어 형태는 다음과 같습니다."), -1, &rc, DT_CENTER);

			rc.top += (rc.bottom - rc.top) / 20 + 10;
			rc.bottom -= (rc.bottom - rc.top) / 10;
			commandInputtedRt = inputToMachineLanRt = rc;

			commandInputtedRt.left += (rt.right - rt.left) / 10;
			commandInputtedRt.right = (rt.right - rt.left) / 2 - 100;
			if (commandInputtedRt.right - commandInputtedRt.left >= 400)
				commandInputtedRt.left = commandInputtedRt.right - 400;
			Rectangle(hdc, commandInputtedRt.left, commandInputtedRt.top, commandInputtedRt.right, commandInputtedRt.bottom);
			commandInputtedRt.top -= 10;
			DrawText(hdc, _T("입력 받은 명령어"), -1, &commandInputtedRt, DT_CENTER);
			commandInputtedRt.top += 15;
			for (int i = 0; i < instructionCount; i++) {
				commandInputtedRt.top += 33;
				DrawText(hdc, instructions[i], -1, &commandInputtedRt, DT_CENTER | DT_VCENTER);
			}

			inputToMachineLanRt.left = (rt.right - rt.left) / 2 - 60;
			inputToMachineLanRt.right = rt.right - commandInputtedRt.left;
			if (inputToMachineLanRt.right - inputToMachineLanRt.left <= 400)
				inputToMachineLanRt.right = inputToMachineLanRt.left + 400;
			Rectangle(hdc, inputToMachineLanRt.left, inputToMachineLanRt.top, inputToMachineLanRt.right, inputToMachineLanRt.bottom);
			inputToMachineLanRt.top -= 10;
			DrawText(hdc, _T("입력 받은 명령어의\n기계어 형태"), -1, &inputToMachineLanRt, DT_CENTER);
			
			inputToMachineLanRt.left += 20;
			inputToMachineLanRt.right -= 20;
			machineLanRt = inputToMachineLanRt;
			machineLanRt.top += 25;

			for (int i = 0; i < instructionCount; i++) {
				machineLanRt.left = inputToMachineLanRt.left;
				machineLanRt.right = inputToMachineLanRt.right;
				machineLanRt.top += 20;
				machineLanRt.bottom = machineLanRt.top + 27;

				switch (instList[i]->type) {
				case LW:
					Rectangle(hdc, inputToMachineLanRt.left, machineLanRt.top, machineLanRt.right, machineLanRt.bottom);

					machineLanRt.top += 3;

					// opcode
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getOpcode(), -1, &machineLanRt, DT_CENTER);

					// rs
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRs(), -1, &machineLanRt, DT_CENTER);

					// rt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRt(), -1, &machineLanRt, DT_CENTER);

					// address
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = inputToMachineLanRt.right;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getAddr(), -1, &machineLanRt, DT_CENTER);

					break;
				case SW:					
					Rectangle(hdc, inputToMachineLanRt.left, machineLanRt.top, machineLanRt.right, machineLanRt.bottom);

					machineLanRt.top += 3;

					// opcode
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getOpcode(), -1, &machineLanRt, DT_CENTER);
					
					// rs
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRs(), -1, &machineLanRt, DT_CENTER);
					
					// rt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRt(), -1, &machineLanRt, DT_CENTER);
					
					// address
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = inputToMachineLanRt.right;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getAddr(), -1, &machineLanRt, DT_CENTER);
					
					break;
				case ADD:
					Rectangle(hdc, inputToMachineLanRt.left, machineLanRt.top, machineLanRt.right, machineLanRt.bottom);

					machineLanRt.top += 3;

					// opcode
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getOpcode(), -1, &machineLanRt, DT_CENTER);

					// rs
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRs(), -1, &machineLanRt, DT_CENTER);

					// rt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRt(), -1, &machineLanRt, DT_CENTER);

					// rd
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRd(), -1, &machineLanRt, DT_CENTER);

					// shamt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getShamt(), -1, &machineLanRt, DT_CENTER);

					// funct
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = inputToMachineLanRt.right;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getFunct(), -1, &machineLanRt, DT_CENTER);
					
					break;
				case SUB:
					Rectangle(hdc, inputToMachineLanRt.left, machineLanRt.top, machineLanRt.right, machineLanRt.bottom);

					machineLanRt.top += 3;

					// opcode
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getOpcode(), -1, &machineLanRt, DT_CENTER);

					// rs
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRs(), -1, &machineLanRt, DT_CENTER);

					// rt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRt(), -1, &machineLanRt, DT_CENTER);

					// rd
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRd(), -1, &machineLanRt, DT_CENTER);

					// shamt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getShamt(), -1, &machineLanRt, DT_CENTER);

					// funct
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = inputToMachineLanRt.right;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getFunct(), -1, &machineLanRt, DT_CENTER);

					break;
				case AND:
					Rectangle(hdc, inputToMachineLanRt.left, machineLanRt.top, machineLanRt.right, machineLanRt.bottom);

					machineLanRt.top += 3;

					// opcode
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getOpcode(), -1, &machineLanRt, DT_CENTER);

					// rs
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRs(), -1, &machineLanRt, DT_CENTER);

					// rt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRt(), -1, &machineLanRt, DT_CENTER);

					// rd
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRd(), -1, &machineLanRt, DT_CENTER);

					// shamt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getShamt(), -1, &machineLanRt, DT_CENTER);

					// funct
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = inputToMachineLanRt.right;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getFunct(), -1, &machineLanRt, DT_CENTER);

					break;
				case OR:
					Rectangle(hdc, inputToMachineLanRt.left, machineLanRt.top, machineLanRt.right, machineLanRt.bottom);

					machineLanRt.top += 3;

					// opcode
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getOpcode(), -1, &machineLanRt, DT_CENTER);

					// rs
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRs(), -1, &machineLanRt, DT_CENTER);

					// rt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRt(), -1, &machineLanRt, DT_CENTER);

					// rd
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRd(), -1, &machineLanRt, DT_CENTER);

					// shamt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getShamt(), -1, &machineLanRt, DT_CENTER);

					// funct
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = inputToMachineLanRt.right;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getFunct(), -1, &machineLanRt, DT_CENTER);

					break;
				case SLT:
					Rectangle(hdc, inputToMachineLanRt.left, machineLanRt.top, machineLanRt.right, machineLanRt.bottom);

					machineLanRt.top += 3;

					// opcode
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getOpcode(), -1, &machineLanRt, DT_CENTER);

					// rs
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRs(), -1, &machineLanRt, DT_CENTER);

					// rt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRt(), -1, &machineLanRt, DT_CENTER);

					// rd
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRd(), -1, &machineLanRt, DT_CENTER);

					// shamt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getShamt(), -1, &machineLanRt, DT_CENTER);

					// funct
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = inputToMachineLanRt.right;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getFunct(), -1, &machineLanRt, DT_CENTER);

					break;
				case BEQ:
					Rectangle(hdc, inputToMachineLanRt.left, machineLanRt.top, machineLanRt.right, machineLanRt.bottom);

					machineLanRt.top += 3;

					// opcode
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getOpcode(), -1, &machineLanRt, DT_CENTER);

					// rs
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRs(), -1, &machineLanRt, DT_CENTER);

					// rt
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = machineLanRt.left + (inputToMachineLanRt.right - inputToMachineLanRt.left) / 6;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getRt(), -1, &machineLanRt, DT_CENTER);

					// address
					machineLanRt.left = machineLanRt.right;
					machineLanRt.right = inputToMachineLanRt.right;
					MoveToEx(hdc, machineLanRt.right, machineLanRt.top - 3, NULL);
					LineTo(hdc, machineLanRt.right, machineLanRt.bottom);
					DrawText(hdc, instList[i]->getAddr(), -1, &machineLanRt, DT_CENTER);
					break;
				}
				machineLanRt.top += 10;
			}
			break;
		}

		// 버튼 글꼴 설정
		SendMessage(hButton1, WM_SETFONT, (WPARAM)bottomTextFont, (LPARAM)TRUE);
		SendMessage(hButton2_delete, WM_SETFONT, (WPARAM)bottomTextFont, (LPARAM)TRUE);
		SendMessage(hButton2_finish, WM_SETFONT, (WPARAM)bottomTextFont, (LPARAM)TRUE);
		SendMessage(hButton2_input, WM_SETFONT, (WPARAM)bottomTextFont, (LPARAM)TRUE);
		SendMessage(hButton3, WM_SETFONT, (WPARAM)bottomTextFont, (LPARAM)TRUE);
		
		// bottom 폰트 설정 해제
		SelectObject(hdc, bottomTextOldFont);
		DeleteObject(bottomTextFont);

		EndPaint(hwnd, &ps);
		break;
	case WM_SIZE:
		GetWindowRect(hwnd, &clientRect);
		if (clientRect.right - clientRect.left <= 700)
			clientRect.right = clientRect.left + 700;
		if (clientRect.bottom - clientRect.top <= 700)
			clientRect.bottom = clientRect.top + 700;
		MoveWindow(hwnd, clientRect.left, clientRect.top, clientRect.right-clientRect.left, clientRect.bottom - clientRect.top, TRUE);

		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			// 확인 버튼 누르면
		case IDC_BUTTON1:
			type = 2;
			if (stepProgressed < 2)
				stepProgressed = 2;

			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		case IDC_BUTTON2_INPUT:
			if (SendMessage(hCombo2, CB_GETCOUNT, 0, 0) >= 10) {
				MessageBox(hwnd, _T("더 이상 입력 하실 수 없습니다!"), _T("에러"), MB_OK);
				break;
			}
			GetDlgItemText(hwnd, IDC_COMBO2, editStr, 100);
			if (_tcscmp(editStr, _T(""))) {
				
				static TCHAR *token[4];
				TCHAR instructionCpy[40];
				
				GetDlgItemText(hwnd, IDC_COMBO2, instructionCpy, 100);
				token[0] = _tcstok(instructionCpy, _T("$")); // 명령어 형식

				if (!_tcscmp(token[0], _T("lw "))) { // 명령어가 lw 이면
					token[1] = _tcstok(NULL, _T(",")); // rt
					token[2] = _tcstok(NULL, _T("$")); // address
					token[3] = _tcstok(NULL, _T(")")); // rs

					token[2] = _tcstok(token[2], _T("("));

					if (!token[1] || !token[2] || !token[3])
						if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
							return 0;
				}
				else if (!_tcscmp(token[0], _T("sw "))) { // 명령어가 sw 이면
					token[1] = _tcstok(NULL, _T(",")); // rt
					token[2] = _tcstok(NULL, _T("$")); // address
					token[3] = _tcstok(NULL, _T(")")); // rs

					token[2] = _tcstok(token[2], _T("("));

					if (!token[1] || !token[2] || !token[3])
						if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
							return 0;
				}
				else if (!_tcscmp(token[0], _T("add "))) { // 명령어가 add 이면
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					if (!token[1] || !token[2] || !token[3])
						if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
							return 0;
				}
				else if (!_tcscmp(token[0], _T("sub "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					if (!token[1] || !token[2] || !token[3])
						if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
							return 0;
				}
				else if (!_tcscmp(token[0], _T("and "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					if (!token[1] || !token[2] || !token[3])
						if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
							return 0;
				}
				else if (!_tcscmp(token[0], _T("or "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					if (!token[1] || !token[2] || !token[3])
						if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
							return 0;
				}
				else if (!_tcscmp(token[0], _T("slt "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					if (!token[1] || !token[2] || !token[3])
						if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
							return 0;
				}
				else if (!_tcscmp(token[0], _T("beq "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T(",")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));

					if (!token[1] || !token[2] || !token[3])
						if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
							return 0;
				}
				else {
					if (MessageBox(hwnd, _T("잘못된 명령어 형식입니다!"), _T("오류"), MB_OK) == IDOK)
						return 0;
				}
				SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)editStr);
			}
			SendMessage(hCombo2, CB_SETCURSEL, 11, 0);
			break;
		case IDC_BUTTON2_DELETE:
			comboIndex = SendMessage(hCombo2, CB_GETCURSEL, 0, 0);
			SendMessage(hCombo2, CB_DELETESTRING, comboIndex, 0);
			break;
		case IDC_BUTTON2_FINISH:
			instructionCount = SendMessage(hCombo2, CB_GETCOUNT, 0, 0);

			if (instructionCount <= 0) {
				MessageBox(hwnd, _T("명령어를 한 개 이상 입력하셔야 합니다!"), _T("경고"), MB_OK);
				return 0;
			}

			static TCHAR *token[4];
			TCHAR instructionCpy[10][40];
			for (int i = 0; i < instructionCount; i++) {
				SendMessage(hCombo2, CB_GETLBTEXT, i, (LPARAM)instructions[i]);
				SendMessage(hCombo2, CB_GETLBTEXT, i, (LPARAM)instructionCpy[i]);
				token[0] = _tcstok(instructionCpy[i], _T("$")); // 명령어 형식

				if (!_tcscmp(token[0], _T("lw "))) { // 명령어가 lw 이면
					token[1] = _tcstok(NULL, _T(",")); // rt
					token[2] = _tcstok(NULL, _T("$")); // address
					token[3] = _tcstok(NULL, _T(")")); // rs
					
					token[2] = _tcstok(token[2], _T("("));
					
					instList[i] = new IType(LW, (TCHAR*)Opcode::LWtwo, token[3], token[1], token[2]);
					instList[i]->setRsToBin();
					instList[i]->setRtToBin();
					instList[i]->setAddrToBin();
				}
				else if (!_tcscmp(token[0], _T("sw "))) { // 명령어가 sw 이면
					token[1] = _tcstok(NULL, _T(",")); // rt
					token[2] = _tcstok(NULL, _T("$")); // address
					token[3] = _tcstok(NULL, _T(")")); // rs

					token[2] = _tcstok(token[2], _T("("));

					instList[i] = new IType(SW, (TCHAR*)Opcode::SWtwo, token[3], token[1], token[2]);
					instList[i]->setRsToBin();
					instList[i]->setRtToBin();
					instList[i]->setAddrToBin();
				}
				else if (!_tcscmp(token[0], _T("add "))) { // 명령어가 add 이면
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					instList[i] = new RType(ADD, (TCHAR*)Opcode::Rtwo, token[2], token[3], token[1], (TCHAR*)_T("00000"), (TCHAR*)Funct::ADDtwo);
				
					instList[i]->setRsToBin();
					instList[i]->setRtToBin();
					instList[i]->setRdToBin();
				}
				else if (!_tcscmp(token[0], _T("sub "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					instList[i] = new RType(SUB, (TCHAR*)Opcode::Rtwo, token[2], token[3], token[1], (TCHAR*)_T("00000"), (TCHAR*)Funct::SUBtwo);

					instList[i]->setRsToBin();
					instList[i]->setRtToBin();
					instList[i]->setRdToBin();
				}
				else if (!_tcscmp(token[0], _T("and "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					instList[i] = new RType(AND, (TCHAR*)Opcode::Rtwo, token[2], token[3], token[1], (TCHAR*)_T("00000"), (TCHAR*)Funct::ANDtwo);
				
					instList[i]->setRsToBin();
					instList[i]->setRtToBin();
					instList[i]->setRdToBin();
				}
				else if (!_tcscmp(token[0], _T("or "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					instList[i] = new RType(OR, (TCHAR*)Opcode::Rtwo, token[2], token[3], token[1], (TCHAR*)_T("00000"), (TCHAR*)Funct::ORtwo);
				
					instList[i]->setRsToBin();
					instList[i]->setRtToBin();
					instList[i]->setRdToBin();
				}
				else if (!_tcscmp(token[0], _T("slt "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T("$")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));
					token[2] = _tcstok(token[2], _T(","));

					instList[i] = new RType(SLT, (TCHAR*)Opcode::Rtwo, token[2], token[3], token[1], (TCHAR*)_T("00000"), (TCHAR*)Funct::SLTtwo);
				
					instList[i]->setRsToBin();
					instList[i]->setRtToBin();
					instList[i]->setRdToBin();
				}
				else if (!_tcscmp(token[0], _T("beq "))) {
					token[1] = _tcstok(NULL, _T("$")); // rd
					token[2] = _tcstok(NULL, _T(",")); // rs
					token[3] = _tcstok(NULL, _T("\0")); // rt

					token[1] = _tcstok(token[1], _T(","));

					instList[i] = new IType(BEQ, (TCHAR*)Opcode::BEQtwo, token[1], token[2], token[3]);

					instList[i]->setRsToBin();
					instList[i]->setRtToBin();
					instList[i]->setAddrToBin();
				}
			}
			type = 3;
			if (stepProgressed < 3)
				stepProgressed = 3;

			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		case IDC_BUTTON3:
			if (MessageBox(hwnd, _T("정말 종료하시겠습니까?"), _T("확인"), MB_YESNO | MB_DEFBUTTON1) == IDNO) {
				return 0;
			}
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		int mouseX, mouseY;
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		
		if (step1Rt.left <= mouseX && mouseX <= step1Rt.right &&
			step1Rt.top <= mouseY && mouseY <= step1Rt.bottom) {
			type = 1;
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		else if (step2Rt.left <= mouseX && mouseX <= step2Rt.right &&
			step2Rt.top <= mouseY && mouseY <= step2Rt.bottom
			&& stepProgressed >= 2) {
			type = 2;
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		else if (step3Rt.left <= mouseX && mouseX <= step3Rt.right &&
			step3Rt.top <= mouseY && mouseY <= step3Rt.bottom
			&&stepProgressed == 3) {
			type = 3;
			InvalidateRgn(hwnd, NULL, TRUE);
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hwnd, _T("정말 종료하시겠습니까?"), _T("확인"), MB_YESNO | MB_DEFBUTTON1) == IDNO) {
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		delete[] instructions;
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}