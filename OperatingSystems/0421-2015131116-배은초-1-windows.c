/* OS HW1 created by Euncho 2020.04.22*/

#include <stdio.h>
#include <windows.h>

int main(void) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	// unicode�� ���� �Ͼ�� ���� �ذ�
	CHAR command[] = "C:\\windows\\system32\\mspaint.exe";
	WCHAR wcommand[56] = { L'\0', };
	MultiByteToWideChar(CP_ACP, 0, command, sizeof(command), wcommand, _countof(wcommand));

	/*�޸� �Ҵ�*/
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	/*�ڽ� ���μ��� ����*/
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

	/*�ڵ� �ݱ�*/
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("Euncho's HW successful! \n");
}