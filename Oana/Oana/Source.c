#include <windows.h>
#include <stdlib.h>
//#include "resource.h"

#define ID_RADIO1 1004
#define ID_RADIO2 1005
#define ID_RADIO3 1006
#define ID_RADIO4 1007
#define ID_RADIO5 1008
#define ID_RADIO6 1009
#define ID_EDIT1 1010 //edit nr. muchii
#define ID_BUTON1 1011 //buton validare nr. muchii
#define ID_STATIC1 1012 //static nr much
#define ID_EDIT2 1013 //edit muchii
#define ID_BUTON2 1014 //edit validare muchie
#define ID_STATIC2 1015 //static muchii
#define ID_BUTON3 1016 //buton selectare matrice
#define ID_BUTON4 1017 //buton selectare lista
#define ID_BUTON5 1018 //buton selectare parcurgere latime

typedef struct nod
{
	int info;
	struct nod *next;
}nod;
int o, vectparc[16];

const char g_szClassName[] = "myWindowClass";
HBITMAP hBitmap = NULL;

void DrawLines(HDC hDC,int muchie)
{
	switch (muchie)
	{
	case 12:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 650, 190); break; }
	case 21:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 650, 190); break; }
	case 13:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 660, 360); break; }
	case 31:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 660, 360); break; }
	case 14:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 452, 425); break; }
	case 41:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 452, 425); break; }
	case 15:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 280, 360); break; }
	case 51:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 280, 360); break; }
	case 16:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 270, 206); break; }
	case 61:{MoveToEx(hDC, 450, 125, NULL); LineTo(hDC, 270, 206); break; }
	case 23:{MoveToEx(hDC, 650, 190, NULL); LineTo(hDC, 660, 360); break; }
	case 32:{MoveToEx(hDC, 650, 190, NULL); LineTo(hDC, 660, 360); break; }
	case 24:{MoveToEx(hDC, 650, 190, NULL); LineTo(hDC, 452, 425); break; }
	case 42:{MoveToEx(hDC, 650, 190, NULL); LineTo(hDC, 452, 425); break; }
	case 25:{MoveToEx(hDC, 650, 190, NULL); LineTo(hDC, 280, 360); break; }
	case 52:{MoveToEx(hDC, 650, 190, NULL); LineTo(hDC, 280, 360); break; }
	case 26:{MoveToEx(hDC, 650, 190, NULL); LineTo(hDC, 270, 206); break; }
	case 62:{MoveToEx(hDC, 650, 190, NULL); LineTo(hDC, 270, 206); break; }
	case 34:{MoveToEx(hDC, 660, 360, NULL); LineTo(hDC, 452, 425); break; }
	case 43:{MoveToEx(hDC, 660, 360, NULL); LineTo(hDC, 452, 425); break; }
	case 35:{MoveToEx(hDC, 660, 360, NULL); LineTo(hDC, 280, 360); break; }
	case 53:{MoveToEx(hDC, 660, 360, NULL); LineTo(hDC, 280, 360); break; }
	case 36:{MoveToEx(hDC, 660, 360, NULL); LineTo(hDC, 270, 206); break; }
	case 63:{MoveToEx(hDC, 660, 360, NULL); LineTo(hDC, 270, 206); break; }
	case 45:{MoveToEx(hDC, 452, 425, NULL); LineTo(hDC, 280, 360); break; }
	case 54:{MoveToEx(hDC, 452, 425, NULL); LineTo(hDC, 280, 360); break; }
	case 46:{MoveToEx(hDC, 452, 425, NULL); LineTo(hDC, 270, 206); break; }
	case 64:{MoveToEx(hDC, 452, 425, NULL); LineTo(hDC, 270, 206); break; }
	case 56:{MoveToEx(hDC, 280, 360, NULL); LineTo(hDC, 270, 206); break; }
	case 65:{MoveToEx(hDC, 280, 360, NULL); LineTo(hDC, 270, 206); break; }
	}
}

