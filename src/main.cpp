#include "includes.hpp"
#include "externMem.hpp"

int main(int argc, char** argv[])
{
    cout << "Continue with program or quit?" << endl << "Y or other: ";
    char cont; cin >> cont;

    switch (cont)
    {
    case 'y':
    case 'Y':
    {
        break;
    }
    default:
    {
        return 0;
    }

    }

    HWND hWnd = FindWindowA(NULL, "Geometry Dash"); // get handle to gd

    if (hWnd == NULL)
    {
        cout << "Geometry Dash is not open!" << endl;
        system("pause");
        return 1;
    }

    DWORD processID = NULL; //process handle
    GetWindowThreadProcessId(hWnd, &processID);
    HANDLE processHandle = NULL;
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL);

    char gameModule1[] = "GeometryDash19.exe"; // change if executable name is different
    DWORD gameBaseAdd1 = GetModuleBaseAddress(_T(gameModule1), processID); // get module base address

    if (gameBaseAdd1 == NULL)
    {
        cout << "Could not obtrain module base address from " << gameModule1 << endl;
        cout << "Make sure the executable name matches!" << endl;
        system("pause");
        return 1;
    }

    cout << "Spoof attempts (A), or change FPS (F)?: ";
    char op; cin >> op;

    switch (op)
    {
    case 'A':
    case 'a':
    {
        //attempts (only for testing, no real practical use)
        DWORD attAddress = 0x0016A1A0;
        vector<DWORD> attOffsets{ 0x144, 0x214, 0xAC, 0x18C, 0xAC, 0xAC, 0x2E8 }; //all pointer offsets
        DWORD attPtrAddress = GetPointerAddress(hWnd, gameBaseAdd1, attAddress, attOffsets);

        //write memory
        while (true)
        {
            int attempts = 100;
            WriteProcessMemory(processHandle, (LPVOID*)(attPtrAddress), &attempts, 4, 0); // '4' for 4 bytes
        }
        break;
    }
    case 'F':
    case 'f':
    {
        cout << "not implemented yet" << endl;
        break;
    }
    default:
    {
        cout << "You did not enter a valid character." << endl;
        break;
    }

    }

    system("pause");
    return 0;
 }
