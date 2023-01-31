#include <stdio.h>
#include <vector>
#include <windows.h>
#include <PhysicalMonitorEnumerationAPI.h>
#include <LowLevelMonitorConfigurationAPI.h>

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <sstream>


std::vector<PHYSICAL_MONITOR> physicalMonitors{};


BOOL CALLBACK monitorEnumProcCallback(HMONITOR hMonitor, HDC hDeviceContext, LPRECT rect, LPARAM data) {
    DWORD numberOfPhysicalMonitors;
    BOOL success = GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &numberOfPhysicalMonitors);
    if (success) {
        auto originalSize = physicalMonitors.size();
        physicalMonitors.resize(physicalMonitors.size() + numberOfPhysicalMonitors);
        success = GetPhysicalMonitorsFromHMONITOR(hMonitor, numberOfPhysicalMonitors,
                                                  physicalMonitors.data() + originalSize);
    }
    return true;
}

std::vector<int> toClose;

void kill_screen() {
    EnumDisplayMonitors(NULL, NULL, &monitorEnumProcCallback, 0);
    int i = 0;
    if (toClose.empty()) {
        for (auto &physicalMonitor: physicalMonitors) {
            toClose.push_back(i);
            i++;
        }
    }

    for (auto id: toClose) {
        int displayId = id;
        int vcpCode = 0xD6;
        int newValue = 5;
        bool success = SetVCPFeature(physicalMonitors[displayId].hPhysicalMonitor, vcpCode, newValue);
        if (!success)
            std::cerr << "Failed to set vcp feature" << std::endl;
        success = SetVCPFeature(physicalMonitors[displayId].hPhysicalMonitor, vcpCode, 4);
        if (!success)
            std::cerr << "Failed to set vcp feature" << std::endl;
    }
    DestroyPhysicalMonitors(physicalMonitors.size(), physicalMonitors.data());
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_QUERYENDSESSION:
            kill_screen();
            return TRUE;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void wait_for_shutdown() {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "WindowClass";
    RegisterClass(&wc);
    CreateWindow(wc.lpszClassName, "Window", WS_OVERLAPPEDWINDOW,
                 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                 NULL, NULL, wc.hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


int main(int ac, char **av) {
    for (int i = 1; i < ac; i++) {
        try {
            toClose.push_back(std::stoi(av[i]));
        } catch (std::exception &e) {
            continue;
        }
    }
    wait_for_shutdown();
    return 0;
}
