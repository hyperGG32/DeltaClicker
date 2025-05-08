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

    MainWindow::MainWindow()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

        ExtendsContentIntoTitleBar(true);
        SetTitleBar(AppTitleBar());
		
		mainClicker = Clicker();
		mainClicker.start();
        
        com_ptr<IWindowNative> windowNative = this->try_as<IWindowNative>();
        HWND hwnd{};
        windowNative->get_WindowHandle(&hwnd);
        


        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~WS_MAXIMIZEBOX; 
        style &= ~WS_THICKFRAME;
        SetWindowLong(hwnd, GWL_STYLE, style);
        SetWindowPos(hwnd, HWND_TOP, 0, 0, 300, 400, SWP_NOMOVE);
		
    }
    
}








void winrt::DeltaClickerGUI::implementation::MainWindow::OffsetModeCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    mainClicker.setRandomMode(OffsetModeCheckBox().IsChecked().GetBoolean());
}


void winrt::DeltaClickerGUI::implementation::MainWindow::OffsetBox_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
{
    mainClicker.setRandomOffset((int)OffsetBox().Value());
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
}


void winrt::DeltaClickerGUI::implementation::MainWindow::DelayBox_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
{
	mainClicker.setDelay((int)DelayBox().Value());
}


void winrt::DeltaClickerGUI::implementation::MainWindow::Window_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args)
{

    //com_ptr<IWindowNative> windowNative = this->try_as<IWindowNative>();
    //HWND hwnd{};
    //windowNative->get_WindowHandle(&hwnd);
    //RECT rect{};
	//GetWindowRect(hwnd, &rect);
	//int Width = rect.right - rect.left;
	//int Height = rect.bottom - rect.top;
   // if (Width > 300) { Width = 300; }
	//if (Height > 400) { Height = 400; }


   // SetWindowPos(hwnd, HWND_TOP, 0, 0, Width, Height, SWP_NOMOVE);
	
}
