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

    if (hWnd != FALSE);
    DWORD processID = NULL; //process handle
    GetWindowThreadProcessId(hWnd, &processID);
    HANDLE processHandle = NULL;
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL);

    char gameModule1[] = "GeometryDash19.exe";
    DWORD gameBaseAdd1 = GetModuleBaseAddress(_T(gameModule1), processID); // get module base address


    //attempts (only for testing, no real practical use)
    DWORD attAddress = 0x0016A1A0;
    vector<DWORD> attOffsets{ 0x144, 0x214, 0xAC, 0x18C, 0xAC, 0xAC, 0x2E8 };
    DWORD attPtrAddress = GetPointerAddress(hWnd, gameBaseAdd1, attAddress, attOffsets);

    //write memory
    while (true)
    {
        int attempts = 1336;
        WriteProcessMemory(processHandle, (LPVOID*)(attPtrAddress), &attempts, 4, 0); // '4' for 4 bytes
    }

    return 0;
 }