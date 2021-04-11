/* OS HW1 created by Euncho 2020.04.22*/

#include <stdio.h>
#include <windows.h>

int main(void) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	// unicode로 인해 일어나는 문제 해결
	CHAR command[] = "C:\\windows\\system32\\mspaint.exe";
	WCHAR wcommand[56] = { L'\0', };
	MultiByteToWideChar(CP_ACP, 0, command, sizeof(command), wcommand, _countof(wcommand));

	/*메모리 할당*/
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	/*자식 프로세스 생성*/
	if (!CreateProcess(NULL,
		wcommand,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi))
	{
		fprintf(stderr, "Create Process failed");
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	printf("Child Complete \n");

	/*핸들 닫기*/
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("Euncho's HW successful! \n");
}