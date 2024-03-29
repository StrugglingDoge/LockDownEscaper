#include "Inject.h"

/***
*     /$$       /$$$$$$$        /$$$$$$$$                                                            
 *    | $$      | $$__  $$      | $$_____/                                                            
 *    | $$      | $$  \ $$      | $$        /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ 
 *    | $$      | $$  | $$      | $$$$$    /$$_____/ /$$_____/ |____  $$ /$$__  $$ /$$__  $$ /$$__  $$
 *    | $$      | $$  | $$      | $$__/   |  $$$$$$ | $$        /$$$$$$$| $$  \ $$| $$$$$$$$| $$  \__/
 *    | $$      | $$  | $$      | $$       \____  $$| $$       /$$__  $$| $$  | $$| $$_____/| $$      
 *    | $$$$$$$$| $$$$$$$/      | $$$$$$$$ /$$$$$$$/|  $$$$$$$|  $$$$$$$| $$$$$$$/|  $$$$$$$| $$      
 *    |________/|_______/       |________/|_______/  \_______/ \_______/| $$____/  \_______/|__/      
 *                                                                      | $$                          
 *                                                                      | $$                          
 *                                                                      |__/
 *
 *  Created by Carson Kelley - 1/2023 - FOR EDUCATIONAL USE ONLY
 *                                                                     
*/

HKEY hKey;
const char* fakeBios = "ALASKA - 1072007\r\n1.30\r\nAmerican Megatrends - 50011";
const char* fakeBiosVersion = "1.30";
const char* fakeVendor = "American Megatrends Inc.";
const char* fakeProduct = "MS-7A34";
const char* fakeSystemManufacturer = "Micro-Star International Co., Ltd.";

const char* originalBios, *originalBiosName, *originalSystemManufacturer, *originalSystemProductName, *originalBiosVersion;
DWORD originalBiosSize, originalBiosNameSize, originalSystemManufacturerSize, originalSystemProductNameSize, originalBiosVersionSize;

