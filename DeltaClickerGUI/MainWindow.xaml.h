#pragma once

#include "MainWindow.g.h"
#include "../../DeltaClicker/DeltaClickerCore.hpp"
namespace winrt::DeltaClickerGUI::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        

        int32_t MyProperty();
        void MyProperty(int32_t value);
        Clicker mainClicker;

 
        
        
        void OffsetBox_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void MouseLayoutComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void DelayBox_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void winrt::DeltaClickerGUI::implementation::MainWindow::DelayBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void winrt::DeltaClickerGUI::implementation::MainWindow::MouseLayoutComboBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void winrt::DeltaClickerGUI::implementation::MainWindow::OffsetModeCheckBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void winrt::DeltaClickerGUI::implementation::MainWindow::OffsetBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OffsetModeCheckBox_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::DeltaClickerGUI::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
        
    };
}
