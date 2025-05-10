#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif


#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Windows.Graphics.h>
#include <Microsoft.UI.Xaml.Window.h>
#include "../../DeltaClicker/DeltaClickerCore.hpp"
#include <Windows.h>
using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Windowing;
using namespace Windows::Graphics;
using namespace Windows::Foundation;



namespace winrt::DeltaClickerGUI::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    MainWindow::MainWindow() // ini
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

        ExtendsContentIntoTitleBar(true);
        SetTitleBar(AppTitleBar());
		
		mainClicker = Clicker();
        mainClicker.loadData();
		mainClicker.start();
		

        if (mainClicker.getType() == 1) {
            mainClicker.setLMB(VK_XBUTTON2);
            mainClicker.setRMB(VK_XBUTTON1);
        }
        else if (mainClicker.getType() == 2) {
            mainClicker.setLMB(VK_XBUTTON1);
            mainClicker.setRMB(VK_XBUTTON2);
        }

        
		com_ptr<IWindowNative> windowNative = this->try_as<IWindowNative>(); // Section of code about scaling and disabling resizing, so the window stays constant. It still does not disable double tap fullscreen.
        HWND hwnd{};
        windowNative->get_WindowHandle(&hwnd);

        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        OutputDebugStringA(("Screen Width" + std::to_string(screenWidth)).c_str());
		OutputDebugStringA(("Screen Height: " + std::to_string(screenHeight)).c_str());


        float scaleX = screenWidth / 1920.0f;
        float scaleY = screenHeight / 1080.0f;

        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~WS_MAXIMIZEBOX; 
        style &= ~WS_THICKFRAME;
        SetWindowLong(hwnd, GWL_STYLE, style);
        SetWindowPos(hwnd, HWND_TOP, 0, 0, static_cast<int>(376 * scaleX), static_cast<int>(520 * scaleY), SWP_NOMOVE);
		
    }
    
}











void winrt::DeltaClickerGUI::implementation::MainWindow::OffsetBox_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
{
    mainClicker.setRandomOffset((int)OffsetBox().Value());
	mainClicker.saveData();
}


void winrt::DeltaClickerGUI::implementation::MainWindow::MouseLayoutComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    
    if (MouseLayoutComboBox().SelectedIndex() == 0) {
        mainClicker.setLMB(VK_XBUTTON2);
		mainClicker.setRMB(VK_XBUTTON1);
	}
    else if (MouseLayoutComboBox().SelectedIndex() == 1) {
        mainClicker.setLMB(VK_XBUTTON1);
        mainClicker.setRMB(VK_XBUTTON2);
    }
    mainClicker.setType((int)MouseLayoutComboBox().SelectedIndex() + 1);
    mainClicker.saveData();
}


void winrt::DeltaClickerGUI::implementation::MainWindow::DelayBox_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
{
	mainClicker.setDelay((int)DelayBox().Value());

    mainClicker.saveData();
}

void winrt::DeltaClickerGUI::implementation::MainWindow::DelayBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	DelayBox().Value(mainClicker.getDelay());
}

void winrt::DeltaClickerGUI::implementation::MainWindow::MouseLayoutComboBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    MouseLayoutComboBox().SelectedIndex(mainClicker.getType() - 1);
}

void winrt::DeltaClickerGUI::implementation::MainWindow::OffsetModeCheckBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    OffsetModeCheckBox().IsChecked(mainClicker.getRandomMode());
}


void winrt::DeltaClickerGUI::implementation::MainWindow::OffsetBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	OffsetBox().Value(mainClicker.getRandomOffset());
}

void winrt::DeltaClickerGUI::implementation::MainWindow::OffsetModeCheckBox_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    mainClicker.setRandomMode(OffsetModeCheckBox().IsChecked().GetBoolean());
    mainClicker.saveData();
}
