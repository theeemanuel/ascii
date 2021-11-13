#include <windows.h>
#include <stdio.h>
#include <math.h>

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

void set_cursor(bool visible)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

int main()
{
	int k, height = 24, width = 80;
    float K1, K2 = 5, R1 = 1, R2 = 2, A = 0, B = 0, phi, theta, z[1760];
    K1 = width*K2*3/(8*(R1+R2)); 
    char b[1760];
    while (true)
    {
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        for (theta = 0; theta < 2*3.14; theta += 0.07)
        {
            for (phi = 0; phi < 2*3.14; phi += 0.02)
            {
            	float circlex = R2 + R1*cos(theta);
				float circley = R1*sin(theta);
				
                float inverseZ = 1 / (circlex*sin(phi)*sin(A) + circley*cos(A) + K2);
                float t = circlex*sin(phi)*cos(A) - circley*sin(A);
                
				int x = (width/2) + (K1/2 + 10)*inverseZ*(circlex*cos(phi)*cos(B) - t*sin(B));
                int y = (height/2) + (K1/2 - 10)*inverseZ*(circlex*cos(phi)*sin(B) + t*cos(B));
                
				int buffer = x + width*y;
                
				int L = 8 * ((sin(theta)*sin(A) - sin(phi)*cos(theta)*cos(A))*cos(B) - sin(phi)*cos(theta)*sin(A) - sin(theta)*cos(A) - cos(phi)*cos(theta)*sin(B));
                if (x > 0 && x < width && y > 0 && y < height && inverseZ > z[buffer])
                {
                    z[buffer] = inverseZ;
                    b[buffer] = ".,-~:;=!*#$@"[L>0? L:0];
                }
            }
        }
        for (k = 0; k < 1761; k++)
        {
        	SetColor(11);
            putchar(k%width? b[k]:10);
            A += 0.00004;
            B += 0.00002;
        }
        gotoxy(0,0);
        set_cursor(0);
    }
    return 0;
}
