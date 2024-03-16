#define SDK_SD_MINIMAL_BUILD
#include <SDK/_Includes.hpp>

int __stdcall DllMain(HMODULE p_Module, DWORD p_Reason, void* p_Reserved)
{
    if (p_Reason == DLL_PROCESS_ATTACH)
    {
        if (!SDK::Utils::IsValidExecutable())
        {
            MessageBoxA(0, "This is not valid executable.\nPlease visit: https://github.com/SDmodding \nAnd check README.md", "Mouse4Fix", MB_OK | MB_ICONERROR);
            return 0;
        }

        void* _Address = UFG_RVA_PTR(0xA3C73C);
        uint8_t _Opcodes[] = { 0x45, 0x31, 0xE4, 0x90, 0x90, 0xE9, 0x24, 0x03, 0x00, 0x00 };

        DWORD _OldProtection;
        if (VirtualProtect(_Address, sizeof(_Opcodes), PAGE_EXECUTE_READWRITE, &_OldProtection))
        {
            __movsb(reinterpret_cast<uint8_t*>(_Address), _Opcodes, sizeof(_Opcodes));
            VirtualProtect(_Address, sizeof(_Opcodes), _OldProtection, &_OldProtection);
        }

        return 0;
    }

    return 1;
}
