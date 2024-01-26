#include <stdio.h>
#include <io.h>
#include <shlobj.h>


int main() {
    const wchar_t *filenameToCheck = L"hotspot.bat";

    wchar_t autostartPath[MAX_PATH];
    if (SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, autostartPath) != S_OK) {
        fprintf(stderr, "Failed to obtain the path to the startup folder.\n");
        return 1;
    }

    wchar_t filePath[MAX_PATH];
    swprintf(filePath, sizeof(filePath) / sizeof(filePath[0]), L"%s\\%s", autostartPath, filenameToCheck);

    if (_waccess(filePath, F_OK) != -1) {
        if (DeleteFileW(filePath)) {
            printf("File deleted.\n");
        }
        else {
            fprintf(stderr, "Failed to delete the file.\n");
            return 1;
        }
    }
    else {
        FILE *file = _wfopen(filePath, L"w");
        if (file) {
            fwprintf(file, L"@echo off\npowershell.exe -encodedCommand QQBkAGQALQBUAHkAcABlACAALQBBAHMAcwBlAG0AYgBsAHkATgBhAG0AZQAgAFMAeQBzAHQAZQBtAC4AUgB1AG4AdABpAG0AZQAuAFcAaQBuAGQAbwB3AHMAUgB1AG4AdABpAG0AZQANAAoAJABhAHMAVABhAHMAawBHAGUAbgBlAHIAaQBjACAAPQAgACgAWwBTAHkAcwB0AGUAbQAuAFcAaQBuAGQAbwB3AHMAUgB1AG4AdABpAG0AZQBTAHkAcwB0AGUAbQBFAHgAdABlAG4AcwBpAG8AbgBzAF0ALgBHAGUAdABNAGUAdABoAG8AZABzACgAKQAgAHwAIABXAGgAZQByAGUALQBPAGIAagBlAGMAdAAgAHsADQAKACAAIAAgACAAJABfAC4ATgBhAG0AZQAgAC0AZQBxACAAJwBBAHMAVABhAHMAawAnACAALQBhAG4AZAANAAoAIAAgACAAIAAkAF8ALgBHAGUAdABQAGEAcgBhAG0AZQB0AGUAcgBzACgAKQAuAEMAbwB1AG4AdAAgAC0AZQBxACAAMQAgAC0AYQBuAGQADQAKACAAIAAgACAAJABfAC4ARwBlAHQAUABhAHIAYQBtAGUAdABlAHIAcwAoACkAWwAwAF0ALgBQAGEAcgBhAG0AZQB0AGUAcgBUAHkAcABlAC4ATgBhAG0AZQAgAC0AZQBxACAAJwBJAEEAcwB5AG4AYwBPAHAAZQByAGEAdABpAG8AbgBgADEAJwANAAoAfQApAFsAMABdAA0ACgBGAHUAbgBjAHQAaQBvAG4AIABBAHcAYQBpAHQAKAAkAFcAaQBuAFIAdABUAGEAcwBrACwAIAAkAFIAZQBzAHUAbAB0AFQAeQBwAGUAKQAgAHsADQAKACAAIAAgACAAJABhAHMAVABhAHMAawAgAD0AIAAkAGEAcwBUAGEAcwBrAEcAZQBuAGUAcgBpAGMALgBNAGEAawBlAEcAZQBuAGUAcgBpAGMATQBlAHQAaABvAGQAKAAkAFIAZQBzAHUAbAB0AFQAeQBwAGUAKQANAAoAIAAgACAAIAAkAG4AZQB0AFQAYQBzAGsAIAA9ACAAJABhAHMAVABhAHMAawAuAEkAbgB2AG8AawBlACgAJABuAHUAbABsACwAIABAACgAJABXAGkAbgBSAHQAVABhAHMAawApACkADQAKACAAIAAgACAAJABuAGUAdABUAGEAcwBrAC4AVwBhAGkAdAAoAC0AMQApACAAfAAgAE8AdQB0AC0ATgB1AGwAbAANAAoAIAAgACAAIAAkAG4AZQB0AFQAYQBzAGsALgBSAGUAcwB1AGwAdAANAAoAfQANAAoADQAKACQAYwBvAG4AbgBlAGMAdABpAG8AbgBQAHIAbwBmAGkAbABlACAAPQAgAFsAVwBpAG4AZABvAHcAcwAuAE4AZQB0AHcAbwByAGsAaQBuAGcALgBDAG8AbgBuAGUAYwB0AGkAdgBpAHQAeQAuAE4AZQB0AHcAbwByAGsASQBuAGYAbwByAG0AYQB0AGkAbwBuACwAIABXAGkAbgBkAG8AdwBzAC4ATgBlAHQAdwBvAHIAawBpAG4AZwAuAEMAbwBuAG4AZQBjAHQAaQB2AGkAdAB5ACwAIABDAG8AbgB0AGUAbgB0AFQAeQBwAGUAIAA9ACAAVwBpAG4AZABvAHcAcwBSAHUAbgB0AGkAbQBlAF0AOgA6AEcAZQB0AEkAbgB0AGUAcgBuAGUAdABDAG8AbgBuAGUAYwB0AGkAbwBuAFAAcgBvAGYAaQBsAGUAKAApAA0ACgAkAHQAZQB0AGgAZQByAGkAbgBnAE0AYQBuAGEAZwBlAHIAIAA9ACAAWwBXAGkAbgBkAG8AdwBzAC4ATgBlAHQAdwBvAHIAawBpAG4AZwAuAE4AZQB0AHcAbwByAGsATwBwAGUAcgBhAHQAbwByAHMALgBOAGUAdAB3AG8AcgBrAE8AcABlAHIAYQB0AG8AcgBUAGUAdABoAGUAcgBpAG4AZwBNAGEAbgBhAGcAZQByACwAIABXAGkAbgBkAG8AdwBzAC4ATgBlAHQAdwBvAHIAawBpAG4AZwAuAE4AZQB0AHcAbwByAGsATwBwAGUAcgBhAHQAbwByAHMALAAgAEMAbwBuAHQAZQBuAHQAVAB5AHAAZQAgAD0AIABXAGkAbgBkAG8AdwBzAFIAdQBuAHQAaQBtAGUAXQA6ADoAQwByAGUAYQB0AGUARgByAG8AbQBDAG8AbgBuAGUAYwB0AGkAbwBuAFAAcgBvAGYAaQBsAGUAKAAkAGMAbwBuAG4AZQBjAHQAaQBvAG4AUAByAG8AZgBpAGwAZQApAA0ACgANAAoAaQBmACAAKAAkAHQAZQB0AGgAZQByAGkAbgBnAE0AYQBuAGEAZwBlAHIALgBUAGUAdABoAGUAcgBpAG4AZwBPAHAAZQByAGEAdABpAG8AbgBhAGwAUwB0AGEAdABlACAALQBlAHEAIAAxACkAIAB7AA0ACgAgACAAIAAgAEEAdwBhAGkAdAAgACgAJAB0AGUAdABoAGUAcgBpAG4AZwBNAGEAbgBhAGcAZQByAC4AUwB0AG8AcABUAGUAdABoAGUAcgBpAG4AZwBBAHMAeQBuAGMAKAApACkAIAAoAFsAVwBpAG4AZABvAHcAcwAuAE4AZQB0AHcAbwByAGsAaQBuAGcALgBOAGUAdAB3AG8AcgBrAE8AcABlAHIAYQB0AG8AcgBzAC4ATgBlAHQAdwBvAHIAawBPAHAAZQByAGEAdABvAHIAVABlAHQAaABlAHIAaQBuAGcATwBwAGUAcgBhAHQAaQBvAG4AUgBlAHMAdQBsAHQAXQApAA0ACgB9AA0ACgBlAGwAcwBlACAAewANAAoAIAAgACAAIABBAHcAYQBpAHQAIAAoACQAdABlAHQAaABlAHIAaQBuAGcATQBhAG4AYQBnAGUAcgAuAFMAdABhAHIAdABUAGUAdABoAGUAcgBpAG4AZwBBAHMAeQBuAGMAKAApACkAIAAoAFsAVwBpAG4AZABvAHcAcwAuAE4AZQB0AHcAbwByAGsAaQBuAGcALgBOAGUAdAB3AG8AcgBrAE8AcABlAHIAYQB0AG8AcgBzAC4ATgBlAHQAdwBvAHIAawBPAHAAZQByAGEAdABvAHIAVABlAHQAaABlAHIAaQBuAGcATwBwAGUAcgBhAHQAaQBvAG4AUgBlAHMAdQBsAHQAXQApAA0ACgB9AA0ACgA=");
            fclose(file);
            printf("File created.\n");
        }
        else {
            fprintf(stderr, "Failed to create the file.\n");
            return 1;
        }
    }

    return 0;
}