int main(int argc, char* argv[])
{
    //Enable color output.
    DWORD dwMode;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOutput, dwMode);
    
    std::cout << R"(

     /$$       /$$$$$$$        /$$$$$$$$                                                            
    | $$      | $$__  $$      | $$_____/                                                            
    | $$      | $$  \ $$      | $$        /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ 
    | $$      | $$  | $$      | $$$$$    /$$_____/ /$$_____/ |____  $$ /$$__  $$ /$$__  $$ /$$__  $$
    | $$      | $$  | $$      | $$__/   |  $$$$$$ | $$        /$$$$$$$| $$  \ $$| $$$$$$$$| $$  \__/
    | $$      | $$  | $$      | $$       \____  $$| $$       /$$__  $$| $$  | $$| $$_____/| $$      
    | $$$$$$$$| $$$$$$$/      | $$$$$$$$ /$$$$$$$/|  $$$$$$$|  $$$$$$$| $$$$$$$/|  $$$$$$$| $$      
    |________/|_______/       |________/|_______/  \_______/ \_______/| $$____/  \_______/|__/      
                                                                      | $$                          
                                                                      | $$                          
                                                                      |__/                          
    
    )" << std::endl;
    
    std::cout << "LockDown Escaper - v1 - "<< BOLDRED << "FOR EDUCATIONAL USE ONLY" << RESET << std::endl;
    std::cout << "Created by Carson Kelley" << std::endl;

    //Display terms of use.
    std::cout << std::endl << "By using this application, you agree to the following:" << std::endl;
    std::cout << "1. This application is for educational use only." << std::endl;
    std::cout << "2. This application is not to be used for malicious purposes." << std::endl;
    std::cout << "3. This application is not to be used to bypass any academic honesty measures." << std::endl;
    std::cout << "4. I, (Carson Kelley), am not responsible for ANY damage caused by this application." << std::endl<< std::endl;
    std::cout << BOLDRED << "If you do not agree to these terms, please exit this application." << RESET << std::endl<< std::endl;

    //Make user agree to terms to continue.
    char input = ' ';
    bool onVM = false;
    while(input != 'y' && input != 'Y' && input != 'n' && input != 'N')
    {
        std::cout << "Type y to agree and continue, or n to exit: ";
        std::cin >> input;
    
        //If user has agreed to the terms, continue.
        if(input == 'y' || input == 'Y')
        {
            std::cout << std::endl << std::endl;
            std::cout << "One more thing, are you currently running this application in a VM?" << std::endl;
            std::cout << BOLDYELLOW << "Note: Registry changes will be made if you answer yes. They will be reverted once injection has finished." << RESET << std::endl << "(y/n): ";
            std::cin >> input;
            if(input == 'y' || input == 'Y')
                onVM = true;
            
            std::cout << "[LDEInjector]: Starting..." << std::endl;

            // Change bios registry to a fake one if running in a VM.
            if(onVM)
            {
                if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
                    //Set SystemBiosVersion to a fake one.
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", "SystemBiosVersion", RRF_RT_REG_MULTI_SZ, NULL, NULL, &originalBiosSize);
                    originalBios = (char*)malloc(originalBiosSize);
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", "SystemBiosVersion", RRF_RT_REG_MULTI_SZ, NULL, (PVOID)originalBios, &originalBiosSize);
                    RegSetValueExA(hKey, "SystemBiosVersion", 0, REG_MULTI_SZ, (const BYTE*)fakeBios, strlen(fakeBios));
                    originalBiosSize = NULL;
                    // Close the key
                    RegCloseKey(hKey);
                }
                if(RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
                {
                    //Set SystemManufacturer to a fake one.
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVendor", REG_SZ, NULL, NULL, &originalBiosNameSize);
                    originalBiosName = (char*)malloc(originalBiosNameSize);
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVendor", REG_SZ, NULL, (PVOID)originalBiosName, &originalBiosNameSize);
                    RegSetValueExA(hKey, "BIOSVendor", 0, REG_SZ, (const BYTE*)fakeVendor, strlen(fakeVendor));

                    //Set BiosVersion to a fake one.
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion", REG_SZ, NULL, NULL, &originalBiosVersionSize);
                    originalBiosVersion = (char*)malloc(originalBiosVersionSize);
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion", REG_SZ, NULL, (PVOID)originalBiosVersion, &originalBiosVersionSize);
                    RegSetValueExA(hKey, "BIOSVersion", 0, REG_SZ, (const BYTE*)fakeBiosVersion, strlen(fakeBiosVersion));
                    
                    //Set SystemManufacturer to a fake one.
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemManufacturer", REG_SZ, NULL, NULL, &originalSystemManufacturerSize);
                    originalSystemManufacturer = (char*)malloc(originalSystemManufacturerSize);
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemManufacturer", REG_SZ, NULL, (PVOID)originalSystemManufacturer, &originalSystemManufacturerSize);
                    RegSetValueExA(hKey, "SystemManufacturer", 0, REG_SZ, (const BYTE*)fakeSystemManufacturer, strlen(fakeSystemManufacturer));

                    //Set SystemProductName to a fake one.
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemProductName", REG_SZ, NULL, NULL, &originalSystemProductNameSize);
                    originalSystemProductName = (char*)malloc(originalSystemProductNameSize);
                    RegGetValueA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemProductName", REG_SZ, NULL, (PVOID)originalSystemProductName, &originalSystemProductNameSize);
                    RegSetValueExA(hKey, "SystemProductName", 0, REG_SZ, (const BYTE*)fakeProduct, strlen(fakeProduct));

                    // Close the key
                    RegCloseKey(hKey);
                }
            }
            
            const BOOL succeeded = Inject::injectToProcess(EXE_LOC);

            if(succeeded)
            {
                std::cout << GREEN << "[+]" << RESET << "[LDEInjector]: Injection succeeded!" << std::endl;
            }else
            {
                std::cout << RED << "[-]" << RESET << "[LDEInjector]: Injection failed!" << std::endl;
            }
            
        }else if(input == 'n' || input == 'N')
        {
            std::cout << "Exiting..." << std::endl;
            return -2;
        }
    }
    
    // Sleep for 8 seconds to allow user to read output.
    Sleep(8000);

    if(onVM)
    {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
            RegSetValueExA(hKey, "SystemBiosVersion", 0, REG_MULTI_SZ, (const BYTE*)originalBios, strlen(originalBios));
            // Close the key
            RegCloseKey(hKey);
        }
        if(RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
        {
            RegSetValueExA(hKey, "BIOSVendor", 0, REG_SZ, (const BYTE*)originalBiosName, strlen(originalBiosName));
            RegSetValueExA(hKey, "SystemManufacturer", 0, REG_SZ, (const BYTE*)originalSystemManufacturer, strlen(originalSystemManufacturer));
            RegSetValueExA(hKey, "SystemProductName", 0, REG_SZ, (const BYTE*)originalSystemProductName, strlen(originalSystemProductName));
            RegSetValueExA(hKey, "BIOSVersion", 0, REG_SZ, (const BYTE*)originalBiosVersion, strlen(originalBiosVersion));
            // Close the key
            RegCloseKey(hKey);
        }
    }
    
    return 0;
}