void adauga_in_coada(nod **prim, nod **ultim, int s)
{
	nod *p;
	p = (nod*)malloc(sizeof(nod));
	p->info = s;
	p->next = NULL;
	if (*prim == NULL)
	{
		*prim = p;
		*ultim = p;
	}
	else
	{
		(*ultim)->next = p;
		*ultim = p;
	}
}

void explorare_latime(int s, int M[][7])
{
	int vizitate[10];
	nod *prim = NULL, *ultim = NULL;
	int i, v, w;
	o = 1;
	for (i = 1; i <= 6; i++) vizitate[i] = 0;
	vizitate[s] = 1;
	adauga_in_coada(&prim, &ultim, s);
	while (prim != NULL)
	{
		v = prim->info;
		for (w = 1; w <= 6; w++)
		if (M[v][w] == 1 && vizitate[w] == 0)
		{
			vizitate[w] = 1;
			vectparc[o] = v * 10 + w;
			o++;
			adauga_in_coada(&prim, &ultim, w);
		}
		prim = prim->next;
	}
}


// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int nrm=0,m[15],i=1,G[7][7],selected=0,ml,nodstart=0,desenlatime=0;
	HWND hEdit;
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
	{
					   DeleteObject(hBitmap);
					   PostQuitMessage(0);
					   break;
	}
	case WM_CREATE:
	{
					  hBitmap = (HBITMAP)LoadImage(NULL, "pic.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

					  for (int k = 1; k <= 6; k++) for (int l = 1; l <= 6; l++) G[k][l] = 0;
					  //for (int k = 1; k <= 16; k++) vectparc[k] = 0;
					  ///////RADIO BUTTON 1
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 450, 125, 15, 15, hwnd, (HMENU)ID_RADIO1, NULL, NULL);
					  if (hEdit == NULL) MessageBox(hwnd, "Nu a fost posibila crearea butonului Radio1", "Eroare", MB_OK | MB_ICONERROR);

					  ///////RADIO BUTTON 2
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 650, 190, 15, 15, hwnd, (HMENU)ID_RADIO2, NULL, NULL);
					  if (hEdit == NULL) MessageBox(hwnd, "Nu a fost posibila crearea butonului Radio2", "Eroare", MB_OK | MB_ICONERROR);

					  ///////RADIO BUTTON 3
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 660, 360, 15, 15, hwnd, (HMENU)ID_RADIO3, NULL, NULL);
					  if (hEdit == NULL) MessageBox(hwnd, "Nu a fost posibila crearea butonului Radio3", "Eroare", MB_OK | MB_ICONERROR);

					  ///////RADIO BUTTON 4
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 452, 425, 15, 15, hwnd, (HMENU)ID_RADIO4, NULL, NULL);
					  if (hEdit == NULL) MessageBox(hwnd, "Nu a fost posibila crearea butonului Radio4", "Eroare", MB_OK | MB_ICONERROR);

					  ///////RADIO BUTTON 5
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 280, 360, 15, 15, hwnd, (HMENU)ID_RADIO5, NULL, NULL);
					  if (hEdit == NULL) MessageBox(hwnd, "Nu a fost posibila crearea butonului Radio5", "Eroare", MB_OK | MB_ICONERROR);

					  ///////RADIO BUTTON 6
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 270, 206, 15, 15, hwnd, (HMENU)ID_RADIO6, NULL, NULL);
					  if (hEdit == NULL) MessageBox(hwnd, "Nu a fost posibila crearea butonului Radio6", "Eroare", MB_OK | MB_ICONERROR);
					  
					  //////////Buton aceptare numar muchii
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Validare", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 200, 50, 65, 25, hwnd, (HMENU)ID_BUTON1, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creat butonul", "Eroare", MB_OK | MB_ICONERROR);

					  //////////EDIT NUMAR MUCHII GRAF
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER, 110, 50, 50, 25, hwnd, (HMENU)ID_EDIT1, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creata caseta", "Eroare", MB_OK | MB_ICONERROR);

					  //////////STATIC TEXT 1
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "STATIC", "Numar muchii", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 50, 100, 25, hwnd, (HMENU)ID_STATIC1, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creata caseta", "Eroare", MB_OK | MB_ICONERROR);


					  //////////Buton aceptare muchii
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "OK", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 200, 100, 50, 25, hwnd, (HMENU)ID_BUTON2, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creat butonul", "Eroare", MB_OK | MB_ICONERROR);

					  //////////EDIT MUCHII GRAF
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER, 110, 100, 50, 25, hwnd, (HMENU)ID_EDIT2, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creata caseta", "Eroare", MB_OK | MB_ICONERROR);

					  //////////STATIC TEXT 2
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "STATIC", "Muchii", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 100, 55, 25, hwnd, (HMENU)ID_STATIC2, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creata caseta", "Eroare", MB_OK | MB_ICONERROR);

					  /////////Buton selectare matrice
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Matrice", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 400, 70, 25, hwnd, (HMENU)ID_BUTON3, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creat butonul", "Eroare", MB_OK | MB_ICONERROR);

					  /////////Buton selectare lista
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Lista", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 450, 70, 25, hwnd, (HMENU)ID_BUTON4, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creat butonul", "Eroare", MB_OK | MB_ICONERROR);

					  /////////Buton selectare mod de parcurgere graf (latime)
					  hEdit = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Latime", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 400, 70, 25, hwnd, (HMENU)ID_BUTON5, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)	MessageBox(hwnd, "Nu a putut fi creat butonul", "Eroare", MB_OK | MB_ICONERROR);

					  break;
	}
	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {
					   case ID_BUTON1://buton aceptare numar muchii
					   {
										  if (nrm == 0)
										  {
											  int len;
											  len = GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT1));
											  if (len == 0) MessageBox(hwnd, "Nu ai introdus nimic!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
											  else if (len > 2) MessageBox(hwnd, "Maxim 2 caractere!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
											  else
											  {
												  int nrmuchii = GetDlgItemInt(hwnd, ID_EDIT1, FALSE, FALSE);
												  if (nrmuchii > 15 || (nrmuchii > 9 && nrmuchii / 10 == 0)) MessageBox(hwnd, "Graful are maxim 15 muchii!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
												  else nrm = nrmuchii;
											  }
										  }
										  else MessageBox(hwnd, "Ai validat deja numarul de muchii!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										  break;
					   }

					   case ID_BUTON2://buton validare muchie
					   {
										  if (i <= nrm)
										  {
											  while (i <= nrm)
											  {
												  int l;
												  l = GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT2));
												  if (l == 0)
												  {
													  MessageBox(hwnd, "Nu ai introdus nimic!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
													  break;
												  }
												  else if (l > 2)
												  {
													  MessageBox(hwnd, "Muchia este formata din 2 noduri!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
													  break;
												  }
												  else
												  {
													  int muchie = GetDlgItemInt(hwnd, ID_EDIT2, FALSE, FALSE);
													  if (muchie % 10 > 6 || muchie % 10 == 0 || muchie / 10 > 6 ||  muchie / 10 ==0 || muchie / 10 == muchie % 10)
													  {
														  MessageBox(hwnd, "Graful are 6 noduri numerotate 1-6!\n Muchiile sunt scrise sub forma ab!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
														  break;
													  }
													  else if (G[muchie % 10][muchie / 10] == 0 && G[muchie / 10][muchie % 10] == 0)
													  {
														  m[i] = muchie;
														  i++;
														  G[muchie % 10][muchie / 10] = 1;
														  G[muchie / 10][muchie % 10] = 1;
														  RedrawWindow(hwnd, 0, 0, RDW_INVALIDATE);
														  break;
													  }
													  else
													  {
														  MessageBox(hwnd, "Muchia introdusa deja exista!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
														  break;
													  }
												  }
											  }
										  }
										  else MessageBox(hwnd, "Ai introdus suficiente muchii!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										  break;
					   }
					   case ID_BUTON3://buton selectare matrice
					   {
										  if (selected == 0)
										  {
											  ml = 0;
											  selected = 1;
										  }
										  else MessageBox(hwnd, "A fost deja selectat modul de reprezentare in memorie al grafului!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										  break;
					   }
					   case ID_BUTON4://buton selectare lista
					   {
										  if (selected == 0)
										  {
											  ml = 1;
											  selected = 1;
										  }
										  else MessageBox(hwnd, "A fost deja selectat modul de reprezentare in memorie al grafului!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										  break;
					   }
					   case ID_BUTON5:
					   {
										 if (nodstart != 0)
										 {
											 explorare_latime(nodstart, G);
											 desenlatime = 1;
											 RedrawWindow(hwnd, 0, 0, RDW_INVALIDATE);
										 }
										 else MessageBox(hwnd, "Nu a fost selectat un nod de pornire!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										 break;
					   }
					   case ID_RADIO1:
					   {
										 if (nodstart == 0) nodstart = 1;
										 else if(nodstart!=0 && nodstart!=1) MessageBox(hwnd, "A fost deja selectat nodul de start!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										 break;
					   }
					   case ID_RADIO2:
					   {
										 if (nodstart == 0) nodstart = 2;
										 else if (nodstart != 0 && nodstart != 2) MessageBox(hwnd, "A fost deja selectat nodul de start!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										 break;
					   }
					   case ID_RADIO3:
					   {
										 if (nodstart == 0) nodstart = 3;
										 else if (nodstart != 0 && nodstart != 3) MessageBox(hwnd, "A fost deja selectat nodul de start!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										 break;
					   }
					   case ID_RADIO4:
					   {
										 if (nodstart == 0) nodstart = 4;
										 else if (nodstart != 0 && nodstart != 4) MessageBox(hwnd, "A fost deja selectat nodul de start!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										 break;
					   }
					   case ID_RADIO5:
					   {
										 if (nodstart == 0) nodstart = 5;
										 else if (nodstart != 0 && nodstart != 5) MessageBox(hwnd, "A fost deja selectat nodul de start!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										 break;
					   }
					   case ID_RADIO6:
					   {
										 if (nodstart == 0) nodstart = 6;
										 else if (nodstart != 0 && nodstart != 6) MessageBox(hwnd, "A fost deja selectat nodul de start!", "Atentionare", MB_OK | MB_ICONEXCLAMATION);
										 break;
					   }
					   }

	break;
	}
	case WM_PAINT:
	{
					 PAINTSTRUCT 	ps;
					 HDC 			hdc;
					 BITMAP 		bitmap;
					 HDC 			hdcMem;
					 HGDIOBJ 		oldBitmap;

					 hdc = BeginPaint(hwnd, &ps);

					 hdcMem = CreateCompatibleDC(hdc);
					 oldBitmap = SelectObject(hdcMem, hBitmap);

					 GetObject(hBitmap, sizeof(bitmap), &bitmap);
					 BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

					 SelectObject(hdcMem, oldBitmap);
					 if(desenlatime==0) for(int j=1;j<=nrm;j++) DrawLines(hdc,m[j]);
					 if(desenlatime==1) for (int j = 1; j < o; j++) DrawLines(hdc, vectparc[j]);
					 DeleteDC(hdcMem);
					 EndPaint(hwnd, &ps);

					 break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	//Step 1: Registering the Window Class 
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL, "p.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	// Step 2: Creating the Window  
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "FEREASTRA", WS_OVERLAPPEDWINDOW^WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 960, 570, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	// Step 3: The Message Loop 
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
