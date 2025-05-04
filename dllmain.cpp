#include "pch.h"

inline bool(__thiscall* CreatorLayer_init)(gd::CreatorLayer*);
bool __fastcall CreatorLayer_initH(gd::CreatorLayer* self) {
    if (!CreatorLayer_init(self)) return false;

    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    auto label = CCLabelBMFont::create("Hi from Pololak", "bigFont.fnt");
    label->setPosition(winSize / 2.f);
    self->addChild(label, 1000);

    return true;
}

DWORD WINAPI my_thread(void* hModule) {
    if (MH_Initialize() != MH_OK) {
        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
    }

    auto cocos = GetModuleHandleA("libcocos2d.dll");
    auto cocos_ext = GetModuleHandleA("libExtensions.dll");

    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x2cea0), CreatorLayer_initH, reinterpret_cast<void**>(&CreatorLayer_init));

    MH_EnableHook(MH_ALL_HOOKS);

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, my_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

